// LCF_C_Demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#pragma warning(disable:4996)	//忽略4996的不安全警告

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <Windows.h>

#include "LCF_ParameterDefine.h"
#include "LCF_UserInterface.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/imgcodecs.hpp"

//获取扫描数据三种方式: 
//1、扫描结束后通过LCF_ExportCacheData接口将扫描数据一次性从控制器导出来，不需要用到回调函数，需要先调用PARAM_CACHE_CONTOUR_COUNT获取缓存的轮廓数量

//2、扫描过程中通过回调函数收集扫描数据。对应回调里   if (arg->rid == LCF_RID_RESULT)
//注意: a) 回调函数里面不应该做耗时的操作，应该只做数据拷贝。
//      b) 在扫描帧率比较高的情况下通过设置PARAM_COUNTOUR_LINE_THRESHOLD参数，调高轮廓回调阈值，减少回调的频率，保证数据能及时缓存不会丢失数据。
//      c) 该参数仅用于降低回调的频率，不用于一次性导出缓存数据。

//3、通过PARAM_CACHE_COUNTOUR_THRESHOLD设置Cache缓存轮廓的阈值，达到阈值后通过回调函数通知用户。对应回调里  else if (arg->rid == LCF_RID_CACHE_REACH_THRE)
//注意: a) 收到通知后，用户通过LCF_ExportCacheData导出缓存数据，通过LCF_ClearCacheData清空缓存数据后重新开始计数。
//      b）该参数一般用在用户已知总共扫描轮廓个数的场景，达到设定轮廓数后通知用户。


//三种导出数据的方式，同一次运行程序时只能开一个
#define GET_MEASURE_RESULT_CALLBCAK				0		// 实时回调导出数据
#define GET_MEASURE_RESULT_CALLBCAK_CACHE		1		// 设置阈值回调导出数据
#define GET_MEASURE_RESULT_EXPORT_ONCE			0		// 扫描完成一次性导出数据


int							handler = -1;				// 设备句柄
LCF_StatusTypeDef			ret = LCF_Status_Succeed;	// 错误码
std::vector<LCF_Result_t>	g_result;					// 获取的测量数据

float g_x_interval = 0;									// x轴的点间距，由传感器出厂标定实际值决定，单位um
float g_y_interval = 0;									// y轴的点间距，用户自己计算所得，编码器触发：g_y_interval = encoder_plus_interval*encoder_div，单位um
int encoder_div = 1;									// 软件设置的分频系数
float encoder_plus_interval = 0.2;						// 编码器的脉冲间隔，单位um

// 参数设置
LCF_TriggerMode_t trigger_mode = LCF_EncoderTrigger;	// 设置控制器的触发方式,实际使用中只能是编码器触发

LCF_DataCacheType_t g_cache_type = LCF_Cache_Controler;		// 选择cache缓存的位置，控制器端还是PC端 LCF_Cache_SDK / LCF_Cache_Controler
int g_sdk_cache_size = 100000;							// 设置PC端缓存的最大轮廓数，若PC端内存小于设置值，返回错误码
	
int cache_threshold = 1000;								// //缓存数据数量到达设置阈值，回调函数事件通知，最大可以设置为十万,用于阈值回调导出数据

// 回调函数实时获取数据
int callBack_count = 0;									// 获取实时数据时，回调函数计数，将累计的数据拼接
#define CALLBCAK_JOINT_MAX	10							// 拼接的最大次数的回调数据，用户自行修改

// 解析出来的灰度数据、高度数据
int realCacheCount = 0;									// 实际缓存的轮廓数量
unsigned int g_resolution_x = 0;						// 导出数据的宽度
unsigned int g_resolution_y = 0;						// 导出数据的长度


int g_grayscale_max = 0;								// 灰度数据最大值
int g_grayscale_min = 0;								// 灰度数据最小值
std::vector<uint16_t> g_grayscale_data;					// 存放解析出来的灰度数据

