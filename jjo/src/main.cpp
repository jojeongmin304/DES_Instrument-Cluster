#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread> // Include QThread
#include "speedprovider.h"
#include "cangatewayclient.h" // Include our new client

// --- Main Function ---
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 1. Create the worker objects
    QThread *thread = new QThread();
    CanGatewayClient *canClient = new CanGatewayClient();
    SpeedProvider speedProvider;

    // 2. Move the CAN client to the background thread
    canClient->moveToThread(thread);

    // 3. Connect signals and slots across threads
    //    Start the client's process() loop when the thread starts.
    QObject::connect(thread, &QThread::started, canClient, &CanGatewayClient::process);
    //    Handle the finished signal to quit the thread.
    QObject::connect(canClient, &CanGatewayClient::finished, thread, &QThread::quit);
    //    Clean up when finished.
    QObject::connect(canClient, &CanGatewayClient::finished, canClient, &CanGatewayClient::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    //    *** THE CRUCIAL CONNECTION ***
    //    Connect the client's message signal to the provider's update slot.
    QObject::connect(canClient, &CanGatewayClient::messageReceived, &speedProvider, &SpeedProvider::onMessageReceived);
    
    //    Optionally, connect the error signal to a lambda for logging.
    QObject::connect(canClient, &CanGatewayClient::errorOccurred, [](const QString &errorString){
        qCritical() << "CAN Client Error:" << errorString;
    });

    // 4. Expose the SpeedProvider to QML
    engine.rootContext()->setContextProperty("speedController", &speedProvider);

    // 5. Start the background thread
    thread->start();

    // Standard QML setup
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    // When the application is about to quit, make sure our thread is stopped.
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&](){
        if(thread->isRunning()){
            thread->quit();
            thread->wait(); // Wait for the thread to finish cleanly
        }
    });

    return app.exec();
}

// Don't forget to include the MOC file if you are not using a build system like CMake/qmake
// #include "main.moc" // May not be needed with qmake/CMake

// Don't forget to include the MOC file if you are not using a build system like CMake/qmake
// #include "main.moc" // May not be needed with qmake/CMake

// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <QQmlContext>
// #include <QTimer>
// #include <QObject>
// #include "speedprovider.h"

// // --- 메인 함수 ---
// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;

//     // 1. SpeedProvider 객체를 생성합니다.
//     SpeedProvider speedProvider;
//     // 2. "speedController"라는 이름으로 QML 환경에 노출시킵니다. ****중요!!!!!!!!!!
//     engine.rootContext()->setContextProperty("speedController", &speedProvider);

//     // Main.qml 파일을 로드합니다.
//     const QUrl url(QStringLiteral("qrc:/Main.qml"));
//     QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                      &app, [url](QObject *obj, const QUrl &objUrl) {
//                          if (!obj && url == objUrl)
//                              QCoreApplication::exit(-1);
//                      }, Qt::QueuedConnection);
//     engine.load(url);

//     return app.exec();
// }

// #include "main.moc"







