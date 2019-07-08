#ifndef ZORLISTING_H
#define ZORLISTING_H

#include "listing.h"
#include "requesting.h"


class ZorListing: public Listing
{
public:
    ZorListing(const QUrl address);
    QMap<int, QString> parsePage() const override;
    ~ZorListing() override;

private:
    Requesting* request;
    QMap<int, QString> listingData(QByteArray arr) const;
    void parseTable(QMap<int, QString>& pairs, QGumboNode& node) const;



    QMap<int, QString> descriptionElements{{5, "Район:"}, {6, "Улица:"},
                                           {9, "Количество комнат:"}, {12, "Общая площадь"},
                                           {10, "Этаж квартиры:"}, {11, "Этажность дома:"},
                                           {15, "Материал стен:"}, {17, "Ремонт:"}, {12, "Общая площадь:"},
                                           {30, "Дополнительно:"}};
};

#endif // ZORLISTING_H