int g_hight_max[MAX_DETECT_LAYER_NUMBER] = { 0 };		// 每层高度数据的最大值  该数据/10.0=实际高度数据
int g_hight_min[MAX_DETECT_LAYER_NUMBER] = { 0 };		// 每层高度数据的最小值  该数据/10.0=实际高度数据
std::vector<int> g_hight_data;							// 存放解析出来的高度数据，该数据是原始数据放大了10倍，g_hight_data/10.0=实际高度（um）

std::string g_save_path_str = "C:\\Users\\huang\\Desktop\\LCF_C_Demo\\LCF_C_Demo\\LCF_C_Demo\\picture\\";	//指定图片保存的路径，用户根据实际使用情况修改


// 回调函数
void UserEventCallbackHandle(int handle, LCF_EventCallbackArgs_t* arg, void*userPara)
{
	//接收到数据
	if (arg->eventType == LCF_EventType_DataRecv)
	{
		if (arg->rid == LCF_RID_RESULT)	//实时数据接收事件
		{
			// 实时回调数据会一直返回，如果不用可以直接注释，也可以设置PARAM_STREAM_OUT参数关闭实时返回
#if GET_MEASURE_RESULT_CALLBCAK
			LCF_Result_t result;
			memcpy(&result, arg->data, sizeof(LCF_Result_t));
			g_result.push_back(result);
#endif
		}
		else if (arg->rid == LCF_RID_CACHE_REACH_THRE)	//缓存轮廓数量到达设定阈值 触发事件
		{
#if GET_MEASURE_RESULT_CALLBCAK_CACHE
			// 从控制器中导出缓存数据
			LCF_Result_t result;
			ret = LCF_ExportCacheData(handler, &result);
			if (ret == LCF_Status_Succeed)
			{
				g_result.push_back(result);		// 保存数据
				LCF_ClearCacheData(handler);	// 清空缓存
			}
#endif
		}
		else if (arg->rid == LCF_RID_API_CALL_EXCEPTION) //API调用异常事件
		{
			printf("Error: %s\n", (char*)(arg->data));
		}
	}
	else if (arg->eventType == LCF_EventType_Disconnect)
	{
		printf("Device disconnected");
	}
}

