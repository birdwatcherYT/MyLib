#ifndef UTILITYIMPL_HPP
#define	UTILITYIMPL_HPP

#include "UtilityDECL.hpp"

namespace mylib {

    template<class T>
    void inner::sortSub(T *array, const int& begin, const int& end) {
        T pivot = array[(begin + end) >> 1];
        int i = begin, j = end;

        while (true) {
            // 基準値以上の値が見つかるまで右方向へ進めていく
            while (array[i] < pivot) ++i;

            // 基準値以下の値が見つかるまで左方向へ進めていく
            while (array[j] > pivot) --j;

            // 左右から進めてきたiとjがぶつかったらループを終える
            if (i >= j) break;

            /* 基準値位置よりも左側にあり、基準値よりも大きい値 (array[i]) と、
               基準値位置よりも右側にあり、基準値よりも小さい値 (array[j]) の
               位置関係を交換する。
             */
            swap_f(array[i], array[j]);

            // 次回に備えて、注目点をずらす
            ++i;
            --j;
        }

        // 基準値の位置より左側に要素が２つ以上あれば、その部分についてクイックソートを再帰させる
        if (i - begin >= 2)
            sortSub(array, begin, i - 1);

        // 基準値の位置より右側に要素が２つ以上あれば、その部分についてクイックソートを再帰させる
        if (end - j >= 2)
            sortSub(array, j + 1, end);
    }

    /**
     * ファイルから整数を得る
     * @param str
     * @param num 格納する変数
     * @return 数字最後の次の位置のポインタ、数字が無いときはNULL
     */
    template<class T>
    char* readInt(char* str, T &number) {
        std::string tmp = "";
        char ch;
        while ((ch = *str++) != '\0') {
            if (ch == '+' || ch == '-') {
                tmp += ch;
                if ((ch = *str++) == '\0')
                    return NULL;
                if (isdigit(ch)) {
                    tmp += ch;
                    while ((ch = *str++) != '\0') {
                        if (isdigit(ch))
                            tmp += ch;
                        else
                            break;
                    }
                    if (TYPE_EQ(T, int))
                        number = (T) atoi(tmp.c_str());
                    else if (TYPE_EQ(T, long))
                        number = (T) atol(tmp.c_str());
                    else
                        number = (T) atoll(tmp.c_str());
                    return str;
                } else {
                    tmp = "";
                }
            } else if (isdigit(ch)) {
                tmp += ch;
                while ((ch = *str++) != '\0') {
                    if (isdigit(ch))
                        tmp += ch;
                    else
                        break;
                }
                if (TYPE_EQ(T, int))
                    number = (T) atoi(tmp.c_str());
                else if (TYPE_EQ(T, long))
                    number = (T) atol(tmp.c_str());
                else
                    number = (T) atoll(tmp.c_str());
                return str;
            }
        }
        return NULL;
    }

    /**
     * デバッグ時に使用。値を出力し、チェックをする。
     * @param value
     * @param file
     * @param function
     * @param line
     */
    template<class T>
    void inner::check(const char *name, const T& value, const char* file, const char* function, const int& line) {
        std::cout << name << " = " << value << std::endl
                << " (" << file << " " << line << "行目 " << function << "関数 内から)" << std::endl;
    }

    template<class T>
    T gcd(const T& n1, const T& n2) {
        T r, a = n1, b = n2;
        //STEP1
        while ((r = a % b) != 0) {
            //STEP1-1
            a = r;
            //STEP1-2
            swap_f(a, b);
        }
        return b;
    }

    template<class T>
    T lcm(const T& n2, const T& n1) {
        return (n1 / gcd(n1, n2))*n2;
    }

