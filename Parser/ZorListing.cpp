#include "ZorListing.h"

ZorListing::ZorListing(const QUrl address) : Listing (address)
{
    request = new Requesting;
}

ZorListing::~ZorListing()
{
    delete request;
}

QMap<QString, QString> ZorListing::parsePage() const
{
    return listingData(request->pageText(address));
}

QMap<QString, QString> ZorListing::listingData(QByteArray arr) const
{
    QMap<QString, QString> data;
    QGumboDocument doc = QGumboDocument::parse(arr);
    QGumboNode root = doc.rootNode();
    parseTable(data, root);
    addPair(data,getElementByTagName(root, HtmlTag::H1), "title");
    QGumboNode table = getElementByClassName(root, "cyantable");
    QGumboNodes spanTags = table.getElementsByTagName(HtmlTag::SPAN);
    QStringList phoneList;
    for(auto span : spanTags)
        phoneList.append(span.innerText());
    addPhones(data, phoneList);
    QGumboNode price = getElementByClassName(root, "theprice");
    addPair(data, getElementByTagName(price, HtmlTag::B), "price");
    QGumboNode description = getElementByClassName(root, "description");
    QGumboNodes pTags = description.getElementsByTagName(HtmlTag::P);
    QString descr;
    for(auto p : pTags)
        descr += p.innerText();
    data.insert("description", descr);
    QGumboNode stats = getElementByClassName(root, "offer_stats");
    QGumboNodes iTags = stats.getElementsByTagName(HtmlTag::I);
    if(iTags.size())
    {
        data.insert("id", iTags.at(2).innerText());
        data.insert("name", iTags.at(1).innerText());
    }
    return data;
}


void ZorListing::parseTable(QMap<QString, QString>& pairs, QGumboNode& node) const
{
    QGumboNode properties = getElementByClassName(node, "wpic");
    QGumboNodes trTags = properties.getElementsByTagName(HtmlTag::TR);
    QGumboNode table = getElementByClassName(node, "cyantable");
    QGumboNodes tags = table.getElementsByTagName(HtmlTag::TR);
    trTags.insert(trTags.end(), tags.begin(), tags.end());
    for(auto tr : trTags)
    {
        QGumboNode th = getElementByTagName(tr, HtmlTag::TH);
        QGumboNode td = getElementByTagName(tr, HtmlTag::TD);
        QMapIterator<QString, QString> description(descriptionElements);
        while(description.hasNext()){
            description.next();
            if(th.innerText() == description.value())
                pairs.insert(description.key(), td.innerText().replace(QRegExp("\\s+"), " "));
        }
    }
}





