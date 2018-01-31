#ifndef GTUGLOBAL_H
    #define GTUGLOBAL_H 
    #include "./GTUMap.h"

    namespace GTU
    {
        /*
            *
            *   This function is taking 3 argumants.
            *   First and secound parameters are for the intersection operation.
            *   Third argumant is for the return value.
            *
        */
        template <class T>
        void setIntersection(const GTUSetBase<T>& first, const GTUSetBase<T>& sec);
    }
#endif