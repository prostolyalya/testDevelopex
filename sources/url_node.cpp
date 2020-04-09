#include "headers/url_node.h"
#include "headers/searcher.h"

UrlNode::UrlNode(QObject *parent)
    : QObject(parent)
{
}

UrlNode::UrlNode(const QString &url)
{
    this->url = url;
}

UrlNode::UrlNode(const UrlNode &node)
{
    Q_UNUSED(node)
}

UrlNode::~UrlNode()
{
    std::for_each(children.begin(), children.end(), [](UrlNode *el) { delete el; });
    emit finished();
}

void UrlNode::startSearch(const QByteArray &text)
{
    QByteArray data = downloadData(url);
    if (data.startsWith("error"))
    {
        findData = { "error", data.mid(5) };
        isFind = true;
        emit continueSearch();
        return;
    }
    findData = searchData(text, data);
    QByteArrayList res = searchUrl(data);
    res.removeAll(url.toUtf8());
    int gens = this->gen + 1;
    for (const auto &tmp : res)
    {
        UrlNode *node = new UrlNode(tmp);
        node->gen = gens;
        children.append(node);
    }
    isFind = true;
    emit continueSearch();
    return;
}

QByteArray UrlNode::downloadData(const QString &url) const
{
    QEventLoop loop;
    QNetworkAccessManager nam;
    QNetworkRequest req((QUrl(url)));
    QNetworkReply *reply = nam.get(req);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error())
    {
        return "error" + reply->errorString().toUtf8();
    }
    QByteArray buffer = reply->readAll();
    return buffer;
}

QByteArrayList UrlNode::searchUrl(const QByteArray &data) const
{
    QByteArray datas = data;
    QByteArrayList list;
    int i = datas.indexOf("\"https://");
    while (i != -1)
    {
        QByteArray res = "";
        while (++i < datas.size() && datas.at(i) != '\"')
            res.append(datas.at(i));
        if (!list.contains(res))
            list.append(res);
        if (++i < datas.size())
            datas.remove(0, i);
        i = datas.indexOf("\"https://");
    }
    return list;
}

QByteArrayList UrlNode::searchData(const QByteArray &text, QByteArray &data) const
{
    QByteArrayList list;
    int i = data.indexOf(text);
    while (i != -1)
    {
        QByteArray res = data.mid(i - 10, text.size() + 20);
        list.append(res);
        i = data.indexOf(text, i + text.size());
    }
    return list;
}

void UrlNode::process()
{
}
