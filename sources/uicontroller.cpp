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
    resultPage->Res += "--------- from url: " + url + "\n";
    if (list.isEmpty())
    {
        resultPage->Res += " -- empty -- \n";
    }
    else if (list.at(0) == "error")
    {
        resultPage->Res += ">>> " + list.at(1) + "\n";
    }
    else
    {
        for (auto tmp : list)
        {
            ++countRes;
            tmp.replace('\n', "");
            tmp.replace("  ", "");
            resultPage->Res += tmp + '\n';
        }
    }
    emit resultPage->resChanged();
}

void UiController::receiveEnded()
{
    resultPage->Res += "    --------- END SEARCH ------------\n";
    QByteArray res =
        "searched " + QByteArray::number(countUrl) + " url with " + QByteArray::number(countRes) + " results";
    resultPage->Res += res;
    countRes = 0;
    countUrl = 0;
    resultPage->readySearch = false;
    emit resultPage->readyChanged();
    emit resultPage->resChanged();
}

void UiController::clearRes()
{
    resultPage->Res = "";

    resultPage->readySearch = true;
    emit resultPage->readyChanged();

    emit resultPage->resChanged();
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
