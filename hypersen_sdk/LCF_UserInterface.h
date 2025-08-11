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

#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__



#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "LCF_BasicInterface.h"

#define IN
#define OUT

//X轴最小分辨率
#define  MINI_ROI_X_RES             64
//Y轴最小分辨率
#define  MINI_ROI_Y_RES             56
//信号无效值
#define  INVALID_VALUE              888888
//最大HDR次数
#define  MAX_HDR_NUMBER             8
//最大检测层数
#define MAX_DETECT_LAYER_NUMBER     (4+0)

//动态分频最大组数
#define MAX_DYNAMIC_DIV_GROUP       3


//错误码定义
typedef enum
{
    LCF_Status_Succeed                      =0,
    LCF_Status_NoCamera                     =1,
    LCF_Status_NoGrabberCard                =2,
    LCF_Status_CamApiCallFailed             =3,
    LCF_Status_ResMulErr                    =4,
    LCF_Status_ResOutOfRange                =5,
    LCF_Status_OldCamFwVer                  =6,
    LCF_Status_ParamOverFlash               =7,
    LCF_Status_CtrlErrCheckSum              =8,
    LCF_Status_CtrlPathNotExist             =9,
    LCF_Status_CalFileNotExist              =10,
    LCF_Status_CalFileFormatErr             =11,
    LCF_Status_NoCalPara                    =12,
    LCF_Status_NoGrayCalPara                =13,
    LCF_Status_GrayCalFileFormatErr         =14,
    LCF_Status_NoRefCalFile                 =15,
    LCF_Status_RefFileFormatErr             =16,
    LCF_Status_RefFileModelNotMatch         =17,
    LCF_Status_SysProcPendingTimeout        =18,
    LCF_Status_CacheNoData                  =19,
    LCF_Status_NoSampleData                 =20,
    LCF_Status_ParaOutOfRange               =21,
    LCF_Status_DeviceNotConnected           =22,
    LCF_Status_InvalidPara                  =23,
    LCF_Status_CmosIndexError               =24,
    LCF_Status_NotInSoftwareTriggerMode     =25,
    LCF_Status_CaptureNotStart              =26,
    LCF_Status_CaptureTimeOut               =27,
    LCF_Status_NoFactoryPara                =28,
    LCF_Status_NoXCalFile                   =29,
    LCF_Status_CtrlIOErr                    =30,
    LCF_Status_NoMacthFramerate             =31,
    LCF_Status_XPointsUnderThre             =32,
    LCF_Status_ParaSizeNotMatch             =33,
    LCF_Status_NoLicense                    =34,
    LCF_Status_ReadOnlyPara                 =35,
    LCF_Status_CommunicateTimeout           =36,
    LCF_Status_CtrlFileNotFound             =37,
    LCF_Status_CtrlOpenFileFailed           =38,
    LCF_Status_PacketLost                   =39,
    LCF_Status_LockSyncTimeout              =40,
    LCF_Status_FileFormatErr                =41,
    LCF_Status_TooFewValidePoints           =42,
    LCF_Status_InvalidPoints                =43,
    LCF_Status_TooFewSamplePoints           =44,
    LCF_Status_FileNameErr                  =45,
    LCF_Status_XCalFormatErr                =46,
    LCF_Status_NoParaMatch                  =47,
    LCF_Status_LicenseFeatureNotFound       =48,
    LCF_Status_LicenseExpired               =49,
    LCF_Status_LoadLibFailed                =50,
    LCF_Status_LicenseLoginFailed           =51,
    LCF_Status_SDKVerNotMatch               =52,
    LCF_Status_UDPSendFailed                =53,
    LCF_Status_CmdBufferSizeNotEnough       =54,
    LCF_Status_InvalidIpPara                =55,
    LCF_Status_TransmitTimeout              =56,
    LCF_Status_AllocateMemFaild             =57,
    LCF_Status_ControlerFileNotFound        =58,
    LCF_Status_NoMatchCmd                   =59,
    LCF_Status_ConnectServerFailed          =60,
    LCF_Status_DeviceAlreadyOpen            =61,
    LCF_Status_DeviceNumberExceedLimit      =62,
    LCF_Status_Undefine                     =63,
    LCF_Status_NotConnected                 =64,
    LCF_Status_CtrlLockSyncTimeout          =65,
    LCF_Status_IOBoardCommTimeout           =66,
    LCF_Status_FileNotFound                 =67,
    LCF_Status_OpenFileFailed               =68,
    LCF_Status_ErrCheckSum                  =69,
    LCF_Status_TriggerModeErrDyExp          =70,
    LCF_Status_CamFWUpdatinge               =71,
    LCF_Status_OpticalFWUpdating            =72,
    LCF_Status_CamConneting                 =73,
    LCF_Status_NoCamUpdateTool              =74,
    LCF_Status_NoOpticalUpdateTool          =75,
    LCF_Status_CtrlFileFormatErr            =76,
    LCF_Status_CamNoFirmware                =77,
    LCF_Status_SensorInitTimeout            =78,
    LCF_Status_ClientNumberExceedLimit      =79,
    LCF_Status_IOBoardInitFailed            =80,
    LCF_Status_IOBoardReturnDataLenErr      =81,
    LCF_Status_IOBoardReturnDataErr         =82,
    LCF_Status_SDKCacheNotConfig            =83,
    LCF_Status_SDKCacheSizeBelowThre        =84,
    LCF_Status_CreateCtrlDirFailed          =85,
    LCF_Status_CreateCtrlFileFailed         =86,
    LCF_Status_ExtractFileFailed            =87,
    LCF_Status_WriteCtrlFileFailed          =88,
    LCF_Status_FWUpdateScriptNotExist       =89,
    LCF_Status_FWUpdateScriptOptFailed      =90,
    LCF_Status_FWUpdatePacketIncomplete     =91,
    LCF_Status_SuperDogFeatureIDNotFound    =92,
    LCF_Status_SuperDogDeviceNotFound       =93,

    LCF_Status_Others                       = 255,

}LCF_StatusTypeDef;

