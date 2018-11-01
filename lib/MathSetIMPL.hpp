#ifndef MATHSETIMPL_HPP
#define	MATHSETIMPL_HPP

#include "MathSetDECL.hpp"

namespace mylib {

    template<class X, class Y >
    Pair<X, Y>::Pair() {
    }

    template<class X, class Y >
    Pair<X, Y>::Pair(const X &x, const Y &y) {
        this->x = x;
        this->y = y;
    }

    template<class X, class Y >
    void Pair<X, Y>::setXY(const X &x, const Y &y) {
        this->x = x;
        this->y = y;
    }

    template<class X, class Y >
    bool Pair<X, Y>::operator<(const Pair<X, Y>& c) const {
        if ((x == c.x && y < c.y) || x < c.x)return true;
        return false;
    }

    template<class X, class Y >
    bool Pair<X, Y>::operator>(const Pair<X, Y>& c) const {
        if ((x == c.x && y > c.y) || x > c.x)return true;
        return false;
    }

    template<class X, class Y >
    bool Pair<X, Y>::operator>=(const Pair<X, Y>& c) const {
        if ((x == c.x && y <= c.y) || x < c.x)return true;
        return false;
    }

    template<class X, class Y >
    bool Pair<X, Y>::operator<=(const Pair<X, Y>& c) const {
        if ((x == c.x && y >= c.y) || x > c.x)return true;
        return false;
    }

    template<class X, class Y >
    bool Pair<X, Y>::operator==(const Pair<X, Y>& c) const {
        if (x != c.x || y != c.y)return false;
        return true;
    }

    template<class X, class Y >
    bool Pair<X, Y>::operator!=(const Pair<X, Y>& c) const {
        if (x != c.x || y != c.y)return true;
        return false;
    }

    template<class T>
    MathSet<T>::MathSet() {
    }

    template<class T>
    MathSet<T>::MathSet(const T *ary, const int &n) {
        this->setElements(ary, n);
    }

    /**
     * べき集合の順番を整理するためだけに定義されたオペレータ(本来の集合の包含関係ではない)
     */
    template<class T >
    bool MathSet< T >::operator<(const MathSet< T >& s) const {
        if (this->size() < s.size())return true;
        if (this->size() == s.size()) {
            for (typename MathSet< T >::iterator it1 = this->begin(), it2 = s.begin(); it1 != this->end(); ++it1, ++it2)
                if (*it1 < *it2)return true;
        }
        return false;
    }

    /**
     * べき集合の順番を整理するためだけに定義されたオペレータ(本来の集合の包含関係ではない)
     */
    template<class T >
    bool MathSet< T >::operator>(const MathSet< T >& s) const {
        typename MathSet<T >::iterator it1, it2;
        if (this->size() > s.size())return true;
        if (this->size() == s.size()) {
            for (it1 = this->begin(), it2 = s.begin(); it1 != this->end(); ++it1, ++it2) {
                if (*it1>*it2)return true;
            }
        }
        return false;
    }

    template<class T >
    bool MathSet< T >::operator==(const MathSet< T >& s) const {

        typename MathSet<T >::iterator it1, it2;
        if (this->size() != s.size())return false;
        for (it1 = this->begin(), it2 = s.begin(); it1 != this->end(); ++it1, ++it2) {
            if (*it1 != *it2)return false;
        }
        return true;
    }

    template<class T >
    T MathSet< T >::operator[](const int& i)const {
        ASSERT(i < this->size(), "Error : 範囲外の参照");

        typename MathSet<T >::iterator it = this->begin();
        for (int k = 0; k < i; ++k)
            ++it;
        return *it;
    }

    template<class T>
    MathSet<T> MathSet<T>::operator+(const MathSet<T> &s)const {
        return unionSet(s);
    }

    template<class T>
    MathSet<T> MathSet<T>::operator-(const MathSet<T> &s)const {
        return differenceSet(s);
    }

    /**
     * 集合の要素をセット
     * @param ary
     * @param n
     */
    template<class T>
    void MathSet<T>::setElements(const T *ary, const int &n) {
        for (int i = 0; i < n; ++i)
            this->insert(ary[i]);
    }

    /**
     * 直積集合
     * @param s
     * @return 
     */
    template<class T>
    template<class U>
    MathSet< Pair<T, U> > MathSet< T >::directProduct(const MathSet< U > &s) const {
        MathSet< Pair<T, U> > ans;
        typename MathSet< T >::iterator itT = this->begin();
        typename MathSet< U >::iterator itU;

        while (itT != this->end()) {
            itU = s.begin();
            while (itU != s.end()) {
                ans.insert(Pair< T, U >(*itT, *itU));
                ++itU;
            }
            ++itT;
        }
        return ans;
    }

    /**
     * 和集合
     * @param s
     * @return 
     */
    template<class T>
    MathSet< T > MathSet< T >::unionSet(const MathSet< T > &s)const {
        MathSet< T > ans = *this;
        typename MathSet< T >::iterator it = s.begin();
        while (it != s.end()) {

            ans.insert(*it);
            ++it;
        }
        return ans;
    }

    /**
     * 共通部分
     * @param s
     * @return 
     */
    template<class T>
    MathSet< T > MathSet< T >::intersecSet(const MathSet< T > &s)const {
        MathSet< T > ans;
        typename MathSet< T >::iterator it = s.begin();
        while (it != s.end()) {

            if (this->find(*it) != this->end())
                ans.insert(*it);
            ++it;
        }
        return ans;
    }

    /**
     * べき集合
     * @return 
     */
    template<class T>
    MathSet< MathSet< T > > MathSet< T >::powerSet()const {
        MathSet< MathSet< T > > ans;
        MathSet< T > tmp;
        typename MathSet< T >::iterator it;
        int i;
        ULONG size = this->size();
        ASSERT(size < 128, "Error : 要素数が多すぎます");
        std::bitset<128> bits;

        for (bits.reset(); !bits[size]; ++bits) {
            tmp.clear();
            for (i = 0, it = this->begin(); it != this->end(); ++i, ++it) {
                if (bits[i])
                    tmp.insert(*it);
            }
            ans.insert(tmp);
        }
        return ans;
    }

    /**
     * 差集合
     * @param s
     * @return 
     */
    template<class T>
    MathSet<T> MathSet<T>::differenceSet(const MathSet<T> &s)const {
        MathSet<T> ans;
        typename MathSet<T>::iterator it = this->begin();
        while (it != this->end()) {
            if (s.find(*it) == s.end())ans.insert(*it);
            ++it;
        }
        return ans;
    }

    template<class T>
    void MathSet< T >::print(std::ostream &os)const {
        if (this->empty()) {
            os << "φ\0";
            return;
        }
        os << "{";
        typename MathSet< T >::const_iterator it = this->begin();
        while (it != this->end()) {
            os << *it << ",";
            ++it;
        }
        os << "\b}";
    }

    template<class S, class T >
    std::ostream &operator<<(std::ostream &os, const Pair<S, T > &c) {
        os << "(" << c.x << "," << c.y << ")";
        return os;
    }

    template<class U>
    std::ostream& operator<<(std::ostream &os, const MathSet< U > &s) {
        s.print(os);
        return os;
    }
}


#endif	/* MATHSETIMPL_HPP */
