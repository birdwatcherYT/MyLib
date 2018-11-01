#ifndef POLYIMPL_HPP
#define	POLYIMPL_HPP

#include "PolyDECL.hpp"

namespace mylib {

    /**
     * 多項式コンストラクタ
     * @param num 係数
     * @param n 最高次数
     * @param f 式全体の係数 default=ONE
     */
    template<class T>
    Poly<T>::Poly(T *num, const int& n, const Frac<T> &f) {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : 符号あり整数を指定してください");
        if (n < 0)maxN = 0;
        else maxN = n;
        this->f = f;
        this->num.resize(maxN + 1);
        memmove(&this->num[0], &num[0], sizeof (T) * (maxN + 1));
        trim();
    }

    /**
     * 多項式コンストラクタ(係数1、最高次数ゼロ)
     */
    template<class T>
    Poly<T>::Poly() {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : 符号あり整数を指定してください");
        maxN = 0;
        num.resize(1);
        num[0] = 0;
        f = Frac<T>::ONE;
    }

    template<class T>
    Poly<T>::Poly(const char *filename) {
        std::ifstream ifs(filename);
        ASSERT(!ifs.fail(), "Error : ファイルがありません");

        const int maxsize = 1024;
        char str[maxsize] = "", *p;
        T number;
        ASSERT(ifs.good(), "Error : ファイルを開けません");

        //degree
        while (ifs.get() != '#')
            ASSERT(!ifs.eof(), "Error : 正常に読み取れません");
        ifs.getline(str, maxsize - 1);
        p = str;
        ASSERT((readInt(p, maxN)) != NULL, "Error : 正常に読み取れません");
        num.resize(maxN + 1);
        //係数
        while (ifs.get() != ':')
            ASSERT(!ifs.eof(), "Error : 正常に読み取れません");
        memset(str, '\0', maxsize);
        ifs.getline(str, maxsize - 1);
        p = str;
        ASSERT((p = readInt(p, number)) != NULL, "Error : 正常に読み取れません");
        f = number;
        if (readInt(p, number) != NULL)
            f /= number;
        //成分
        memset(str, '\0', maxsize);
        ifs.getline(str, maxsize - 1);
        p = str;
        for (int i = 0; i <= maxN; ++i)
            ASSERT((p = readInt(p, num[i])) != NULL, "Error : 成分が足りません");
        ifs.close();
    }

    /**
     * 最高次n
     * @param n
     */
    template<class T>
    Poly<T>::Poly(const int& n) {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : 符号あり整数を指定してください");
        if (n < 0)maxN = 0;
        else maxN = n;
        num.resize(maxN + 1);
        for (int i = 0; i <= maxN; ++i)num[i] = 0;
        f = Frac<T>::ONE;
    }

    template<class T>
    const T& Poly<T>::operator[](const int& i)const {
        return num[i];
    }

    template<class U>
    std::ostream &operator<<(std::ostream &os, const Poly<U> &x) {
        x.print(os);
        return os;
    }

    template<class U>
    std::ostream &operator<<(std::ostream &os, const std::vector< Poly<U> > &v) {
        for (UINT i = 0U, size = v.size(); i < size; ++i)
            os << v[i];

        return os;
    }

    /**
     * f(x) の値を返す
     * @param x
     * @return 
     */
    template<class T>
    Frac<T> Poly<T>::value(const Frac<T>& x) const {
        Frac<T> ans = num[0];

        for (int i = 1; i <= maxN; ++i)
            ans = ans * x + num[i];

        return ans*f;
    }

