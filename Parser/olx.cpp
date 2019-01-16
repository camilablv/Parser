#include "olx.h"

Olx::Olx(QObject *parent) : QObject(parent)
{
    request = new Requesting;
    write = new Write;
}

Olx::~Olx()
{
    delete request;
    delete write;
}

void Olx::Start()
{
    QUrl startPageAdsForSaleApartments("https://olx.uz/nedvizhimost/kvartiry/prodazha/tashkent/");
    parseListing(request->pageText(startPageAdsForSaleApartments));
}


void Olx::parseListing(QByteArray html)
{
    OlxListingsPage listingsPage(html);
    QList<QUrl> addresses = listingsPage.listingAddresses();
    auto lambda = [this](const QUrl& address)->void{QByteArray adHTML = request->pageText(address);
        if(adHTML.isEmpty()) return;
        OlxListingPage page(adHTML, address);
        QMap<int, QString> listData = page.parseListingData();
        write->writeToExcel(listData, row);
        row++;};
    Iterable<QList<QUrl>&> iterator(addresses);
    iterator.forEach(lambda);



    QUrl nextPage = listingsPage.nextListingPageUrl();
    if(!nextPage.isEmpty())
        parseListing(request->pageText(nextPage));
}

