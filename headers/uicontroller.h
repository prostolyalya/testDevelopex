#ifndef UICONTROLLER_H
#define UICONTROLLER_H
#include <QObject>

#include "headers/resultpage.h"
#include "headers/startpage.h"

class UiController : public QObject
{
    Q_OBJECT

public:
    UiController(QObject *parent = nullptr);
    UiController(const UiController &uiController);
    ~UiController();

    StartPage *getStartPage() const;
    ResultPage *getResultPage() const;

private:
    StartPage *startPage;
    ResultPage *resultPage;

    int countRes = 0;
    int countUrl = 0;

public slots:
    void receiveResponse(const QByteArrayList &list, const QByteArray &url);
    void receiveEnded();
    void clearRes();
    void stopSearch();
    void process();

signals:
    void startSearch(const QString &text, const QString &url, const int &countThreads, const int &deepSearch);
    void stoppSearch();
    void finished();
};

#endif // UICONTROLLER_H