//返回过程数据的RID
typedef enum
{
    //测量结果
    LCF_RID_RESULT = 0,
    //API调用错误
    LCF_RID_API_CALL_EXCEPTION,
    //API调用警告
    LCF_RID_API_CALL_WARNING,
    //控制器IO中断,IN0、IN1、OUT0、OUT1对应事件触发时对应的RID
    LCF_RID_IO_ASYNC_EVENT,
    //控制器缓存轮廓数大于等于用户设定阈值
    LCF_RID_CACHE_REACH_THRE,
    //SDK版本和控制器固件版本不匹配
    LCF_RID_VERSION_NOT_MATCH,
    //网络异常
    LCF_RID_NETWORK_EXCEPTION,


}LCF_DataRid_t;


//异步通知事件类型
typedef enum
{
     //事件类型:接收数据
    LCF_EventType_DataRecv = 0,
    //事件类型:设备断开连接
    LCF_EventType_Disconnect,
}LCF_EventTypeDef;


//曝光模式
typedef enum
{
    //正常曝光模式，CMOS曝光时间等于用户设定的曝光时间
    LCF_Normal_Exposure =0,
    //动态曝光模式，曝光时间等于外部触发间隔
    LCF_Dynamic_Exposure
}LCF_ExposureMode_t;


//增益
typedef enum
{
    //2K resolution sensor
    LCF_2K_Gain_1 = 1,
    LCF_2K_Gain_2 = 2,
    LCF_2K_Gain_4 = 4,
}LCF_CameraGain_t;

//触发模式
typedef enum
{
    //内部连续触发
	LCF_InternalTrigger = 0,
    //编码器触发
	LCF_EncoderTrigger = 1,
    //软件单次触发
	LCF_SoftwareTrigger = 2,
    //外部触发
    LCF_ExternalTrigger = 3,

}LCF_TriggerMode_t;



//外部触发模式
typedef enum
{
    //下降沿触发
    LCF_ExternalFalling =0,
    //上升沿触发
    LCF_ExternalRasing,
    //双边沿触发
    LCF_ExternalRasingFalling,
    //低电平触发
    LCF_ExternalLowLevel,
    //高电平触发
    LCF_ExternalHighLevel,

}LCF_ExternalTriggerMode_t;

//编码器分频模式
typedef enum
{
    //固定分频
    LCF_Fixed_Division = 0,
    //动态分频
    LCF_Dynamic_Division,

}LCF_EncoderDivisionMode_t;

//binning模式
typedef enum
{
	LCF_BinMode_No = 0x0,
    //X轴Binning，扩大X轴点间隔，提高帧率
	LCF_BinMode_2X1 = 0x01,
    //Z轴Binning，降低Z轴分辨率，提高帧率
    LCF_BinMode_1X2 = 0x02,
    //X轴、Z轴Binning，扩大X轴点间隔、降低Z轴分辨率，提高帧率
    LCF_BinMode_2X2 = 0x03,
    //Binning扩展模式，提高帧率
    LCF_BinMode_Ext = 0x04,
}LCF_BinningMode_t;

//X量程
typedef enum
{
    //X轴满量程
    LCF_X_Range_Full = 0x0,
    //X轴3/4量程
    LCF_X_Range_3_4,
    //X轴1/2量程
    LCF_X_Range_2_4,
    //X轴1/4量程
    LCF_X_Range_1_4,
    //X轴1/8量程
    LCF_X_Range_1_8,
}LCF_X_Range_t;


//X量程缩小方向
typedef enum
{
    //裁剪掉X轴尾部
    LCF_X_Reduce_Tail = 0,
    //裁剪掉X轴头部
    LCF_X_Reduce_Head,
    //裁剪掉X轴两端
    LCF_X_Reduce_Edge
}LCF_X_Reduce_dir_t;

//X轴降采样
typedef enum
{
    LCF_X_Subsample_No = 0x0,
    //X轴2倍降采样，X点数量变为1/2
    LCF_X_Subsample_X2 = 0x01,
    //X轴4倍降采样，X点数量变为1/4
    LCF_X_Subsample_X4 = 0x02,
    //X轴8倍降采样，X点数量变为1/8
    LCF_X_Subsample_X8 = 0x03,
    //X轴16倍降采样，X点数量变为1/16
    LCF_X_Subsample_X16 = 0x04,
}LCF_X_Subsample_t;


//Z轴降采样
typedef enum
{
    LCF_Z_Subsample_No = 0x0,
    //Z轴2倍降采样
    LCF_Z_Subsample_X2 = 0x01,
}LCF_Z_Subsample_t;



//HDR多帧合成模式,使用多帧不同光强/曝光的测量数据合成一帧
typedef enum
{
    //关闭HDR模式
    LCF_HDRMode_OFF = 1,
    //使用2帧不同光强/曝光的测量数据合成一帧
    LCF_HDRMode_2,
    //使用3帧不同光强/曝光的测量数据合成一帧
	LCF_HDRMode_3,
    //使用4帧不同光强/曝光的测量数据合成一帧
	LCF_HDRMode_4,
    //使用5帧不同光强/曝光的测量数据合成一帧
	LCF_HDRMode_5,
    //使用6帧不同光强/曝光的测量数据合成一帧
	LCF_HDRMode_6,
    //使用7帧不同光强/曝光的测量数据合成一帧
	LCF_HDRMode_7,
    //使用8帧不同光强/曝光的测量数据合成一帧
	LCF_HDRMode_8,
}LCF_HDRMode_t;


//HDR模式下选择灰度图类型
typedef enum
{
    //多帧HDR模式下，使用多帧平均灰度作为最终灰度图
    LCF_HDR_I_Avg = 0,
    //多帧HDR模式下，使用信号最强的一帧灰度图作为最终灰度图
    LCF_HDR_I_Max,
    //多帧HDR模式下，使用信号最弱的一帧灰度图作为最终灰度图
    LCF_HDR_I_Min
}LCF_HDR_Intensity_t;


