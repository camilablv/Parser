#include "olxlistingspage.h"

OlxListingsPage::OlxListingsPage()
{

}

QList<QUrl> OlxListingsPage::olxListing(const QByteArray &html) const
{
    QList<QUrl> listing;
    QGumboNodes contentTable;
    QGumboNodes listH3;
    QGumboDocument document = QGumboDocument::parse(html);
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
            listing.append(pageAddress);
        }
    }
    return listing;
}
