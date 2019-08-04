#ifndef ZORLISTING_H
#define ZORLISTING_H

#include "Listing.h"
#include "Requesting.h"


class ZorListing: public Listing
{
public:
    ZorListing(const QUrl address);
    QMap<QString, QString> parsePage() const override;
    ~ZorListing() override;

private:
    Requesting* request;
    QMap<QString, QString> listingData(QByteArray arr) const;
    void parseTable(QMap<QString, QString> &pairs, QGumboNode& node) const;



    QMap<QString, QString> descriptionElements{{"address", "Район:"}, {"address", "Улица:"},
                                           {"rooms", "Количество комнат:"}, {"floor", "Этаж квартиры:"},
                                           {"number_of_floors", "Этажность дома:"},
                                           {"wall_material", "Материал стен:"}, {"condition", "Ремонт:"}, {"square", "Общая площадь:"},
                                           {"additionally", "Дополнительно:"}};
};

#endif // ZORLISTING_H