//近端、远端、多距离模式下信号检测灵敏度
typedef enum
{
    //低灵敏度
    LCF_LowSensitivity = 0,
    //正常灵敏度
    LCF_NormalSensitivity,
    //高灵敏度
    LCF_HighSensitivity,
    //自定义灵敏度
    LCF_CustomizeSensitivity,
}LCF_SignalDetectSensitivity_t;

//测量模式
typedef enum
{
    //单层模式,测量强度最强的信号
	LCF_Mode_SinglePeak = 0,
    //多层模式，测量所有检测到的信号
    LCF_Mode_MultiPeak,
    //近端模式，测量最靠近传感头的信号
	LCF_Mode_NearEnd,
    //远端模式，测量最远离传感头的信号
	LCF_Mode_FarEnd,
    //厚度模式，测量厚度
	LCF_Mode_Thickness,
}LCF_MeasureModet_t;



//ROI自适应参数
typedef enum
{
    //适应ROI到用户指定帧率，点间距优先，压缩Z向量程
    LCF_SetRoiForFps_NoBinning,
    //适应ROI到用户指定帧率，Z向量程优先，扩大X向点间距，X向有效点数变为最大点数的一半,X向量程不变
    LCF_SetRoiForFps_X_Binning,
    //适应ROI到用户指定帧率，Z向量程优先，减低Z向分辨率
    LCF_SetRoiForFps_Z_Binning,
    //适应ROI到用户指定帧率，速度和Z向量程优先，扩大X向点间距、减低Z向分辨率
    LCF_SetRoiForFps_X_Z_Binning,

}LCF_AdjustRoiFpsPara_t;


//编码器输入模式
typedef enum
{
    //2相1倍频
    LCF_ENCODER_MUT_2_INC_1 = 1,
    //2相2倍频
    LCF_ENCODER_MUT_2_INC_2 = 2,
    //2相4倍频
    LCF_ENCODER_MUT_2_INC_4 = 3,
}LCF_EncoderInputMode_t;


//控制器IO端口,这些端口不是实时端口只用于绑定特定的触发功能，不用于实时触发传感器采集
typedef enum
{
    //IN0
    LCF_IO_IN0 = 0,
    //IN1
    LCF_IO_IN1,
    //OUT0
    LCF_IO_OUT0,
    //OUT1
    LCF_IO_OUT1
}LCF_IO_Port_t;


//控制器IO事件触发类型
typedef enum
{
    //上升沿触发
    LCF_IO_TriggerRasing =0,
    //下降沿触发
    LCF_IO_TriggerFalling,
    //双边沿触发
    LCF_IO_TriggerRasingFalling,
}LCF_IO_TriggerMode_t;


//控制器IO引脚功能
typedef enum
{
   //IO端口空闲,不绑定任何功能
   LCF_IO_Func_Idle =0,
   //IO引脚触发传感器启动采集数据
   LCF_IO_Func_StartSample,
   //IO引脚触发传感器停止采集数据
   LCF_IO_Func_StopSample,
   //IO引脚触发传感器清空缓存数据
   LCF_IO_Func_ClearCache,
   //IO引脚中断通知，将该中断事件通过回调函数通知用户，SDK内部不做任何处理
   LCF_IO_Func_AsyncNotice,
}LCF_IO_Func_t;


//数据Cache选择，只对LCF_ExportCacheData方式导出数据有效
typedef enum
{
    //扫描数据缓存在控制器中
    LCF_Cache_Controler = 0,

    //扫描数据缓存在SDK中，需要先通过参数PARAM_SDK_CACHE_SIZE
    LCF_Cache_SDK       = 1

}LCF_DataCacheType_t;


typedef struct
{
    char        ip_addr[32];
    uint32_t    port;

}LCF_DeviceEthPara_t;

typedef enum
{
    //传感器已经就绪，SDK可以连接
    LCF_CS_CameraReady           = 0,

    //检测不到传感头
    LCF_CS_NoCamera              = 1,

    //控制器固件为旧版本固件
    LCF_CS_OldFirmware           = 2,

    //控制器连接的TCP客户端个数已经达到上限
    LCF_CS_ClientsReachMax       = 3,

    //控制器和PC不在同一网段
    LCF_CS_NetSegmentNotMatch    = 4,

    //PC网卡速率达不到千兆网速率
    LCF_CS_NotGigabitNetwork     = 5,

    //PC网卡没有打开巨型帧
    LCF_CS_JumboFrameError       = 6,

    //控制IP和PC端IP冲突，需要修改控制器IP
    LCF_CS_IPConflict            =7,

    //防火墙未关闭，扫描信息可能被拦截
    LCF_CS_FirewallEnalble      =8,


}LCF_ControlerStatus_t;


typedef struct
{
    //控制器IP
    char            controlerIP[32];
    //控制器网关
    char            controlerGateway[32];
    //控制子网掩码
    char            controlerNetmask[32];
    //控制器MAC地址
    char            controlerMAC[32];
     //控制器端口号
    int             controlerPort;
    //连接控制器的本地网卡IP
    char            localIP[32];
    //连接控制器的本地网卡MAC地址
    char            localMAC[32];
    //控制器用户ID名
    char            deviceUserID[64];
    //控制器序列号
    char            controlerSN[64];
     //控制器固件版本
    char            controlerFWVersion[64];
    //控制器型号
    char            controlerModelName[64];
    //当前控制器的状态,值等于 LCF_ControlerStatus_t
    int             status;
    //控制器时间戳高32位
    int             timeStamp_H;
    //控制器时间戳低32位
    int             timeStamp_L;
    //固件类型
    char            firmwareType[32];
    //控制器运行时间，单位分钟
    int             controlerRunTime_Min;
    //控制器剩余磁盘空间
    float           freeDiskSpace_GB;
    //控制器剩余内存
    float           freeMem_GB;
    //控制器光模块温度
    int             grabberCardTemp;
    //控制器CPU温度
    int             cpuTemp;
    //控制器GPU温度
    int             gpuTemp;

    int             reserve[251];
}LCF_DeviceControlInfo_t;


