#include "headers/threads_manager.h"

ThreadsManager::ThreadsManager(QObject *parent)
    : QObject(parent)
{
}

ThreadsManager::~ThreadsManager()
{
    std::for_each(threadsList.begin(), threadsList.end(), [](QThread *el) { el->quit(); });
}

void ThreadsManager::addThread(QObject *worker)
{
    QThread *thread = new QThread();

    QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
    QObject::connect(worker, SIGNAL(finished()), this, SLOT(removeThread()));
    QObject::connect(thread, SIGNAL(finished()), this, SLOT(removeThread()));
    worker->moveToThread(thread);
    threadsList << thread;
    thread->start();
    return;
}

int ThreadsManager::getThreadsListSize()
{
    return threadsList.size();
}

void ThreadsManager::toThread(QObject *worker, QThread *thread)
{
    worker->moveToThread(thread);
}

void ThreadsManager::clearThreads()
{
    while (threadsList.size() != 2)
    {
        QThread *thread = threadsList.takeLast();
        thread->quit();
    }
}

void ThreadsManager::removeThread()
{
    QObject *object = QObject::sender();
    QThread *remThread = reinterpret_cast<QThread *>(object);
    if (remThread)
    {
        threadsList.removeOne(remThread);
    }
}
