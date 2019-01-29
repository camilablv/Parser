#include "olxListingsPage.h"

OlxListingsPage::OlxListingsPage(const QByteArray &html) : arr(html){}

QList<QUrl> OlxListingsPage::listingAddresses() const
{
    QRegExp fragment("#(.*)");
    QList<QUrl> listing;
    QGumboNodes contentTable;
    QGumboNodes listH3;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNodes nodesSection = root.getElementsByTagName(HtmlTag::SECTION);
    if(0 < nodesSection.size()) contentTable = nodesSection.at(0).getElementById("offers_table");
    if(0 < contentTable.size()) listH3 = contentTable.at(0).getElementsByTagName(HtmlTag::H3);

    for(uint i = 0; i < listH3.size(); i++)
    {
        QGumboAttributes attr;
        QGumboNodes nodesA = listH3.at(i).getElementsByTagName(HtmlTag::A);

        if(0 < nodesA.size()) attr = nodesA.at(0).allAttributes();
        for(uint j = 0; j < attr.size(); j++)
        {
            if(attr.at(j).name() != "href") continue;
            QUrl pageAddress(attr.at(j).value());
            listing.append(pageAddress.toString().replace(fragment, ""));
        }
    }
    return listing;
}

QUrl OlxListingsPage::nextListingPageUrl() const
{
    QUrl nextPage;
    QGumboNodes nodesSpan;
    QGumboDocument document = QGumboDocument::parse(arr);
    QGumboNode root = document.rootNode();
    QGumboNodes nodesSection = root.getElementsByTagName(HtmlTag::SECTION);
    if(0 < nodesSection.size()) nodesSpan = nodesSection.at(0).getElementsByTagName(HtmlTag::SPAN);
    for(uint i =0; i < nodesSpan.size(); i++)
    {
        QGumboAttributes attrSpan = nodesSpan.at(i).allAttributes();
        for(uint j = 0; j < attrSpan.size();j++)
        {
            if(attrSpan.at(j).value() != "fbold next abs large") continue;
            QGumboNode span = nodesSpan.at(i);
            QGumboNodes nodesA = span.getElementsByTagName(HtmlTag::A);
            if(nodesA.size() == 0) continue;
            QGumboAttributes attrA;
            attrA = nodesA.at(0).allAttributes();
            for(uint k = 0; k < attrA.size(); k++)
            {
                if(attrA.at(k).name() != "href") continue;
                QUrl nextPage = attrA.at(k).value();
                return nextPage;
            }
        }
    }
    return nextPage;
}


