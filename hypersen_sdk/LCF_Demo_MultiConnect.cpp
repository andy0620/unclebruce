/**
  *  LCF系列设备的SDK支持同时连接两台控制器
  *      1、demo主要说明如何一次连接两个控制器
  *      2、数据导出的方式用设置Cache缓存轮廓阈值的方式
  **/

#include <stdio.h>
#include <string>
#include <vector>

#include "LCF_UserInterface.h"
#include "LCF_ParameterDefine.h"

LCF_StatusTypeDef ret = LCF_Status_Succeed;	// 错误码

// 设备句柄，用来区分不同的设备
int g_handle_1 = -1;
int g_handle_2 = -1;

// 设备连接状态
bool g_isConnect_1 = false;
bool g_isConnect_2 = false;

// cache轮廓缓存阈值，缓存轮廓数量到达设置值后通过回调事件通知 arg->rid == LCF_RID_CACHE_REACH_THRE
#define CACHE_REACH_THRE	1000

// 测量数据
std::vector<LCF_Result_t>	g_result_1;
std::vector<LCF_Result_t>	g_result_2;

unsigned int g_resolution_x_1 = 0;						// 导出数据的宽度
unsigned int g_resolution_y_1 = 0;						// 导出数据的长度
std::vector<uint16_t> g_grayscale_data_1;				// 存放解析出来的灰度数据
std::vector<int> g_hight_data_1;						// 存放解析出来的高度数据，该数据是原始数据放大了10倍，g_hight_data/10.0=实际高度（um）

unsigned int g_resolution_x_2 = 0;
unsigned int g_resolution_y_2 = 0;
std::vector<uint16_t> g_grayscale_data_2;
std::vector<int> g_hight_data_2;




// 回调函数
void UserEventCallbackHandle(int handle, LCF_EventCallbackArgs_t* arg, void*userPara)
{
	// 设备1
	if (handle == g_handle_1)
	{
		if (arg->eventType == LCF_EventType_DataRecv)	// 数据接收事件
		{
			if (arg->rid == LCF_RID_CACHE_REACH_THRE)	//缓存轮廓数量到达设定阈值 触发事件
			{
				// 从控制器中导出缓存数据
				LCF_Result_t result;
				ret = LCF_ExportCacheData(g_handle_1, &result);
				if (ret == LCF_Status_Succeed)
				{
					g_result_1.push_back(result);		// 保存数据
					LCF_ClearCacheData(g_handle_1);	// 清空缓存
				}
			}
			else if (arg->rid == LCF_RID_API_CALL_EXCEPTION)	// API 调用异常事件
			{
				//printf("Error: %s\n", (char*)(arg->data));
			}
		}
		else if (arg->eventType == LCF_EventType_Disconnect)	// 设备断开连接事件
		{
			printf("Device disconnected");
		}
	}
	// 设备2
	else if(handle == g_handle_2)
	{
		if (arg->eventType == LCF_EventType_DataRecv)
		{
			if (arg->rid == LCF_RID_CACHE_REACH_THRE)	//缓存轮廓数量到达设定阈值 触发事件
			{
				// 从控制器中导出缓存数据
				LCF_Result_t result;
				ret = LCF_ExportCacheData(g_handle_2, &result);
				if (ret == LCF_Status_Succeed)
				{
					g_result_2.push_back(result);		// 保存数据
					LCF_ClearCacheData(g_handle_2);	// 清空缓存
				}
			}
			else if (arg->rid == LCF_RID_API_CALL_EXCEPTION)	// API 调用异常事件
			{
				//printf("Error: %s\n", (char*)(arg->data));
			}
		}
		else if (arg->eventType == LCF_EventType_Disconnect)
		{
			printf("Device disconnected");
		}
	}
}

