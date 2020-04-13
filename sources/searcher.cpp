#include "headers/searcher.h"

void Searcher::setThreadsManager(ThreadsManager *value)
{
    threadsManager = value;
}

Searcher::Searcher(QObject *parent)
    : QObject(parent)
{
}

Searcher::~Searcher()
{
    emit finished();
}

void Searcher::startSearch(const QString &text, const QString &url, const int &countThreads,
                           const int &deepSearch)
{
    if (!queuedList.isEmpty())
        return;
    stop = false;
    this->checkStop = 0;
    this->deepSearch = deepSearch;
    this->textSearch = text.toUtf8();
    this->countThread = countThreads + 2;
    rootUrlNode = new UrlNode(url);
    connect(rootUrlNode, &UrlNode::continueSearch, this, &Searcher::queuedSearch);
    threadsManager->addThread(rootUrlNode);
    rootUrlNode->startSearch(textSearch);
}

void Searcher::queuedSearch()
{
    UrlNode *node = reinterpret_cast<UrlNode *>(QObject::sender());
    QByteArrayList res = node->findData;
    emit responseFindText(res, node->url.toUtf8());
    if (node->gen < deepSearch)
        for (const auto &tmpNode : node->children)
        {
            connect(tmpNode, &UrlNode::continueSearch, this, &Searcher::queuedSearch, Qt::QueuedConnection);
            queuedList.enqueue(tmpNode);
        }
    searchProcess(node);
}

void Searcher::stopSearch()
{
    setStop(true);
}

void Searcher::process()
{
}

void Searcher::setStop(bool value)
{
    stop = value;
}

void Searcher::searchProcess(UrlNode *node)
{
    if (queuedList.isEmpty() || stop)
    {
        if (++checkStop == countThread - 2)
            endSearch();
        return;
    }
    UrlNode *fromQueue = queuedList.dequeue();
    if (!stop)
    {
        QThread *thread = node->thread();
        threadsManager->toThread(fromQueue, thread);
        fromQueue->startSearch(textSearch);
        while (threadsManager->getThreadsListSize() < countThread && queuedList.size() > 0)
        {
            fromQueue = queuedList.dequeue();
            threadsManager->addThread(fromQueue);
            fromQueue->startSearch(textSearch);
        }
    }
}

void Searcher::endSearch()
{
    emit endFindText();
    queuedList.clear();
    delete rootUrlNode;
    threadsManager->clearThreads();

    qDebug() << "end search";
}
