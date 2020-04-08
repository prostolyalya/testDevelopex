#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QMetaType>
#include <QtQuickControls2>

#include "headers/nodemanager.h"
#include "headers/url_node.h"

Q_DECLARE_METATYPE(StartPage)
Q_DECLARE_METATYPE(UrlNode *)

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qRegisterMetaType<StartPage>();
    qRegisterMetaType<UrlNode *>();
    qmlRegisterType<StartPage>("StartPage", 1, 0, "StartData");
    qmlRegisterType<StartPage>("ResultPage", 1, 0, "ResultData");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

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
    //    QByteArray data = nodeManager->downloaderPage->downloadData("https://www.google.com/");
    //    qDebug() << nodeManager->downloaderPage->searchUrl(data);

    engine.load(url);

    return app.exec();
}
