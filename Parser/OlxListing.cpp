#include "OlxListing.h"

OlxListing::OlxListing(const QUrl address) : Listing(address)
{
    request = new Requesting;
};

OlxListing::~OlxListing()
{
    delete request;
};

QMap<QString, QString> OlxListing::parsePage() const
{
    QMap<QString, QString> data;
    QByteArray page = request->pageText(address);
    QString id = getId(page);
    QString token = getToken(page);
    data = listingData(page, request->olxPhoneText(address, id, token));
    return data;
}

QMap<QString, QString> OlxListing::listingData(QByteArray arr, QByteArray phone) const
{
    QMap<QString, QString> data;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNode title = getElementByTagName(root, HtmlTag::H1);
    addPair(data, title, "title");
    QGumboNode titleboxDetails = getElementByClassName(root, "offer-titlebox__details");
    QGumboNode city = getElementByTagName(titleboxDetails, HtmlTag::STRONG);
    addPair(data, city, "address");
    QGumboNode em = getElementByTagName(titleboxDetails, HtmlTag::EM);
    data.insert("date", em.innerText());
    QGumboNode small = getElementByTagName(em, HtmlTag::SMALL);
    data.insert("id", innerText(small));
    QGumboNode details = getElementByClassName(root, "descriptioncontent");
    parseTable(data, details);
    QGumboNode name = getElementByClassName(root, "offer-sidebar__box");
    data.insert("name", innerText(getElementByTagName(name, HtmlTag::H4)));
    addPhones(data, phoneList(phone));
    QGumboNode textContent = getElementById(root, "textContent");
    addPair(data, textContent, "description");
    return data;
}

QString OlxListing::innerText(const QGumboNode& node) const
{
    auto children = node.children();
    if(children.size())
    {
        return innerText(children.at(0));
    }
    return node.innerText().trimmed();
}

void OlxListing::parseTable(QMap<QString, QString> &pairs, QGumboNode &node) const
{
    QGumboNodes tdTags = node.getElementsByTagName(HtmlTag::TD);
    for(auto tag : tdTags)
    {
        if(tag.hasAttribute("width"))
        {
            QGumboNode tr = getElementByTagName(tag, HtmlTag::TR);
            QGumboNode td = getElementByTagName(tr, HtmlTag::TD);
            QGumboNode th = getElementByTagName(tr, HtmlTag::TH);
            QMapIterator<QString, QString> description(descriptionElements);
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
}

//void OlxListing::addPhones(QMap<QString, QString>& pairs,const QStringList &phoneList) const
//{
//    int telephoneNumberColumn = 22;
//    for(auto phone : phoneList)
//        pairs.insert(telephoneNumberColumn++, phone);
//}
