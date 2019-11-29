#pragma once

#include <functional>
#include <memory>
#include <utility>
#include <type_traits>
#include <vector>
#include <limits>

namespace fefu
{

    template<typename T>
    class allocator;

    template<typename K, typename T,
            typename Hash = std::hash<K>,
            typename Pred = std::equal_to<K>,
            typename Alloc = allocator<std::pair<const K, T>>>
    class hash_map;


    template<typename T>
    class allocator {
    public:
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<const T>::type;
        using value_type = T;

        allocator() noexcept  = default;

        allocator(const allocator&) noexcept = default;

        template <class U>

        allocator(const allocator<U>&) noexcept{

        }

        ~allocator() = default;

        pointer allocate(size_type size){
            if (size == 0){
                return nullptr;
            }
            return static_cast<pointer>(:: operator new (size * sizeof(value_type)));
        }

        void deallocate(pointer p, size_type n) noexcept{
            if (n != 0 && p != nullptr){
                ::operator delete(p, n);
            }
        }
    };

    template<typename ValueType>
    class hash_map_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;//тип, указывающий на набор операций, поддерживаемых итератором.
        using value_type = ValueType; //тип значения, на которое указывает итератор типа T
        using difference_type = std::ptrdiff_t; //целочисленный тип, представляющий значения смещений итераторов относительно друг друга;
        using reference = ValueType&; // тип ссылки, возвращаемой при разыменовании итератора;
        using pointer = ValueType*; //тип указателя, возвращаемого при обращении к объекту итератора через operator-> (может не быть “настоящим” указателем);

        hash_map_iterator() noexcept = default;

        hash_map_iterator(const hash_map_iterator& other) noexcept{
            m_data = other.m_data;
            index = other.index;
            m_set = other.m_set;
        }

        reference operator*() const{
            return (*(m_data + index));
        }

        pointer operator->() const{
            return (m_data + index);
        }

        // prefix ++
        hash_map_iterator& operator++(){
            int i = 1;
            while ((i + index >= m_set->size()) || *(m_set->begin() + i + index) != 1){
                if (i >= m_set->size()){
                    index = m_set->size();
                    return *this;
                }
                ++i;
            }
            index += i;
            return *this;
        }

        // postfix ++
        hash_map_iterator operator++(int){
            hash_map_iterator copy(*this);
            ++(*this);
            return copy;
        }

        friend bool operator==(const hash_map_iterator<ValueType>& first, const hash_map_iterator<ValueType>& second){
            return((first.m_data + first.index) == (second.m_data + second.index));
        }

        friend bool operator!=(const hash_map_iterator<ValueType>& first, const hash_map_iterator<ValueType>& second){
            return((first.m_data + first.index) != (second.m_data + second.index));
        }
        template<typename K, typename T,
                typename Hash,
                typename Pred,
                typename Alloc>
        friend class hash_map;
        template <typename val>
        friend class hash_map_const_iterator;

