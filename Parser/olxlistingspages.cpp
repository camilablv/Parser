#include "olxlistingspages.h"

OlxListingsPages::OlxListingsPages()
{

}

QUrl OlxListingsPages::nextListingPage(const QByteArray &html) const
{
    QUrl nextPage;
    QGumboNodes nodesSpan;
    QGumboDocument document = QGumboDocument::parse(html);
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