int main()
{
	// 防止控制台输出乱码
	SetConsoleOutputCP(CP_UTF8);

	//扫描出来的设备
	LCF_DeviceEthPara_t* deviceList;
	uint32_t deviceNumber = 0;

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
		printf("Number of devices detected: %d\n", deviceNumber);

		// 打印扫描出来的设备
		for (int i = 0; i < deviceNumber; i++)
		{
			printf("IP address: %s\n", deviceList[i].ip_addr);
			printf("Port: %d\n", deviceList[i].port);
		}
	}

	//如果检测到2台设备，尝试连接
	if (deviceNumber >= 2)
	{
		//电脑ip必须和设备ip在同一个网段里，否则连接失败

		//连接设备1
		LCF_StatusTypeDef ret1 = LCF_ConnectDevice(deviceList[0].ip_addr, deviceList[0].port, &g_handle_1);
		if (ret1 != LCF_Status_Succeed)
		{
			printf("%s connect failed，error code: %d \n", deviceList[0].ip_addr, ret1);
		}
		else
		{
			g_isConnect_1 = true;
			printf("%s connect success!\n", deviceList[0].ip_addr);
		}

		//连接设备2
		LCF_StatusTypeDef ret2 = LCF_ConnectDevice(deviceList[1].ip_addr, deviceList[1].port, &g_handle_2);
		if (ret2 != LCF_Status_Succeed)
		{
			printf("%s connect failed，error code: %d \n", deviceList[1].ip_addr, ret2);
		}
		else
		{
			g_isConnect_2 = true;
			printf("%s connect success!\n", deviceList[1].ip_addr);
		}

		// 没有连上任何设备，程序结束
		if (!g_isConnect_1 && !g_isConnect_2)
		{
			printf("All device can not connect, please press any key to end the program!\n");
			printf("Please press any key to end the program!\n");
			getchar();
			return 0;
		}
	}
	else
	{
		printf("Number of devices less than 2.\n");
		printf("Please press any key to end the program!\n");
		getchar();
		return 0;
	}

	//开始采集数据
	if (g_isConnect_1)
	{
		LCF_StatusTypeDef ret = LCF_StartCapture(g_handle_1);
		if (ret != LCF_Status_Succeed)
		{
			printf("%s start capture failed, error code: %d \n", deviceList[0].ip_addr, ret);
		}
		else
		{
			printf("%s start capture! \n", deviceList[0].ip_addr);
		}
	}

	//开始采集数据
	if (g_isConnect_2)
	{
		LCF_StatusTypeDef ret = LCF_StartCapture(g_handle_2);
		if (ret != LCF_Status_Succeed)
		{
			printf("%s start capture failed, error code: %d \n", deviceList[1].ip_addr, ret);
		}
		else
		{
			printf("%s start capture! \n", deviceList[1].ip_addr);
		}
	}

	while (1)
	{
		//等待数据采集够触发缓存阈值，解析灰度数据和高度数据
		if (g_result_1.size())
		{
			// 获取数据的长宽
			g_resolution_x_1 = 0;
			g_resolution_y_1 = 0;
			g_resolution_x_1 = g_result_1.at(0).x_count;
			g_resolution_y_1 = g_result_1.at(0).y_count;

			// 解析灰度数据
			int grayscale_count = g_result_1.at(0).x_count * g_result_1.at(0).y_count;
			g_grayscale_data_1.resize(grayscale_count);
			memcpy(g_grayscale_data_1.data(), g_result_1.at(0).intensity, grayscale_count * sizeof(uint16_t));

			// 解析高度数据,单位10um
			int hight_count = g_result_1.at(0).layer_number * g_result_1.at(0).x_count * g_result_1.at(0).y_count;
			g_hight_data_1.resize(hight_count);
			memcpy(g_hight_data_1.data(), g_result_1.at(0).height, hight_count * sizeof(int));

			// 清除已经解析的数据
			std::vector<LCF_Result_t>::iterator front = g_result_1.begin();
			g_result_1.erase(front);
		}

		if (g_result_2.size())
		{
			// 获取数据的长宽
			g_resolution_x_2 = 0;
			g_resolution_y_2 = 0;
			g_resolution_x_2 = g_result_2.at(0).x_count;
			g_resolution_y_2 = g_result_2.at(0).y_count;

			// 解析灰度数据
			int grayscale_count = g_result_2.at(0).x_count * g_result_2.at(0).y_count;
			g_grayscale_data_2.resize(grayscale_count);
			memcpy(g_grayscale_data_2.data(), g_result_2.at(0).intensity, grayscale_count * sizeof(uint16_t));

			// 解析高度数据,单位10um
			int hight_count = g_result_2.at(0).layer_number * g_result_2.at(0).x_count * g_result_2.at(0).y_count;
			g_hight_data_2.resize(hight_count);
			memcpy(g_hight_data_2.data(), g_result_2.at(0).height, hight_count * sizeof(int));

			// 清除已经解析的数据
			std::vector<LCF_Result_t>::iterator front = g_result_2.begin();
			g_result_2.erase(front);
		}
	}

	if (g_isConnect_1)
	{
		LCF_StopCapture(g_handle_1);	// 停止数据采集
		LCF_CloseDevice(g_handle_1);	// 断开设备连接
	}

	if (g_isConnect_2)
	{
		LCF_StopCapture(g_handle_2);	// 停止数据采集
		LCF_CloseDevice(g_handle_2);	// 断开设备连接
	}

	return 0;
}

