#ifndef GTUSET_H
    #define GTUSET_H 
    #include "./GTUSetAbstract.h"

    namespace GTU
    {
        template <class T>
        class GTUSet : public GTUSetBase<T>
        {
        public:
            GTUSet(int size = 10);
            // Copy constructer.
            GTUSet(const GTUSetBase<T> & other);
            // Move set by it's first and last iterator.
            GTUSet(const typename GTUSetBase<T>::GTUIterator & first, const typename GTUSetBase<T>::GTUIterator & last);
            // Assign other to this.
            const GTUSet & operator = (const GTUSetBase<T> & other);
            /*
                *
                *   These functions are virtual and their info is in GTUSetBase.h file.
                *
            */
            bool empty() const noexcept override;
            int size() const noexcept override;
            int max_size() const noexcept override;
            void insert(const T & data) throw(std::bad_pafram) override;
            void erase(const T & data) override;
            void clear() noexcept override;
            typename GTUSetBase<T>::GTUIterator find(const T & data) const noexcept override;
            int count(const T & data) const noexcept override;
            typename GTUSetBase<T>::GTUIterator begin() const noexcept override;
            typename GTUSetBase<T>::GTUIterator end() const noexcept override;
        private:
            int _size;
            int _capacity;
            std::shared_ptr<T> _set;
        };
    }
#endif