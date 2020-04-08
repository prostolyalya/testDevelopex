#ifndef RESULTPAGE_H
#define RESULTPAGE_H
#include <QObject>

class ResultPage : public QObject
{
    Q_OBJECT

public:
    ResultPage(QObject *parent = nullptr);

    Q_PROPERTY(QString res READ res WRITE setRes NOTIFY resChanged)
    Q_PROPERTY(bool ready READ getReady WRITE setReady NOTIFY readyChanged)
    Q_INVOKABLE void stop();

    QString Res;
    QString res();
    QString resultRead();
    bool readySearch = false;

    void setRes(const QString &value);
    void setReady(const bool &val);
    bool getReady();

signals:
    void resChanged();
    void readyChanged();
    void stopSearch();
};

#endif // RESULTPAGE_H
