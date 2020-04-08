#include "headers/nodemanager.h"

UiController *NodeManager::getUiController() const
{
    return uiController;
}

NodeManager::NodeManager(QObject *parent)
    : QObject(parent)
{
    uiController = new UiController();
    threadsManager = new ThreadsManager();
    searcher = new Searcher();
    searcher->setThreadsManager(threadsManager);
    threadsManager->addThread(searcher);
    threadsManager->addThread(uiController);
    connect(uiController, &UiController::startSearch, searcher, &Searcher::startSearch);
    connect(searcher, &Searcher::responseFindText, uiController, &UiController::receiveResponse,
            Qt::QueuedConnection);
    connect(searcher, &Searcher::endFindText, uiController, &UiController::receiveEnded);
    connect(uiController, &UiController::stoppSearch, searcher, &Searcher::stopSearch);
}

NodeManager::~NodeManager()
{
    disconnect(uiController, &UiController::startSearch, searcher, &Searcher::startSearch);
    disconnect(searcher, &Searcher::responseFindText, uiController, &UiController::receiveResponse);
    disconnect(searcher, &Searcher::endFindText, uiController, &UiController::receiveEnded);
    disconnect(uiController, &UiController::stoppSearch, searcher, &Searcher::stopSearch);
    delete uiController;
    delete threadsManager;
    delete searcher;
}
