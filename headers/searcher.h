#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QQueue>

#include "threads_manager.h"
#include "url_node.h"

class Searcher : public QObject
{
    Q_OBJECT

    ThreadsManager *threadsManager;
    UrlNode *rootUrlNode;

    QByteArray textSearch;
    int countThread = 0;
    int deepSearch = 0;
    QQueue<UrlNode *> queuedList;
    int checkStop;

public:
    Searcher(QObject *parent = nullptr);
    ~Searcher();

    void setThreadsManager(ThreadsManager *value);
    void searchProcess(UrlNode *node);

    void setStop(bool value);

public slots:
    void startSearch(const QString &text, const QString &url, const int &countThreads, const int &deepSearch);
    void queuedSearch();
    void stopSearch();
    void process();

signals:
    void responseFindText(const QByteArrayList &list, const QByteArray &url);
    void endFindText();
    void finished();

private:
    void endSearch();

    bool stop = false;
};

#endif // SEARCHER_H
