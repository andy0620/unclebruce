#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "cameramanager.h"
#include "motionmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // --- Backend Registration ---
    // Create backend objects
    CameraManager cameraManager;
    MotionManager motionManager;

    // Expose C++ objects to QML
    engine.rootContext()->setContextProperty("cameraManager", &cameraManager);
    engine.rootContext()->setContextProperty("motionManager", &motionManager);

    // --- Load QML ---
    // For development, we load from a file directly.
    // For deployment, a Qt Resource file (qrc) is typically used.
    const QUrl url(QStringLiteral("main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
