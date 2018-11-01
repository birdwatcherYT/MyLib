#ifndef LISTDECL_HPP
#define	LISTDECL_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Utility.hpp"
#include "Typedefs.hpp"

namespace mylib {

    /**
     * 線形リスト\n
     * List();\n
     * List(const ULLONG &size);\n
     * List(const T* array, const ULLONG &size);\n
     * List(const List<T> &_list);\n
     * 末尾にはダミーノード
     */
    template<class T>
    class List {
    private:

        /**
         * リストのノードを表す
         */
        class Node {
        public:
            T data;
            Node *next;
        };
    public:

        /**
         * リストのイテレーター
         */
        class Iterator {
            Node *pointer;
        public:
            Iterator();
            Iterator(Node *p);
            bool operator!=(const Iterator &it)const;
            bool operator==(const Iterator &it)const;
            Node* operator->()const;
            Iterator& operator=(Node *p);
            T &operator*()const;
            Iterator operator++();
            Iterator operator++(int n);
            Iterator operator+(const ULLONG &n)const;
            Iterator operator+=(const ULLONG &n);

            operator Node*()const {
                return pointer;
            }
        };
    private:
        Node *head, *tail;
        Node *allocNode() const;
    public:
        List();
        List(const ULLONG &size);
        List(const T* array, const ULLONG &size);
        List(const List<T> &_list);
        ~List();
        Iterator begin()const;
        Iterator end()const;
        T front()const;
        void allSet(const T &data)const;
        void set(const T &data, const Iterator &it)const;
        void pushHead(const T &data);
        void pushTail(const T &data);
        bool popHead(T &data);
        bool popHead();
        bool empty()const;
        ULLONG size()const;
        void clear();
        void clear(const Iterator &it);
        void reverse();
        void insert(const Iterator& it, const T &data);
        Iterator erase(const Iterator& it);
        Iterator find(const T& data, const Iterator &it)const;
        Iterator find(const T& data)const;
        bool find(const T& data, const Iterator &it, ULLONG &after)const;
        void resize(const ULLONG &newSize);
        void resize(const ULLONG &newSize, const T& data);
        void remove(const T &data);
        void print(std::ostream &os = std::cout)const;
        T &operator[](const ULLONG &pos);
        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const List<U> &__list);
        List<T> &operator=(const List<T> &_list);
    };

}
#endif	/* LISTDECL_HPP */

