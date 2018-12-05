#ifndef ZOR_H
#define ZOR_H

#include <QObject>

class Zor : public QObject
{
    Q_OBJECT
public:
    explicit Zor(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ZOR_H