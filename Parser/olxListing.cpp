#include "olxListing.h"

OlxListing::OlxListing(const QUrl address) : Listing(address)
{
    parsing = new OlxHtmlParsing;
    request = new Requesting;
};

OlxListing::~OlxListing()
{
    delete parsing;
    delete request;
};

QMap<int, QString> OlxListing::parsePage() const
{
    QMap<int, QString> data;
    QByteArray page = request->pageText(address);
    QString id = getId(page);
    QString token = getToken(page);
    data = listingData(page, request->olxPhoneText(address, id, token));
    return data;
}

QMap<int, QString> OlxListing::listingData(QByteArray arr, QByteArray phone) const
{
    QMap<int, QString> data;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNode title = getElementByTagName(root, HtmlTag::H1);
    addPair(data, title, 6);
    QGumboNode titleboxDetails = getElementByClassName(root, "offer-titlebox__details");
    QGumboNode city = getElementByTagName(titleboxDetails, HtmlTag::STRONG);
    addPair(data, city, 2);
    QGumboNode em = getElementByTagName(titleboxDetails, HtmlTag::EM);
    data.insert(1, em.innerText());
    QGumboNode small = getElementByTagName(em, HtmlTag::SMALL);
    data.insert(45, innerText(small));
//не получается достать дату и номер объявления. доделать позже
    QGumboNode details = getElementByClassName(root, "descriptioncontent");
    parseTable(data, details);
    addPhones(data, phoneList(phone));
    QGumboNode textContent = getElementById(root, "textContent");
    addPair(data, textContent, 29);
    return data;
}

QString OlxListing::innerText(const QGumboNode& node) const
{
    auto children = node.children();
    if(children.size())
    {
        return innerText(children.at(0));
    }
    return node.innerText();
}

void OlxListing::parseTable(QMap<int, QString> &pairs, QGumboNode &node) const
{
    QGumboNodes tdTags = node.getElementsByTagName(HtmlTag::TD);
    for(auto tag : tdTags)
    {
        if(tag.hasAttribute("width"))
        {
            QGumboNode tr = getElementByTagName(tag, HtmlTag::TR);
            QGumboNode td = getElementByTagName(tr, HtmlTag::TD);
            QGumboNode th = getElementByTagName(tr, HtmlTag::TH);
            QMapIterator<int, QString> description(descriptionElements);
            while(description.hasNext()){
                description.next();
                if(th.innerText() == description.value())
                    pairs.insert(description.key(), innerText(td).trimmed());
            }
        }
    }
}

QString OlxListing::getToken(const QByteArray& arr) const
{
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QRegExp phoneToken("(var phoneToken = )|(\')|(\\s+)|(\\;)");
    QGumboNode sectionNode = getElementByClassName(root, "offer-section");
    QGumboNode scriptNode = getElementByTagName(sectionNode, HtmlTag::SCRIPT);
    return scriptNode.innerText().replace(phoneToken, "");
}

QString OlxListing::getId(const QByteArray& arr) const
{
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNode contactTag = getElementById(root, "contact_methods_below");
    QGumboNode liTag = getElementByTagName(contactTag, HtmlTag::LI);
    QString classValue = liTag.getAttribute("class");
    QStringList list = classValue.split(",");
    QString id;
    if(list.size()) id = list.at(1);
    return id.replace(QRegExp("( 'id':)|(\'+)"), "");
}

QList<QString> OlxListing::phoneList(const QByteArray &arr) const
{
    QStringList list;
    QJsonDocument doc = QJsonDocument::fromJson(arr);
    QJsonObject root = doc.object();
    while (root.size()) {
        list.append(root.take("value").toString());
    }
    return std::move(list);

//    QList<QString> list;
//    QJsonDocument doc = QJsonDocument::fromJson(arr);
//    QJsonObject root = doc.object();
//    QJsonValue phones = root.value("phones");
//    if(phones.isArray())
//    {
//        QJsonArray phoneArray = phones.toArray();
//        for(int i = 0; i < phoneArray.count(); i++)
//        {
//            QJsonObject phone = phoneArray.at(i).toObject();
//            list.append(phone.value("phone_original").toString());
//        }
//    }
    //    return list;
}

void OlxListing::addPhones(QMap<int, QString>& pairs,const QStringList &phoneList) const
{
    int telephoneNumberColumn = 22;
    for(auto phone : phoneList)
        pairs.insert(telephoneNumberColumn++, phone);
}