//传感头出厂参数
typedef struct
{
    // 该传感头型号
    char        model[32];
    // 该传感头序列号
    char        serialNumber[64];
    //量程近端距离，等于真实值*10，单位mm
    int         measureRangeMin;
    //量程远端距离，等于真实值*10，单位mm
    int         measureRangeMax;
    //X轴扫描长度，等于真实值*10，单位mm
    int         scanLength;
    //校正时间戳
    uint32_t    calibrationTimestamp;
    //记录校正时温度的温度
    int         calibrationTemp;

    int         reserve[510];
}LCF_SensorHeadFactoryPara_t;


//用户配置参数
#pragma pack(4)
typedef struct
{
    //曝光时间，us
    int                 exposureTime;
    //照明强度(0.0~100.0)
    float               lightIntensity;
    //X轴扫描长度，单位mm
    float               scanLength;
    //CMOS X轴最大分辨率
    int                 max_resolution_X;
    //CMOS Y轴(对应测量深度图的Z轴)最大分辨率
    int                 max_resolution_Y;
    //像素深度
    int                 pixel_depth;
    //当前X轴分辨率,该值为没有降采样的分辨率
    int                 resolution_x_raw;
    //当前Y轴分辨率,该值为没有降采样的分辨率
    int                 resolution_y_raw;
    //X轴偏移
    int                 pos_x_raw;
    //Y轴偏移
    int                 pos_y_raw;
    //回调阈值，控制器内部轮廓大于该值才通知用户
    int                 countourLineThreshold;
    //帧率控制
    int                 frameRateControl;
    //帧率
    int                 frameRate;
    //时间域滑动中值滤波深度
    int                 medianFilterDepth;
    //时间域滑动平均深度
    int                 movingAvgFilterDepth;
    //空间域域滑动中值滤波深度
    int                 spaceMedianFilterDepth;
    //空间域滑动平均深度
    int                 spaceMovingAvgFilterDepth;
    //编码器分频系数
    int                 encoderDivision;
    //无效信号阈值(0~255)
    int                 invalidSignalThrehold;
    //多光强HDR模式下，每个HDR模式下对应的光强(0.0~100.0)
    float               HDR_LightIntensity[MAX_HDR_NUMBER][MAX_HDR_NUMBER];
    //信号计算阈值(0~1)
    float               calculateThrehold;
    //传感器增益
    int                 cameraGain;
    //HDR 次数
    int                 HDR_Num;
    //触发模式
    int                 triggerMode;
    //binning模式
    int                 binningMode;
    //测量模式
    int                 measureMode;
    //HDR去除饱和\无信号数据
    int                 removeInvalidSignal;
    //输出高度图翻转
    int                 reverseHightValue;
    //控制器固件版本号
    char                controlerFWVersion[32];
    //传感头固件版本号
    char                sensorFWVersion[32];
    //X轴点间隔，单位um
    float               x_point_interval;
    //编码器输入模式
    int                 encoderInputMode;
    //空洞插值最大的空洞长度
    int                 maxInterpolationPoint;
    //信号数量限制
    int                 signalNumberLimit;
    //最小计算点数阈值
    int                 calPointsThreshold;
    //灰度数据fft2宽度
    int                 intensity_fft2_w;
    //灰度数据fft2高度
    int                 intensity_fft2_h;
    //高度数据fft2宽度
    int                 height_fft2_w;
    //高度数据fft2高度
    int                 height_fft2_h;
    //2维平面中值滤波
    int                 medianFilterDepth_2D;
    //2维平面平均滤波
    int                 avgFilterDepth_2D;
    //2维平面形态学闭运算
    int                 morphClose_2D;
    //2维平面形态学开运算
    int                 morphOpen_2D;
    //多层距离排序方式
    int                 surfaceSorting;
    //多距离、远端模式是否使能折射率校正
    int                refractiveCal;
    //外部触发模式
    int                externalTriggerMode;
    //X轴降采样比例
    int                x_subsample;
    //2D灰度数据锐化
    int                intensity_sharpen;
    //CMOS HDR参数magic
    int                cmos_hdr_para_magic;
    //CMOS HDR模式
    int                cmos_hdr_mode;
    //外部IO同步输出使能
    int                triggerSyncOutEn; 
    //心跳包超时时间，单位秒
    int                heartBeatTimeout;
    //信号平滑长度
    int                signalSmooth;
    //近端量程，单位um
    int                measureRange_near;
    //远端量程，单位um
    int                measureRange_far;
    //IN0、IN1、OUT0、OUT1 IO口电平触发方式
    int                controlerIOTriggerMode[4];
    //IN0、IN1、OUT0、OUT1 IO口绑定的功能
    int                controlerIOFunc[4];
    //使能灰度图重采样
    int                intensityResample;
    //HDR模式下信号饱和区域的滤除范围
    int                HDR_SaturationRemoveLen;
    //IO输入消抖延迟时间，单位ms
    int                IO_DebounceTime;
    //多层距离下，第一层和第二层最小距离（um）
    int                firstLayerMinDist;
    //多层距离下，第一层最小点数
    int                firstLayerMinLen;
    //选择对应层的灰度图
    int                intensityLayerSelect;
    //Cache缓存轮廓阈值，达到阈值后异步通知用户
    int                cacheCountourThreshold;
    //Z轴降采样比例
    int                z_subsample;             
    //使能偏移滤波
    int                enFilterOffset;
    //插值的最大Z方向间隙(um)
    int                interpolationMaxThickness;
    //集群滤波最小长度
    int                 clusterFilterMinLen;
    //集群滤波最小Z方向间隙(um)
    int                 clusterFilterDistanceZ;
    //信号检测灵敏度
    int                 signalDetectSensitivity;
    //光源超功率模式
    int                 lightOverpower;
    //2D平滑滤波中心距离标准差
    float               avgFilterSigma_s_2D;
    //2D平滑滤波中心点差值标准差
    float               avgFilterSigma_diff_2D;
    //2维平面形态学闭运算Z方向标准差
    int                 morphClose_sigma_2D;
    //X轴量程
    int                 x_range;
    //CMOS曝光模式
    int                 exposureMode;
    //一维空间平滑滤波Z方向阈值
    int                 spaceMovingAvgFilter_Z_Thre;
    //编码器分频模式
    int                 encoderDivisionMode;
    //动态分频组数
    int                 dyncDivGroupNumber;
    //动态分频对应的电机脉冲位置
    int                 dyncDivEncoderPos[MAX_DYNAMIC_DIV_GROUP];
    //动态分频下对应每个区域的分频值
    int                 dyncDivision[MAX_DYNAMIC_DIV_GROUP];
    //滤除伪边沿
    int                 trim_edges_filter;
    //开运行Z阈值，和周围点差值大于该值认为是离群点
    int                 morphOpen_Z_Thre_2D;
    //HDR模式下灰度图选择
    int                 hdr_intensity_select;
    //2D偏移滤波
    int                 enFilterOffset_2D;
    //X轴量程缩小方向
    int                 x_reduce_dir;
    //HDR多曝光模式，支持每帧数据不同的曝光时间
    int                 HDR_MultiExpMode;
    //多曝光HDR模式下，每个HDR模式下对应的曝光时间
    int                 HDR_Exposure[MAX_HDR_NUMBER][MAX_HDR_NUMBER];
    //灰度补偿
    int                 intensityCal;
    //X方向实际分辨率
    int                 resolution_x;
    //暖机亮度值
    int                 warnUpLight;
    //光源使用寿命延长
    int                energySavingMode;
    //自定义信号检测灵敏度
    int               customizeSensitivity;
    //灰度清晰化
    int               graySharpnessLevel;
    //灰度二值化使能
    int               grayBinEn;
    //灰度二值化反向
    int               grayBinReverse;
    //灰度二值化自动查找阈值
    int               grayBinAutoThre;
    //灰度二值化阈值
    int               grayBinThre;  
    //数据缓存选择
    int               dataCacheSelet;
    //SDK Cache缓存大小，单位：轮廓数
    int               sdkCacheSize;
    //使用SDK Cache导出数据时，等待
    int               expWaitFifoEmpty;

    //保留区域
   int               reserve[499];
}LCF_DeviceSetting_t;
#pragma pack()



