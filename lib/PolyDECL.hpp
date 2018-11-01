#ifndef POLYDECL_HPP
#define	POLYDECL_HPP

#include <iostream>
#include <vector>
#include <typeinfo>
#include <cstdlib>
#include <cstring>
#include "Frac.hpp"
#include "Utility.hpp"
#include "Typedefs.hpp"

namespace mylib {

    /**
     * 有理係数の多項式クラス\n
     * a[0]x^n + ... + a[n-1]x + a[n]
     * Poly(T *num, const int& n, const Frac<T> &f = Frac<T>::ONE);\n
     * Poly();\n
     * Poly(const char *filename);\n
     * Poly(const int& n);
     */
    template<class T>
    class Poly {
        std::vector<T> num;
        int maxN; //最高次数
        Frac<T> f;
    public:
        Poly(T *num, const int& n, const Frac<T> &f = Frac<T>::ONE);
        Poly();
        Poly(const char *filename);
        Poly(const int& n);

        Frac<T> value(const Frac<T> &x)const;
        void trim();
        void setNums(T *num, const int& n, const Frac<T> &f = Frac<T>::ONE);
        T get(const int &i)const;
        int getMaxN()const;
        Frac<T> getCoefficient()const;
        void set(const T &number, const int &i);
        void set(const Frac<T> &f);
        void print(std::ostream &os = std::cout) const;
        Poly<T> add(const Poly<T> &x)const;
        Poly<T> subtract(const Poly<T> &x)const;
        Poly<T> shiftRight(const int& k)const;
        Poly<T> shiftLeft(const int &k)const;
        Poly<T> subMul(const Frac<T> &k)const;
        Poly<T> multiply(const Poly<T> &x)const;
        Poly<T> divide(const Poly<T> &x)const;
        Poly<T> mod(const Poly<T> &x)const;
        void divideAndMod(const Poly<T> &x, Poly<T> &div, Poly<T> &m)const;
        std::vector<Poly<T> > factrization()const;
        Poly<T> differential()const;
        Poly<T> integral()const;

        const T& operator[](const int &i)const;
        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const Poly<U> &x);
        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const std::vector< Poly<U> > &v);

        Poly<T> operator+(const Poly<T> &x)const;
        Poly<T> operator-(const Poly<T> &x)const;
        Poly<T> operator*(const Poly<T> &x)const;
        Poly<T> operator/(const Poly<T> &x)const;
        Poly<T> operator%(const Poly<T> &x)const;
        Poly<T> operator*(const T &n)const;
        Poly<T> operator/(const T &n)const;
        Poly<T> operator*(const Frac<T> &f)const;
        Poly<T> operator/(const Frac<T> &f)const;

        Poly<T>& operator+=(const Poly<T> &x);
        Poly<T>& operator-=(const Poly<T> &x);
        Poly<T>& operator*=(const Poly<T> &x);
        Poly<T>& operator/=(const Poly<T> &x);
        Poly<T>& operator%=(const Poly<T> &x);

        bool operator==(const Poly<T> &x)const;
        bool operator!=(const Poly<T> &x)const;
    };
    typedef Poly<int> PolyInt;
    typedef Poly<long> PolyLong;
    typedef Poly<long long> PolyLLong;
    typedef Poly<BigInt> PolyBig;
}



#endif	/* POLYDECL_HPP */

