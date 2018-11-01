#ifndef FRACIMPL_HPP
#define	FRACIMPL_HPP

#include "FracDECL.hpp"

namespace mylib {

    template<class T>
    Frac<T>& Frac<T>::operator=(const T& n) {
        setValue(n);
        return *this;
    }

    template<class T>
    Frac<T> Frac<T>::createOne() {
        Frac<T> one;
        one.a = 1;
        one.b = 1;
        return one;
    }

    template<class T>
    double Frac<T>::toDouble(const Frac<int>& f) {
        return (double) f.a / f.b;
    }

    template<class T>
    double Frac<T>::toDouble(const Frac<long>& f) {
        return (double) f.a / f.b;
    }

    template<class T>
    double Frac<T>::toDouble(const Frac<long long>& f) {
        return (double) f.a / f.b;
    }

    template<class T>
    Frac<T>::Frac() {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : Fractionに変換できません");
        a = 0;
        b = 1;
    }

    /**
     * 
     * @param a 分子
     * @param b 分母 default=1
     */
    template<class T>
    Frac<T>::Frac(const T& a, const T& b) {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : Fractionに変換できません");
        this->a = a;
        this->b = b;
        trim();
    }

    template<class T>
    Frac<T> Frac<T>::pow(const int& n) const {
        Frac<T> ans = ONE, tmp = *this;
        int exp = n;
        if (n < 0) {
            exp = -n;
            tmp = inverse();
        }

        if (exp & 1)ans = tmp;
        while (exp != 0) {
            tmp = tmp.multiply(tmp);
            if ((exp >>= 1)&1)ans = ans.multiply(tmp);
        }
        return ans;
    }

    template<class T>
    void Frac<T>::setValue(const T &a, const T &b) {
        this->a = a;
        this->b = b;
        trim();
    }

    template<class T>
    bool Frac<T>::equal(const Frac<T> &f) const {
        if (getSign() == f.getSign() && abs_f(a) == abs_f(f.a) && abs_f(b) == abs_f(f.b)) {
            return true;
        }
        return false;
    }

    /**
     * 分母
     */
    template<class T>
    T Frac<T>::getBelow() const {
        return abs_f(b);
    }

    /**
     * 分子
     */
    template<class T>
    T Frac<T>::getAbove() const {
        return abs_f(a);
    }

    /**
     * 整数であるかどうか
     * @return 
     */
    template<class T>
    bool Frac<T>::isInt()const {
        return (abs_f(b) == 1);
    }

    template<class T>
    void Frac<T>::print(std::ostream &os) const {
        if (getSign() < 0)os << '-';
        os << abs_f(a);
        if (abs_f(b) != 1) os << '/' << abs_f(b);
    }

    template<class T>
    void Frac<T>::trim() {
        if (a == 0) {
            b = 1;
            return;
        }

        ASSERT(b != 0, "Error : 分母はゼロにできません");
        T g = gcd(abs_f(a), abs_f(b));
        a /= g;
        b /= g;
    }

    /**
     * 正:1
     * 零:0
     * 負:-1
     * @return 
     */
    template<class T>
    int Frac<T>::getSign()const {
        if (a == 0)return 0;
        if ((a > 0) ^ (b > 0))return -1;
        return 1;
    }

    template<class T>
    Frac<T> Frac<T>::inverse()const {
        return Frac<T>(b, a);
    }

    template<class T>
    Frac<T> Frac<T>::add(const Frac<T> &f) const {
        Frac<T> ans;
        T g = gcd(abs_f(b), abs_f(f.b));
        ans.a = (f.b / g) * a + (b / g) * f.a;
        ans.b = (b / g) * f.b;
        ans.trim();
        return ans;
    }

    template<class T>
    Frac<T> Frac<T>::subtract(const Frac<T> &f)const {
        Frac<T> ans = f;
        ans.a = -ans.a;
        return this->add(ans);
    }

    template<class T>
    Frac<T> Frac<T>::multiply(const Frac<T> &f)const {
        Frac<T> ans;
        ans.a = a * f.a;
        ans.b = b * f.b;
        ans.trim();
        return ans;
    }

    template<class T>
    Frac<T> Frac<T>::divide(const Frac<T> &f) const {
        Frac<T> ans;
        ans.a = a * f.b;
        ans.b = b * f.a;

        ans.trim();
        return ans;
    }

    template<class T>
    T Frac<T>::toInt() const {
        return a / b;
    }

    template<class T>
    BigDec Frac<T>::toBigDec(const int accuracy)const {
        BigDec above = a, below = b;
        return above.divide(below, accuracy);
    }

    template<class T>
    double Frac<T>::toDouble() const {
        std::string str = toString(toBigDec());
        return atof(str.c_str());
    }

    template<class T>
    Frac<T> Frac<T>::operator++() {
        *this = *this+ONE;
        return *this;
    }

    template<class T>
    Frac<T> Frac<T>::operator++(int n) {
        Frac<T> tmp = *this;
        *this = *this+ONE;
        return tmp;
    }

    template<class T>
    Frac<T> Frac<T>::operator--() {
        *this = *this-ONE;
        return *this;
    }