//异步事件参数
typedef struct
{
	LCF_EventTypeDef	eventType;		//事件类型
	LCF_DataRid_t       rid;			//数据RID
    void*               data;           //数据
	int					dataLen;		//数据个数
}LCF_EventCallbackArgs_t;


typedef struct
{

    /****************多层高度统计信息，若是单层模式，则只有第一个数组成员有效*****************/
    //高度最大值，数值 /10.0 = 实际的高度，单位um
    int         maxHeightValue[MAX_DETECT_LAYER_NUMBER];
    //高度最小值，数值 /10.0 = 实际的高度，单位um
    int         minHeightValue[MAX_DETECT_LAYER_NUMBER];
    //高度最大值X坐标
    int         maxHeightValue_X[MAX_DETECT_LAYER_NUMBER];
    //高度最大值Y坐标
    int         maxHeightValue_Y[MAX_DETECT_LAYER_NUMBER];
    //高度最小值X坐标
    int         minHeightValue_X[MAX_DETECT_LAYER_NUMBER];
    //高度最小值Y坐标
    int         minHeightValue_Y[MAX_DETECT_LAYER_NUMBER];


   /***************灰度统计信息*****************/
    //灰度最大值
    int         maxIntensityValue;
    //灰度最小值
    int         minIntensityValue;
     //灰度最大值X坐标
    int         maxIntensityValue_X;
     //灰度最大值Y坐标
    int         maxIntensityValue_Y;
     //灰度最小值X坐标
    int         minIntensityValue_X;
     //灰度最小值Y坐标
    int         minIntensityValue_Y;

}LCF_StatisticInfo_t;


typedef struct
{
    //记录不同分频下的y位置
     //例:第0~ y_pos[0]轮廓为encoderDiv[0]分频;第y_pos[0]~ y_pos[1]轮廓为encoderDiv[1]分频;第y_pos[1]~ y_pos[2]轮廓为encoderDiv[2]分频
    //分频 x 电机一个脉冲对应的距离值等于Y方向扫描间隔
    int y_pos[MAX_DYNAMIC_DIV_GROUP];
    //分频数值
    int encoderDiv[MAX_DYNAMIC_DIV_GROUP];
}LCF_DynamicDivisionInof_t;


//轮廓数据
typedef struct
{
	//轮廓长度
    uint32_t                x_count;
	//轮廓个数
    uint32_t                y_count;
    //层数，若当前为单层模式，该值为1
    uint32_t                layer_number;

    //轮廓X轴点间隔，单位um
    float                   x_interval;   
    /*
     * 存放多个轮廓数据, 点数等于 layer_number* x_count * y_count, 数值 /10.0 = 实际的高度,单位um；例 height[0] = 2000-> 对应高度为 2000/10.0 = 200um，无信号点数则填充为空洞数值INVALID_VALUE
     * 第一层(靠近传感器)数据地址为:height。第二层数据地址为:height + x_count * y_count,其他层以此类推。
    */
    int*                    height;

    //存放轮廓的灰度图，点数等于 x_count * y_count
    uint16_t*               intensity;

    //存放每个轮廓的触发计数，个数等于y_count
    uint32_t*               triggerCount;

    //返回轮廓统计信息，包含最大最小值
    LCF_StatisticInfo_t     statisticInfo;

    //返回动态编码器分频模式下，编码器分频信息，只对LCF_ExportCacheData导出的测量结果有效，回调函数返回的测量结果该字段无效
    LCF_DynamicDivisionInof_t  dynamicDiv;
}LCF_Result_t;



