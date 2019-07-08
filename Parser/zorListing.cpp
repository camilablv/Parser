#include "zorListing.h"

ZorListing::ZorListing(const QUrl address) : Listing (address)
{
    request = new Requesting;
}

ZorListing::~ZorListing()
{
    delete request;
}

QMap<int, QString> ZorListing::parsePage() const
{
    return listingData(request->pageText(address));
}

QMap<int, QString> ZorListing::listingData(QByteArray arr) const
{
    QMap<int, QString> data;
    QGumboDocument doc = QGumboDocument::parse(arr);
    QGumboNode root = doc.rootNode();
    parseTable(data, root);
    //QGumboNode title = getElementByClassName(root, "offer_title"); это не нужно
    addPair(data,getElementByTagName(root, HtmlTag::H1), 6);
    QGumboNode table = getElementByClassName(root, "cyantable");
    QGumboNodes spanTags = table.getElementsByTagName(HtmlTag::SPAN);
    int telephoneNumberColumn = 22;
    for(auto span : spanTags)
        data.insert(telephoneNumberColumn++, span.innerText());
    QGumboNode price = getElementByClassName(root, "theprice");
    addPair(data, getElementByTagName(price, HtmlTag::B), 33);
    QGumboNode description = getElementByClassName(root, "description");
    QGumboNodes pTags = description.getElementsByTagName(HtmlTag::P);
    QString descr;
    for(auto p : pTags)
        descr += p.innerText();
    data.insert(29, descr);
    QGumboNode stats = getElementByClassName(root, "offer_stats");
    QGumboNodes iTags = stats.getElementsByTagName(HtmlTag::I);
    if(iTags.size())
    {
        data.insert(45, iTags.at(2).innerText());
        data.insert(34, iTags.at(1).innerText());
    }
    return data;
}


void ZorListing::parseTable(QMap<int, QString>& pairs, QGumboNode& node) const
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
        QMapIterator<int, QString> description(descriptionElements);
        while(description.hasNext()){
            description.next();
            if(th.innerText() == description.value())
                pairs.insert(description.key(), td.innerText().replace(QRegExp("\\s+"), " "));
        }
    }
}





