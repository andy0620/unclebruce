#include "LCF_UserInterface.h"

/**
 * @brief LCF_ConnectDevice:连接控制器
 * @param controllerIp:  控制器IP，输入NULL则使用默认的通讯参数连接
 * @param controllerPort 控制器端口号，输入0或 IP输入NULL则使用默认的通讯参数连接
 * @param deviceHandler  返回设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef LCF_ConnectDevice(char* controllerIp, uint16_t controllerPort, int* deviceHandler)
{
	return (LCF_StatusTypeDef)LCFAPI_ConnectDevice( controllerIp,  controllerPort,  deviceHandler);
}

/**
 * @brief LCF_CloseDevice 断开设备连接
 * @param handle          设备句柄
 */
void LCF_CloseDevice(int handle)
{
	LCFAPI_CloseDevice(handle);
}

/**
 * @brief LCF_IsConnect 获取传感器的连接状态
 * @param handle        设备句柄
 * @return 返回连接状态
 */
bool LCF_IsConnect(int handle)
{
	return LCFAPI_IsConnect(handle);
}


/**
 * @brief LCF_IsStart 获取传感器的采集状态
 * @param handle      设备句柄
 * @return            返回采集状态
 */
bool LCF_IsStart(int handle)
{
    return LCFAPI_IsStart(handle);
}


/**
 * @brief LCF_StartCapture 启动传感器测量
 * @param handle           设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef LCF_StartCapture(int handle)
{
	return (LCF_StatusTypeDef)LCFAPI_StartCapture(handle);
}

/**
 * @brief LCF_StopCapture 停止传感器测量
 * @param handle          设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef LCF_StopCapture(int handle)
{
	return (LCF_StatusTypeDef)LCFAPI_StopCapture(handle);
}

/**
 * @brief LCF_SingleShot 单次采集一帧轮廓数据，需要先将传感器设置为软件触发模式、然后启动传感器测量在调用该接口
 * @param handle        设备句柄
 * @param result        返回轮廓数据
 * @return 返回错误码
 */
LCF_StatusTypeDef LCF_SingleShot(int handle, LCF_Result_t* result)
{
	return(LCF_StatusTypeDef)LCFAPI_SingleShot(handle,(uint8_t*)result);
}

/**
 * @brief LCF_RegisterEventCallback 注册事件回调函数
 * @param eventHandle               回调函数
 * @param userPara                  用户参数
 * @return 返回错误码
 */
LCF_StatusTypeDef  LCF_RegisterEventCallback(LCF_UserEventCallbackHandle eventHandle, void* userPara)
{
	return (LCF_StatusTypeDef)LCFAPI_RegisterEventCallback((void*)eventHandle, userPara);
}

/**
 * @brief LCF_UnregisterEventCallback 注销回调函数
 * @return 返回错误码
 */
LCF_StatusTypeDef LCF_UnregisterEventCallback()
{
	return (LCF_StatusTypeDef)LCFAPI_UnregisterEventCallback();
}


/**
 * @brief LCF_GetDeviceSetting 获取传感器所有设置
 * @param handle        设备句柄
 * @param setting       返回传感器所有设置信息
 * @return 返回错误码
 */
LCF_StatusTypeDef LCF_GetDeviceSetting(int handle, LCF_DeviceSetting_t* setting)
{

	return(LCF_StatusTypeDef)LCFAPI_GetDeviceSetting(handle,(uint8_t*)setting);
}

/**
 * @brief LCF_ExportCacheData 导出控制器缓存的所有轮廓数据
 * @param handle            设备句柄
 * @param result            深度数据
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_ExportCacheData(int handle, LCF_Result_t* result)
{
    return (LCF_StatusTypeDef)LCFAPI_ExportCacheData(handle,(uint8_t*)(result));
}

/**
 * @brief LCF_ClearCacheData 清空缓存数据
 * @param handle             设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_ClearCacheData(int handle)
{
	return (LCF_StatusTypeDef)LCFAPI_ClearCacheData(handle);
}

/**
 * @brief LCF_GetErrorInfo 获取传感器错误描述信息
 * @param handle           设备句柄
 * @return 返回错误描述字符串
 */
const char* LCF_GetErrorInfo(int handle)
{
	return LCFAPI_GetErrorInfo(handle);
}