//控制统计信息
typedef struct
{
    //CPU温度
    int cpu_temp;
    //GPU温度
    int gpu_temp;
    //相机温度
    int camera_temp;
    //采集卡温度
    int grabber_card_temp;
    //计算帧率
    int calculateFrameRate;
    //CMOS帧率
    int cameraFrameRate;
    //传输帧率
    int transmitFrameRate;
    //资源占用率
    int occupancyRate;
    //光源温度
    int lightTemp;
    //相机丢帧信息
    int cmosLostFrame;
    //相机错误帧信息
    int cmosErrorFrame;
    //相机CMOS历史最大帧率
    int cameraMaxFrameRateHistory;
    //控制器剩余磁盘空间
    float freeDiskSpace_GB;
    //控制器剩余内存
    float freeMem_GB;

    //保留区域
    int             reserve[121];
}LCF_DeviceStatisticInfo_t;



//异步通知回调函数
typedef void(*LCF_UserEventCallbackHandle)(int handle, LCF_EventCallbackArgs_t* arg, void* userPara);


/**
 * @brief LCF_ScanDeviceList 扫描传感器，返回传感器IP和端口号; 注:使用该接口扫描设备需要关闭PC端防火墙，反则可能会扫描不到设备
 * @param deviceList    返回扫描到的设备列表，存放IP和端口信息
 * @param deviceNumber  扫描到的设备个数
 * @return 返回错误码
 */
LCF_StatusTypeDef    LCF_ScanDeviceList(LCF_DeviceEthPara_t **deviceList, uint32_t* deviceNumber);


/**
 * @brief LCF_ScanDeviceList_Detail:扫描传感器，返回控制器详细信息; 注:使用该接口扫描设备需要关闭PC端防火墙，反则可能会扫描不到设备
 * @param infoList   返回扫描到的设备列表，存放控制器相关的详细信息
 * @param listNum    扫描到的设备个数
 * @return           返回错误码
 */
LCF_StatusTypeDef    LCF_ScanDeviceList_Detail(LCF_DeviceControlInfo_t** deviceList, uint32_t* deviceNumber);


/**
 * @brief LCF_ConnectDevice:连接控制器
 * @param controllerIp:  控制器IP，输入NULL则使用默认的通讯参数连接
 * @param controllerPort 控制器端口号，输入0或 IP输入NULL则使用默认的通讯参数连接
 * @param deviceHandler  返回设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef    LCF_ConnectDevice(IN char* controllerIp, IN uint16_t controllerPort, OUT int* deviceHandler);

/**
 * @brief LCF_CloseDevice 断开设备连接
 * @param handle          设备句柄
 */
void				 LCF_CloseDevice(IN int handle);

/**
 * @brief LCF_IsConnect 获取传感器的连接状态
 * @param handle        设备句柄
 * @return 返回连接状态
 */
bool				 LCF_IsConnect(IN int handle);

/**
 * @brief LCF_IsStart 获取传感器的采集状态
 * @param handle      设备句柄
 * @return            返回采集状态
 */
bool                 LCF_IsStart(int handle);

/**
 * @brief LCF_StartCapture 启动传感器测量
 * @param handle           设备句柄
 * @return  返回错误码
 */
LCF_StatusTypeDef	 LCF_StartCapture(IN int handle);

/**
 * @brief LCF_StopCapture 停止传感器测量
 * @param handle          设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef	 LCF_StopCapture(IN int handle);

/**
 * @brief LCF_RegisterEventCallback 注册事件回调函数
 * @param eventHandle               回调函数
 * @param userPara                  用户参数
 * @return 返回错误码
 */
LCF_StatusTypeDef	 LCF_RegisterEventCallback(IN LCF_UserEventCallbackHandle eventHandle, IN void* userPara);

/**
 * @brief LCF_UnregisterEventCallback 注销回调函数
 * @return 返回错误码
 */
LCF_StatusTypeDef	 LCF_UnregisterEventCallback();

/**
 * @brief LCF_SingleShot 单次采集一帧轮廓数据，需要先将传感器设置为软件触发模式、然后启动传感器测量再调用该接口
 * @param handle        设备句柄
 * @param result        返回轮廓数据
 * @return 返回错误码
 */
LCF_StatusTypeDef	 LCF_SingleShot(IN int handle, OUT LCF_Result_t* result);


/**
 * @brief LCF_GetErrorInfo 获取传感器错误描述信息
 * @param handle           设备句柄
 * @return 返回错误描述字符串
 */
const char*          LCF_GetErrorInfo(IN int handle);


/**
 * @brief LCF_Reboot    重启控制器
 * @param handle        设备句柄
 * @return              返回错误码
 */
LCF_StatusTypeDef    LCF_Reboot(IN int handle);



/**
 * @brief LCF_Shutdown  关闭控制器
 * @param handle        设备句柄
 * @return              返回错误码
 */
LCF_StatusTypeDef  LCF_Shutdown(int handle);

/**
 * @brief LCF_SetIntParameter 设置Int类型参数接口，
 * @param handle              设备句柄
 * @param paramName           参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value               设置的值
 * @return                    返回错误码
 */
LCF_StatusTypeDef   LCF_SetIntParameter(IN int handle, IN const char* paramName,IN int value);

/**
 * @brief LCF_SetFloatParameter 设置Float类型参数接口，
 * @param handle                设备句柄
 * @param paramName             参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value                 设置的值
 * @return                      返回错误码
 */
LCF_StatusTypeDef   LCF_SetFloatParameter(IN int handle,IN const char* paramName,IN float value);