int main()
{
	// 防止控制台输出乱码
	SetConsoleOutputCP(CP_UTF8);

	//扫描出来的设备
	LCF_DeviceEthPara_t* deviceList;
	uint32_t deviceNumber = 0;

	// 默认的设备参数
	char ip_addr[] = "192.168.1.188";
	uint16_t controllerPort = 58080;

	//注册回调函数
	ret = LCF_RegisterEventCallback(UserEventCallbackHandle, NULL);
	if (ret != LCF_Status_Succeed)
	{
		printf("Error! Retcode: %d \n", ret);
		getchar();
		return 0;
	}
	else
	{
		printf("Register the callback function success!\n");
	}

	//扫描传感器，返回传感器IP和端口号
	ret = LCF_ScanDeviceList(&deviceList, &deviceNumber);
	if (ret != LCF_Status_Succeed)
	{
		printf("Error! Retcode: %d \n", ret);
		getchar();
		return 0;
	}
	else
	{
		if (deviceNumber)
		{
			printf("Number of devices detected: %d\n", deviceNumber);
			printf("IP address: %s\n", deviceList[0].ip_addr);
			printf("Port: %d\n", deviceList[0].port);

		}

	}

	//如果检测到设备，尝试连接
	if (deviceNumber)
	{
		//电脑ip必须和设备ip在同一个网段里，否则连接失败
		for (short i = 0; i <= deviceNumber; i++)
		{
			ret = LCF_ConnectDevice(deviceList[i].ip_addr, deviceList[i].port, &handler);
			if (ret != LCF_Status_Succeed)
			{
				printf("%s connect failed，error code: %d \n", deviceList[i].ip_addr, ret);

				if (i == deviceNumber)
				{
					printf("All device can not connect, please press any key to end the program!");
					getchar();
					return 0;
				}
			}
			else
			{
				printf("Connect success!\n");
				break;
			}
		}
	}
	else
	{
		//未检测到使用ip，端口，使用默认配置连接
		ret = LCF_ConnectDevice(ip_addr, controllerPort, &handler);
		if (ret != LCF_Status_Succeed)
		{
			printf("Error! Retcode: %d \n", ret);
			printf("Please press any key to end the program!");
			getchar();
			return 0;
		}
		else
		{
			printf("Connect success!\n");
		}
	}



	//心跳包超时时间,单位（秒）,需要调试时设大有点，防止调试时设备断开连接
	int heart_beat = 60000;
	LCF_SetIntParameter(handler, PARAM_HEART_BEAT_TIMEOUT, heart_beat);
	if (ret != LCF_Status_Succeed)
	{
		printf("Heart beat set failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}

	//获取SDK版本号
	char sdkVersion[30] = { 0 };
	ret = LCF_GetStringParameter(handler, PARAM_SDK_VERSION, sdkVersion);
	if (ret != LCF_Status_Succeed)
	{
		printf("SDK version get failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("SDK Version: %s\n", sdkVersion);
	}

	//获取控制器版本号
	char controlerVersion[30] = { 0 };
	ret = LCF_GetStringParameter(handler, PARAM_CONTROLER_FW_VERSION, controlerVersion);
	if (ret != LCF_Status_Succeed)
	{
		printf("Controler firmware version get failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Controller Version: %s \n", controlerVersion);
	}

	//获取传感器版本号
	char sensorVersion[30] = { 0 };
	ret = LCF_GetStringParameter(handler, PARAM_SENSOR_FW_VERSION, sensorVersion);
	if (ret != LCF_Status_Succeed)
	{
		printf("Sensor version get failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Sensor Version: %s\n", sensorVersion);
	}

	////设置曝光时间us
	//int exposure_time = 500;
	//ret = LCF_SetIntParameter(handler, PARAM_EXPOSURE_TIME, exposure_time);
	//if (ret != LCF_Status_Succeed)
	//{
	//	printf("Exposure time set failed, error code: %d \n", ret);
	//  printf("Please press any key to end the program!");
	//	getchar();
	//	return 0;
	//}

	// 设置传感器触发方式，实际生产扫轮廓时只能是编码器触发
	ret = LCF_SetIntParameter(handler, PARAM_TRIGGER_MODE, trigger_mode);
	if (ret != LCF_Status_Succeed)
	{
		printf("Trigger mode set failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("EncoderTrigger is set successful. \n");
	}

	// 获取x点间隔
	ret = LCF_GetFloatParameter(handler, PARAM_X_INTERVAL, &g_x_interval);
	if (ret != LCF_Status_Succeed)
	{
		printf("X interval get failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("X interval get successful, X interval is: %f um.\n", g_x_interval);
	}

	// 获取分频系数,计算轮廓间隔
	ret = LCF_GetIntParameter(handler, PARAM_ENCODER_DIV, &encoder_div);
	if (ret != LCF_Status_Succeed)
	{
		printf("Encoder division get failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		g_y_interval = encoder_div * encoder_plus_interval;	//根据编码器的脉冲间隔和分频系数计算每条轮廓间的距离，单位us，测试时使用的机台的0.2um的脉冲间隔，客户根据自己的参数修改
		printf("Encoder division get successful, Encoder division is: %d. \n", encoder_div);
		printf("Y interval get successful, Y interval is: %f um.\n", g_y_interval);
	}

	// 选择cache缓存的位置，控制器端还是PC端。控制器端是固定的10万条轮廓；PC端可以自己设置，最大10万条轮廓。
	ret = LCF_SetIntParameter(handler, PARAM_CACHE_SELECT, g_cache_type);
	if (ret != LCF_Status_Succeed)
	{
		printf("Cache location set failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Cache location set sucessful, location is: LCF_Cache_SDK \n");

		// 缓存在PC端
		if (g_cache_type == LCF_Cache_SDK)
		{
			// 设置SDK cache可以缓存轮廓的数量，最大为10万
			ret = LCF_SetIntParameter(handler, PARAM_SDK_CACHE_SIZE, g_sdk_cache_size);
			if (ret != LCF_Status_Succeed)
			{
				printf("SDK cache size set failed, error code: %d \n", ret);
				printf("Please press any key to end the program!");
				getchar();
				return 0;
			}
			else
			{
				printf("SDK cache size set sucessful, size is: %d \n", g_sdk_cache_size);
			}

			// 确保数据从SDK cache中导出时，全部数据都被导出
			ret = LCF_SetIntParameter(handler, PARAM_EXP_WAIT_FIFO_EMPTY, 1);
			if (ret != LCF_Status_Succeed)
			{
				printf("PARAM_EXP_WAIT_FIFO_EMPTY set failed, error code: %d \n", ret);
				printf("Please press any key to end the program!");
				getchar();
				return 0;
			}
			else
			{
				printf("PARAM_EXP_WAIT_FIFO_EMPTY set sucessful! \n");
			}
		}
	}	

#if GET_MEASURE_RESULT_CALLBCAK
	// 设置一次回调的轮廓阈值,最大可以设置采集64条轮廓后回调函数返回一次数据
	int line_threshold = 64;
	ret = LCF_SetIntParameter(handler, PARAM_COUNTOUR_LINE_THRESHOLD, line_threshold);
	if (ret != LCF_Status_Succeed)
	{
		printf("Line threshold set failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Line threshold set sucessful, threshold is: %d \n", line_threshold);
	}
#endif

#if GET_MEASURE_RESULT_CALLBCAK_CACHE
	// 设置cache缓存阈值,控制器内部采集的轮廓数量达到设定的阈值时，通过回调函数通知用户，用户调用LCF_ExportCacheData接口从控制器导出数据
	ret = LCF_SetIntParameter(handler, PARAM_CACHE_COUNTOUR_THRESHOLD, cache_threshold);
	if (ret != LCF_Status_Succeed)
	{
		printf("Cache threshold set failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Cache threshold set sucessful, threshold is: %d \n", cache_threshold);
	}
#endif

	// 清空缓存数据
	ret = LCF_ClearCacheData(handler);
	if (ret != LCF_Status_Succeed)
	{
		printf("Cache data clear failed，error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Cache data have clear! \n");
	}

	//开始采集数据
	ret = LCF_StartCapture(handler);
	if (ret != LCF_Status_Succeed)
	{
		printf("Start capture failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Start capture! \n");
	}

	// 等待轮廓扫描完成一次性导出数据,这种方式和回调函数无关
#if GET_MEASURE_RESULT_EXPORT_ONCE
	// 采集完轮廓后，按任意键，开始处理数据
	printf("Wait for the outline to be scanned!\n");
	printf("After scanning, press any key to start processing the data!\n");
	getchar();
	printf("Start processing data! \n");

	// 获取实际缓存的轮廓数量
	ret = LCF_GetIntParameter(handler, PARAM_CACHE_CONTOUR_COUNT, &realCacheCount);
	if (ret != LCF_Status_Succeed)
	{
		printf("The number of contours actually cached get failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("The number of contours actually cached is: %d \n", realCacheCount);
	}

	// 从控制器中导出缓存数据
	LCF_Result_t result;
	ret = LCF_ExportCacheData(handler, &result);
	if (ret != LCF_Status_Succeed)
	{
		printf("Cache data export failed, error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		g_result.push_back(result);
		printf("Cache data export successful! \n");
	}

	// 清空缓存数据
	ret = LCF_ClearCacheData(handler);
	if (ret != LCF_Status_Succeed)
	{
		printf("Cache data clear failed，error code: %d \n", ret);
		printf("Please press any key to end the program!");
		getchar();
		return 0;
	}
	else
	{
		printf("Cache data have clear! \n");
	}
#endif

	// 采集已经打开，等待编码器触发
	printf("Please start moving the encoder!\n");

	while (1)
	{
#if GET_MEASURE_RESULT_CALLBCAK
		// 用回调返回实时数据时，由于数据量少，拼成图片看不出什么，可以将数据拼接一下
		if (g_result.size() >= CALLBCAK_JOINT_MAX)
		{
			//将数据拷贝出来
			std::vector<LCF_Result_t>	result_temp;
			size_t size = g_result.size();
			result_temp.assign(g_result.begin(), g_result.begin() + size);
			g_result.erase(g_result.begin(), g_result.begin() + size );

			// 获取数据的长宽
			g_resolution_x = 0;
			g_resolution_y = 0;
			g_resolution_x = result_temp.at(0).x_count;

			int* grayscale_index = new int[result_temp.size()];
			int* hight_index = new int[result_temp.size()];
			int grayscale_count = 0;
			int hight_count = 0;

			for (int i = 0; i < result_temp.size(); i++)
			{
				g_resolution_y += result_temp.at(i).y_count;

				// 更新索引
				grayscale_index[i] = result_temp.at(i).x_count * result_temp.at(i).y_count;
				hight_index[i] = result_temp.at(i).layer_number * result_temp.at(i).x_count * result_temp.at(i).y_count;

				grayscale_count += grayscale_index[i];
				hight_count += hight_index[i];

				// 解析灰度数据
				g_grayscale_data.resize(grayscale_count);
				memcpy(g_grayscale_data.data() + (grayscale_count - grayscale_index[i]), result_temp.at(i).intensity, grayscale_index[i] * sizeof(uint16_t));

				// 解析高度数据,单位10um
				g_hight_data.resize(hight_count);
				memcpy(g_hight_data.data() + (hight_count - hight_index[i]), result_temp.at(i).height, grayscale_index[i] * sizeof(int));
			}

			// 清除已经解析的数据
			delete[] grayscale_index;
			delete[] hight_index;
		}
#else
		// 解析导出来的数据
		if (g_result.size())
		{
			// 记录x轴点间距
			g_x_interval = g_result.at(0).x_interval;

			// 记录数据的最大最小值
			g_grayscale_max = g_result.at(0).statisticInfo.maxIntensityValue;
			g_grayscale_min = g_result.at(0).statisticInfo.minIntensityValue;
			memcpy(g_hight_max, g_result.at(0).statisticInfo.maxHeightValue, sizeof(int) * MAX_DETECT_LAYER_NUMBER);
			memcpy(g_hight_min, g_result.at(0).statisticInfo.minHeightValue, sizeof(int) * MAX_DETECT_LAYER_NUMBER);

			// 获取数据的长宽
			g_resolution_x = 0;
			g_resolution_y = 0;
			g_resolution_x = g_result.at(0).x_count;
			g_resolution_y = g_result.at(0).y_count;

			// 解析灰度数据
			int grayscale_count = g_result.at(0).x_count * g_result.at(0).y_count;
			g_grayscale_data.resize(grayscale_count);
			memcpy(g_grayscale_data.data(), g_result.at(0).intensity, grayscale_count * sizeof(uint16_t));

			// 解析高度数据,单位10um
			int hight_count = g_result.at(0).layer_number * g_result.at(0).x_count * g_result.at(0).y_count;
			g_hight_data.resize(hight_count);
			memcpy(g_hight_data.data(), g_result.at(0).height, hight_count * sizeof(int));

			// 清除已经解析的数据
			std::vector<LCF_Result_t>::iterator front = g_result.begin();
			g_result.erase(front);
		}
#endif
		
		// 导出灰度图
		if (g_grayscale_data.size())
		{
			//将数据从uint16_t转换成uint8_t
			uint8_t *grayscale_temp = new uint8_t[g_grayscale_data.size()];
			for (int i = 0; i < g_grayscale_data.size(); i++)
			{
				grayscale_temp[i] = (uint8_t)g_grayscale_data.at(i);
			}

			// 获取时间戳
			time_t timep;
			struct tm *p;
			time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
			p = localtime(&timep);//用localtime将秒数转化为struct tm结构体
			std::string time_str = std::to_string(1 + p->tm_mon) + std::to_string(p->tm_mday) + std::to_string(p->tm_hour) + std::to_string(p->tm_min) + std::to_string(p->tm_sec);
			// 设置图片保存路径
			std::string image_type_raw_str = "_image_gray_raw.bmp";
			std::string full_path_gray_raw_str = g_save_path_str + time_str + image_type_raw_str;	//原始图片保存路径
			std::string image_type_scale_str = "_image_gray_scale.bmp";
			std::string full_path_gray_scale_str = g_save_path_str + time_str + image_type_scale_str;	//缩放图片保存路径
			std::string image_type_color_str = "_image_color.bmp";
			std::string full_path_color_str = g_save_path_str + time_str + image_type_color_str;	//伪彩图保存路径

			// 保存原始灰度图片
			cv::Mat image_sre = cv::Mat(g_resolution_y, g_resolution_x, CV_8UC1, grayscale_temp);
			cv::imwrite(full_path_gray_raw_str, image_sre);
			printf("The original grayscale image has been saved!\n");

			// 图像缩放：用户用编码器触发扫描轮廓，获取的轮廓数据不是完整的实物轮廓数据，采集的数据存在X方向的间隔和Y方向的间隔
			// X方向是传感器投影出来的光线，这条光线一共有2048个点，点与点的间隔称为X方向的间隔，由控制器的一些参数决定，该间隔可以通过返回的数据获得x_interval；
			// Y方向是编码器运动的方向，控制器获取到编码器的信号后开始采集数据，一个信号采集一条轮廓，轮廓之间是有间隔的， 轮廓与轮廓之间的间隔（y_interval） = 编码器脉冲间隔 * 分频系数；
			// 控制器扫描的轮廓数据在内存上是连续排列的，X、Y方向的间隔为1，如果要导成图片，就需要原始数据进行比例缩放，该缩放比例就是ratio = y_interval/x_interval,
			// 例如，设：X = 2048, Y = 1000, x_interval = 3um，y_interval = 10um，缩放后为X = 2048*1 = 2048, Y = 1000*(10/3)= 3333

			// 缩放灰度图
			cv::Size dsize = cv::Size(image_sre.cols * 1, image_sre.rows * (g_y_interval / g_x_interval));	//x方向缩放为1，y轴缩放为 (g_y_interval / g_x_interval)
			cv::Mat img_dst = cv::Mat(dsize, image_sre.type());	//创建一个容器
			cv::resize(image_sre, img_dst, dsize, 0, 0, cv::INTER_NEAREST);

			//保存缩放的图片
			cv::imwrite(full_path_gray_scale_str, img_dst);
			printf("The scaled grayscale image has been saved!\n");

			//保存伪彩图
			cv::Mat img_color;
			cv::applyColorMap(img_dst, img_color, cv::COLORMAP_JET);	//深度图渲染类型（红高蓝低） 伪彩图 颜色类型
			cv::imwrite(full_path_color_str, img_color);			    //保存缩放的图片
			printf("The depth map has been saved!\n");

			// 清理内存
			g_grayscale_data.clear();
			g_hight_data.clear();
			delete[] grayscale_temp;
		}
	}

	// 停止数据采集
	LCF_StopCapture(handler);

	//断开设备连接
	LCF_CloseDevice(handler);

	return 0;
}

