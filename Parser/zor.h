#ifndef ZOR_H
#define ZOR_H

#include <QObject>
#include <QUrl>
#include <qgumbodocument.h>
#include <qgumbonode.h>
#include <qgumboattribute.h>
#include <write.h>

class Zor : public QObject
{
    Q_OBJECT
public:
    explicit Zor(QObject *parent = nullptr);
    ~Zor();
    void Start();

signals:

public slots:

private:

};

#endif // ZOR_H
