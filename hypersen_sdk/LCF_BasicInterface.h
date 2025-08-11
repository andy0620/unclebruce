///////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Copyright (c) 2017-2021 Hypersen Technology Co. Ltd.						//
// All rights reserved.                                                     //
//                                                                          //
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY   //
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE      //
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A               //
// PARTICULAR PURPOSE.                                                      //
//                                                                          //
// Website: www.hypersen.com                                                //
// Email: sales@hypersen.com												//
//////////////////////////////////////////////////////////////////////////////

#ifndef __BASICINTERFACE_H__
#define __BASICINTERFACE_H__

#include <stdint.h>
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _LCF_API
#define _LCF_API  _declspec(dllexport)
#else
#define _LCF_API  _declspec(dllimport)
#endif



_LCF_API int            LCFAPI_ScanDeviceList(uint8_t** deviceList,uint32_t* deviceNumber);
_LCF_API int			LCFAPI_ConnectDevice(char* controllerIp, uint16_t controllerPort, int*deviceHandler);
_LCF_API void			LCFAPI_CloseDevice(int handle);
_LCF_API int			LCFAPI_IsConnect(int handle);
_LCF_API int			LCFAPI_IsStart(int handle);
_LCF_API int			LCFAPI_StartCapture(int handle);
_LCF_API int			LCFAPI_StopCapture(int handle);
_LCF_API int			LCFAPI_SingleShot(int handle,uint8_t*result);
_LCF_API int			LCFAPI_RegisterEventCallback(void* eventHandle, void *userPara);
_LCF_API int			LCFAPI_UnregisterEventCallback();
_LCF_API int			LCFAPI_GetDeviceSetting(int handle,uint8_t* setting);
_LCF_API int			LCFAPI_ExportCacheData(int handle, uint8_t *result);
_LCF_API int			LCFAPI_ClearCacheData(int handle);
_LCF_API const char*	LCFAPI_GetErrorInfo(int handle);
_LCF_API int			LCFAPI_SaveSetting(int handle);
_LCF_API int			LCFAPI_RestoreFactorySetting(int handle);
_LCF_API int			LCFAPI_SetHDRIntensityGroup(int handle, int HDR_Mode, float intenSity[]);
_LCF_API int            LCFAPI_SetHDRExposureGroup(int handle, int HDR_Mode, int exposure[]);
_LCF_API int			LCFAPI_ReadSensorHeadFactoryPara(int handle, uint8_t *para);
_LCF_API int            LCFAPI_GetMaxROIFrameRate(int handle,int x_res,int y_res,int* maxFrameRate);
_LCF_API int            LCFAPI_Reboot(int handle);
_LCF_API int            LCFAPI_Shutdown(int handle);
_LCF_API int            LCFAPI_ClearEncoderTriggerCount(int handle);
_LCF_API int            LCFAPI_ExportDeviceSetting(int handle,char*path);
_LCF_API int            LCFAPI_ImportDeviceSetting(int handle,char*fileName);
_LCF_API int            LCFAPI_GetDeviceStatisticInfo(int handle,uint8_t *info);
_LCF_API int            LCFAPI_AdjustRoiForFps(int handle, int mode, int frameRate, float *Z_Range);
_LCF_API int            LCFAPI_SetMeasureRange(int handle, int farRange_um,int nearRange_um);
_LCF_API int            LCFAPI_SetIOPortFunc( int handle,int io_port,int triggerMode,int io_func);
_LCF_API int            LCFAPI_FindGoodLight(int handle,int enHDR);
_LCF_API int            LCFAPI_SetEncoderDyncDivValue(int handle,int encoderPos[], int division[], int real_div[], int group_member);

_LCF_API int            LCFAPI_SetIntParameter(int handle,const char* paramName,int value);
_LCF_API int            LCFAPI_SetFloatParameter(int handle,const char* paramName,float value);
_LCF_API int            LCFAPI_SetDoubleParameter(int handle,const char* paramName,double value);
_LCF_API int            LCFAPI_SetStringParameter(int handle,const char* paramName,char* value);

_LCF_API int            LCFAPI_GetIntParameter(int handle,const char* paramName,int* value);
_LCF_API int            LCFAPI_GetFloatParameter(int handle,const char* paramName,float* value);
_LCF_API int            LCFAPI_GetDoubleParameter(int handle,const char* paramName,double* value);
_LCF_API int            LCFAPI_GetStringParameter(int handle,const char* paramName,char* value);



_LCF_API int           LCFAPI_ScanDeviceList_Detail(uint8_t** deviceList, uint32_t* deviceNumber);
_LCF_API int           LCFAPI_ForceIP(const char*controlerSN,const char*ip,const char*gateway,const char*netmask);
_LCF_API int           LCFAPI_SetEthParam(const char*controlerSN,const char*ip,const char*gateway,const char*netmask);
_LCF_API int           LCFAPI_SetControllerParam(const char*controlerSN,const char*paramName,uint8_t*value);
_LCF_API int           LCFAPI_GetControllerParam(const char*controlerSN,const char*paramName,uint8_t*value);

_LCF_API int           LCFAPI_WriteUserFlashData(int handle,uint8_t*data,int len);
_LCF_API int           LCFAPI_ReadUserFlashData(int handle, uint8_t*data, int *len);

#ifdef __cplusplus
	}
#endif

#endif