    template<class T>
    Frac<T> Frac<T>::operator--(int n) {
        Frac<T> tmp = *this;
        *this = *this-ONE;
        return tmp;
    }

    template<class T>
    Frac<T> Frac<T>::operator-() const {
        return Frac<T>(-a, b);
    }

    template<class T>
    Frac<T> Frac<T>::operator+() const {
        return *this;
    }

    template<class T>
    Frac<T> Frac<T>::operator+(const Frac<T> &f) const {
        return this->add(f);
    }

    template<class T>
    Frac<T> Frac<T>::operator-(const Frac<T> &f) const {
        return this->subtract(f);
    }

    template<class T>
    Frac<T> Frac<T>::operator*(const Frac<T> &f) const {
        return this->multiply(f);
    }

    template<class T>
    Frac<T> Frac<T>::operator/(const Frac<T> &f) const {
        return this->divide(f);
    }

    template<class T>
    bool Frac<T>::operator==(const Frac<T>& f) const {
        return equal(f);
    }

    template<class T>
    Frac<T> Frac<T>::operator+(const T& n) const {
        return this->add(Frac<T>(n, 1));
    }

    template<class T>
    Frac<T> Frac<T>::operator-(const T &n) const {
        return this->subtract(Frac<T>(n, 1));
    }

    template<class T>
    Frac<T> Frac<T>::operator*(const T& n) const {
        T t = 1;
        return this->multiply(Frac<T>(n, t));
    }

    template<class T>
    Frac<T> Frac<T>::operator/(const T& n) const {
        T t = 1;
        return this->divide(Frac<T>(n, t));
    }

    template<class T>
    Frac<T> Frac<T>::operator ^(const int& n) const {
        return pow(n);
    }

    template<class U>
    Frac<U> operator+(const U&n, const Frac<U> &f) {
        return f + n;
    }

    template<class U>
    Frac<U> operator-(const U& n, const Frac<U> &f) {
        return -f + n;
    }

    template<class U>
    Frac<U> operator*(const U& n, const Frac<U> &f) {
        return f*n;
    }

    template<class U>
    Frac<U> operator/(const U& n, const Frac<U> &f) {
        return n * f.inverse();
    }

    template<class T>
    Frac<T>& Frac<T>::operator+=(const Frac<T> &f) {
        *this = *this+f;
        return *this;
    }

    template<class T>
    Frac<T>& Frac<T>::operator-=(const Frac<T> &f) {
        *this = *this-f;
        return *this;
    }

    template<class T>
    Frac<T>& Frac<T>::operator*=(const Frac<T> &f) {
        *this = *this*f;
        return *this;
    }

    template<class T>
    Frac<T>& Frac<T>::operator/=(const Frac<T> &f) {
        *this = *this / f;
        return *this;
    }

    template<class T>
    Frac<T>& Frac<T>::operator+=(const T& n) {
        *this = *this+n;
        return *this;
    }

    template<class T>
    Frac<T>& Frac<T>::operator-=(const T& n) {
        *this = *this-n;
        return *this;
    }

    template<class T>
    Frac<T>& Frac<T>::operator*=(const T& n) {
        *this = *this*n;
        return *this;
    }

    template<class T>
    Frac<T>& Frac<T>::operator/=(const T& n) {
        *this = *this / n;
        return *this;
    }

    template<class T>
    bool Frac<T>::operator<(const Frac<T> &f)const {
        return subtract(f).getSign() < 0;
    }

    template<class T>
    bool Frac<T>::operator>(const Frac<T> &f)const {
        return subtract(f).getSign() > 0;
    }

    template<class T>
    bool Frac<T>::operator<=(const Frac<T> &f)const {
        return subtract(f).getSign() <= 0;
    }

    template<class T>
    bool Frac<T>::operator>=(const Frac<T> &f)const {
        return subtract(f).getSign() >= 0;
    }

    template<class T>
    bool Frac<T>::operator!=(const Frac<T> &f)const {
        return !equal(f);
    }

    template<class T>
    bool Frac<T>::operator==(const T &n)const {
        return equal(Frac<T>(n));
    }

    template<class T>
    bool Frac<T>::operator<(const T &n)const {
        return subtract(Frac<T>(n)).getSign() < 0;
    }

    template<class T>
    bool Frac<T>::operator>(const T &n)const {
        return subtract(Frac<T>(n)).getSign() > 0;
    }

    template<class T>
    bool Frac<T>::operator<=(const T &n)const {
        return subtract(Frac<T>(n)).getSign() <= 0;
    }

    template<class T>
    bool Frac<T>::operator>=(const T &n)const {
        return subtract(Frac<T>(n)).getSign() >= 0;
    }

    template<class T>
    bool Frac<T>::operator!=(const T &n)const {
        return !equal(Frac<T>(n));
    }

    template<class U>
    std::ostream& operator<<(std::ostream& os, const Frac<U>& f) {
        f.print(os);
        return os;
    }

    template<class T>
    const Frac<T> Frac<T>::ONE = createOne();
    template<class T>
    const Frac<T> Frac<T>::ZERO;

}


#endif	/* FRACIMPL_HPP */

