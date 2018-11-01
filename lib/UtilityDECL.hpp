#ifndef UTILITYDECL_HPP
#define	UTILITYDECL_HPP

#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cfloat>
#include <climits>
#include <typeinfo>
#include <cctype>
#include <bitset>
#include "BigInt.hpp"
#include "Typedefs.hpp"

/**
 * CONDITIONを満たさない時、MESSAGEを表示して終了する
 */
#define ASSERT(CONDITION,MESSAGE) mylib::inner::assert((CONDITION), MESSAGE, __FILE__, __FUNCTION__, __LINE__)
/**
 * 値のチェック
 */
#define CHECK(VALUE) mylib::inner::check(#VALUE, VALUE ,__FILE__, __FUNCTION__, __LINE__)
/**
 * 要素数
 */
#define ELEMENTS_OF(array) (sizeof((array)) / sizeof((array)[0]))
/**
 * ビット数
 */
#define BITS_OF(obj) (sizeof(obj) * 8 )
/**
 * バイト数
 */
#define BYTES_OF(obj) (sizeof(obj))
/**
 * タイプが同じならtrue
 */
#define TYPE_EQ(type1,type2) (typeid(type1) == typeid(type2))
/**
 * 変数名と添字の結合
 */
#define CONNECT(val,i) (val##i)
/**
 * 変数名を文字列で得る
 */
#define NAME(val) (#val)

namespace mylib {

    class BigInt;
    namespace inner {
        template<class T>
        void sortSub(T *array, const int& begin, const int& end);
        void assert(bool flag, const char* message, const char* file, const char* function, const int& line);
        template<class T>
        void check(const char *name, const T& value, const char* file, const char* function, const int& line);
    }

    bool readDouble(std::ifstream &ifs, double &num);
    bool readInt(std::ifstream &ifs, int &num);
    bool readDouble(FILE *fp, double &num);
    bool readInt(FILE *fp, int &num);

    template<class T>
    char* readInt(char* str, T &number);
    char* readInt(char* str, BigInt &number);
    char* readDouble(char* str, double &number);

    bool DBLeq(const double &a, const double &b);

    template<class T>
    inline T gcd(const T& n1, const T& n2);

    template<class T>
    inline T lcm(const T& n2, const T& n1);

    template<class T>
    T extendEuclid(const T& a, const T& b, T& x, T& y);

    template<class T>
    inline T abs_f(const T &n);

    template<class T>
    inline T power_f(const T &a, const int &n);

    template<class T>
    inline void swap_f(T &a, T &b);

    template<class T>
    inline void swap_f(T *a, T *b);

    template<class T>
    void printArray(T *array, const int& n, std::ostream &os = std::cout);

    template<class T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);

    template<size_t size>
    std::bitset<size> operator++(std::bitset<size> &bits);

    template<size_t size>
    std::bitset<size> operator++(std::bitset<size> &bits, int n);

    template<class T>
    void quickSort(T *array, const int& n);

    template<class T>
    const T *linearSearch(const T *array, const T &target, const int &n);

    template<class T>
    const T *binarySearch(const T *array, const T &target, const int &n);

    template<class T>
    std::string toString(const T &n);

    template<class T>
    T combination(int n, int r);

    double processTimer();
    time_t timer();

    int getRandom(const int &min, const int &max);
    double solver(double (*func)(const double&), double low, double high, const double &eps = 1e-12, const unsigned &countMax = INT_MAX);
    double integrate(double (*func)(const double&), double a, double b, const double& width);
    void factorization(ULLONG n, std::ostream &os = std::cout);
    bool isPrime(ULLONG n);


    void allReplace(std::string& text, const std::string& before, const std::string& after);
    void allReplace(std::string &text, const char& ch, const std::string &after);
    void firstReplace(std::string& text, const std::string& before, const std::string& after, const std::string::size_type& pos = 0);

    bool onlyChar(const std::string &text, const std::string::size_type& pos);
    bool onlyNum(const std::string &text, const std::string::size_type& pos);
    std::string::size_type bracketSearch(const std::string &str, std::string::size_type startPos);
    char *bracketSearch(char *startKakko);
    int getNumberI(const LLONG &n, const int &i);
}

#endif	/* UTILITYDECL_HPP */

