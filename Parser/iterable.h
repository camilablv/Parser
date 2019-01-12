#ifndef ITERABLE_H
#define ITERABLE_H

#include <QList>
#include <QListIterator>
#include <functional>

class Iterable
{
public:
    Iterable(const QList<QUrl>& list);
    void forEach(const std::function<void(const QUrl &)> &f) const;
private:

    const QList<QUrl> urls;
};

#endif // ITERABLE_H
