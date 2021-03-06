#ifndef THREADSMANAGER_H
#define THREADSMANAGER_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "url_node.h"

class ThreadsManager : public QObject
{
    Q_OBJECT

public:
    ThreadsManager(QObject *parent = nullptr);
    ~ThreadsManager();

    void addThread(QObject *worker);
    int getThreadsListSize();
    void toThread(QObject *worker, QThread *thread);
    void clearThreads();

private:
    QList<QThread *> threadsList;

public slots:
    void removeThread();

signals:
    void finished();
};

#endif // THREADSMANAGER_H
