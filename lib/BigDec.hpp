#ifndef BIGDEC_HPP
#define	BIGDEC_HPP

#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include "BigInt.hpp"
#include "Typedefs.hpp"

namespace mylib {

    /**
     * 任意桁の小数を扱うクラス\n
     * 以下、コンストラクタ\n
     * BigDec(); 宣言のみ。初期値ゼロ\n
     * BigDec(const LLONG &n); long long int で初期化 \n
     * BigDec(std::string str); 文字列から初期化 \n
     * BigDec(const BigInt &bigint, const int &scale = 0); BigInt * 10^scale で初期化 
     */
    class BigDec {
        BigInt bigint;
        int scale;
    public:
        const static int DEFAULT_ACCURACY;
        const static BigDec ZERO;
        const static BigDec ONE;
        const static BigDec TWO;
        const static BigDec THREE;
        const static BigDec FOUR;
        const static BigDec HALF;
        const static BigDec PI;
        const static BigDec PI2;
        const static BigDec E;
        const static BigDec LN2;

        //コンストラクタ
        BigDec();
        BigDec(const LLONG &n);
        BigDec(std::string str);
        BigDec(const BigInt &bigint, const int &scale = 0);

        //関数
        int getSign()const;
        void print(bool exp = false, std::ostream &os = std::cout)const;
        BigDec add(const BigDec &d)const;
        BigDec subtract(const BigDec &d)const;
        BigDec multiply(const BigDec &d)const;
        BigDec divide(const BigDec &d, const int &accuracy = DEFAULT_ACCURACY)const;
        BigDec divide(const BigInt &n, const int &accuracy = DEFAULT_ACCURACY)const;
        BigDec changeScale(const int &newScale)const;
        BigDec abs()const;
        BigDec inverse(const int &accuracy = DEFAULT_ACCURACY)const;
        BigDec round(const int &accuracy)const;
        double toDouble()const;
        int toInt()const;
        long toLong()const;
        LLONG toLLong()const;
        BigInt toBigInt()const;

        static BigDec exp(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec log(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec cos(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec sin(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec tan(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec sinh(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec cosh(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec tanh(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec asin(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec acos(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec atan(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec pow(const BigDec &x, const BigDec &a, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec sqrt(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec asinh(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec acosh(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        static BigDec atanh(const BigDec &x, const int &accuracy = DEFAULT_ACCURACY);
        //演算子
        friend std::ostream &operator<<(std::ostream &os, const BigDec &d);
        BigDec& operator=(const BigInt &n);
        BigDec& operator=(const LLONG &n);

        BigDec operator++(int n);
        BigDec operator++();
        BigDec operator--(int n);
        BigDec operator--();

        BigDec operator-()const;
        BigDec operator+()const;
        BigDec operator+(const BigDec &d) const;
        BigDec operator-(const BigDec &d) const;
        BigDec operator*(const BigDec &d) const;
        BigDec operator/(const BigDec &d) const;
        BigDec operator%(const BigDec &d) const;
        BigDec operator^(const int &n) const;
        BigDec operator+(const BigInt &n) const;
        BigDec operator-(const BigInt &n) const;
        BigDec operator*(const BigInt &n) const;
        BigDec operator/(const BigInt &n) const;
        BigDec operator%(const BigInt &n) const;
        BigDec operator+(const LLONG &n) const;
        BigDec operator-(const LLONG &n) const;
        BigDec operator*(const LLONG &n) const;
        BigDec operator/(const LLONG &n) const;
        BigDec operator%(const LLONG &n) const;
        friend BigDec operator+(const BigInt &n, const BigDec &d);
        friend BigDec operator-(const BigInt &n, const BigDec &d);
        friend BigDec operator*(const BigInt &n, const BigDec &d);
        friend BigDec operator/(const BigInt &n, const BigDec &d);
        friend BigDec operator%(const BigInt &n, const BigDec &d);
        friend BigDec operator+(const LLONG &n, const BigDec &d);
        friend BigDec operator-(const LLONG &n, const BigDec &d);
        friend BigDec operator*(const LLONG &n, const BigDec &d);
        friend BigDec operator/(const LLONG &n, const BigDec &d);
        friend BigDec operator%(const LLONG &n, const BigDec &d);

        BigDec& operator+=(const BigDec &d);
        BigDec& operator-=(const BigDec &d);
        BigDec& operator*=(const BigDec &d);
        BigDec& operator/=(const BigDec &d);
        BigDec& operator%=(const BigDec &d);
        BigDec& operator+=(const BigInt &n);
        BigDec& operator-=(const BigInt &n);
        BigDec& operator*=(const BigInt &n);
        BigDec& operator/=(const BigInt &n);
        BigDec& operator%=(const BigInt &n);
        BigDec& operator+=(const LLONG &n);
        BigDec& operator-=(const LLONG &n);
        BigDec& operator*=(const LLONG &n);
        BigDec& operator/=(const LLONG &n);
        BigDec& operator%=(const LLONG &n);

        bool operator<(const BigDec &d)const;
        bool operator>(const BigDec &d)const;
        bool operator<=(const BigDec &d)const;
        bool operator>=(const BigDec &d)const;
        bool operator==(const BigDec &d)const;
        bool operator!=(const BigDec &d)const;
        bool operator<(const BigInt &n)const;
        bool operator>(const BigInt &n)const;
        bool operator<=(const BigInt &n)const;
        bool operator>=(const BigInt &n)const;
        bool operator==(const BigInt &n)const;
        bool operator!=(const BigInt &n)const;
        bool operator<(const LLONG &d)const;
        bool operator>(const LLONG &d)const;
        bool operator<=(const LLONG &d)const;
        bool operator>=(const LLONG &d)const;
        bool operator==(const LLONG &d)const;
        bool operator!=(const LLONG &d)const;
        friend bool operator<(const BigInt &n, const BigDec &d);
        friend bool operator>(const BigInt &n, const BigDec &d);
        friend bool operator<=(const BigInt &n, const BigDec &d);
        friend bool operator>=(const BigInt &n, const BigDec &d);
        friend bool operator==(const BigInt &n, const BigDec &d);
        friend bool operator!=(const BigInt &n, const BigDec &d);
        friend bool operator<(const LLONG &n, const BigDec &d);
        friend bool operator>(const LLONG &n, const BigDec &d);
        friend bool operator<=(const LLONG &n, const BigDec &d);
        friend bool operator>=(const LLONG &n, const BigDec &d);
        friend bool operator==(const LLONG &n, const BigDec &d);
        friend bool operator!=(const LLONG &n, const BigDec &d);
    };
    typedef BigDec Decimal;
}

#endif	/* BIGDEC_HPP */

