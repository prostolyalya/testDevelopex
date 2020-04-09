#include "headers/uicontroller.h"

UiController::UiController(QObject *parent)
    : QObject(parent)
{
    startPage = new StartPage();
    resultPage = new ResultPage();

    connect(startPage, &StartPage::startSearch, this, &UiController::startSearch);
    connect(startPage, &StartPage::clearResult, this, &UiController::clearRes);
    connect(resultPage, &ResultPage::stopSearch, this, &UiController::stopSearch);
}

UiController::UiController(const UiController &uiController)
{
    Q_UNUSED(uiController)
}

UiController::~UiController()
{
    disconnect(startPage, &StartPage::startSearch, this, &UiController::startSearch);
    disconnect(startPage, &StartPage::clearResult, this, &UiController::clearRes);
    disconnect(resultPage, &ResultPage::stopSearch, this, &UiController::stopSearch);
    delete startPage;
    delete resultPage;
    finished();
}

StartPage *UiController::getStartPage() const
{
    return startPage;
}

void UiController::receiveResponse(const QByteArrayList &list, const QByteArray &url)
{
    ++countUrl;
    QString res;
    res = "--------- from url: " + url + "\n";
    if (list.isEmpty())
    {
        res += " -- empty -- \n";
    }
    else if (list.at(0) == "error")
    {
        res += ">>> " + list.at(1) + "\n";
    }
    else
    {
        for (auto tmp : list)
        {
            ++countRes;
            tmp.replace('\n', "");
            tmp.replace("  ", "");
            res += tmp + '\n';
        }
    }
    resultPage->appendToResult(res);
}

void UiController::receiveEnded()
{
    QString res = "    --------- END SEARCH ------------\n";
    res +=
        "searched " + QByteArray::number(countUrl) + " url with " + QByteArray::number(countRes) + " results";
    resultPage->appendToResult(res);
    resultPage->setReady(false);
    countRes = 0;
    countUrl = 0;
}

void UiController::clearRes()
{
    resultPage->setResult("");
    resultPage->setReady(true);
}

void UiController::stopSearch()
{
    emit stoppSearch();
}

void UiController::process()
{
}

ResultPage *UiController::getResultPage() const
{
    return resultPage;
}
