/*
 * Copyright (C) 2012 BMW Car IT GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CAPU_HASHSET_H
#define CAPU_HASHSET_H

#include "capu/container/Hash.h"
#include "capu/container/HashTable.h"

namespace capu
{
    /**
     * Unordered set of objects with fast lookup and retrieval.
     */
    template <class T, class C = Comparator, class H = CapuDefaultHashFunction>
    class HashSet
    {
    private:
        class HashSetIterator
        {
        public:

            /**
             * constructor
             *
             * @param list     array of linked list which provide channing for hash set
             * @param listSize size of hash set (size of linked list array)
             */
            HashSetIterator(const HashSetIterator& iter);

            /**
             * destructor
             */
            ~HashSetIterator();

            HashSetIterator& operator=(const HashSetIterator& iter);

            /**
             * Indirection
             * @return the current value referenced by the iterator
             */
            const T& operator*();

            /**
             * Dereference
             * @return a pointer to the current object the iterator points to
             */
            const T* operator->();

            /**
             * Compares two iterators
             * @return true if the iterators point to the same position
             */
            capu::bool_t operator==(const HashSetIterator& iter) const;

            /**
             * Compares two iterators
             * @return true if the iterators do not point to the same position
             */
            capu::bool_t operator!=(const HashSetIterator& iter) const;

            /**
             * Step the iterator forward to the next element (prefix operator)
             * @return the next iterator
             */
            const HashSetIterator& operator++() const;

            /**
             * Step the iterator forward to the next element (prefix operator)
             * @return the next iterator
             */
            HashSetIterator& operator++();

            /**
             * Step the iterator forward to the next element (postfix operator)
             * @return the next iterator
             */
            const HashSetIterator operator++(int32_t) const;

            /**
             * Step the iterator forward to the next element (postfix operator)
             * @return the next iterator
             */
            HashSetIterator operator++(int32_t);

        private:

            friend class HashSet<T, C, H>;

            /**
             * Internal constructor for HashSet
             *
             * @para iter iterator of the underlying hashtable
             */
            HashSetIterator(const typename HashTable<T, char_t, C, H>::Iterator& iter);

            typename HashTable<T, char_t, C, H>::Iterator m_iter;
        };

    public:

        /**
         * Iterator for hashsets
         */
        typedef HashSetIterator Iterator;

        /**
         * Default Constructor
         */
        HashSet();

        /**
         * Parameterized Constructor
         * @param bitsize size of initial HashSet
         */
        HashSet(const uint8_t bitsize);

        /**
         * Copy constructor.
         */
        HashSet(const HashSet& other);

        /**
         * Destructor
         */
        ~HashSet();

        /**
         * put a new value to the hash set.
         *
         * @param value             new value that will be put to hash set
         *
         * @return CAPU_OK if remove is successful
         *         CAPU_ERROR if value already exists in the set
         *
         */
        status_t put(const T& value);

        /**
         * Remove value associated with key in the hash set.
         *
         * @param value             value that will be removed
         *
         * @return CAPU_OK if remove is successful
         *         CAPU_ERANGE if specified value does not exist in hash set
         *
         */
        status_t remove(const T& value);

        /**
         * Checks if the provided value is already contained in the hash set.
         *
         * @param value             value that will be checked
         *
         * @return true if element is already contained in the hash set
         *         false otherwise
         *
         */
        bool_t hasElement(const T& value) const;

        /**
         * Returns count of the hash set.
         * @return number of element in hash set
         */
        uint_t count() const;

        /**
         * Clear all values of the hash set.
         *
         * @return CAPU_OK if all elements in list have been deleted
         */
        status_t clear();

        /**
         * Return iterator for iterating key value tuples.
         * @return Iterator
         */
        Iterator begin() const;

        /**
         * returns an interator pointing after the last element of the list
         * @return iterator
         */
        const Iterator end() const;

    private:
        HashTable<T, char_t, C, H> m_table;
    };

    template <class T, class C, class H>
    HashSet<T, C, H>::HashSet(const HashSet& other)
        : m_table(other.m_table) // just copy the inner hash table (which defines a copy constructor)
    {
    }

    template <class T, class C, class H>
    HashSet<T, C, H>::HashSet()
        : m_table(DEFAULT_HASH_SET_BIT_SIZE)
    {
    }

    template <class T, class C, class H>
    HashSet<T, C, H>::~HashSet()
    {
    }

    template <class T, class C, class H>
    HashSet<T, C, H>::HashSet(const uint8_t bitsize)
        : m_table(bitsize)
    {
    }

    template <class T, class C, class H>
    status_t HashSet<T, C, H>::put(const T& value)
    {
        if (m_table.contains(value))
        {
            return CAPU_ERROR;
        }
        return m_table.put(value, 0);
    }

    template <class T, class C, class H>
    status_t HashSet<T, C, H>::remove(const T& value)
    {
        return m_table.remove(value);
    }

    template <class T, class C, class H>
    bool_t HashSet<T, C, H>::hasElement(const T& value) const
    {
        return m_table.contains(value);
    }

    template <class T, class C, class H>
    uint_t HashSet<T, C, H>::count() const
    {
        return m_table.count();
    }

    template <class T, class C, class H>
    status_t HashSet<T, C, H>::clear()
    {
        m_table.clear();
        return CAPU_OK;
    }

    template <class T, class C, class H>
    typename HashSet<T, C, H>::Iterator HashSet<T, C, H>::begin() const
    {
        return Iterator(m_table.begin());
    }

    template <class T, class C, class H>
    const typename HashSet<T, C, H>::Iterator HashSet<T, C, H>::end() const
    {
        return Iterator(m_table.end());
    }

    template <class T, class C, class H>
    HashSet<T, C, H>::HashSetIterator::HashSetIterator(const typename HashTable<T, char_t, C, H>::Iterator& iter)
        : m_iter(iter)
    {
    }

    template <class T, class C, class H>
    HashSet<T, C, H>::HashSetIterator::HashSetIterator(const HashSetIterator& iter)
        : m_iter(iter.m_iter)
    {
    }

    template <class T, class C, class H>
    HashSet<T, C, H>::HashSetIterator::~HashSetIterator()
    {
    }

    template <class T, class C, class H>
    typename HashSet<T, C, H>::HashSetIterator& HashSet<T, C, H>::HashSetIterator::operator=(const HashSetIterator& iter)
    {
        m_iter = iter.m_iter;
        return *this;
    }

    template <class T, class C, class H>
    const T& HashSet<T, C, H>::HashSetIterator::operator*()
    {
        typename HashTable<T, char_t, C, H>::HashTableEntry& entry = *m_iter;
        return entry.key;
    }

    template <class T, class C, class H>
    const T* HashSet<T, C, H>::HashSetIterator::operator->()
    {
        const typename HashTable<T, char_t, C, H>::HashTableEntry& entry = *m_iter;
        return &(entry.key);
    }

    template <class T, class C, class H>
    capu::bool_t HashSet<T, C, H>::HashSetIterator::operator==(const HashSetIterator& iter) const
    {
        return m_iter == iter.m_iter;
    }

    template <class T, class C, class H>
    capu::bool_t HashSet<T, C, H>::HashSetIterator::operator!=(const HashSetIterator& iter) const
    {
        return m_iter != iter.m_iter;
    }

    template <class T, class C, class H>
    const typename HashSet<T, C, H>::HashSetIterator& HashSet<T, C, H>::HashSetIterator::operator++() const
    {
        m_iter++;
        return *this;
    }

    template <class T, class C, class H>
    typename HashSet<T, C, H>::HashSetIterator& HashSet<T, C, H>::HashSetIterator::operator++()
    {
        m_iter++;
        return *this;
    }

    template <class T, class C, class H>
    const typename HashSet<T, C, H>::HashSetIterator HashSet<T, C, H>::HashSetIterator::operator++(int32_t) const
    {
        typename HashSet<T, C, H>::HashSetIterator oldValue(*this);
        ++(*this);
        return oldValue;
    }

    template <class T, class C, class H>
    typename HashSet<T, C, H>::HashSetIterator HashSet<T, C, H>::HashSetIterator::operator++(int32_t)
    {
        typename HashSet<T, C, H>::HashSetIterator oldValue(*this);
        ++(*this);
        return oldValue;
    }
}

#endif /* CAPU_HASHSET_H */
