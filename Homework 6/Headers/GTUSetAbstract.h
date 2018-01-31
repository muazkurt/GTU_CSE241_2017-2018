/*
    *
    *
*/
#ifndef GTUSETABSTRACT_H
    #define GTUSETABSTRACT_H 
    #include <iostream>
    #include <iterator>
    #include <memory>
    namespace std
    {
        class bad_pafram
        { };
    }
    namespace GTU
    {
        /*
            *   GTU Set abstract class
        */
        template <class T>
        class GTUSetBase
        {
        public:
            /*
                *   GTU Iterator Class
            */
            class GTUIterator
            {
            public:
                /*
                    *   Constructers
                */
                GTUIterator(T * container);
                GTUIterator(const std::shared_ptr<T> container);
                GTUIterator(const GTUIterator & other);
                /*
                    *   Operators.
                */
                T & operator *();
                const T & operator *() const;
                //Returns the item iterator.
                T * & operator -> ();
                const T * operator ->() const;
                //Returns the next item iterator.
                GTUIterator & operator ++();
                const GTUIterator & operator ++(int);
                //Returs the prewioust item iterator.
                GTUIterator & operator --();
                const GTUIterator & operator --(int);
                //Casts this item to other.
                const GTUIterator & operator = (const GTUIterator & other);
                //Checks if two iterator same or not.
                bool operator == (const GTUIterator & other) const;
                bool operator != (const GTUIterator & other) const;
                //Deletes _interface
                ~GTUIterator();
            private:
                T * _interface;
            };
            // Checks if the object empty or not. (is _size > 0)
            virtual bool empty() const noexcept = 0;
            // Returns the using space.
            virtual int size() const noexcept = 0;
            // Returns the capacity
            virtual int max_size() const noexcept = 0;
            // Adds data element to the set. If there is the same element in set
            //  throws std::bad_pafram.
            virtual void insert(const T & data) throw(std::bad_pafram) = 0;
            // Deletes the given item from set.
            virtual void erase(const T & data) = 0;
            // Clear all contets in set and deletes the allocated space.
            virtual void clear() noexcept = 0;
            // Finds the given data and returns it's iterator.
            virtual GTUIterator find(const T & data) const noexcept = 0;
            // Checks how much data in set. If there is 2 or more items, it's an error condition.
            virtual int count(const T & data) const noexcept = 0;
            // Returns 0th element's iterator.
            virtual GTUIterator begin() const noexcept = 0;
            // Returns _size th element's iterator.
            virtual GTUIterator end() const noexcept = 0;
        };
    }
#endif