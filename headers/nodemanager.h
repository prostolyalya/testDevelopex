#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <QObject>

#include "uicontroller.h"
#include "threads_manager.h"
#include "searcher.h"
#include "url_node.h"

class NodeManager : public QObject
{
    Q_OBJECT

    UiController *uiController;
    ThreadsManager *threadsManager;
    Searcher *searcher;

public:
    NodeManager(QObject *parent = nullptr);
    ~NodeManager();

    UiController *getUiController() const;
};

#endif // NODEMANAGER_H
