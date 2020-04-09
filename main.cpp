#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "headers/nodemanager.h"

Q_DECLARE_METATYPE(StartPage)
Q_DECLARE_METATYPE(ResultPage)

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qRegisterMetaType<StartPage>();
    qRegisterMetaType<ResultPage>();
    qmlRegisterType<StartPage>("StartPage", 1, 0, "StartData");
    qmlRegisterType<ResultPage>("ResultPage", 1, 0, "ResultData");
    NodeManager *nodeManager = new NodeManager;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("startData", nodeManager->getUiController()->getStartPage());
    engine.rootContext()->setContextProperty("resultData", nodeManager->getUiController()->getResultPage());

    engine.load(url);

    return app.exec();
}