    template<class T>
    void Poly<T>::trim() {
        int i, j = -1, k = -1;

        //係数は必ず正
        switch (f.getSign()) {
            case 0:
                maxN = 0;
                num.resize(1);
                num[0] = 0;
                f = Frac<T>::ONE;
                return;
            case -1:
                f = -f;
                for (i = 0; i <= maxN; ++i)
                    num[i] = -num[i];
                break;
        }

        //ゼロでない2つ
        for (i = 0; i <= maxN; ++i)
            if (num[i] != 0) {
                j = i;
                break;
            }
        for (++i; i <= maxN; ++i)
            if (num[i] != 0) {
                k = i;
                break;
            }

        T gc;
        if (j >= 0 && k >= 0)
            gc = gcd(abs_f(num[j]), abs_f(num[k]));
        else if (j >= 0 && k < 0) {
            f *= abs_f(num[j]);
            num[j] = (num[j] < 0) ? -1 : 1;
            gc = 1;
        } else {
            maxN = 0;
            num.resize(1);
            f = Frac<T>::ONE;
            return;
        }
        for (++i; i <= maxN; ++i) {
            if (gc == 1)break;
            if (num[i] != 0)
                gc = gcd(gc, abs_f(num[i]));
        }
        if (gc != 1) {
            f *= gc;
            for (i = 0; i <= maxN; ++i)
                num[i] /= gc;
        }

        //実際の最高次にする
        if (j > 0) {
            maxN -= j;
            memmove(&num[0], &num[j], sizeof (T)*(maxN + 1));
            num.resize(maxN + 1);
        }
    }

    template<class T>
    T Poly<T>::get(const int &i)const {
        return (i > maxN || i < 0) ? 0 : num[i];
    }

    template<class T>
    void Poly<T>::print(std::ostream &os) const {
        os << "#degree " << maxN << std::endl;
        os << "scale : " << f << std::endl;
        for (int i = 0; i <= maxN; ++i)
            os << num[i] << ",";
        os << "\b " << std::endl;
    }