    /**
     * 拡張ユークリッド互除法 ax + by = gcd(a,b)
     *
     * @param a xの係数
     * @param b yの係数
     * @param solution 解x,yを格納する
     * @return gcd(a,b)
     */
    template<class T>
    T extendEuclid(const T& a, const T& b, T& x, T& y) {
        //STEP1
        T x0 = 1, x1 = 0, x2, y0 = 0, y1 = 1, y2, r0 = a, r1 = b, r2, q2;
        //STEP2
        while (r1 != 0) {
            //STEP2-1
            q2 = r0 / r1;
            r2 = r0 % r1;
            //STEP2-2
            x2 = x0 - q2 * x1;
            y2 = y0 - q2 * y1;
            //
            x0 = x1;
            x1 = x2;
            y0 = y1;
            y1 = y2;
            r0 = r1;
            r1 = r2;
        }
        x = x0;
        y = y0;
        return r0;
    }

    template<class T>
    T abs_f(const T &n) {
        return (n > 0) ? n : -n;
    }

    template<class T>
    T power_f(const T &a, const int &n) {
        bool negative = (n < 0);
        int exp = (n < 0) ? -n : n;
        T ans = 1, tmp = a;
        if (exp & 1)ans = tmp;
        while (exp != 0) {
            tmp *= tmp;
            if ((exp >>= 1)&1)ans *= tmp;
        }
        if (negative)ans = 1 / ans;
        return ans;
    }

    template<class T>
    T combination(int n, int r) {
        T ans = 0;
        if (n < r)return ans;
        if (r < 0)r = n - r;
        ans = 1;
        for (int i = 1; i <= r; ++i)
            ans = ans * (n - i + 1) / i;

        return ans;
    }

    template<class T>
    void swap_f(T &a, T &b) {
        T t = a;
        a = b;
        b = t;
    }

    template<class T>
    void swap_f(T *a, T *b) {
        T t = *a;
        *a = *b;
        *b = t;
    }

    template<class T>
    std::string toString(const T &n) {
        std::ostringstream os;
        os << n;
        return os.str();
    }

    template<class T>
    void quickSort(T *array, const int& n) {
        inner::sortSub(array, 0, n - 1);
    }

    template<class T>
    const T *linearSearch(const T* array, const T& target, const int& n) {
        for (const T *p = array; p != &array[n]; ++p)
            if (*p == target)return p;
        return NULL;
    }

    template<class T>
    const T* binarySearch(const T* array, const T& target, const int& n) {
        if (target < array[0] || target > array[n - 1])return NULL;
        int left = 0, right = n - 1, mid;
        do {
            mid = (left + right) >> 1;
            if (target < array[mid])right = mid - 1;
            else left = mid + 1;
        } while (left <= right);
        if (target == array[right])return &array[right];
        else return NULL;
    }

    template<class T>
    void printArray(T *array, const int& n, std::ostream &os) {
        for (T *p = array; p != &array[n]; ++p)
            os << *p << ',';
        os << "\b " << std::endl;
    }

    /**
     * vectorの出力
     * @param os
     * @param v
     * @return 
     */
    template<class T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
        for (UINT i = 0U, size = v.size(); i < size; ++i)
            os << v[i] << ",";
        os << "\b " << std::endl;
        return os;
    }

    /**
     * bitsetの前置インクリメント
     * @param bits
     * @return 
     */
    template<size_t size>
    std::bitset<size> operator++(std::bitset<size> &bits) {
        if (bits[0]) {
            bits[0] = false;
            for (ULONG i = 1; i < size; ++i) {
                if (bits[i]) {
                    bits[i] = false;
                } else {
                    bits[i] = true;
                    break;
                }
            }
        } else {
            bits[0] = true;
        }
        return bits;
    }

    /**
     * bitsetの後置インクリメント
     * @param bits
     * @param n
     * @return 
     */
    template<size_t size>
    std::bitset<size> operator++(std::bitset<size> &bits, int n) {
        std::bitset<size> tmp = bits;
        if (bits[0]) {
            bits[0] = false;

            for (ULONG i = 1UL; i < size; ++i) {
                if (bits[i]) {
                    bits[i] = false;
                } else {
                    bits[i] = true;
                    break;
                }
            }
        } else {
            bits[0] = true;
        }
        return tmp;
    }
}

#endif	/* UTILITYIMPL_HPP */

