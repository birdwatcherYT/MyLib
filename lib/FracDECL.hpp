#ifndef FRACDECL_HPP
#define	FRACDECL_HPP

#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "BigInt.hpp"
#include "Utility.hpp"
#include "BigDec.hpp"
#include "Typedefs.hpp"
namespace mylib {

    /*
     * 分数クラス\n
     * Frac(); 初期値ゼロ\n
     * Frac(const T& a, const T& b = 1); a/b
     */
    template<class T>
    class Frac {
        //a,bともに整数系のクラス
        T a, b; //  a/b
        void trim();
    public:
        static const Frac<T> ZERO;
        static const Frac<T> ONE;
        //コンストラクタ
        Frac();
        Frac(const T& a, const T& b = 1);

        int getSign()const;
        void setValue(const T& a, const T& b = 1);
        Frac<T> inverse()const;
        void print(std::ostream &os = std::cout)const;
        T getBelow()const;
        T getAbove()const;
        bool isInt()const;
        bool equal(const Frac<T> &f)const;
        Frac<T> pow(const int& n)const;
        Frac<T> add(const Frac<T> &f)const;
        Frac<T> subtract(const Frac<T> &f)const;
        Frac<T> multiply(const Frac<T> &f)const;
        Frac<T> divide(const Frac<T> &f)const;

        T toInt()const;
        BigDec toBigDec(const int accuracy = BigDec::DEFAULT_ACCURACY)const;
        double toDouble()const;

        static Frac<T> createOne();

        static double toDouble(const Frac<int> &f);
        static double toDouble(const Frac<long> &f);
        static double toDouble(const Frac<long long> &f);

        Frac<T> operator++(int n);
        Frac<T> operator++();
        Frac<T> operator--(int n);
        Frac<T> operator--();

        Frac<T> operator-()const;
        Frac<T> operator+()const;
        Frac<T>& operator=(const T& n);
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const Frac<U>& f);

        Frac<T> operator+(const Frac<T> &f)const;
        Frac<T> operator-(const Frac<T> &f)const;
        Frac<T> operator*(const Frac<T> &f)const;
        Frac<T> operator/(const Frac<T> &f)const;
        Frac<T> operator+(const T& n) const;
        Frac<T> operator-(const T& n) const;
        Frac<T> operator*(const T& n) const;
        Frac<T> operator/(const T& n) const;
        Frac<T> operator^(const int& n) const;
        template<class U>
        friend Frac<U> operator+(const U& n, const Frac<U> &f);
        template<class U>
        friend Frac<U> operator-(const U& n, const Frac<U> &f);
        template<class U>
        friend Frac<U> operator*(const U& n, const Frac<U> &f);
        template<class U>
        friend Frac<U> operator/(const U& n, const Frac<U> &f);

        bool operator==(const Frac<T> &f)const;
        bool operator<(const Frac<T> &f)const;
        bool operator>(const Frac<T> &f)const;
        bool operator<=(const Frac<T> &f)const;
        bool operator>=(const Frac<T> &f)const;
        bool operator!=(const Frac<T> &f)const;
        bool operator==(const T &n)const;
        bool operator<(const T &n)const;
        bool operator>(const T &n)const;
        bool operator<=(const T &n)const;
        bool operator>=(const T &n)const;
        bool operator!=(const T &n)const;

        Frac<T>& operator+=(const Frac<T> &f);
        Frac<T>& operator-=(const Frac<T> &f);
        Frac<T>& operator*=(const Frac<T> &f);
        Frac<T>& operator/=(const Frac<T> &f);
        Frac<T>& operator+=(const T& n);
        Frac<T>& operator-=(const T& n);
        Frac<T>& operator*=(const T& n);
        Frac<T>& operator/=(const T& n);
    };
    typedef Frac<int> FracInt;
    typedef Frac<long> FracLong;
    typedef Frac<long long> FracLLong;
    typedef Frac<BigInt> FracBig;
}



#endif	/* FRACDECL_HPP */

