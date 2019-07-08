#include "listing.h"

Listing::Listing(const QUrl url) : address(url) {}

//QMap<int, QString> Listing::parsePage()
//{
//    return QMap<int, QString>();
//}

Listing::~Listing(){};

QGumboNode Listing::getElementByClassName(const QGumboNode& node, QString&& className) const
{
    QGumboNodes nodes = node.getElementsByClassName(className);
    if(nodes.size())
        return nodes.at(0);
    return QGumboNode();
}

QGumboNode Listing::getElementById(const QGumboNode &node, QString &&id) const
{
    QGumboNodes nodes = node.getElementById(id);
    if(nodes.size())
        return nodes.at(0);
    return QGumboNode();
}

QGumboNode Listing::getElementByTagName(const QGumboNode& node,const HtmlTag tag) const
{
    QGumboNodes nodes = node.getElementsByTagName(tag);
    if(nodes.size())
        return nodes.at(0);
    return QGumboNode();
}

void Listing::addPair(QMap<int, QString>& pairs,const QGumboNode& node, int key) const
{
    pairs.insert(key, node.innerText().trimmed());
}