/**
 * @brief LCF_SetDoubleParameter 设置Double类型参数接口，
 * @param handle                 设备句柄
 * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value                  设置的值
 * @return
 */
LCF_StatusTypeDef   LCF_SetDoubleParameter(IN int handle,IN const char* paramName,IN double value);

/**
 * @brief LCF_SetStringParameter 设置字符串类型参数接口
 * @param handle                 设备句柄
 * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value                  设置的值
 * @return
 */
LCF_StatusTypeDef   LCF_SetStringParameter(IN int handle, IN const char* paramName,IN char* value);

/**
 * @brief LCF_GetIntParameter 获取Int类型参数值的接口
 * @param handle              设备句柄
 * @param paramName           参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value               返回值
 * @return
 */
LCF_StatusTypeDef   LCF_GetIntParameter(IN int handle,IN const char* paramName,OUT int* value);

/**
 * @brief LCF_GetFloatParameter 获取Float类型参数值的接口
 * @param handle             设备句柄
 * @param paramName          参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value              返回值
 * @return
 */
LCF_StatusTypeDef   LCF_GetFloatParameter(IN int handle,IN const char* paramName,OUT float* value);

/**
 * @brief LCF_GetDoubleParameter 获取Double类型参数值的接口
 * @param handle                 设备句柄
 * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value                  返回值
 * @return
 */
LCF_StatusTypeDef   LCF_GetDoubleParameter(IN int handle,IN const char* paramName, OUT double* value);

/**
 * @brief LCF_GetStringParameter 获取字符串类型参数值的接口
 * @param handle                 设备句柄
 * @param paramName              参数名，包含的参数可以参考LCF_ParamterDefine.h文件
 * @param value                  返回值
 * @return
 */
LCF_StatusTypeDef    LCF_GetStringParameter(IN int handle,IN const char* paramName,OUT char* value);


/**
 * @brief LCF_GetDeviceSetting 获取传感器所有设置
 * @param handle        设备句柄
 * @param setting       返回传感器所有设置信息
 * @return 返回错误码
 */
LCF_StatusTypeDef    LCF_GetDeviceSetting(IN int handle, OUT LCF_DeviceSetting_t* setting);

/**
 * @brief LCF_SaveSetting 保存当前传感器设置到Flash中
 * @param handle          设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef   LCF_SaveSetting(IN int handle);


/**
 * @brief LCF_RestoreFactorySetting  恢复出厂设置
 * @param handle        设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef   LCF_RestoreFactorySetting(IN int handle);

/**
 * @brief LCF_ExportCacheData 导出控制器缓存的所有轮廓数据,可以通过PARAM_CACHE_CONTOUR_COUNT参数获取Cache里面轮廓个数
 * @param handle            设备句柄
 * @param result            深度数据
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_ExportCacheData(IN int handle, OUT LCF_Result_t* result);

/**
 * @brief LCF_ClearCacheData 清空缓存数据
 * @param handle             设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_ClearCacheData(IN int handle);

/**
 * @brief LCF_SetHDRIntensityGroup 设置某个HDR模式下，每一帧的光强值
 * @param handle        设备句柄
 * @param HDR_Mode      HDR模式
 * @param intenSity     每一帧的光强值，例:如果HDR_Mode为LCF_HDRMode_4，则该数组指定4帧数据的光强值
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_SetHDRIntensityGroup(IN int handle, IN LCF_HDRMode_t HDR_Mode,IN float intenSity[]);


/**
 * @brief LCF_SetHDRExposureGroup 设置某个HDR模式下，每一帧的曝光时间；
 *                                最小曝光时间不能小于当前配置下的最小帧周期，例:当前配置下传感器最大帧率为1000HZ，则HDR最小曝光时间不能小于1000us
 * @param handle        设备句柄
 * @param HDR_Mode      HDR模式
 * @param exposure      每一帧的曝光时间，例:如果HDR_Mode为LCF_HDRMode_4，则该数组指定4帧数据的曝光时间
 * @return 返回错误码
 */
LCF_StatusTypeDef	LCF_SetHDRExposureGroup(IN int handle, IN LCF_HDRMode_t HDR_Mode,IN int exposure[]);


/**
 * @brief LCF_GetDeviceStatisticInfo  获取设备统计信息
 * @param handle                      设备句柄
 * @param info                        返回设备统计信息
 * @return 返回错误码
 */
LCF_StatusTypeDef   LCF_GetDeviceStatisticInfo(IN int handle,OUT LCF_DeviceStatisticInfo_t*info);

/**
 * @brief LCF_ReadSensorHeadFactoryPara 读取传感器出厂参数
 * @param handle        设备句柄
 * @param para          返回传感器出参数
 * @return 返回错误码
 */
LCF_StatusTypeDef   LCF_ReadSensorHeadFactoryPara(IN int handle, OUT LCF_SensorHeadFactoryPara_t* para);


/**
 * @brief LCF_ClearEncoderTriggerCount   清除编码器计数值，控制器编码器计数从0开始，计数到用户设定的分频值后触发传感器采集
 * @param handle                         设备句柄
 * @return 返回错误码
 */
LCF_StatusTypeDef  LCF_ClearEncoderTriggerCount(IN int handle);

/**
 * @brief LCF_ExportDeviceSetting 导出设备配置信息到文件中
 * @param handle                  设备句柄
 * @param path                    导出路径
 * @return 返回错误码
 */
LCF_StatusTypeDef  LCF_ExportDeviceSetting(IN int handle,IN char*path);

/**
 * @brief LCF_ImportDeviceSetting 导入设备配置文件
 * @param handle                  设备句柄
 * @param fileName                文件路径名
 * @return 返回错误码
 */
LCF_StatusTypeDef  LCF_ImportDeviceSetting(IN int handle,IN char*fileName);


