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

QString Listing::innerText(const QGumboNode& node) const
{
    auto children = node.children();
    if(children.size())
    {
        return innerText(children.at(0));
    }
    return node.innerText().trimmed();
}

void Listing::addPhones(QMap<int, QString>& pairs,const QStringList &phoneList) const
{
    int telephoneNumberColumn = 22;
    for(auto phone : phoneList)
        pairs.insert(telephoneNumberColumn++, phone);
}
