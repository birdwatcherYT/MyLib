#ifndef COMPLEXIMPL_HPP
#define	COMPLEXIMPL_HPP

#include "ComplexDECL.hpp"

namespace mylib {

    template<class T>
    Complex<T>::Complex() {
        //ASSERT(TYPE_EQ(T, double) || TYPE_EQ(T, Frac<int>) || TYPE_EQ(T, Frac<long>) || TYPE_EQ(T, Frac<LLONG>), "Error : 実数か分数を指定してください");
        x = 0;
        y = 0;
    }

    template<class T>
    Complex<T>::Complex(const T &x, const T &y) {
        //ASSERT(TYPE_EQ(T, double) || TYPE_EQ(T, Frac<int>) || TYPE_EQ(T, Frac<long>) || TYPE_EQ(T, Frac<LLONG>), "Error : 実数か分数を指定してください");
        this->x = x;
        this->y = y;
    }

    template<class T>
    void Complex<T>::print(std::ostream &os) const {
        using namespace std;

        os << x;
        if (y >= 0)os << "+";
        os << y << "i";
    }

    /**
     * 共役複素数
     */
    template<class T>
    Complex<T> Complex<T>::conjugate()const {
        return Complex<T>(x, -y);
    }

    /**
     * 逆数
     */
    template<class T>
    Complex<T> Complex<T>::inverse() const {
        Complex<T> ans = conjugate();
        ans = ans / abs2();
        return ans;
    }

    /**
     * 大きさの二乗値
     */
    template<class T>
    T Complex<T>::abs2() const {
        return x * x + y * y;
    }

    template<class T>
    T Complex<T>::re() const {
        return x;
    }

    template<class T>
    T Complex<T>::im() const {
        return y;
    }