/**
 * @brief LCF_AdjustRoiForFps 设置传感器帧率，如果当前分辨率无法满足用户指定帧率，则自动适配合适的ROI分辨率，适应指定的帧率并返回该设定下的Z轴量程
 * @param handle              设备句柄
 * @param mode                适配模式
 * @param frameRate           指定帧率
 * @param Z_Range             返回适配成功后的Z轴理论量程，单位um
 * @return 返回错误码
 */
LCF_StatusTypeDef  LCF_AdjustRoiForFps(IN int handle, IN LCF_AdjustRoiFpsPara_t mode, IN int frameRate, OUT float *Z_Range);


/**
 * @brief LCF_SetMeasureRange 设置传感器量程，例：LCF1000传感器量程为 +-1600um，可以设置的远端范围最小为-1600，近端最大范围为1600
 * @param handle              设备句柄
 * @param farRange_um         远端测量范围,单位um
 * @param nearRange_um        近端测量范围,单位um
 * @return  返回错误码
 */
LCF_StatusTypeDef  LCF_SetMeasureRange(IN int handle, IN int farRange_um,IN int nearRange_um);


/**
 * @brief LCF_SetIOPortFunc  设置控制器IO引脚(IN0、IN1、OUT0、OUT1)的功能
 * @param handle             设备句柄
 * @param io_port            IO引脚
 * @param triggerMode        IO引脚的触发方式
 * @param io_func            IO引脚绑定的功能
 * @return 返回错误码
 */
LCF_StatusTypeDef   LCF_SetIOPortFunc(IN int handle,IN LCF_IO_Port_t io_port, IN LCF_IO_TriggerMode_t triggerMode, IN LCF_IO_Func_t io_func);


/**
 * @brief LCF_FindGoodLight 根据当前测量位置，查找合适的光强
 * @param handle            设备句柄
 * @param enHDR             是否在HDR模式下查找，0:不使用HDR 1:使用HDR
 * @return                  返回错误码
 */
LCF_StatusTypeDef   LCF_FindGoodLight(IN int handle,IN int enHDR);



/**
 * @brief LCF_SetEncoderDyncDivValue 设置动态编码器分频模式下，每个位置的分频值；用户可以根据编码器脉冲个数设定几个不同的分频值。
 * @param handle            设备句柄
 * @param encoderPos        编码器脉冲个数，第一个位置固定为0；
 *                          例:encoderPos[0]=0,division[0]=16,在起始位置使用16分频，encoderPos[1]=2000,division[0]=4,达到2000个编码器脉冲后切换为4分频
 * @param division          不同位置编码器分频值
 * @param real_div          返回实际的分频
 * @param group_member      分频组数
 * @return                  返回错误码
 */
LCF_StatusTypeDef       LCF_SetEncoderDyncDivValue(int handle,int encoderPos[], int division[], int real_div[], int group_member);



/**
 * @brief LCF_SetControllerParam 通过广播命令设置控制器参数，该接口不受SDK连接状态影响，在SDK未连接控制器前依旧可以调用;
 *                               为了使控制器能够接收到广播命令，需要将本地防火墙关闭。
 * @param controlerSN   通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
 * @param paramName     参数名，包含的参数可以参考LCF_ParamterDefine.h文件PARAM_CTRL_XXXX类型的控制参数
 * @param value         设置的数据
 * @return  返回错误码
 */
LCF_StatusTypeDef       LCF_SetControllerParam(const char *controlerSN, const char *paramName, uint8_t *value);


/**
 * @brief LCF_SetControllerParam 通过广播命令获取控制器参数，该接口不受SDK连接状态影响，在SDK未连接控制器前依旧可以调用;
 *                               为了使控制器能够接收到广播命令，需要将本地防火墙关闭。
 * @param controlerSN   通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
 * @param paramName     参数名，包含的参数可以参考LCF_ParamterDefine.h文件PARAM_CTRL_XXXX类型的控制参数
 * @param value         设置的数据
 * @return  返回错误码
 */
LCF_StatusTypeDef       LCF_GetControllerParam(const char *controlerSN, const char *paramName, uint8_t *value);



/**
 * @brief LCF_ForceIP  临时修改控制器IP参数,用户可以根据本地网口的网段，将控制器IP设置在同一网段下;控制器重新启动后IP恢复为初始值;需要永久修改控制器IP可以使用LCF_SetEthParam接口或连接上控制器后,使用PARAM_IP_ADDR参数进行修改
 * @param controlerSN  通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
 * @param ip            控制器IP
 * @param gateway       控制器网关
 * @param netmask       控制器子网掩码
 * @return
 */
LCF_StatusTypeDef       LCF_ForceIP(const char*controlerSN,const char*ip,const char*gateway,const char*netmask);


/**
 * @brief LCF_ForceIP   永久修改控制器IP参数，修改完成后重启控制器后生效
 * @param controlerSN   通过LCF_ScanDeviceList_Detail 扫描到的控制器序列号
 * @param ip            控制器IP
 * @param gateway       控制器网关
 * @param netmask       控制器子网掩码
 * @return
 */
LCF_StatusTypeDef       LCF_SetEthParam(const char*controlerSN,const char*ip,const char*gateway,const char*netmask);


/**
 * @brief LCF_WriteUserFlashData 用户自定义数据写入传感头内部Flash
 * @param handle        设备句柄
 * @param data          写入数据
 * @param len           数据长度,单位字节
 * @return
 */
LCF_StatusTypeDef       LCF_WriteUserFlashData(int handle, uint8_t*data,int len);

/**
 * @brief LCF_ReadUserFlashData 读取传感头内部Flash用户写入的数据
 * @param handle         设备句柄
 * @param data           返回用户数据
 * @param len           返回数据长度,单位字节。如果Flash没被写入过数据则返回数据长度为0
 * @return
 */
LCF_StatusTypeDef       LCF_ReadUserFlashData(int handle, uint8_t*data, int *len);



#ifdef __cplusplus
}
#endif

#endif
