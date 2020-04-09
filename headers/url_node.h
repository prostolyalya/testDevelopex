#ifndef URLNODE_H
#define URLNODE_H
#include <QObject>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class UrlNode : public QObject
{
    Q_OBJECT

public:
    UrlNode(QObject* parent = nullptr);
    UrlNode(const QString& url);
    UrlNode(const UrlNode& node);
    ~UrlNode();

    QList<QByteArray> findData;
    QVector<UrlNode*> children;

    QString url;
    bool isFind = false;
    int gen = 1;

public:
    void startSearch(const QByteArray& text);

private:
    QByteArray downloadData(const QString& url) const;
    QByteArrayList searchUrl(const QByteArray& data) const;
    QByteArrayList searchData(const QByteArray& text, QByteArray& data) const;

public slots:
    void process();

signals:
    void finished();
    void continueSearch();
};

#endif // URLNODE_H
