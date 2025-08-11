#include "cameramanager.h"
#include "hypersen_sdk/LCF_UserInterface.h"
#include "hypersen_sdk/LCF_ParameterDefine.h"
#include <QDebug>
#include <QThread>

// --- Static Callback Implementation ---
// The SDK requires a C-style static or global function for its callback.
// This function will act as a bridge, forwarding the callback to the specific CameraManager instance.
void CameraManager::staticCallback(int handle, void* arg, void* userPara)
{
    if (userPara) {
        CameraManager* instance = static_cast<CameraManager*>(userPara);
        // It's good practice to handle callbacks in the main Qt thread if they update UI.
        // However, for now, we will process it directly, keeping it simple.
        instance->processCallback(handle, arg);
    }
}

CameraManager::CameraManager(QObject *parent) : QObject(parent)
{
    qDebug() << "CameraManager created.";
    // Register the event callback, passing `this` as the user parameter
    LCF_StatusTypeDef ret = LCF_RegisterEventCallback(CameraManager::staticCallback, this);
    if (ret != LCF_Status_Succeed) {
        qWarning() << "Failed to register camera callback. Error code:" << ret;
    }
}

CameraManager::~CameraManager()
{
    if (m_isConnected) {
        disconnectDevice();
    }
    LCF_UnregisterEventCallback();
    qDebug() << "CameraManager destroyed.";
}

bool CameraManager::isConnected() const
{
    return m_isConnected;
}

QString CameraManager::statusMessage() const
{
    return m_statusMessage;
}

void CameraManager::connectDevice(const QString &ip, int port)
{
    if (m_isConnected) {
        m_statusMessage = "Already connected.";
        emit statusChanged(m_statusMessage);
        return;
    }

    qDebug() << "Attempting to connect to camera at" << ip << ":" << port;

    // The SDK expects a char*, so we need to convert the QString.
    QByteArray ipArray = ip.toLocal8Bit();
    char* controllerIp = ipArray.data();

    LCF_StatusTypeDef ret = LCF_ConnectDevice(controllerIp, static_cast<uint16_t>(port), &m_handle);

    if (ret == LCF_Status_Succeed) {
        m_isConnected = true;
        m_statusMessage = "Camera Connected";
        qDebug() << m_statusMessage;
    } else {
        m_isConnected = false;
        const char* error_info = LCF_GetErrorInfo(m_handle);
        m_statusMessage = QString("Connection Failed: %1").arg(error_info);
        qWarning() << m_statusMessage;
        emit errorOccurred(m_statusMessage);
    }

    emit connectedChanged(m_isConnected);
    emit statusChanged(m_statusMessage);
}

void CameraManager::disconnectDevice()
{
    if (!m_isConnected) {
        return;
    }
    qDebug() << "Disconnecting camera.";
    LCF_CloseDevice(m_handle);
    m_isConnected = false;
    m_handle = -1;
    m_statusMessage = "Disconnected";

    emit connectedChanged(m_isConnected);
    emit statusChanged(m_statusMessage);
}

void CameraManager::startCapture()
{
    if (!m_isConnected) {
        m_statusMessage = "Cannot start: Not connected.";
        emit statusChanged(m_statusMessage);
        emit errorOccurred(m_statusMessage);
        return;
    }

    qDebug() << "Starting camera capture.";
    LCF_StatusTypeDef ret = LCF_StartCapture(m_handle);
    if (ret == LCF_Status_Succeed) {
        m_statusMessage = "Capture Started";
    } else {
        const char* error_info = LCF_GetErrorInfo(m_handle);
        m_statusMessage = QString("Start Capture Failed: %1").arg(error_info);
        emit errorOccurred(m_statusMessage);
    }
    qDebug() << m_statusMessage;
    emit statusChanged(m_statusMessage);
}

void CameraManager::stopCapture()
{
    if (!m_isConnected) {
        m_statusMessage = "Cannot stop: Not connected.";
        emit statusChanged(m_statusMessage);
        emit errorOccurred(m_statusMessage);
        return;
    }

    qDebug() << "Stopping camera capture.";
    LCF_StatusTypeDef ret = LCF_StopCapture(m_handle);
    if (ret == LCF_Status_Succeed) {
        m_statusMessage = "Capture Stopped";
    } else {
        const char* error_info = LCF_GetErrorInfo(m_handle);
        m_statusMessage = QString("Stop Capture Failed: %1").arg(error_info);
        emit errorOccurred(m_statusMessage);
    }
    qDebug() << m_statusMessage;
    emit statusChanged(m_statusMessage);
}

void CameraManager::setExposure(int exposureTime)
{
    if (!m_isConnected) {
        emit errorOccurred("Cannot set exposure: Not connected.");
        return;
    }

    qDebug() << "Setting exposure to" << exposureTime;
    LCF_StatusTypeDef ret = LCF_SetIntParameter(m_handle, PARAM_EXPOSURE_TIME, exposureTime);
    if (ret != LCF_Status_Succeed) {
        const char* error_info = LCF_GetErrorInfo(m_handle);
        QString msg = QString("Failed to set exposure: %1").arg(error_info);
        qWarning() << msg;
        emit errorOccurred(msg);
    } else {
        m_statusMessage = QString("Exposure set to %1 us").arg(exposureTime);
        emit statusChanged(m_statusMessage);
    }
}

void CameraManager::findGoodLight()
{
    if (!m_isConnected) {
        emit errorOccurred("Cannot find good light: Not connected.");
        return;
    }
    qDebug() << "Finding good light setting...";
    m_statusMessage = "Finding good light...";
    emit statusChanged(m_statusMessage);

    // This can be a long-running operation.
    // In a real app, this should be run in a separate thread.
    LCF_StatusTypeDef ret = LCF_FindGoodLight(m_handle, 0); // 0 = not in HDR mode
    if (ret != LCF_Status_Succeed) {
        const char* error_info = LCF_GetErrorInfo(m_handle);
        QString msg = QString("Find good light failed: %1").arg(error_info);
        qWarning() << msg;
        emit errorOccurred(msg);
    } else {
        m_statusMessage = "Find good light completed.";
        emit statusChanged(m_statusMessage);
    }
}


// --- Private Methods ---

void CameraManager::processCallback(int handle, void* arg)
{
    if (handle != m_handle) return;

    LCF_EventCallbackArgs_t* cb_arg = static_cast<LCF_EventCallbackArgs_t*>(arg);

    if (cb_arg->eventType == LCF_EventType_Disconnect) {
        qWarning() << "Camera disconnected by event!";
        m_isConnected = false;
        m_handle = -1;
        m_statusMessage = "Disconnected (Event)";

        // Ensure signals are emitted from the main thread if this callback is on another thread
        QMetaObject::invokeMethod(this, [this](){
            emit connectedChanged(m_isConnected);
            emit statusChanged(m_statusMessage);
        }, Qt::QueuedConnection);

    } else if (cb_arg->eventType == LCF_EventType_DataRecv) {
        // Handle data reception
        if (cb_arg->rid == LCF_RID_RESULT) {
            // A new profile/image has been received.
            // In a real application, we would copy the data from cb_arg->data
            // and emit a signal to the UI thread for display.
            // For now, we just log it.
            // Note: This can be very frequent!
        }
    }
}