    private:
        hash_map_iterator(pointer iter, const size_t i,  const std::vector<char> *sost) noexcept{
            m_data = iter;
            index = i;
            m_set = sost;
        }
        pointer m_data;
        size_t index;
        const std::vector<char> *m_set;
    };

    template<typename ValueType>
    class hash_map_const_iterator {
// Shouldn't give non const references on value
    public:
        using iterator_category = std::forward_iterator_tag;
        using i = ValueType;
        using difference_type = std::ptrdiff_t;
        using reference = const ValueType&;
        using pointer = const ValueType*;

        hash_map_const_iterator() noexcept = default;

        hash_map_const_iterator(const hash_map_const_iterator& other) noexcept{
            m_data = other.m_data;
            index = other.index;
            m_set = other.m_set;
        }

        hash_map_const_iterator(const hash_map_iterator<ValueType>& other) noexcept{
            m_data = other.m_data;
            index = other.index;
            m_set = other.m_set;
        }
        hash_map_const_iterator(pointer iter, size_t i,  const std::vector<char> *sost) noexcept{
            m_data = iter;
            index = i;
            m_set = sost;
        }

        reference operator*() const{
            return (*(m_data + index));
        }

        pointer operator->() const{
            return (&(*(m_data + index)));
        }

        // prefix ++
        hash_map_const_iterator& operator++(){
            int i = 1;
            while ((i + index >= m_set->size()) || *(m_set->begin() + i + index) != 1){
                if (i >= m_set->size()){
                    index = m_set->size();
                    return *this;
                }
                ++i;
            }
            index += i;
            return *this;
        }

        // postfix ++
        hash_map_const_iterator operator++(int){
            hash_map_const_iterator copy(*this);
            ++(*this);
            return copy;
        }

        friend bool operator==(const hash_map_const_iterator<ValueType>& first, const hash_map_const_iterator<ValueType>& second){
            return((first.m_data + first.index) == (second.m_data + second.index));
        }

        friend bool operator!=(const hash_map_const_iterator<ValueType>& first, const hash_map_const_iterator<ValueType>& second){
            return((first.m_data + first.index) != (second.m_data + second.index));
        }
        template<typename K, typename T,
                typename Hash,
                typename Pred,
                typename Alloc>
        friend class hash_map;

    private:
        pointer m_data;
        size_t index;
        const std::vector<char> *m_set;
    };

    template<typename K, typename T,
            typename Hash,
            typename Pred,
            typename Alloc>
    class hash_map{
    public:
        using key_type = K;
        using mapped_type = T;
        using hasher = Hash;
        using key_equal = Pred;
        using allocator_type = Alloc;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = hash_map_iterator<value_type>;
        using const_iterator = hash_map_const_iterator<value_type>;
        using size_type = std::size_t;

        /// Default constructor.
        hash_map():m_alloc(), m_size(0), m_set(),
                   real_size(0), load(0), m_hash(), m_key_equal(),
                   default_load_factor(2.0/3.0) {
        }

        /**
         *  @brief  Default constructor creates no elements.
         *  @param n  Minimal initial number of buckets.
         */

        explicit hash_map(size_type n) : m_alloc(),
                                         m_data(m_alloc.allocate(n)),
                                         m_size(n),
                                         m_set((n), 0),
                                         real_size(0),
                                         load(0),
                                         m_hash(),
                                         m_key_equal(),
                                         default_load_factor(2.0/3.0) {}

        /**
         *  @brief  Builds an %hash_map from a range.
         *  @param  first  An input iterator.
         *  @param  last  An input iterator.
         *  @param  n  Minimal initial number of buckets.
         *
         *  Create an %hash_map consisting of copies of the elements from
         *  [first,last).  This is linear in N (where N is
         *  distance(first,last)).
         *
         */

        template<typename InputIterator>
        hash_map(InputIterator first, InputIterator last,
                 size_type n = 0):m_alloc(),
                                  m_data(m_alloc.allocate(n)),
                                  m_size(n),
                                  m_set((n), 0),
                                  load(0),
                                  real_size(0),
                                  m_key_equal(),
                                  m_hash(),
                                  default_load_factor(2/3) {
            insert(first, last);
        }

        /// Copy constructor.
        hash_map(const hash_map &src):m_alloc(src.m_alloc),
                                      m_data(m_alloc.allocate(src.m_size)),
                                      m_size(src.m_size),
                                      load(src.load),
                                      m_set(src.m_set),
                                      real_size(src.real_size),
                                      m_key_equal(src.m_key_equal),
                                      m_hash(),
                                      default_load_factor(src.default_load_factor){
            place_elements(src);
        }


        /// Move constructor.
        hash_map(hash_map &&other) : m_alloc(other.m_alloc),
                                     m_data(other.m_data),
                                     m_size (std::move(other.m_size)),
                                     m_set (std::move(other.m_set)),
                                     real_size (std::move(other.real_size)),
                                     load (std::move(other.load)),
                                     m_key_equal(other.m_key_equal),
                                     m_hash(other.m_hash),
                                     default_load_factor(other.default_load_factor)

        {
            other.m_data = nullptr;
            other.m_size = 0;
        }

        /**
         *  @brief Creates an %hash_map with no elements.
         *  @param a An allocator object.
         */

        explicit hash_map(const allocator_type &a) : m_alloc(a),
                                                     m_data(m_alloc.allocate(0)),
                                                     m_size(0),
                                                     m_set((0), 0),
                                                     real_size(0),
                                                     load(0),
                                                     default_load_factor(2/3),
                                                     m_key_equal(),
                                                     m_hash(){}


        /**
        *  @brief Copy constructor with allocator argument.
        * @param  uset  Input %hash_map to copy.
        * @param  a  An allocator object.
        */
        hash_map(const hash_map& umap,
                 const allocator_type& a):m_alloc(a),
                                          m_data(m_alloc.allocate(umap.m_size)),
                                          m_size(umap.m_size),
                                          m_set(umap.m_set),
                                          real_size (umap.m_size),
                                          load (umap.load),
                                          default_load_factor(umap.default_load_factor),
                                          m_key_equal(umap.m_key_equal),
                                          m_hash() {
            place_elements(umap);
        }

        /**
        *  @brief  Move constructor with allocator argument.
        *  @param  uset Input %hash_map to move.
        *  @param  a    An allocator object.
        */
        hash_map(hash_map&& umap,
                 const allocator_type& a):m_alloc(a),
                                          m_data(umap.m_data),
                                          m_size (umap.m_size),
                                          m_set (std::move(umap.m_set)),
                                          real_size (umap.real_size),
                                          load (umap.load),
                                          default_load_factor(umap.default_load_factor),
                                          m_key_equal(umap.m_key_equal),
                                          m_hash()
        {
            umap.m_data = nullptr;
            umap.m_size = 0;
        }

        /**
         *  @brief  Builds an %hash_map from an initializer_list.
         *  @param  l  An initializer_list.
         *  @param n  Minimal initial number of buckets.
         *
         *  Create an %hash_map consisting of copies of the elements in the
         *  list. This is linear in N (where N is @a l.size()).
         */
        hash_map(std::initializer_list<value_type> l,
                 size_type n = 0) : m_alloc(),
                                    m_data(m_alloc.allocate(n)),
                                    m_size(n),
                                    m_set((n), 0),
                                    real_size(0),
                                    load(0),
                                    default_load_factor(2/3),
                                    m_key_equal(),
                                    m_hash(){
            insert(l);
        }

        /// Copy assignment operator.
        hash_map& operator = (const hash_map& other){ //ПРОВЕРИТЬ
            m_alloc.deallocate(m_data, m_size);
            m_data = m_alloc.allocate(other.m_size);
            m_alloc = other.m_alloc;
            m_size = other.m_size;
            m_set = other.m_set;
            load = other.load;
            real_size = other.real_size;
            default_load_factor = other.default_load_factor;
            m_key_equal = other.m_key_equal;
            m_hash = other.m_hash;
            place_elements(other);
            return *this;
        }

        // Move assignment operator.
        hash_map& operator=(hash_map &&other) {
            if (this != &other) {
                m_alloc.deallocate(m_data, m_size);
                m_data = m_alloc.allocate(other.m_size);
                m_alloc = other.m_alloc;
                m_size = other.m_size;
                m_set = std::move(other.m_set);
                load = other.load;
                real_size = other.real_size;
                default_load_factor = other.default_load_factor;
                m_key_equal = other.m_key_equal;
                m_hash = other.m_hash;

                other.m_data = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        /**
         *  @brief  %hash_map list assignment operator.
         *  @param  l  An initializer_list.
         *
         *  This function fills an %hash_map with copies of the elements in
         *  the initializer list @a l.
         *
         *  Note that the assignment completely changes the %hash_map and
         *  that the resulting %hash_map's size is the same as the number
         *  of elements assigned.
         */
        hash_map& operator=(std::initializer_list<value_type> l){
            m_alloc.deallocate(m_data, m_size);
            m_alloc.~allocator_type();
            m_key_equal.~key_equal();
            m_hash.~hasher();
            this(l);
        }
//
//        ///  Returns the allocator object used by the %hash_map.
        allocator_type get_allocator() const noexcept{
            return m_alloc;
        }

        // size and m_size:

        ///  Returns true if the %hash_map is empty.
        bool empty() const noexcept {
            return (real_size == 0);
        }

        ///  Returns the size of the %hash_map.
        size_type size() const noexcept {
            return m_size;
        }

        ///  Returns the maximum size of the %hash_map.
        size_type max_size() const noexcept{
            return std::numeric_limits<size_type>::max();
        }

        void place_elements(const hash_map &other){
            for(size_type i = 0; i < other.m_size; i++){
                if (other.m_set[i] != 0){
                    new(m_data + i) value_type{(other.m_data[i].first), (other.m_data[i].second)};
                }
            }
        }
        // iterators.

        /**
         *  Returns a read/write iterator that points to the first element in the
         *  %hash_map.
         */
        iterator begin() noexcept {
            if (m_size == 0) {
                return end();
            }

            for (size_type i = 0; i < m_size; i++) {
                if (m_set[i] == 1) {
                    return iterator(m_data, i, &m_set);
                }
            }
            return end();
        }

        //@{
        /**
         *  Returns a read-only (constant) iterator that points to the first
         *  element in the %hash_map.
         */
        const_iterator begin() const noexcept {
            if (m_size == 0) {
                return end();
            }

            for (size_type i = 0; i < m_size; i++) {
                if (m_set[i] == 1) {
                    return const_iterator(m_data, i, &m_set);
                }
            }
            return end();
        }

        const_iterator cbegin() const noexcept {
            if (m_size == 0) {
                return cend();
            }

            for (size_type i = 0; i < m_size; i++) {
                if (m_set[i]) {
                    return const_iterator(m_data, i, &m_set);
                }
            }
            return cend();
        }

        /**
         *  Returns a read/write iterator that points one past the last element in
         *  the %hash_map.
         */
        iterator end() noexcept {
            return iterator(m_data, m_size, &m_set);
        }

        //@{
        /**
         *  Returns a read-only (constant) iterator that points one past the last
         *  element in the %hash_map.
         */
        const_iterator end() const noexcept {
            return const_iterator(m_data, m_size, &m_set);
        }

        const_iterator cend() const noexcept{
            return const_iterator(m_data, m_size, &m_set);
        }
        //@}

        // modifiers.

        /**
         *  @brief Attempts to build and insert a std::pair into the
         *  %hash_map.
         *
         *  @param args  Arguments used to generate a new pair instance (see
         *	        std::piecewise_contruct for passing arguments to each
        *	        part of the pair constructor).
        *
        *  @return  A pair, of which the first element is an iterator that points
        *           to the possibly inserted pair, and the second is a bool that
        *           is true if the pair was actually inserted.
        *
        *  This function attempts to build and insert a (key, value) %pair into
        *  the %hash_map.
        *  An %hash_map relies on unique keys and thus a %pair is only
        *  inserted if its first element (the key) is not already present in the
        *  %hash_map.
        *
        *  Insertion requires amortized constant time.
        */
        template<typename... _Args>
        std::pair<iterator, bool> emplace(_Args&&... args){
            return try_emplace(std::forward<_Args>(args)...);
        }
//
//        /**
//         *  @brief Attempts to build and insert a std::pair into the
//         *  %hash_map.
//         *
//         *  @param k    Key to use for finding a possibly existing pair in
//         *                the hash_map.
//         *  @param args  Arguments used to generate the .second for a
//         *                new pair instance.
//         *
//         *  @return  A pair, of which the first element is an iterator that points
//         *           to the possibly inserted pair, and the second is a bool that
//         *           is true if the pair was actually inserted.
//         *
//         *  This function attempts to build and insert a (key, value) %pair into
//         *  the %hash_map.
//         *  An %hash_map relies on unique keys and thus a %pair is only
//         *  inserted if its first element (the key) is not already present in the
//         *  %hash_map.
//         *  If a %pair is not inserted, this function has no effect.
//         *
//         *  Insertion requires amortized constant time.
//         */

        template <typename... _Args>
        std::pair<iterator, bool> try_emplace(const key_type& k, _Args&&... args){
            change_hash();
            size_type index = find_index(k);
            if (m_set[index] == 0){
                real_size++;
                new(m_data + index) value_type{k,mapped_type(std::forward<_Args>(args)...)};
                m_set[index] = 1;
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }

            if(m_set[index] == 1){
                return std::make_pair(iterator(m_data, index, &m_set), false);
            }

            if(m_set[index] == 2){
                real_size++;
                m_data[index].~value_type();
                m_set[index] = 1;
                new(m_data + index) value_type{k,mapped_type(std::forward<_Args>(args)...)};
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }
            return std::make_pair(iterator(m_data, index, &m_set), false);
        }
//
        // move-capable overload
        template <typename... _Args>
        std::pair<iterator, bool> try_emplace(key_type&& k, _Args&&... args){
            size_type index = find_index(std::move(k));
            if (m_set[index] == 0){
                m_set[index] = 1;
                change_hash();
                new(m_data + index) value_type{std::move(k), mapped_type(std::forward<_Args>(args)...)};
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }

            if(m_set[index] == 1){
                return std::make_pair(iterator(m_data, index, &m_set), false);
            }

            if(m_set[index] == 2){
                change_hash();
                m_data[index].~value_type();
                m_set[index] = 1;
                new(m_data + index) value_type{std::move(k), mapped_type(std::forward<_Args>(args)...)};
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }
            return std::make_pair(iterator(m_data, index, &m_set), false);
        }

        //@{
        /**
         *  @brief Attempts to insert a std::pair into the %hash_map.
         *  @param x Pair to be inserted (see std::make_pair for easy
         *	     creation of pairs).
        *
        *  @return  A pair, of which the first element is an iterator that
        *           points to the possibly inserted pair, and the second is
        *           a bool that is true if the pair was actually inserted.
        *
        *  This function attempts to insert a (key, value) %pair into the
        *  %hash_map. An %hash_map relies on unique keys and thus a
        *  %pair is only inserted if its first element (the key) is not already
        *  present in the %hash_map.
        *
        *  Insertion requires amortized constant time.
        */
        size_type find_index(key_type k) const{
            size_type index = m_hash(k) % m_size;
            size_type busy_index = m_size;
            size_type count = m_size;
            while (m_set[index] != 0 || count == 0){
                if (m_key_equal(m_data[index].first, k)){
                    if(m_set[index] == 1){
                        return index;
                    }
                    if(m_set[index] == 2){
                        if(busy_index < index)
                            busy_index = index;
                    }
                }
                index = (index + 1) % m_size;
                count--;
            }
            if (index < busy_index){
                return index;
            }

            else{
                return busy_index;
            }
        }

        std::pair<iterator, bool> insert(const value_type& x){
            change_hash();
            size_type index = find_index(x.first);
            if (m_set[index] == 0){
                real_size++;
                new(m_data + index) value_type{x.first, x.second};
                m_set[index] = 1;
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }

            if(m_set[index] == 1){
                return std::make_pair(iterator(m_data, index, &m_set), false);
            }

            if(m_set[index] == 2){
                real_size++;
                m_data[index].~value_type();
                m_set[index] = 1;
                new(m_data + index) value_type{x.first, x.second};
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }
            return std::make_pair(iterator(m_data, index, &m_set), false);
        }

        std::pair<iterator, bool> insert(value_type&& x){
            change_hash();
            size_type index = find_index(x.first);
            if (m_set[index] == 0){
                real_size++;
                new(m_data + index) value_type{std::move(x.first), std::move(x.second)};
                m_set[index] = 1;
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }

            if(m_set[index] == 1){
                return std::make_pair(iterator(m_data, index, &m_set), false);
            }

            if(m_set[index] == 2){
                real_size++;
                m_data[index].~value_type();
                m_set[index] = 1;
                new(m_data + index) value_type{std::move(x.first), std::move(x.second)};
                return std::make_pair(iterator(m_data, index, &m_set), true);
            }
            return std::make_pair(iterator(m_data, index, &m_set), false);
        }

        //@}

        /**
         *  @brief A template function that attempts to insert a range of
         *  elements.
         *  @param  first  Iterator pointing to the start of the range to be
         *                   inserted.
         *  @param  last  Iterator pointing to the end of the range.
         *
         *  Complexity similar to that of the range constructor.
         */
        template<typename _InputIterator>
        void insert(_InputIterator first, _InputIterator last){
            while(first != last){
                insert(*first);
                ++first;
            }
        }

        /**
         *  @brief Attempts to insert a list of elements into the %hash_map.
         *  @param  l  A std::initializer_list<value_type> of elements
         *               to be inserted.
         *
         *  Complexity similar to that of the range constructor.
         */
        void insert(std::initializer_list<value_type> l){
            insert(l.begin(), l.end());
        }


        /**
         *  @brief Attempts to insert a std::pair into the %hash_map.
         *  @param k    Key to use for finding a possibly existing pair in
         *                the map.
         *  @param obj  Argument used to generate the .second for a pair
         *                instance.
         *
         *  @return  A pair, of which the first element is an iterator that
         *           points to the possibly inserted pair, and the second is
         *           a bool that is true if the pair was actually inserted.
         *
         *  This function attempts to insert a (key, value) %pair into the
         *  %hash_map. An %hash_map relies on unique keys and thus a
         *  %pair is only inserted if its first element (the key) is not already
         *  present in the %hash_map.
         *  If the %pair was already in the %hash_map, the .second of
         *  the %pair is assigned from obj.
         *
         *  Insertion requires amortized constant time.
         */
//        template <typename _Obj>
//        std::pair<iterator, bool> insert_or_assign(const key_type& k, _Obj&& obj);
//
////        // move-capable overload
//        template <typename _Obj>
//        std::pair<iterator, bool> insert_or_assign(key_type&& k, _Obj&& obj);

        //@{
        /**
         *  @brief Erases an element from an %hash_map.
         *  @param  position  An iterator pointing to the element to be erased.
         *  @return An iterator pointing to the element immediately following
         *          @a position prior to the element being erased. If no such
         *          element exists, end() is returned.
         *
         *  This function erases an element, pointed to by the given iterator,
         *  from an %hash_map.
         *  Note that this function only erases the element, and that if the
         *  element is itself a pointer, the pointed-to memory is not touched in
         *  any way.  Managing the pointer is the user's responsibility.
         */
        iterator erase(const_iterator position){
            iterator it = find(position->first);
            if (it != end()){
                m_set[it.index] = 2;
                return  ++it;
            }
            return end();
        }
//
        // LWG 2059.
        iterator erase(iterator position){
            auto it = find(position->first);
            if (it != end()){
                m_set[it.index] = 2;
                return ++it;
            }
            return end();
        }
        //@}

        /**
         *  @brief Erases elements according to the provided key.
         *  @param  x  Key of element to be erased.
         *  @return  The number of elements erased.
         *
         *  This function erases all the elements located by the given key from
         *  an %hash_map. For an %hash_map the result of this function
         *  can only be 0 (not present) or 1 (present).
         *  Note that this function only erases the element, and that if the
         *  element is itself a pointer, the pointed-to memory is not touched in
         *  any way.  Managing the pointer is the user's responsibility.
         */
//
        size_type erase(const key_type& x){
            iterator it = find(x);
            if (it != end()){
                m_set[it.index] == 2;
                return 1;
            }
            else
                return 0;
        }

        /**
         *  @brief Erases a [first,last) range of elements from an
         *  %hash_map.
         *  @param  first  Iterator pointing to the start of the range to be
         *                  erased.
         *  @param last  Iterator pointing to the end of the range to
         *                be erased.
         *  @return The iterator @a last.
         *
         *  This function erases a sequence of elements from an %hash_map.
         *  Note that this function only erases the elements, and that if
         *  the element is itself a pointer, the pointed-to memory is not touched
         *  in any way.  Managing the pointer is the user's responsibility.
         */
        iterator erase(const_iterator first, const_iterator last){
            while(first != last){
                erase(first);
                ++first;
            }
            return end();
        }

        /**
         *  Erases all elements in a n %hash_map.
         *  Note that this function only erases the elements, and that if the
         *  elements themselves are pointers, the pointed-to memory is not touched
         *  in any way.  Managing the pointer is the user's responsibility.
         */
        void clear() noexcept{
            for (size_type i = 0; i < m_size; i++){
                m_data[i].~value_type();
                m_set[i] = 0;
            }
            real_size = 0;
            load = 0;
        }

        /**
         *  @brief  Swaps data with another %hash_map.
         *  @param  x  An %hash_map of the same element and allocator
         *  types.
         *
         *  This exchanges the elements between two %hash_map in constant
         *  time.
         *  Note that the global std::swap() function is specialized such that
         *  std::swap(m1,m2) will feed to this function.
         */

        void swap(hash_map& x){
            using std::swap;
            swap(m_data, x.m_data);
            swap(m_set, x.m_set);
            swap(m_size, x.m_size);
            swap(real_size, x.real_size);
            swap(load, x.load);
        }

        template<typename _H2, typename _P2>
        void merge(hash_map<K, T, _H2, _P2, Alloc>& source){
            insert(source.begin(), source.end());
        }

        template<typename _H2, typename _P2>
        void merge(hash_map<K, T, _H2, _P2, Alloc>&& source){
            insert(source.begin(), source.end());
        }

        // observers.

        ///  Returns the hash functor object with which the %hash_map was
        ///  constructed.
        Hash hash_function() const{
            return m_hash;
        }

        ///  Returns the key comparison object with which the %hash_map was
        ///  constructed.
        Pred key_eq() const{
            return m_key_equal;
        }

        // lookup.

        //@{
        /**
         *  @brief Tries to locate an element in an %hash_map.
         *  @param  x  Key to be located.
         *  @return  Iterator pointing to sought-after element, or end() if not
         *           found.
         *
         *  This function takes a key and tries to locate the element with which
         *  the key matches.  If successful the function returns an iterator
         *  pointing to the sought after element.  If unsuccessful it returns the
         *  past-the-end ( @c end() ) iterator.
         */
        iterator find(const key_type& x){
            size_type index = m_hash(x) % m_set.size();
            if (m_set[index] == 1){
                return (iterator(m_data, index, &m_set));
            }
            return (end());
        }

        const_iterator find(const key_type& x) const{
            size_type index = m_hash(x) % m_set.size();
            if (m_set[index] == 1){
                return (const_iterator(m_data, index, &m_set));
            }
            return (cend());
        }
        //@}

        /**
         *  @brief  Finds the number of elements.
         *  @param  x  Key to count.
         *  @return  Number of elements with specified key.
         *
         *  This function only makes sense for %unordered_multimap; for
         *  %hash_map the result will either be 0 (not present) or 1
         *  (present).
         */
        size_type count(const key_type& x) const{
            size_type index = m_hash(x) % m_set.size();
            auto it = find(x);
            if (it != end()){
                return 1;
            }
            else
                return 0;
        }

        /**
         *  @brief  Finds whether an element with the given key exists.
         *  @param  x  Key of elements to be located.
         *  @return  True if there is any element with the specified key.
         */
        bool contains(const key_type& x) const{
            auto it = find(x);
            if (it != end()){
                return true;
            }
            else
                return false;
        }

        //@{
        /**
         *  @brief  Subscript ( @c [] ) access to %hash_map data.
         *  @param  k  The key for which data should be retrieved.
         *  @return  A reference to the data of the (key,data) %pair.
         *
         *  Allows for easy lookup with the subscript ( @c [] )operator.  Returns
         *  data associated with the key specified in subscript.  If the key does
         *  not exist, a pair with that key is created using default values, which
         *  is then returned.
         *
         *  Lookup requires constant time.
         */
        mapped_type& operator[](const key_type& k){
            size_type index = find_index(k);
            if (m_set[index] == 1)
                return m_data[index].second;
            if (m_set[index] == 2){
                change_hash();
                m_data[index].~value_type();
                new(m_data + index) value_type{k, mapped_type{}};
                m_set[index] = 1;
                return m_data[index].second;
            }
            else {
                change_hash();
                new(m_data + index) value_type{k, mapped_type{}};
                m_set[index] = 1;
                return m_data[index].second;
            }
        }

        mapped_type& operator[](key_type&& k){
            size_type index = find_index(m_hash(std::move(k)));
            if (m_set[index] == 1) {
                return m_data[index].second;
            }
            if (m_set[index] == 2){
                change_hash();
                m_data[index].~value_type();
                new(m_data + index) value_type{k, mapped_type{}};
                m_set[index] = 1;
                return m_data[index].second;
            }
            else {
                change_hash();
                new(m_data + index) value_type{k, mapped_type{}};
                m_set[index] = 1;
                return m_data[index].second;
            }
        }
        //@}

        //@{
        /**
         *  @brief  Access to %hash_map data.
         *  @param  k  The key for which data should be retrieved.
         *  @return  A reference to the data whose key is equal to @a k, if
         *           such a data is present in the %hash_map.
         *  @throw  std::out_of_range  If no such data is present.
         */
        mapped_type& at(const key_type& k){
            size_type index = find_index(k);
            if (m_set[index] == 1){
                return m_data[index].second;
            }
            else{
                throw std::out_of_range("No such data is present.");
            }
        }

        const mapped_type& at(const key_type& k) const{
            const iterator it = find(k);
            if (it != (*m_data).end){
                size_type index = m_hash(k) % m_set.size();
                if (m_set[index] == 1){
                    return m_data[index].second;
                }
            }
            else{
                throw std::out_of_range("No such data is present.");
            }
        }
        //@}

        // bucket interface.

        /// Returns the number of buckets of the %hash_map.
        size_type bucket_count() const noexcept{
            return real_size;
        }

        /*
        * @brief  Returns the bucket index of a given element.
        * @param  _K  A key instance.
        * @return  The key bucket index.
        */
        size_type bucket(const key_type& _K) const {
            auto it = find(_K);
            if (it != end()) {
                size_type index = m_hash(_K) % m_set.size();
                if (m_set[index] == 1) {
                    return index;
                }
            }
            else{
                return -1;
            }
        }

        // hash policy.

        /// Returns the average number of elements per bucket.
        float load_factor() const noexcept{
            if ( m_size == 0)
                return 1;
            float loadd = real_size / m_size;
            return loadd;
        }

        /// Returns a positive number that the %hash_map tries to keep the
        /// load factor less than or equal to.
        float max_load_factor() const noexcept{
            return default_load_factor;
        }

        /**
         *  @brief  Change the %hash_map maximum load factor.
         *  @param  z The new maximum load factor.
         */
        void max_load_factor(float z){
            default_load_factor = z;

        }

        /**
         *  @brief  May rehash the %hash_map.
         *  @param  n The new number of buckets.
         *
         *  Rehash will occur only if the new number of buckets respect the
         *  %hash_map maximum load factor.
         */

        void rehash(size_type n){
            hash_map other(n);
            other.insert(this->begin(), this->end());
            *this = std::move(other);
        }

        void change_hash(){
            load = load_factor();
            if (load_factor() > default_load_factor){
                rehash(2 * (m_size +  1));
            }
        }

        /**
         *  @brief  Prepare the %hash_map for a specified number of
         *          elements.
         *  @param  n Number of elements required.
         *
         *  Same as rehash(ceil(n / max_load_factor())).
         */
        void reserve(size_type n){
            rehash(n);
        }

        bool operator==(const hash_map& other) const{
            if (real_size == other.real_size){
                if (m_size == 0){
                    return true;
                }
                auto this_it = begin();
                while (this_it != (end())){
                    auto oth_it = (find(this_it->first));
                    if (oth_it == other.end()){
                        return false;
                    }
                    ++this_it;
                }
                return true;
            }
            else
                return false;
        }

    private:
        allocator_type m_alloc; // выделяет память для m_size
        hasher m_hash;// хэш-функция
        key_equal m_key_equal; // Хрень которая сравнивает ключи??
        std::vector<char> m_set; // Вектор состояния
        value_type* m_data; // Все тут хранится
        size_type m_size; // Размер m_data
        float default_load_factor; // р-р
        float load;
        size_type real_size; //  Настоящая загруженность
    };

} // namespace fefu