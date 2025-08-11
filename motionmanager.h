#ifndef MOTIONMANAGER_H
#define MOTIONMANAGER_H

#include <QObject>
#include <QString>
#include <QTimer>

// Forward declaration for the Zmotion handle
typedef void* ZMC_HANDLE;

class MotionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(double currentPosition READ currentPosition NOTIFY positionChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusChanged)

public:
    explicit MotionManager(QObject *parent = nullptr);
    ~MotionManager();

    bool isConnected() const;
    double currentPosition() const;
    QString statusMessage() const;

public slots:
    void connectDevice(const QString &ip = "192.168.0.11");
    void disconnectDevice();

    // Motion commands for a single axis (axis 0)
    void enableAxis(int axis = 0);
    void disableAxis(int axis = 0);
    void moveAbsolute(int axis, double position);
    void jog(int axis, int direction); // 1 for fwd, -1 for rev
    void stop(int axis);
    void setSpeed(int axis, double speed);
    void setUnits(int axis, double units); // Set pulse equivalent

signals:
    void connectedChanged(bool isConnected);
    void positionChanged(double currentPosition);
    void statusChanged(const QString &status);
    void errorOccurred(const QString &errorMessage);

private slots:
    void updatePosition();

private:
    ZMC_HANDLE m_handle = nullptr;
    bool m_isConnected = false;
    double m_currentPosition = 0.0;
    QString m_statusMessage = "Disconnected";
    QTimer *m_positionUpdateTimer;
};

#endif // MOTIONMANAGER_H
