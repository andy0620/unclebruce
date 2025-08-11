#include "motionmanager.h"
#include "zmotion_sdk/zauxdll2.h"
#include <QDebug>

MotionManager::MotionManager(QObject *parent)
    : QObject(parent), m_positionUpdateTimer(new QTimer(this))
{
    qDebug() << "MotionManager created.";

    // Setup a timer to periodically poll for the axis position
    connect(m_positionUpdateTimer, &QTimer::timeout, this, &MotionManager::updatePosition);
}

MotionManager::~MotionManager()
{
    if (m_isConnected) {
        disconnectDevice();
    }
    qDebug() << "MotionManager destroyed.";
}

bool MotionManager::isConnected() const
{
    return m_isConnected;
}

double MotionManager::currentPosition() const
{
    return m_currentPosition;
}

QString MotionManager::statusMessage() const
{
    return m_statusMessage;
}

void MotionManager::connectDevice(const QString &ip)
{
    if (m_isConnected) {
        m_statusMessage = "Already connected.";
        emit statusChanged(m_statusMessage);
        return;
    }

    qDebug() << "Attempting to connect to motion controller at" << ip;

    QByteArray ipArray = ip.toLocal8Bit();
    char* controllerIp = ipArray.data();

    // ZAux_OpenEth returns 0 on success
    int ret = ZAux_OpenEth(controllerIp, &m_handle);

    if (ret == 0 && m_handle != nullptr) {
        m_isConnected = true;
        m_statusMessage = "Motion Controller Connected";
        qDebug() << m_statusMessage;
        // Start polling for position
        m_positionUpdateTimer->start(100); // Poll every 100ms
    } else {
        m_isConnected = false;
        m_statusMessage = QString("Motion Connection Failed. Code: %1").arg(ret);
        qWarning() << m_statusMessage;
        emit errorOccurred(m_statusMessage);
    }

    emit connectedChanged(m_isConnected);
    emit statusChanged(m_statusMessage);
}

void MotionManager::disconnectDevice()
{
    if (!m_isConnected) {
        return;
    }
    m_positionUpdateTimer->stop();
    qDebug() << "Disconnecting motion controller.";
    ZAux_Close(m_handle);
    m_isConnected = false;
    m_handle = nullptr;
    m_statusMessage = "Disconnected";

    emit connectedChanged(m_isConnected);
    emit statusChanged(m_statusMessage);
}

void MotionManager::enableAxis(int axis)
{
    if (!m_isConnected) return;
    // For many controllers, ATYPE must be set before other params.
    // This is a typical initialization sequence.
    ZAux_Direct_SetAtype(m_handle, axis, 1); // 1 = Pulse
    ZAux_Direct_SetUnits(m_handle, axis, 100); // 100 pulses per unit
    ZAux_Direct_SetSpeed(m_handle, axis, 1000);
    ZAux_Direct_SetAccel(m_handle, axis, 10000);
    ZAux_Direct_SetDecel(m_handle, axis, 10000);

    m_statusMessage = QString("Axis %1 configured and enabled.").arg(axis);
    emit statusChanged(m_statusMessage);
}

void MotionManager::disableAxis(int axis)
{
    if (!m_isConnected) return;
    // Set axis type to 0 to disable
    ZAux_Direct_SetAtype(m_handle, axis, 0);
    m_statusMessage = QString("Axis %1 disabled.").arg(axis);
    emit statusChanged(m_statusMessage);
}

void MotionManager::moveAbsolute(int axis, double position)
{
    if (!m_isConnected) {
        emit errorOccurred("Cannot move: Not connected.");
        return;
    }
    qDebug() << "Moving axis" << axis << "to position" << position;
    int ret = ZAux_Direct_Single_MoveAbs(m_handle, axis, static_cast<float>(position));
    if (ret != 0) {
        QString msg = QString("MoveAbsolute failed. Code: %1").arg(ret);
        qWarning() << msg;
        emit errorOccurred(msg);
    } else {
        m_statusMessage = QString("Moving axis %1 to %2").arg(axis).arg(position);
        emit statusChanged(m_statusMessage);
    }
}

void MotionManager::jog(int axis, int direction)
{
    if (!m_isConnected) {
        emit errorOccurred("Cannot jog: Not connected.");
        return;
    }
    qDebug() << "Jogging axis" << axis << "in direction" << direction;
    // VMOVE (velocity move) is used for jogging. Direction is 1 or -1.
    int ret = ZAux_Direct_Single_Vmove(m_handle, axis, direction);
     if (ret != 0) {
        QString msg = QString("Jog failed. Code: %1").arg(ret);
        qWarning() << msg;
        emit errorOccurred(msg);
    } else {
        m_statusMessage = QString("Jogging axis %1").arg(axis);
        emit statusChanged(m_statusMessage);
    }
}

void MotionManager::stop(int axis)
{
    if (!m_isConnected) {
        emit errorOccurred("Cannot stop: Not connected.");
        return;
    }
    qDebug() << "Stopping axis" << axis;
    // Mode 3 is rapid stop
    int ret = ZAux_Direct_Single_Cancel(m_handle, axis, 3);
    if (ret != 0) {
        QString msg = QString("Stop failed. Code: %1").arg(ret);
        qWarning() << msg;
        emit errorOccurred(msg);
    } else {
        m_statusMessage = QString("Axis %1 stopped.").arg(axis);
        emit statusChanged(m_statusMessage);
    }
}

void MotionManager::setSpeed(int axis, double speed)
{
    if (!m_isConnected) {
        emit errorOccurred("Cannot set speed: Not connected.");
        return;
    }
    qDebug() << "Setting speed for axis" << axis << "to" << speed;
    int ret = ZAux_Direct_SetSpeed(m_handle, axis, static_cast<float>(speed));
    if (ret != 0) {
        QString msg = QString("Set speed failed. Code: %1").arg(ret);
        qWarning() << msg;
        emit errorOccurred(msg);
    }
}

void MotionManager::setUnits(int axis, double units)
{
    if (!m_isConnected) {
        emit errorOccurred("Cannot set units: Not connected.");
        return;
    }
    qDebug() << "Setting units for axis" << axis << "to" << units;
    int ret = ZAux_Direct_SetUnits(m_handle, axis, static_cast<float>(units));
    if (ret != 0) {
        QString msg = QString("Set units failed. Code: %1").arg(ret);
        qWarning() << msg;
        emit errorOccurred(msg);
    }
}

void MotionManager::updatePosition()
{
    if (!m_isConnected) {
        return;
    }

    float current_pos_float = 0.0f;
    // We poll axis 0 for this example
    int ret = ZAux_Direct_GetDpos(m_handle, 0, &current_pos_float);

    if (ret == 0) {
        double new_pos = static_cast<double>(current_pos_float);
        if (qAbs(new_pos - m_currentPosition) > 1e-3) { // Check for significant change
            m_currentPosition = new_pos;
            emit positionChanged(m_currentPosition);
        }
    } else {
        // Stop polling if we get an error
        m_positionUpdateTimer->stop();
        QString msg = QString("Failed to get position. Polling stopped. Code: %1").arg(ret);
        qWarning() << msg;
        emit errorOccurred(msg);
    }
}
