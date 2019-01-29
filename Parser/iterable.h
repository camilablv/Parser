#ifndef ITERABLE_H
#define ITERABLE_H

template <typename T>
class Iterable
{
public:
    Iterable(const T &list);
    template<typename L>
    void forEach(L &f) const;
private:

    const T urls;
};

template <typename T>
Iterable<T>::Iterable(const T &list) : urls(list){}

template <typename T>
template <typename L>
void Iterable<T>::forEach(L& f) const
{
    for(auto x : urls)
        f(x);
}

#endif // ITERABLE_H
