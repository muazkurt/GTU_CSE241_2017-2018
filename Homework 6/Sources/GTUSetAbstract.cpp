#include "../Headers/GTUSetAbstract.h"


namespace GTU
{   
    template <class T>    
    GTUSetBase<T>::GTUIterator::GTUIterator(T * container) : _interface(container)
    {/*--.--*/}
    
    template <class T>
    GTUSetBase<T>::GTUIterator::GTUIterator(const std::shared_ptr<T> container) : _interface(&(*container))
    {/*--.--*/}
    
    template <class T>
    GTUSetBase<T>::GTUIterator::GTUIterator(const GTUSetBase<T>::GTUIterator & other) : _interface(other._interface)
    {/*--.--*/}


    template <class T>
    T & GTUSetBase<T>::GTUIterator::operator *()
    {
        return *_interface;
    }

    template <class T>
    const T & GTUSetBase<T>::GTUIterator::operator *() const
    {
        return *_interface;
    }

    template <class T>
    T * & GTUSetBase<T>::GTUIterator::operator -> ()
    {
        return &(*(*this));
    }

    template <class T>
    const T * GTUSetBase<T>::GTUIterator::operator ->() const
    {
        return &(*(*this));
    }

    template <class T>
    typename GTUSetBase<T>::GTUIterator & GTUSetBase<T>::GTUIterator::operator ++()
    {
        ++_interface;
        return *this;
    }

    template <class T>
    const typename GTUSetBase<T>::GTUIterator & GTUSetBase<T>::GTUIterator::operator ++(int)
    {
        GTUSetBase<T>::GTUIterator temp(*this);
        ++_interface;
        return temp;
    }

    template <class T>
    typename GTUSetBase<T>::GTUIterator & GTUSetBase<T>::GTUIterator::operator --()
    {
        --_interface;
        return *this;
    }

    template <class T>
    const typename GTUSetBase<T>::GTUIterator & GTUSetBase<T>::GTUIterator::operator --(int)
    {
        GTUSetBase<T>::GTUIterator temp(*this);
        --_interface;
        return temp;
    }

    template <class T>
    const typename GTUSetBase<T>::GTUIterator & GTUSetBase<T>::GTUIterator::operator = (const GTUSetBase<T>::GTUIterator & other)
    {
        _interface = other._interface;
        return *this;
    }
    
    template <class T>
    bool GTUSetBase<T>::GTUIterator::operator == (const GTUSetBase<T>::GTUIterator & other) const
    {
        return _interface == other._interface;
    }

    template <class T>
    bool GTUSetBase<T>::GTUIterator::operator != (const GTUSetBase<T>::GTUIterator & other) const
    {
        return !(*this == other);
    }
    template <class T>
    GTUSetBase<T>::GTUIterator::~GTUIterator ()
    {
        _interface = nullptr;
    }
}