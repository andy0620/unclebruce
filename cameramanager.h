#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include <QString>

// Forward declaration of the SDK's C-style handle
// We don't need to include the full SDK header here, which is good practice.
// typedef int LCF_StatusTypeDef;

class CameraManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusChanged)

public:
    explicit CameraManager(QObject *parent = nullptr);
    ~CameraManager();

    bool isConnected() const;
    QString statusMessage() const;

public slots:
    void connectDevice(const QString &ip = "192.168.1.188", int port = 58080);
    void disconnectDevice();
    void startCapture();
    void stopCapture();
    void setExposure(int exposureTime);
    void findGoodLight();

signals:
    void connectedChanged(bool isConnected);
    void statusChanged(const QString &status);
    void errorOccurred(const QString &errorMessage);
    // We can later add a signal to send image data to QML
    // void newImageData(const QImage &image);

private:
    // Callback function needs to be static to be passed to the C library
    static void staticCallback(int handle, void* arg, void* userPara);
    void processCallback(int handle, void* arg);

    int m_handle = -1;
    bool m_isConnected = false;
    QString m_statusMessage = "Disconnected";
};

#endif // CAMERAMANAGER_H
