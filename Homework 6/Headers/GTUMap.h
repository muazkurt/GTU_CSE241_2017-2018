#ifndef GTUMAP_H
    #define GTUMAP_H 
    #include "./GTUSet.h"
    #include <utility>
    
    namespace GTU
    {
        template <class K, class V>
        class GTUMap : public GTUSet<std::pair<K, V>>
        {
        public:
            GTUMap(int width = 10);
            GTUMap(const GTUSetBase<std::pair<K, V>> & other);
            GTUMap(const typename GTUSetBase<std::pair<K, V>>::GTUIterator & first, const typename GTUSetBase<std::pair<K, V>>::GTUIterator & last);
            // Updates insert function from GTUSet for pair.
            void insert(const std::pair<K, V> & data) throw(std::bad_pafram);
            // Counts Key and Value.
            int count(const std::pair<K, V> & data) throw(std::bad_pafram);
            // Takes a K and returns V. Every K has a unique V.
            V & operator [] (const K & input) noexcept;
            const V & operator [] (const K & input) const noexcept;
        };
    }
#endif