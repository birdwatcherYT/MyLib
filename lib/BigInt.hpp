#ifndef BIGINT_HPP
#define	BIGINT_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <vector>
#include <typeinfo>
#include <cstring>
#include "Utility.hpp"
#include "Typedefs.hpp"

namespace mylib {

    /**
     * 大きい整数を扱うクラス \n
     * 以下コンストラクタ \n
     * BigInt();宣言のみ。初期値はゼロ \n
     * BigInt(std::string str); 文字列から整数にする。 \n
     * BigInt(const LLONG &num); long long int からBigIntに変換 \n
     * BigInt(const int *num, int size, const int& sign = 1); 配列からの初期化。配列には1要素あたり4桁。sizeは配列の個数 \n
     */
    class BigInt {
    private:
        int *num; //動的配列
        int sign; //正:1、零:0、負:-1
        int size; //配列のサイズ
        int divSub(const BigInt &n, BigInt &pro)const;
        BigInt(const int &size, const bool &tmp);
        void resize(int size);
        void trim();
    public:
        static const BigInt ZERO;
        static const BigInt ONE;
        static const BigInt TWO;
        static const BigInt THREE;
        static const BigInt SIX;
        static const BigInt TEN; //10
        static const BigInt TEN2; //100
        static const BigInt TEN3; //1000
        static const int LIMIT = 10000; //各配列の上限。10000は含まない。
        static const int KETA = 4; //1配列に入れる桁数
        static const int SIGN_PLUS = 1;
        static const int SIGN_ZERO = 0;
        static const int SIGN_MINUS = -1;

        //コンストラクタ
        BigInt();
        BigInt(std::string str);
        BigInt(const LLONG &n);
        BigInt(const int *num, int size, const int& sign = 1);
        BigInt(const BigInt &n);

        ~BigInt();

        //関数
        BigInt abs()const;
        void setValue(const int *num, const int& sign, int size);
        int getSize()const;
        int getSign()const;
        int getNum(const int &i)const;
        void setSign(int sign);
        int getHeadIndex()const;
        bool equal(const BigInt &n)const;
        void print(std::ostream &os = std::cout)const;
        int getKeta()const;

        BigInt add(const BigInt &n)const;
        BigInt subtract(const BigInt &n)const;
        BigInt multiply(const BigInt &n)const;
        BigInt mod(const BigInt &n)const;
        BigInt divide(const BigInt &n)const;

        BigInt mulInt(const int& n)const;
        BigInt divInt(const int& n)const;

        BigInt shiftLeft(const int& k)const;
        BigInt shiftRight(const int& k)const;

        void increment();
        void decrement();

        BigInt pow(const int& k)const;
        BigInt powMod(const LLONG &k, const LLONG &m)const;

        double toDouble()const;
        int toInt()const;
        long toLong()const;
        LLONG toLLong()const;

        //staticな関数群------------------------------------------------------------
        static int absCompare(const BigInt &a, const BigInt &b);
        static BigInt getMax(int size);
        static int compare(const BigInt &a, const BigInt &b);
        static BigInt fact(const int& n);
        static BigInt toBigInt(const LLONG &n);

        //演算子のオーバーロード
        BigInt &operator=(const BigInt &n);
        bool operator==(const BigInt &n)const;
        bool operator!=(const BigInt &n)const;
        bool operator<(const BigInt &n)const;
        bool operator>(const BigInt &n)const;
        bool operator<=(const BigInt &n)const;
        bool operator>=(const BigInt &n)const;

        BigInt &operator=(const LLONG &n);
        bool operator==(const LLONG &n)const;
        bool operator!=(const LLONG &n)const;
        bool operator>(const LLONG &n)const;
        bool operator<(const LLONG &n)const;
        bool operator>=(const LLONG &n)const;
        bool operator<=(const LLONG &n)const;

        BigInt operator+(const BigInt &n)const;
        BigInt operator-(const BigInt &n)const;
        BigInt operator*(const BigInt &n)const;
        BigInt operator/(const BigInt &n)const;
        BigInt operator%(const BigInt &n)const;
        BigInt operator^(const int &n)const;
        BigInt operator+(const LLONG &n)const;
        BigInt operator-(const LLONG &n)const;
        BigInt operator*(const LLONG &n)const;
        BigInt operator/(const LLONG &n)const;
        BigInt operator%(const LLONG &n)const;

        friend BigInt operator+(const LLONG &n, const BigInt &b);
        friend BigInt operator-(const LLONG &n, const BigInt &b);
        friend BigInt operator*(const LLONG &n, const BigInt &b);
        friend BigInt operator/(const LLONG &n, const BigInt &b);
        friend BigInt operator%(const LLONG &n, const BigInt &b);

        BigInt operator++(int n);
        BigInt operator++();
        BigInt operator--(int n);
        BigInt operator--();

        BigInt &operator+=(const BigInt &n);
        BigInt &operator-=(const BigInt &n);
        BigInt &operator*=(const BigInt &n);
        BigInt &operator/=(const BigInt &n);
        BigInt &operator%=(const BigInt &n);
        BigInt &operator+=(const LLONG &n);
        BigInt &operator-=(const LLONG &n);
        BigInt &operator*=(const LLONG &n);
        BigInt &operator/=(const LLONG &n);
        BigInt &operator%=(const LLONG &n);

        BigInt operator-()const;
        friend std::ostream& operator<<(std::ostream &os, const BigInt& n);
    };

}


#endif	/* BIGINT_HPP */

