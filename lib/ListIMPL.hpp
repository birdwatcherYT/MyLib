#ifndef LISTIMPL_HPP
#define	LISTIMPL_HPP

#include "ListDECL.hpp"

namespace mylib {

    template<class T>
    List<T>::List() {
        Node *dummy = allocNode();
        head = tail = dummy;
        tail->next = tail;
    }

    template<class T>
    List<T>::List(const ULLONG &size) {
        Node *dummy = allocNode();
        head = tail = dummy;
        tail->next = tail;
        resize(size);
    }

    /**
     * 配列からリストを作る
     * @param array
     * @param size
     */
    template<class T>
    List<T>::List(const T* array, const ULLONG &size) {
        Node *dummy = allocNode();
        head = tail = dummy;
        tail->next = tail;
        for (const T *p = array; p != &array[size]; ++p)
            this->pushTail(*p);
    }

    template<class T>
    List<T>::List(const List<T> &_list) {
        *this = _list;
    }

    template<class T>
    List<T>::~List() {
        this->clear();
        free(tail);
    }

    /**
     * ノードのメモリ確保
     * @return 
     */
    template<class T>
    typename List<T>::Node *List<T>::allocNode() const {
        Node *p = (Node*) malloc(sizeof (Node));
        ASSERT(p != NULL, "Error : メモリ確保に失敗");
        return p;
    }

    /**
     * 先頭イテレーター
     * @return 
     */
    template<class T>
    typename List<T>::Iterator List<T>::begin()const {
        return Iterator(head);
    }

    /**
     * 末尾イテレーター(ダミーノードのポインタ)
     * @return 
     */
    template<class T>
    typename List<T>::Iterator List<T>::end() const {
        return Iterator(tail);
    }

    /**
     * リストの先頭にdataを追加
     * @param data
     */
    template<class T>
    void List<T>::pushHead(const T &data) {
        Node *newNode = allocNode();
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }

    /**
     * リストの末尾にdataを追加
     * @param data
     */
    template<class T>
    void List<T>::pushTail(const T &data) {
        Node *newNode = allocNode();
        tail->data = data;
        tail->next = newNode;
        tail = newNode;
        tail->next = tail;
    }

    /**
     * 全要素削除(ダミーノード以外)
     */
    template<class T>
    void List<T>::clear() {
        Node *p = head, *q;
        while (p != tail) {
            q = p->next;
            free(p);
            p = q;
        }
        head = tail;
    }

    /**
     * itから末尾まで削除
     * @param it
     */
    template<class T>
    void List<T>::clear(const Iterator& it) {
        for (Iterator i = it; i != end();)
            i = erase(i);
    }

    /**
     * 順番反転
     */
    template<class T>
    void List<T>::reverse() {
        List<T> newList;
        T data;
        while (this->popHead(data))
            newList.pushHead(data);

        while (newList.popHead(data))
            this->pushTail(data);
    }

    /**
     * サイズの変更
     * @param newSize
     */
    template<class T>
    void List<T>::resize(const ULLONG &newSize) {
        T data;
        resize(newSize, data);
    }

    /**
     * サイズの変更(新しい要素はdataで埋める)
     * @param newSize
     * @param data
     */
    template<class T>
    void List<T>::resize(const ULLONG &newSize, const T& data) {
        Node *p = head;
        ULLONG i;
        for (i = 0; i < newSize && p != tail; ++i)
            p = p->next;
        if (p == tail) {
            for (; i < newSize; ++i)
                pushTail(data);
        } else {
            clear(Iterator(p));
        }
    }

    /**
     * dataの値を持つノードを削除
     * @param data
     */
    template<class T>
    void List<T>::remove(const T& data) {
        Iterator it = begin();
        while ((it = find(data, it)) != end())
            it = erase(it);
    }

    template<class T>
    void List<T>::print(std::ostream &os)const {
        Node *p = head;
        while (p != tail) {
            os << p->data << ",";
            p = p->next;
        }
        os << "\b " << std::endl;
    }

    /**
     * 空かどうか返す
     * @return 
     */
    template<class T>
    bool List<T>::empty() const {
        return (head == tail);
    }

    /**
     * 要素数を返す
     * @return 
     */
    template<class T>
    ULLONG List<T>::size() const {
        ULLONG i = 0;
        Node *p = head;
        while (p != tail) {
            ++i;
            p = p->next;
        }
        return i;
    }

    /**
     * 先頭要素をdataに格納後、削除
     * @param data
     * @return 格納成功
     */
    template<class T>
    bool List<T>::popHead(T &data) {
        if (empty()) return false;

        Node *tmp = head->next;
        data = head->data;
        free(head);
        head = tmp;
        return true;
    }

    /**
     * 先頭要素の削除
     * @return 
     */
    template<class T>
    bool List<T>::popHead() {
        if (empty()) return false;

        Node *tmp = head->next;
        free(head);
        head = tmp;
        return true;
    }