    template<class T>
    Complex<T> Complex<T>::add(const Complex<T> &c) const {
        Complex<T> ans;
        ans.x = x + c.x;
        ans.y = y + c.y;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::subtract(const Complex<T> &c)const {
        Complex<T> ans;
        ans.x = x - c.x;
        ans.y = y - c.y;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::multiply(const Complex<T> &c)const {
        Complex<T> ans;
        ans.x = x * c.x - y * c.y;
        ans.y = y * c.x + x * c.y;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::divide(const Complex<T> &c)const {
        Complex<T> ans;
        ans = this->multiply(c.conjugate());
        T d = c.abs2();
        ans.x /= d;
        ans.y /= d;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::add(const T& r) const {
        Complex<T> ans = *this;
        ans.x += r;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::subtract(const T& r) const {
        Complex<T> ans = *this;
        ans.x -= r;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::multiply(const T& r) const {
        Complex<T> ans = *this;
        ans.x *= r;
        ans.y *= r;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::divide(const T& r) const {
        Complex<T> ans = *this;
        ans.x /= r;
        ans.y /= r;
        return ans;
    }

    /**
     * 累乗
     * @param n 整数
     */
    template<class T>
    Complex<T> Complex<T>::power(const int & n) const {
        Complex<T> ans(1, 0), tmp = *this;
        int exp = abs(n);
        if (exp & 1)ans = tmp;
        while (exp != 0) {
            tmp = tmp.multiply(tmp);
            if ((exp >>= 1)&1)ans *= tmp;
        }
        T t = 1;
        if (n < 0)ans = t / ans;
        return ans;
    }

    template<class T>
    Complex<T> Complex<T>::operator ^(const int& n) const {
        return power(n);
    }

    template<class T>
    void Complex<T>::setValue(const T& x, const T& y) {
        this->x = x;
        this->y = y;
    }

    template<class T>
    bool Complex<T>::operator==(const Complex<T>& c) const {
        return (x == c.x && y == c.y);
    }

    template<class T>
    bool Complex<T>::operator==(const T &r) const {
        return (x == r && y == 0);
    }

    template<class T>
    Complex<T> Complex<T>::operator+(const Complex<T> &c) const {
        return this->add(c);
    }

    template<class T>
    Complex<T> Complex<T>::operator-(const Complex<T> &c) const {
        return this->subtract(c);
    }

    template<class T>
    Complex<T> Complex<T>::operator*(const Complex<T> &c)const {
        return this->multiply(c);
    }

    template<class T>
    Complex<T> Complex<T>::operator/(const Complex<T> &c) const {
        return this->divide(c);
    }

    template<class T>
    Complex<T>& Complex<T>::operator=(const T& r) {
        setValue(r);
        return *this;
    }

    template<class T>
    Complex<T> Complex<T>::operator+(const T& r) const {
        return this->add(r);
    }

    template<class T>
    Complex<T> Complex<T>::operator-(const T& r) const {
        return this->subtract(r);
    }

    template<class T>
    Complex<T> Complex<T>::operator*(const T& r) const {
        return this->multiply(r);
    }

    template<class T>
    Complex<T> Complex<T>::operator/(const T& r) const {
        return this->divide(r);
    }

    template<class T>
    Complex<T>& Complex<T>::operator+=(const Complex<T> &c) {
        *this = this->add(c);
        return *this;
    }

    template<class T>
    Complex<T>& Complex<T>::operator-=(const Complex<T> &c) {
        *this = this->subtract(c);
        return *this;
    }

    template<class T>
    Complex<T>& Complex<T>::operator*=(const Complex<T> &c) {
        *this = this->multiply(c);
        return *this;
    }

    template<class T>
    Complex<T>& Complex<T>::operator/=(const Complex<T> &c) {
        *this = this->divide(c);
        return *this;
    }

    template<class T>
    Complex<T>& Complex<T>::operator+=(const T& r) {
        *this = this->add(r);
        return *this;
    }

    template<class T>
    Complex<T>& Complex<T>::operator-=(const T& r) {
        *this = this->subtract(r);
        return *this;
    }

    template<class T>
    Complex<T>& Complex<T>::operator*=(const T& r) {
        *this = this->multiply(r);
        return *this;
    }

    template<class T>
    Complex<T>& Complex<T>::operator/=(const T& r) {
        *this = this->divide(r);
        return *this;
    }

    template<class T>
    Complex<T> Complex<T>::operator-() const {
        return Complex<T>(-x, -y);
    }

    template<class T>
    Complex<T> Complex<T>::operator+() const {
        return *this;
    }

    template<class U>
    std::ostream& operator<<(std::ostream& os, const Complex<U>& c) {
        c.print(os);
        return os;
    }

    template<class U>
    Complex<U> operator+(const U& r, const Complex<U> &c) {
        return c.add(r);
    }

    template<class U>
    Complex<U> operator-(const U& r, const Complex<U> &c) {
        return (-c).add(r);
    }

    template<class U>
    Complex<U> operator*(const U& r, const Complex<U> &c) {
        return c.multiply(r);
    }

    template<class U>
    Complex<U> operator/(const U& r, const Complex<U> &c) {
        return c.inverse().multiply(r);
    }

    template<class T>
    Complex<double> Complex<T>::exponential(const Complex<double>& c) {
        Complex<double> t(cos(c.im()), sin(c.im()));
        return std::pow(M_E, c.re()) * t;
    }

    template<class T>
    template<class U>
    Complex<double> Complex<T>::exponential(const Complex<Frac<U> >& c) {
        double tmp = Frac<U>::toDouble(c.im());
        Complex<double> t(cos(tmp), sin(tmp));
        return std::pow(M_E, Frac<U>::toDouble(c.re())) * t;
    }

    template<class T>
    double Complex<T>::cAbs(const Complex<double> &c) {
        return std::sqrt(c.x * c.x + c.y * c.y);
    }

    template<class T>
    template<class U>
    double Complex<T>::cAbs(const Complex< Frac<U> > &c) {
        Frac<U> f = c.abs2();
        return std::sqrt((double) f.getAbove() / f.getBelow());
    }

    /**
     * 複素線積分
     * @param func 被積分関数
     * @param circ 積分経路関数
     * @param a 積分区間開始位置
     * @param b 積分区間終点位置
     * @param width 区間の幅
     * @return 積分結果
     */
    template<class T>
    Complex<double> Complex<T>::complexIntegrate(Complex<double> (*func)(const Complex<double>& z),
            Complex<double> (*circ)(const double &t),
            const double &a, const double &b, const double &width) {
        Complex<double> sum, prev, next;
        ULLONG n = (ULLONG) ((b - a) / width);

        prev = circ(a);
        for (ULLONG i = 1ULL; i <= n; ++i) {
            next = circ(a + i * width);
            sum += func(next)*(next - prev);
            prev = next;
        }
        return sum;
    }

}


#endif	/* COMPLEXIMPL_HPP */

