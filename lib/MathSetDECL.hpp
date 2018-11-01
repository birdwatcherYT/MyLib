#ifndef MATHSETDECL_HPP
#define	MATHSETDECL_HPP

#define Set MathSet

#include <set>
#include <iostream>
#include <bitset>
#include "Utility.hpp"
#include "Typedefs.hpp"

namespace mylib {

    /**
     * ペア(組)
     */
    template<class X, class Y >
    class Pair {
        X x;
        Y y;
    public:
        Pair();
        Pair(const X &x, const Y &y);
        void setXY(const X &x, const Y &y);

        /**
         * 順番を整理するためだけに定義されたオペレータ
         */
        bool operator<(const Pair<X, Y > &c)const;
        bool operator>(const Pair<X, Y > &c)const;
        bool operator<=(const Pair<X, Y > &c)const;
        bool operator>=(const Pair<X, Y > &c)const;
        bool operator==(const Pair<X, Y > &c)const;
        bool operator!=(const Pair<X, Y > &c)const;
        template<class S, class T >
        friend std::ostream &operator<<(std::ostream &os, const Pair<S, T > &c);
    };

    /**
     * 集合(数学)\n
     * MathSet(); 初期値は空集合 \n
     * MathSet(const T *ary, const int &n); 追加したい要素の配列と個数から初期化
     */
    template<class T >
    class MathSet : public std::set<T > {
    public:
        MathSet();
        MathSet(const T *ary, const int &n);
        /**
         * べき集合の順番を整理するためだけに定義されたオペレータ(本来の集合の包含関係ではない)
         */
        bool operator<(const MathSet< T > &s)const;
        bool operator>(const MathSet< T > &s)const;

        bool operator==(const MathSet< T > &s)const;
        T operator[](const int &i)const;

        MathSet<T> operator+(const MathSet<T> &s)const;
        MathSet<T> operator-(const MathSet<T> &s)const;

        template<class U>
        MathSet< Pair<T, U> > directProduct(const MathSet<U> &s) const;
        MathSet<T> unionSet(const MathSet<T> &s)const;
        MathSet<T> intersecSet(const MathSet<T> &s)const;
        MathSet< MathSet<T> > powerSet()const;
        MathSet<T> differenceSet(const MathSet<T> &s)const;
        void setElements(const T *ary, const int &n);
        void print(std::ostream &os = std::cout)const;
        template<class U>
        friend std::ostream& operator<<(std::ostream &os, const MathSet<U> &s);
    };

    typedef MathSet<char> SetChar;
    typedef MathSet<short> SetShrt;
    typedef MathSet<int> SetInt;
    typedef MathSet<long> SetLong;
    typedef MathSet<LLONG> SetLLong;

    typedef MathSet<float> SetFLT;
    typedef MathSet<double> SetDBL;
    typedef MathSet<LDBL> SetLDBL;
}

#endif	/* MATHSETDECL_HPP */

