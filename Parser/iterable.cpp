#include "iterable.h"

template <typename T, typename L>
Iterable<T, L>::Iterable(const L &list) : urls(list){}

template <typename T, typename L>
void Iterable<T, L>::forEach(T& f) const
{
    QListIterator<QUrl> iter(urls);
    while(iter.hasNext())
    {
        f(iter.next());
    }
}
