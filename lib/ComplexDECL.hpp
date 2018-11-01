#ifndef COMPLEXDECL_HPP
#define	COMPLEXDECL_HPP

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <typeinfo>
#include "Frac.hpp"
#include "Typedefs.hpp"
namespace mylib {

    /**
     * 複素数クラス\n
     * Complex<T>(); 初期値ゼロ\n
     * Complex<T>(const T& x, const T& y = 0); x+yi
     */
    template<class T>
    class Complex {
    private:
        T x, y; // x + yi
    public:
        //コンストラクタ
        Complex<T>(const T& x, const T& y = 0);
        Complex<T>();

        void print(std::ostream &os = std::cout)const;
        inline void setValue(const T& x, const T& y = 0);
        Complex<T> conjugate()const;
        Complex<T> inverse()const;
        inline T abs2()const;
        inline T re()const;
        inline T im()const;
        Complex<T> power(const int& n)const;

        Complex<T> add(const Complex<T> &c)const;
        Complex<T> subtract(const Complex<T> &c)const;
        Complex<T> multiply(const Complex<T> &c)const;
        Complex<T> divide(const Complex<T> &c)const;

        Complex<T> add(const T& r)const;
        Complex<T> subtract(const T& r)const;
        Complex<T> multiply(const T& r)const;
        Complex<T> divide(const T& r)const;

        //演算子
        Complex<T> operator^(const int& n)const;
        bool operator==(const Complex<T> &c)const;
        bool operator==(const T &r)const;
        Complex<T> operator+(const Complex<T> &c)const;
        Complex<T> operator-(const Complex<T> &c)const;
        Complex<T> operator*(const Complex<T> &c)const;
        Complex<T> operator/(const Complex<T> &c)const;

        Complex<T>& operator=(const T& r);
        Complex<T> operator+(const T& r) const;
        Complex<T> operator-(const T& r) const;
        Complex<T> operator*(const T& r) const;
        Complex<T> operator/(const T& r) const;

        Complex<T>& operator+=(const Complex<T> &c);
        Complex<T>& operator-=(const Complex<T> &c);
        Complex<T>& operator*=(const Complex<T> &c);
        Complex<T>& operator/=(const Complex<T> &c);

        Complex<T>& operator+=(const T& r);
        Complex<T>& operator-=(const T& r);
        Complex<T>& operator*=(const T& r);
        Complex<T>& operator/=(const T& r);

        Complex<T> operator-()const;
        Complex<T> operator+()const;

        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const Complex<U> &c);
        template<class U>
        friend Complex<U> operator+(const U& r, const Complex<U> &c);
        template<class U>
        friend Complex<U> operator-(const U& r, const Complex<U> &c);
        template<class U>
        friend Complex<U> operator*(const U& r, const Complex<U> &c);
        template<class U>
        friend Complex<U> operator/(const U& r, const Complex<U> &c);

        static Complex<double> exponential(const Complex<double> &c);
        template<class U>
        static Complex<double> exponential(const Complex< Frac<U> > &c);
        static double cAbs(const Complex<double> &c);
        template<class U>
        static double cAbs(const Complex< Frac<U> > &c);
        static Complex<double> complexIntegrate(Complex<double> (*func)(const Complex<double>& z),
                Complex<double> (*circ)(const double &t),
                const double &a, const double &b, const double &width);

    };

    typedef Complex<double> CompDBL;
    typedef Complex<FracInt> CompInt;
    typedef Complex<FracLong> CompLong;
    typedef Complex<FracLLong> CompLLong;

}

#endif	/* COMPLEXDECL_HPP */