    template<class T>
    Poly<T> Poly<T>::add(const Poly<T> &x) const {
        bool larger = (maxN > x.maxN);
        int diff = abs(maxN - x.maxN), newN = (larger) ? maxN : x.maxN;
        T gc, lc;
        Poly<T> ans(newN);
        gc = gcd(f.getAbove(), x.f.getAbove());
        lc = lcm(f.getBelow(), x.f.getBelow());
        ans.f.setValue(gc, lc);

        if (larger)
            for (int i = 0; i <= newN; ++i)
                ans.num[i] = f.getSign()*(lc / f.getBelow())*(f.getAbove() / gc) * num[i]
                    + x.f.getSign()*(lc / x.f.getBelow())*(x.f.getAbove() / gc) * x.get(i - diff);
        else
            for (int i = 0; i <= newN; ++i)
                ans.num[i] = f.getSign()*(lc / f.getBelow())*(f.getAbove() / gc) * get(i - diff)
                + x.f.getSign()*(lc / x.f.getBelow())*(x.f.getAbove() / gc) * x.num[i];
        ans.trim();
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::subtract(const Poly<T> &x) const {
        Poly<T> ans = x;
        ans.f = -ans.f;
        return add(ans);
    }

    template<class T>
    Poly<T> Poly<T>::shiftRight(const int& k)const {
        if (k <= 0)return *this;
        Poly<T> ans(maxN - k);
        for (int i = 0; i <= ans.maxN; ++i)
            ans.num[i] = get(i);
        ans.f = f;
        ans.trim();
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::shiftLeft(const int &k) const {
        if (k <= 0)return *this;
        Poly<T> ans(maxN + k);
        for (int i = 0; i <= ans.maxN; ++i)
            ans.num[i] = get(i);
        ans.f = f;
        ans.trim();
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::subMul(const Frac<T> &k)const {
        Poly<T> ans = *this;
        ans.f *= k;
        ans.trim();
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::multiply(const Poly<T> &x)const {
        Poly<T> ans;
        for (int i = x.maxN; i >= 0; --i)
            ans = ans.add(subMul(x.num[i] * x.f).shiftLeft(x.maxN - i));
        ans.trim();
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::divide(const Poly<T>& x) const {
        if (maxN < x.maxN)return Poly(0);
        Poly<T> ans(maxN - x.maxN), tmp = *this, part(x.maxN);
        ans.f = f / x.f;
        T gc;
        memmove(&part.num[0], &num[0], sizeof (T)*(part.maxN + 1));

        for (int i = 0; i <= ans.maxN; ++i) {
            if (part.num[0] % abs_f(x.num[0]) != 0) {
                gc = gcd(abs_f(part.num[0]), abs_f(x.num[0]));
                gc = x.num[0] / gc;
                ans.f /= gc;
                for (int j = 0; j < i; ++j)
                    ans.num[j] *= gc;
                for (int j = 0; j <= part.maxN; ++j)
                    part.num[j] *= gc;
                for (int j = i + x.maxN + 1; j <= tmp.maxN; ++j)
                    tmp.num[j] *= gc;
            }
            ans.num[i] = part.num[0] / x.num[0];
            for (int j = 0; j < x.maxN; ++j)
                part.num[j] = part.num[j + 1] - ans.num[i] * x.num[j + 1];
            part.num[x.maxN] = tmp.get(i + x.maxN + 1);
        }
        ans.trim();

        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::mod(const Poly<T>& x) const {
        if (maxN < x.maxN)return *this;
        Poly<T> tmp = *this, part(x.maxN);
        T gc, t;

        part.f = f / x.f;
        memmove(&part.num[0], &num[0], sizeof (T)*(part.maxN + 1));


        for (int i = 0; i <= maxN - x.maxN; ++i) {
            if (part.num[0] % abs_f(x.num[0]) != 0) {
                gc = gcd(abs_f(part.num[0]), abs_f(x.num[0]));
                gc = x.num[0] / gc;
                part.f /= gc;
                for (int j = 0; j <= part.maxN; ++j)
                    part.num[j] *= gc;
                for (int j = i + x.maxN + 1; j <= tmp.maxN; ++j)
                    tmp.num[j] *= gc;
            }
            t = part.num[0] / x.num[0];
            for (int j = 0; j < x.maxN; ++j)
                part.num[j] = part.num[j + 1] - t * x.num[j + 1];
            part.num[x.maxN] = tmp.get(i + x.maxN + 1);
        }
        return part.shiftRight(1);
    }

    template<class T>
    void Poly<T>::divideAndMod(const Poly<T> &x, Poly<T> &div, Poly<T> &m)const {
        if (maxN < x.maxN) {
            div = Poly<T>(0);
            m = *this;
            return;
        }

        Poly<T> ans(maxN - x.maxN), tmp = *this, part(x.maxN);
        ans.f = f / x.f;

        T gc;
        memmove(&part.num[0], &num[0], sizeof (T)*(part.maxN + 1));


        for (int i = 0; i <= ans.maxN; ++i) {
            if (part.num[0] % abs_f(x.num[0]) != 0) {
                gc = gcd(abs_f(part.num[0]), abs_f(x.num[0]));
                gc = x.num[0] / gc;
                ans.f /= gc;
                for (int j = 0; j < i; ++j)
                    ans.num[j] *= gc;
                for (int j = 0; j <= part.maxN; ++j)
                    part.num[j] *= gc;
                for (int j = i + x.maxN + 1; j <= tmp.maxN; ++j)
                    tmp.num[j] *= gc;
            }
            ans.num[i] = part.num[0] / x.num[0];
            for (int j = 0; j < x.maxN; ++j)
                part.num[j] = part.num[j + 1] - ans.num[i] * x.num[j + 1];
            part.num[x.maxN] = tmp.get(i + x.maxN + 1);
        }
        part.f = ans.f;
        ans.trim();
        div = ans;
        m = part.shiftRight(1);
    }

    template<class T>
    void Poly<T>::setNums(T *num, const int& n, const Frac<T> &f) {
        if (n < 0)maxN = 0;
        else maxN = n;
        this->f = f;
        this->num.resize(n + 1);
        memmove(&this->num[0], num, sizeof (T)*(maxN + 1));
        trim();
    }

    template<class T>
    std::vector<Poly<T> > Poly<T>::factrization()const {
        std::vector< Poly<T> > ans;
        T ary[2] = {1, 0};
        Poly<T> x(ary, 1), div, m;
        T i, j;
        for (i = maxN; i >= 0 && num[i] == 0; --i)
            ans.insert(ans.end(), x);

        Poly<T> tmp = shiftRight(maxN - i);

        for (i = 1; i <= abs_f(tmp.num[tmp.maxN]); ++i) {
            if (abs_f(tmp.num[tmp.maxN]) % i == 0) {
                for (j = 1; j <= abs_f(tmp.num[0]); ++j) {
                    if (abs_f(tmp.num[0]) % j == 0) {
                        ary[0] = j, ary[1] = i;
                        x.setNums(ary, 1);
                        tmp.divideAndMod(x, div, m);
                        if (m.num[m.maxN] == 0) {
                            ans.insert(ans.end(), x);
                            tmp = div;
                            i = 0;
                            break;
                        }
                        //----------------------
                        ary[0] = j, ary[1] = -i;
                        x.setNums(ary, 1);
                        tmp.divideAndMod(x, div, m);
                        if (m.num[m.maxN] == 0) {
                            ans.insert(ans.end(), x);
                            tmp = div;
                            i = 0;
                            break;
                        }
                    }
                }
            }
        }
        ans.insert(ans.end(), tmp);
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::differential()const {
        Poly<T> ans(maxN - 1);
        ans.f = f;
        for (int i = 0; i <= ans.maxN; ++i)
            ans.num[i] = num[i] * (maxN - i);

        ans.trim();
        return ans;
    }

    template<class T>
    void Poly<T>::set(const T &number, const int &i) {
        if (i < 0 || i > maxN)return;
        num[i] = number;
    }

    template<class T>
    void Poly<T>::set(const Frac<T> &f) {
        this->f = f;
    }

    template<class T>
    int Poly<T>::getMaxN()const {
        return maxN;
    }

    template<class T>
    Frac<T> Poly<T>::getCoefficient()const {
        return f;
    }

    template<class T>
    Poly<T> Poly<T>::integral()const {
        Poly<T> ans = *this;
        T gc;
        for (int i = 0; i <= maxN; ++i) {
            if (ans.num[i] % abs_f(maxN - i + 1) != 0) {
                gc = gcd(abs_f(maxN - i + 1), abs_f(ans.num[i]));
                ans.f /= (maxN - i + 1) / gc;
                for (int j = 0; j <= maxN; ++j) {
                    if (j == i)continue;
                    ans.num[j] *= (maxN - i + 1) / gc;
                }
            } else {
                ans.num[i] /= (maxN - i + 1);
            }
        }
        return ans.shiftLeft(1);
    }

    template<class T>
    Poly<T> Poly<T>::operator+(const Poly<T> &x)const {
        return add(x);
    }

    template<class T>
    Poly<T> Poly<T>::operator-(const Poly<T> &x)const {
        return subtract(x);
    }

    template<class T>
    Poly<T> Poly<T>::operator*(const Poly<T> &x)const {
        return multiply(x);
    }

    template<class T>
    Poly<T> Poly<T>::operator/(const Poly<T> &x)const {
        return divide(x);
    }

    template<class T>
    Poly<T> Poly<T>::operator%(const Poly<T> &x)const {
        return mod(x);
    }

    template<class T>
    Poly<T> Poly<T>::operator*(const T &n)const {
        Poly<T> ans = *this;
        ans.f = ans.f*n;
        ans.trim();
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::operator/(const T &n)const {
        Poly<T> ans = *this;
        ans.f = ans.f / n;
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::operator*(const Frac<T> &f)const {
        Poly<T> ans = *this;
        ans.f = ans.f * f;
        ans.trim();
        return ans;
    }

    template<class T>
    Poly<T> Poly<T>::operator/(const Frac<T> &f)const {
        Poly<T> ans = *this;
        ans.f = ans.f / f;
        return ans;
    }

    template<class T>
    Poly<T>& Poly<T>::operator+=(const Poly<T> &x) {
        *this = *this+x;
        return *this;
    }

    template<class T>
    Poly<T>& Poly<T>::operator-=(const Poly<T> &x) {
        *this = *this-x;
        return *this;
    }

    template<class T>
    Poly<T>& Poly<T>::operator*=(const Poly<T> &x) {
        *this = *this*x;
        return *this;
    }

    template<class T>
    Poly<T>& Poly<T>::operator/=(const Poly<T> &x) {
        *this = *this / x;
        return *this;
    }

    template<class T>
    Poly<T>& Poly<T>::operator%=(const Poly<T> &x) {
        *this = *this % x;
        return *this;
    }

    template<class T>
    bool Poly<T>::operator==(const Poly<T> &x)const {
        if (f != x.f || maxN != x.maxN)return false;

        for (int i = 0; i <= maxN; ++i)
            if (num[i] != x.num[i])return false;

        return true;
    }

    template<class T>
    bool Poly<T>::operator!=(const Poly<T> &x)const {
        return !(*this == x);
    }
}


#endif	/* POLYIMPL_HPP */

