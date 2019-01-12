#include "iterable.h"

Iterable::Iterable(const QList<QUrl> &list) : urls(list){}

void Iterable::forEach(const std::function<void(const QUrl &)> &f) const
{
    QListIterator<QUrl> iter(urls);
    while(iter.hasNext())
    {
        f(iter.next());
    }
}
