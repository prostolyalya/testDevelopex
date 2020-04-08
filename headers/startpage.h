#ifndef STARTPAGE_H
#define STARTPAGE_H
#include <QObject>
#include <QDebug>

class StartPage : public QObject
{
    Q_OBJECT

public:
    StartPage(QObject *parent = nullptr);
    StartPage(const StartPage &stPage);

    Q_INVOKABLE void search(const QString &text, const QString &url, const int &countThreads,
                            const int &deepSearch);
signals:
    void startSearch(const QString &text, const QString &url, const int &countThreads, const int &deepSearch);
    void clearResult();
};

#endif // STARTPAGE_H
