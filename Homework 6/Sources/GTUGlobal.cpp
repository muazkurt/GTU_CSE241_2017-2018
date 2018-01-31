#include "../Headers/GTUGlobal.h"

    namespace GTU
    {
        template <class T>
        void setIntersection(const GTUSetBase<T>& first, const GTUSetBase<T>& sec, GTUSetBase<T>& returnVal)
        {
            for(typename GTUSetBase<T>::GTUIterator i = first.begin(); i != first.end(); ++i)
                for(typename GTUSetBase<T>::GTUIterator j = sec.begin(); j != sec.end(); ++j)
                    if(*i == *j)
                        returnVal.insert(*i);
        }
    }