#include "../Headers/GTUSet.h"
namespace GTU
{
    template <class T>
    GTUSet<T>::GTUSet(int size) : GTUSetBase<T>(), _capacity(size), _size(0)
    {
        if(size < 0) throw std::bad_pafram();
        _set = std::shared_ptr<T>(new T [_capacity], std::default_delete<T[]>());
    }

    template <class T>
    GTUSet<T>::GTUSet(const GTUSetBase<T> & other) : GTUSet(other.max_size())
    {
        *this = other;
    }

    template <class T>
    GTUSet<T>::GTUSet(const typename GTUSetBase<T>::GTUIterator & first, const typename GTUSetBase<T>::GTUIterator & last) : GTUSet()
    {
        for(typename GTUSetBase<T>::GTUIterator temp = first; temp != last; ++temp)
            insert(*temp);
    }

    template <class T>
    const GTUSet<T> & GTUSet<T>::operator = (const GTUSetBase<T> & other)
    {
        if(max_size() != other.max_size())
        {
            _set = nullptr;
            _capacity = other.max_size();
            _set = std::shared_ptr<T>(new T [_capacity], std::default_delete<T[]>());
        }
        _size = 0;
        for(typename GTUSetBase<T>::GTUIterator counter = other.begin(); counter != other.end(); ++counter)
        {
            *(_set.get() + _size) = *(counter);
        }
        return *(this);
    }
    
    template <class T>
    bool GTUSet<T>::empty() const noexcept
    {
        return (_size == 0);
    }
    
    template <class T>
    int GTUSet<T>::size() const noexcept
    {
        return _size;
    }
    
    template <class T>
    int GTUSet<T>::max_size() const noexcept
    {
        return _capacity;
    }
    
    template <class T>
    void GTUSet<T>::insert(const T & data) throw(std::bad_pafram)
    {
        if(count(data) != 0)
            throw new std::bad_pafram();
        if(_size == _capacity)
        {
            _capacity *= 2;
            std::shared_ptr<T> temp(_set);
            _set = std::shared_ptr<T>(new T [_capacity], std::default_delete<T[]>());
            for(int i = 0; i < _size; ++i)
                *(_set.get() + i) = *(temp.get() + i);
        }
        *(_set.get() + _size++) = data;
    }

    template <class T>
    void GTUSet<T>::erase(const T & data)
    {
        if(count(data) == 0)
            throw std::bad_pafram();
        for(int i = 0; i < _size; ++i)
            if(*(_set.get() + i) == data)
            {
                while(i < _size)
                {
                    *(_set.get() + i) = *(_set.get() + (i + 1));
                    ++i;
                }
            }
    }
    
    template <class T>
    void GTUSet<T>::clear() noexcept
    {
        *this = GTUSet<T>();
    }

    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::find(const T & data) const noexcept
    {
        int i;
        for(i = 0; *(_set.get() + i) != data && i < _size; ++i);
        return _set.get() + i;
    }

    template <class T>
    int GTUSet<T>::count(const T & data) const noexcept 
    {
        int temp_c = 0;
        for(int i = 0; i < _size; ++i)
            if(*(_set.get() + i) == data)
                ++temp_c;
        return temp_c;
    }

    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::begin() const noexcept
    {
        return _set;
    }
    
    template <class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::end() const noexcept
    {
        return _set.get() + _size;
    }
}