/**
 * @brief LCF_SaveSetting 保存当前传感器设置
 * @param handle          设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_SaveSetting(int handle)
{
	return (LCF_StatusTypeDef)LCFAPI_SaveSetting(handle);
}

/**
 * @brief LCF_RestoreFactorySetting  恢复出厂设置
 * @param handle        设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_RestoreFactorySetting(int handle)
{
	return (LCF_StatusTypeDef)LCFAPI_RestoreFactorySetting(handle);
}



/**
 * @brief LCF_SetHDRIntensityGroup 设置某个HDR模式下，每一帧的光强值
 * @param handle        设备句柄
 * @param HDR_Mode      HDR模式
 * @param intenSity     每一帧的光强值，例:如果HDR_Mode为LCF_HDRMode_4，则该数组指定4帧数据的光强值
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_SetHDRIntensityGroup(int handle, LCF_HDRMode_t HDR_Mode, float intenSity[])
{
    return (LCF_StatusTypeDef)LCFAPI_SetHDRIntensityGroup(handle, (int)HDR_Mode,intenSity);
}


/**
 * @brief LCF_SetHDRExposureGroup 设置某个HDR模式下，每一帧的曝光时间
 * @param handle        设备句柄
 * @param HDR_Mode      HDR模式
 * @param exposure      每一帧的曝光时间，例:如果HDR_Mode为LCF_HDRMode_4，则该数组指定4帧数据的曝光时间
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_SetHDRExposureGroup(IN int handle, IN LCF_HDRMode_t HDR_Mode,IN int exposure[])
{
    return (LCF_StatusTypeDef)LCFAPI_SetHDRExposureGroup(handle, (int)HDR_Mode,exposure);
}



/**
 * @brief LCF_ReadSensorHeadFactoryPara 读取传感器出厂参数
 * @param handle        设备句柄
 * @param para          返回传感器出参数
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_ReadSensorHeadFactoryPara(int handle, LCF_SensorHeadFactoryPara_t* para)
{
	return (LCF_StatusTypeDef)LCFAPI_ReadSensorHeadFactoryPara(handle, (uint8_t*)para);
}



 /**
  * @brief LCF_GetMaxROIFrameRate 获取用户指定的分辨率下CMOS支持的最大帧率
  * @param handle             设备句柄
  * @param x_res              X分辨率
  * @param y_res              Y分辨率
  * @param maxFrameRate       返回最大帧率
  * @return
  */
 LCF_StatusTypeDef LCF_GetMaxROIFrameRate(int handle, int x_res, int y_res, int *maxFrameRate)
 {
      return (LCF_StatusTypeDef)LCFAPI_GetMaxROIFrameRate(handle,x_res,y_res,maxFrameRate);
 }

 /**
  * @brief LCF_ScanDeviceList  扫描传感器，返回传感器IP和端口号
  * @param deviceList    返回设备IP地址信息
  * @param deviceNumber  设备个数
  * @return 返回错误码
  */
 LCF_StatusTypeDef LCF_ScanDeviceList(LCF_DeviceEthPara_t **deviceList, uint32_t *deviceNumber)
 {

     return (LCF_StatusTypeDef)LCFAPI_ScanDeviceList((uint8_t**)deviceList,deviceNumber);
 }


 /**
  * @brief LCF_ScanDeviceList_Detail:扫描传感器，返回控制器详细信息; 注:使用该接口扫描设备需要关闭PC端防火墙，反则可能会扫描不到设备
  * @param infoList   返回扫描到的设备列表，存放控制器相关的详细信息
  * @param listNum    扫描到的设备个数
  * @return           返回错误码
  */
 LCF_StatusTypeDef     LCF_ScanDeviceList_Detail(LCF_DeviceControlInfo_t** deviceList, uint32_t* deviceNumber)
 {
     return (LCF_StatusTypeDef)LCFAPI_ScanDeviceList_Detail((uint8_t**)deviceList,deviceNumber);
 }



 /**
  * @brief LCF_SetIntParameter 设置Int类型参数接口，
  * @param handle              设备句柄
  * @param paramName           参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value               设置的值
  * @return
  */
 LCF_StatusTypeDef LCF_SetIntParameter(int handle, const char *paramName, int value)
 {
     return (LCF_StatusTypeDef)LCFAPI_SetIntParameter(handle, paramName, value);
 }

 /**
  * @brief LCF_SetFloatParameter 设置Float类型参数接口，
  * @param handle                设备句柄
  * @param paramName             参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value                 设置的值
  * @return
  */
 LCF_StatusTypeDef LCF_SetFloatParameter(int handle, const char *paramName, float value)
 {
     return (LCF_StatusTypeDef)LCFAPI_SetFloatParameter(handle, paramName, value);
 }

 /**
  * @brief LCF_SetDoubleParameter 设置Double类型参数接口，
  * @param handle                 设备句柄
  * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value                  设置的值
  * @return
  */
 LCF_StatusTypeDef LCF_SetDoubleParameter(int handle, const char *paramName, double value)
 {
      return (LCF_StatusTypeDef)LCFAPI_SetDoubleParameter(handle, paramName, value);
 }

 /**
  * @brief LCF_SetStringParameter 设置字符串类型参数接口
  * @param handle                 设备句柄
  * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value                  设置的值
  * @return
  */
 LCF_StatusTypeDef LCF_SetStringParameter(int handle, const char *paramName, char *value)
 {
     return (LCF_StatusTypeDef)LCFAPI_SetStringParameter(handle, paramName, value);
 }

 /**
  * @brief LCF_GetIntParameter 获取Int类型参数值的接口
  * @param handle              设备句柄
  * @param paramName           参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value               返回值
  * @return
  */
 LCF_StatusTypeDef LCF_GetIntParameter(int handle, const char *paramName, int *value)
 {
     return (LCF_StatusTypeDef)LCFAPI_GetIntParameter(handle, paramName, value);
 }

 /**
  * @brief LCF_GetFloatParameter 获取Float类型参数值的接口
  * @param handle             设备句柄
  * @param paramName          参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value              返回值
  * @return
  */
 LCF_StatusTypeDef LCF_GetFloatParameter(int handle, const char *paramName, float *value)
 {
     return (LCF_StatusTypeDef)LCFAPI_GetFloatParameter(handle, paramName, value);
 }

 /**
  * @brief LCF_GetDoubleParameter 获取Double类型参数值的接口
  * @param handle                 设备句柄
  * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value                  返回值
  * @return
  */
 LCF_StatusTypeDef LCF_GetDoubleParameter(int handle, const char *paramName, double *value)
 {
     return (LCF_StatusTypeDef)LCFAPI_GetDoubleParameter(handle, paramName, value);
 }

 /**
  * @brief LCF_GetStringParameter 获取字符串类型参数值的接口
  * @param handle                 设备句柄
  * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
  * @param value                  返回值
  * @return
  */
 LCF_StatusTypeDef LCF_GetStringParameter(int handle, const char *paramName, char *value)
 {
     return (LCF_StatusTypeDef)LCFAPI_GetStringParameter(handle, paramName, value);
 }


 /**
  * @brief LCF_Reboot    重启控制器
  * @param handle        设备句柄
  * @return              返回错误描述字符串
  */
 LCF_StatusTypeDef LCF_Reboot(int handle)
 {
       return (LCF_StatusTypeDef)LCFAPI_Reboot(handle);
 }


 /**
  * @brief LCF_ClearEncoderTriggerCount   清除编码器计数值，控制器编码器计数从0开始，计数到用户设定的分频值后触发传感器采集
  * @param handle                         设备句柄
  * @return 返回错误码
  */
 LCF_StatusTypeDef LCF_ClearEncoderTriggerCount(int handle)
 {
      return (LCF_StatusTypeDef)LCFAPI_ClearEncoderTriggerCount(handle);
 }


 /**
  * @brief LCF_ExportDeviceSetting 导出设备配置信息到文件中
  * @param handle                  设备句柄
  * @param path                    导出路径
  * @return 返回错误码
  */
 LCF_StatusTypeDef LCF_ExportDeviceSetting(int handle, char *path)
 {
     return (LCF_StatusTypeDef)LCFAPI_ExportDeviceSetting(handle,path);
 }


 /**
  * @brief LCF_ImportDeviceSetting 导入设备配置文件
  * @param handle                  设备句柄
  * @param fileName                文件路径名
  * @return 返回错误码
  */
 LCF_StatusTypeDef LCF_ImportDeviceSetting(int handle, char *fileName)
 {
      return (LCF_StatusTypeDef)LCFAPI_ImportDeviceSetting(handle,fileName);
 }



 /**
  * @brief LCF_GetDeviceStatisticInfo  获取设备统计信息
  * @param handle                      设备句柄
  * @param info                        返回设备统计信息
  * @return 返回错误码
  */
 LCF_StatusTypeDef LCF_GetDeviceStatisticInfo(int handle, LCF_DeviceStatisticInfo_t *info)
 {
      return (LCF_StatusTypeDef)LCFAPI_GetDeviceStatisticInfo(handle,(uint8_t*)info);
 }


 /**
  * @brief LCF_AdjustRoiForFps 如果当前设置无法满足用户指定帧率，则自动适配合适的ROI分辨率，适应指定的帧率
  * @param handle              设备句柄
  * @param mode                适配模式
  * @param frameRate           指定帧率
  * @param Z_Range             返回适配成功后的Z轴理论量程，单位um
  * @return 返回错误码
  */
 LCF_StatusTypeDef LCF_AdjustRoiForFps(int handle, LCF_AdjustRoiFpsPara_t mode, int frameRate, float *Z_Range)
 {
      return (LCF_StatusTypeDef)LCFAPI_AdjustRoiForFps(handle,(int)mode,frameRate,Z_Range);
 }


 /**
  * @brief LCF_SetMeasureRange 设置传感器量程，例：LCF1000传感器量程为 +-1600um，可以设置的远端范围最小为-1600，近端最大范围为1600
  * @param handle              设备句柄
  * @param farRange_um         远端测量范围
  * @param nearRange_um        近端测量范围
  * @return  返回错误码
  */
 LCF_StatusTypeDef LCF_SetMeasureRange(int handle, int farRange_um, int nearRange_um)
 {
    return (LCF_StatusTypeDef)LCFAPI_SetMeasureRange(handle,farRange_um,nearRange_um);
 }


 /**
  * @brief LCF_SetIOPortFunc  设置控制器IO引脚(IN0、IN1、OUT0、OUT1)的功能
  * @param handle             设备句柄
  * @param io_port            IO引脚
  * @param triggerMode        IO引脚的触发方式
  * @param io_func            IO引脚绑定的功能
  * @return 返回错误码
  */
 LCF_StatusTypeDef LCF_SetIOPortFunc(int handle, LCF_IO_Port_t io_port, LCF_IO_TriggerMode_t triggerMode, LCF_IO_Func_t io_func)
 {
    return (LCF_StatusTypeDef)LCFAPI_SetIOPortFunc(handle,io_port,triggerMode,io_func);
 }


 /**
  * @brief LCF_FindGoodLight 根据当前测量位置，查找合适的光强
  * @param handle            设备句柄
  * @param enHDR             是否在HDR模式下查找，0:不使用HDR 1:使用HDR
  * @return                  返回错误码
  */
 LCF_StatusTypeDef LCF_FindGoodLight(int handle, int enHDR)
 {
    return (LCF_StatusTypeDef)LCFAPI_FindGoodLight(handle,enHDR);
 }


 /**
  * @brief LCF_SetEncoderDyncDivValue 设置动态编码器分频模式下，各个区域的分频值；用户可以根据编码器脉冲个数设定几个不同的分频值。例:在0~5000个编码器脉冲区间使用一个分频值，在5000~10000个脉冲区间使用另外一个分频值
  * @param handle            设备句柄
  * @param encoderPos        不同区域编码器脉冲个数，例:encoderPos[0]=1000,division[0]=16,则在编码器0~1000个脉冲区间使用16分频，encoderPos[1]=2000,division[0]=4,则在编码1000~2000个脉冲区间使用4分频；
  * @param division          不同区域编码器分频值
  * @param group_member      分频组数
  * @return                  返回错误码
  */
 LCF_StatusTypeDef LCF_SetEncoderDyncDivValue(int handle, int encoderPos[], int division[], int real_div[], int group_member)
 {
      return (LCF_StatusTypeDef)LCFAPI_SetEncoderDyncDivValue(handle,encoderPos,division,real_div,group_member);
 }


 /**
  * @brief LCF_Shutdown  关闭控制器
  * @param handle        设备句柄
  * @return              返回错误码
  */
 LCF_StatusTypeDef LCF_Shutdown(int handle)
 {
      return (LCF_StatusTypeDef)LCFAPI_Shutdown(handle);
 }


 /**
  * @brief LCF_SetControllerParam 通过广播命令设置控制器参数，该接口不受SDK连接状态影响，在SDK未连接控制器前依旧可以调用;
  *                               为了使控制器能够接收到广播命令，需要将本地防火墙关闭。
  * @param controlerSN   通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
  * @param paramName     参数名，包含的参数可以参考LCF_ParamterDefine.h文件PARAM_CTRL_XXXX类型的控制参数
  * @param value         设置的数据
  * @return  返回错误码
  */
 LCF_StatusTypeDef       LCF_SetControllerParam(const char *controlerSN, const char *paramName, uint8_t *value)
 {
      return (LCF_StatusTypeDef)LCFAPI_SetControllerParam(controlerSN, paramName, value);
 }


 /**
  * @brief LCF_SetControllerParam 通过广播命令获取控制器参数，该接口不受SDK连接状态影响，在SDK未连接控制器前依旧可以调用;
  *                               为了使控制器能够接收到广播命令，需要将本地防火墙关闭。
  * @param controlerSN   通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
  * @param paramName     参数名，包含的参数可以参考LCF_ParamterDefine.h文件PARAM_CTRL_XXXX类型的控制参数
  * @param value         设置的数据
  * @return  返回错误码
  */
 LCF_StatusTypeDef       LCF_GetControllerParam(const char *controlerSN, const char *paramName, uint8_t *value)
 {
      return (LCF_StatusTypeDef)LCFAPI_GetControllerParam(controlerSN, paramName, value);
 }


 /**
  * @brief LCF_ForceIP  临时修改控制器IP参数,用户可以根据本地网口的网段，将控制器IP设置在同一网段下;控制器重新启动后IP恢复为初始值;需要永久修改控制器IP可以使用LCF_SetEthParam接口或连接上控制器后,使用PARAM_IP_ADDR参数进行修改
  * @param controlerSN  通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
  * @param ip            控制器IP
  * @param gateway       控制器网关
  * @param netmask       控制器子网掩码
  * @return
  */
 LCF_StatusTypeDef       LCF_ForceIP(const char*controlerSN,const char*ip,const char*gateway,const char*netmask)
 {
     return (LCF_StatusTypeDef)LCFAPI_ForceIP(controlerSN,ip,gateway,netmask);
 }


 /**
  * @brief LCF_ForceIP   永久修改控制器IP参数，修改完成后重启控制器后生效
  * @param controlerSN   通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
  * @param ip            控制器IP
  * @param gateway       控制器网关
  * @param netmask       控制器子网掩码
  * @return
  */
 LCF_StatusTypeDef       LCF_SetEthParam(const char*controlerSN,const char*ip,const char*gateway,const char*netmask)
 {
     return (LCF_StatusTypeDef)LCFAPI_SetEthParam(controlerSN,ip,gateway,netmask);
 }


 /**
  * @brief LCF_WriteUserFlashData 用户自定义数据写入传感头内部Flash
  * @param handle        设备句柄
  * @param data          写入数据
  * @param len           数据长度,单位字节
  * @return
  */
 LCF_StatusTypeDef       LCF_WriteUserFlashData(int handle, uint8_t*data,int len)
 {
     return (LCF_StatusTypeDef)LCFAPI_WriteUserFlashData(handle,data,len);
 }


 /**
  * @brief LCF_ReadUserFlashData 读取传感头内部Flash用户写入的数据
  * @param handle         设备句柄
  * @param data           返回用户数据
  * @param len           返回数据长度,单位字节。如果Flash没被写入过数据则返回数据长度为0
  * @return
  */
 LCF_StatusTypeDef       LCF_ReadUserFlashData(int handle, uint8_t*data,int *len)
 {
     return (LCF_StatusTypeDef)LCFAPI_ReadUserFlashData(handle,data,len);
 }
