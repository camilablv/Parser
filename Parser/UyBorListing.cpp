#include "UyBorListing.h"


UyBorListing::UyBorListing(const QUrl address) : Listing(address)
{
    request = new Requesting;
}

UyBorListing::~UyBorListing()
{
    delete request;
}

QMap<QString, QString> UyBorListing::parsePage() const
{
    QMap<QString, QString> data;
    QByteArray page = request->pageText(address);
    QString id = getId(page);
    QString token = getToken(page);
    data = listingData(page, phoneList(request->uyBorPhoneText(id, token, address)));
    return data;
}

QMap<QString, QString> UyBorListing::listingData(const QByteArray& arr, const QStringList& phoneList) const
{
    QMap<QString, QString> data;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    data = jsonReader->listingData(getScriptData(root));
    addPhones(data, phoneList);
    data.insert("source", "uybor");
    return data;
}


QString UyBorListing::getToken(const QByteArray& arr) const
{
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNodes head = root.getElementsByTagName(HtmlTag::HEAD);
    QGumboNodes metaTags;
    if(0 < head.size()) metaTags = head.at(0).getElementsByTagName(HtmlTag::META);
    for(uint i = 0; i < metaTags.size(); i++)
    {
        QGumboAttributes attr = metaTags.at(i).allAttributes();
        if(attr.at(0).value() == "csrf-token")
            return attr.at(1).value();
    }
    return "";
}
QString UyBorListing::getId(const QByteArray& arr) const
{
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    return jsonReader->getUyBorID(getScriptData(root));
}


QList<QString> UyBorListing::phoneList(const QByteArray& arr) const
{

    return jsonReader->phoneList(arr);
}

QString UyBorListing::getScriptData(const QGumboNode& node) const
{
    QGumboNode bodyTag = getElementByTagName(node, HtmlTag::BODY);
    QGumboNodes scripts = bodyTag.getElementsByTagName(HtmlTag::SCRIPT);
    if(scripts.size())
    {
        QString script = scripts.at(4).innerText();
        QRegularExpression rx("(?<=var listingViewData = )({.*});", QRegularExpression::InvertedGreedinessOption);
        auto match = rx.match(script, 0, QRegularExpression::MatchType::PartialPreferCompleteMatch);
        auto captured = match.capturedTexts();
        return  captured.at(1);
    }
    return "";
}
