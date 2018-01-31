#include "../Headers/GTUMap.h"

namespace GTU
{
    template <class K, class V>
    GTUMap<K, V>::GTUMap(int width) : GTUSet<std::pair<K, V>>(width)
    {/*--.--*/}
    
    template <class K, class V>
    GTUMap<K, V>::GTUMap(const GTUSetBase<std::pair<K, V>> & other): GTUSet<std::pair<K, V>>(other)
    {/*--.--*/}
    
    template <class K, class V>
    GTUMap<K, V>::GTUMap(const typename GTUSetBase<std::pair<K, V>>::GTUIterator & first, const typename GTUSetBase<std::pair<K, V>>::GTUIterator & last) : GTUSet<std::pair<K, V>>(first, last)
    {/*--.--*/}

    template <class K, class V>
    void GTUMap<K, V>::insert(const std::pair<K, V> & data) throw(std::bad_pafram)
    {
        if(count(data) != 0)
            throw std::bad_pafram();
        GTUSet<std::pair<K, V>>::insert(data);
    }

    template <class K, class V>
    int GTUMap<K, V>::count(const std::pair<K, V> & data) throw(std::bad_pafram)
    {
        int i = 0;
        for(typename GTUSetBase<std::pair<K, V>>::GTUIterator k = this->begin(); k != this->end(); ++k)
            if(std::get<0>(*k) == std::get<0>(data) || std::get<1>(*k) == std::get<1>(data))
                ++i;
        return i;
    }

    template <class K, class V>
    const V & GTUMap<K, V>::operator [](const K & input) const noexcept
    {
        typename GTUSetBase<std::pair<K, V>>::GTUIterator x = this->begin();
        for(; x != this->end() && std::get<0>(*x) != input; ++x);
        return std::get<1>(*x);
    }

    template <class K, class V>
    V & GTUMap<K, V>::operator [] (const K & input) noexcept
    {
        typename GTUSetBase<std::pair<K, V>>::GTUIterator x = this->begin();
        for(; x != this->end() && std::get<0>(*x) != input; ++x);
        return std::get<1>(*x);
    }
}