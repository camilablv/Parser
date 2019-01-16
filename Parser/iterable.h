#ifndef ITERABLE_H
#define ITERABLE_H

#include <QList>
#include <QListIterator>
#include <functional>

template <typename T, typename L>
class Iterable
{
public:
    Iterable(const L &list);
    void forEach(T &f) const;
private:

    const QList<QUrl> urls;
};

#endif // ITERABLE_H
