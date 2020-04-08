#include "headers/startpage.h"

StartPage::StartPage(QObject *parent)
    : QObject(parent)
{
}

StartPage::StartPage(const StartPage &stPage)
{
    Q_UNUSED(stPage)
}

void StartPage::search(const QString &text, const QString &url, const int &countThreads,
                       const int &deepSearch)
{
    emit startSearch(text, url, countThreads, deepSearch);
    emit clearResult();
}
