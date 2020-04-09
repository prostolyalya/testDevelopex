#include "headers/resultpage.h"

ResultPage::ResultPage(QObject *parent)
    : QObject(parent)
{
}

void ResultPage::stop()
{
    emit stopSearch();
}

QString ResultPage::getResult()
{
    return result;
}

void ResultPage::setResult(const QString &value)
{
    result = value;
}

void ResultPage::appendToResult(const QString &value)
{
    result += value;
    emit resChanged();
}

void ResultPage::setReady(const bool &val)
{
    readySearch = val;
    emit readyChanged();
}

bool ResultPage::getReady()
{
    return readySearch;
}
