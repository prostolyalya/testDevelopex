#include "headers/resultpage.h"

ResultPage::ResultPage(QObject *parent)
    : QObject(parent)
{
}

void ResultPage::stop()
{
    emit stopSearch();
}

QString ResultPage::res()
{
    return Res;
}

void ResultPage::setRes(const QString &value)
{
    Res = value;
}

void ResultPage::setReady(const bool &val)
{
    readySearch = val;
}

bool ResultPage::getReady()
{
    return readySearch;
}

QString ResultPage::resultRead()
{
    QString result = "";
    for (const auto &tmp : result)
        result.append(tmp);
    return result;
}