    /**
     * pos番目のデータを参照\n
     * 順番にアクセスする場合Iteratorを使うと効率が良い
     * @param pos [0,size-1]
     * @return 
     */
    template<class T>
    T &List<T>::operator[](const ULLONG& pos) {
        Node *p = head;
        //pos回進む
        for (ULLONG i = 0ULL; i < pos; ++i)
            p = p->next;
        return p->data;
    }

    template<class U>
    std::ostream &operator<<(std::ostream &os, const List<U> &__list) {
        __list.print(os);
        return os;
    }

    template<class T>
    List<T> &List<T>::operator=(const List<T>& _list) {
        this->clear();
        for (const Node* p = _list.head; p != _list.tail; p = p->next)
            this->pushTail(p->data);

        return *this;
    }

    /**
     * 先頭要素を返す
     * @return 
     */
    template<class T>
    T List<T>::front() const {
        return head->data;
    }

    /**
     * すべてdataの値にする
     * @param data
     */
    template<class T>
    void List<T>::allSet(const T& data) const {
        Node *p = head;
        while (p != tail) {
            p->data = data;
            p = p->next;
        }
    }

    /**
     * itの位置の要素をdataの値にする
     * @param data
     * @param it
     */
    template<class T>
    void List<T>::set(const T& data, const Iterator &it) const {
        *it = data;
    }

    /**
     * itからdataの値を持つ場所を探す
     * @param data
     * @param it
     * @return 見つかった位置
     */
    template<class T>
    typename List<T>::Iterator List<T>::find(const T& data, const Iterator &it)const {
        Iterator i = it;
        while (i != end()) {
            if (*i == data)return i;
            ++i;
        }
        return end();
    }

    /**
     * itの位置からどれだけ後にdataがあるか
     * @param data
     * @param it
     * @param after itからの相対位置
     * @return 見つかったかどうか
     */
    template<class T>
    bool List<T>::find(const T& data, const Iterator &it, ULLONG &after)const {
        ULLONG i = 0ULL;
        Iterator p = it;
        while (p != end()) {
            if (*p == data) {
                after = i;
                return true;
            }
            ++p, ++i;
        }
        return false;
    }

    /**
     * 先頭からdataの値を持つ場所を探す
     * @param data
     * @param it
     * @return 見つかった位置
     */
    template<class T>
    typename List<T>::Iterator List<T>::find(const T& data)const {
        return find(data, begin());
    }

    /**
     * itの位置にdataを挿入
     * @param it
     * @param data
     */
    template<class T>
    void List<T>::insert(const Iterator& it, const T &data) {
        if (it == begin()) {
            pushHead(data);
        } else if (it == end()) {
            pushTail(data);
        } else {
            Node *newNode = allocNode();
            newNode->data = it->data;
            newNode->next = it->next;
            it->data = data;
            it->next = newNode;
        }
    }

    /**
     * itの位置のdataを削除
     * @param it
     * @return 
     */
    template<class T>
    typename List<T>::Iterator List<T>::erase(const Iterator& it) {
        if (it == end()) return it;
        Node *tmp = it->next;
        it->data = tmp->data;
        it->next = tmp->next;
        if (tmp == tail) {
            tail = (Node*) it;
            tail->next = tail;
        }
        free(tmp);
        return it;
    }

    template<class T>
    List<T>::Iterator::Iterator() {
        pointer = NULL;
    }

    template<class T>
    List<T>::Iterator::Iterator(Node *p) {
        pointer = p;
    }

    template<class T>
    T &List<T>::Iterator::operator*()const {
        return pointer->data;
    }

    template<class T>
    bool List<T>::Iterator::operator!=(const Iterator &it) const {
        return pointer != it.pointer;
    }

    template<class T>
    bool List<T>::Iterator::operator==(const Iterator &it) const {
        return pointer == it.pointer;
    }

    template<class T>
    typename List<T>::Iterator& List<T>::Iterator::operator=(Node *p) {
        pointer = p;
        return *this;
    }

    template<class T>
    typename List<T>::Iterator List<T>::Iterator::operator++() {
        pointer = pointer->next;
        return *this;
    }

    template<class T>
    typename List<T>::Iterator List<T>::Iterator::operator++(int n) {
        Iterator tmp = pointer;
        pointer = pointer->next;
        return tmp;
    }

    template<class T>
    typename List<T>::Iterator List<T>::Iterator::operator+(const ULLONG& n) const {
        Iterator it = *this;
        for (ULLONG i = 0; i < n; ++i)
            it.pointer = it.pointer->next;
        return it;
    }

    template<class T>
    typename List<T>::Iterator List<T>::Iterator::operator+=(const ULLONG& n) {
        for (ULLONG i = 0; i < n; ++i)
            pointer = pointer->next;
        return *this;
    }

    template<class T>
    typename List<T>::Node* List<T>::Iterator::operator->() const {
        return pointer;
    }

}

#endif	/* LISTIMPL_HPP */
