#ifndef RESULTPAGE_H
#define RESULTPAGE_H
#include <QObject>

class ResultPage : public QObject
{
    Q_OBJECT

public:
    ResultPage(QObject *parent = nullptr);
    ResultPage(const ResultPage &resPage);

    Q_PROPERTY(QString res READ getResult WRITE setResult NOTIFY resChanged)
    Q_PROPERTY(bool ready READ getReady WRITE setReady NOTIFY readyChanged)
    Q_INVOKABLE void stop();

    QString getResult();
    void setResult(const QString &value);
    void appendToResult(const QString &value);
    void setReady(const bool &val);
    bool getReady();

private:
    QString result;
    bool readySearch = false;

signals:
    void resChanged();
    void readyChanged();
    void stopSearch();
};

#endif // RESULTPAGE_H
