#ifndef LISTING_H
#define LISTING_H

#include <QUrl>
#include <QMap>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>

class Listing
{
public:
    explicit Listing(const QUrl url);
    virtual QMap<QString, QString> parsePage() const = 0;
    virtual ~Listing();
protected:
    QGumboNode getElementByClassName(const QGumboNode &node, QString&& className) const;
    QGumboNode getElementById(const QGumboNode &node, QString&& id) const;
    QGumboNode getElementByTagName(const QGumboNode& node, const HtmlTag tag) const;
    void addPair(QMap<QString, QString> &pairs, const QGumboNode &node, QString key) const;
    QString innerText(const QGumboNode& node) const;
    void addPhones(QMap<QString, QString>& pairs,const QStringList &phoneList) const;
    QUrl address;
};

#endif // LISTING_H
