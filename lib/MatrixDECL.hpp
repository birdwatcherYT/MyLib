#ifndef MATRIXDECL_HPP
#define	MATRIXDECL_HPP

#define Vec Matrix
#define Mat Matrix

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cstring>
#include "Frac.hpp"
#include "BigInt.hpp"
#include "Utility.hpp"
#include "Typedefs.hpp"

namespace mylib {

    /**
     * 行列クラス(有理数)\n
     * Matrix(const T *num, const int& row, const int& col = 1, const Frac<T> &f = Frac<T>::ONE);\n
     * Matrix(const T *num, const int& row, const Frac<T> &f);\n
     * Matrix(const int& row, const int& col = 1);\n
     * Matrix(const char *filename);\n
     * Matrix(const Matrix<T>& m);
     */
    template<class T>
    class Matrix {
    private:
        T *num; //行列の値(動的配列)
        int row, col; //行、列
        Frac<T> f; //係数(有理数)
    public:
        //コンストラクタ
        Matrix(const T *num, const int& row, const int& col = 1, const Frac<T> &f = Frac<T>::ONE);
        Matrix(const T *num, const int& row, const Frac<T> &f);
        Matrix(const int& row, const int& col = 1);
        Matrix(const char *filename);
        Matrix(const Matrix<T>& m);
        ~Matrix();

        void trim();
        void divLine(const int& i, T n);
        void mulLine(const int& i, T n);
        void mulLine(const int&i, Frac<T> c);
        void addLine(const int &i, const int &j, Frac<T> c);
        void swapLine(const int& i1, const int& i2);

        T getIJ(const int& i, const int& j)const;
        T* getIJAdd(const int& i, const int& j)const;
        int getRow()const;
        int getCol()const;
        void setIJ(const int& i, const int& j, const T& n);
        Frac<T> getCoefficient()const;
        Matrix<T> add(const Matrix<T> &m)const;
        Matrix<T> subtract(const Matrix<T> &m)const;
        Matrix<T> multiply(const Matrix<T> &m)const;
        Matrix<T> multiply(const T& n)const;
        Matrix<T> multiply(const Frac<T> &f)const;
        Matrix<T> divide(const T& n)const;
        Matrix<T> divide(const Frac<T> &f)const;
        Matrix<T> transpose()const;
        Matrix<T> inverse()const;
        Matrix<T> cofactorMatrix()const;
        T cofactorSub(const int& i, const int& j)const;
        Frac<T> cofactor(const int& i, const int& j)const;
        bool equal(const Matrix<T> &m)const;
        T detSub()const;
        int rank()const;
        Matrix<T> stairsMatrix()const;
        Frac<T> det()const;
        Frac<T> trace()const;
        void print(std::ostream &os = std::cout)const;

        Frac<T> innerProduct(const Vec<T>& v)const;
        Matrix<T> outerProduct(const Vec<T> &v)const;
        Vec<T> crossProduct(const Vec<T> &v)const;
        Matrix<T> wedgeProduct(const Vec<T> &v)const;

        bool isVector()const;
        static Matrix<T> createE(const int& n);
        static Matrix<T> multiplyP(const int &n, const int &i, const Frac<T> &c);
        static Matrix<T> addP(const int &n, const int &i, const int &j, const Frac<T> &c);
        static Matrix<T> swapP(const int &n, const int &i, const int &j);
        static Vec<T> solver(Matrix<T> A, Vec<T> b);

        //演算子
        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);

        Matrix<T> operator^(int n) const;
        Matrix<T> operator-() const;
        Matrix<T> operator+() const;
        Matrix<T>& operator=(const Matrix<T> &m);

        bool operator==(const Matrix<T> &m)const;
        bool operator!=(const Matrix<T> &m)const;

        Matrix<T> operator+(const Matrix<T> &m)const;
        Matrix<T> operator-(const Matrix<T> &m)const;
        Matrix<T> operator*(const Matrix<T> &m)const;
        template<class U>
        friend Matrix<U> operator*(const U& n, const Matrix<U> &m);
        template<class U>
        friend Matrix<U> operator*(const Frac<U>& f, const Matrix<U> &m);
        Matrix<T> operator*(const T &n)const;
        Matrix<T> operator*(const Frac<T>& f)const;
        Matrix<T> operator/(const T &n) const;
        Matrix<T> operator/(const Frac<T> &f)const;
        T *operator[](const int &i)const;
        T& operator()(const int &i)const;

        Matrix<T>& operator+=(const Matrix<T> &m);
        Matrix<T>& operator-=(const Matrix<T> &m);
        Matrix<T>& operator*=(const Matrix<T> &m);

    };

    typedef Matrix<int> MatInt, VecInt;
    typedef Matrix<long> MatLong, VecLong;
    typedef Matrix<long long> MatLLong, VecLLong;
    typedef Matrix<BigInt> MatBig, VecBig;
    typedef class MatDBL VecDBL;

    /**
     * 行列(小数)\n
     * MatDBL(const double *num, const int &row, const int &col = 1);\n
     * MatDBL(const int &row, const int &col = 1);\n
     * MatDBL(const MatDBL& m);\n
     * MatDBL(const char *filename);
     */
    class MatDBL {
        double *num;
        int row, col;
        int selectPivot(const int &j, const int &start)const;
    public:
        MatDBL(const double *num, const int &row, const int &col = 1);
        MatDBL(const int &row, const int &col = 1);
        MatDBL(const MatDBL& m);
        MatDBL(const char *filename);

        ~MatDBL();

        int getRow()const;
        int getCol()const;
        MatDBL add(const MatDBL &m)const;
        MatDBL subtract(const MatDBL &m)const;
        MatDBL multiply(const MatDBL &m)const;
        double getIJ(const int &i, const int &j);
        void divLine(const int& i, double f);
        void mulLine(const int& i, double f);
        void addLine(const int &i, const int &j, double c);
        void swapLine(const int& i1, const int& i2);
        MatDBL transpose()const;
        void print(std::ostream &os = std::cout)const;
        double trace()const;
        bool isVector()const;
        MatDBL inverse()const;
        double det()const;
        double cofactor(const int& i, const int& j)const;
        MatDBL cofactorMatrix()const;

        double innerProduct(const VecDBL& v)const;
        MatDBL outerProduct(const VecDBL &v)const;
        VecDBL crossProduct(const VecDBL &v)const;
        MatDBL wedgeProduct(const VecDBL &v)const;

        static MatDBL multiplyP(const int &n, const int &i, const double &c);
        static MatDBL addP(const int &n, const int &i, const int &j, const double &c);
        static MatDBL swapP(const int &n, const int &i, const int &j);
        static MatDBL createE(const int& n);
        static VecDBL solver(MatDBL A, VecDBL b);
        static VecDBL approximate(const char *filename, const int &length, const int &n);

        friend std::ostream& operator<<(std::ostream& os, const MatDBL& m);

        double *operator[](const int &i)const;
        double& operator()(const int &i)const;

        MatDBL operator-() const;
        MatDBL operator+() const;
        MatDBL operator+(const MatDBL &m)const;
        MatDBL operator-(const MatDBL &m)const;
        MatDBL operator*(const MatDBL &m)const;
        MatDBL operator*(const double &f)const;
        MatDBL operator/(const double &f)const;
        friend MatDBL operator*(const double& f, const MatDBL &m);

        MatDBL& operator+=(const MatDBL &m);
        MatDBL& operator-=(const MatDBL &m);
        MatDBL& operator*=(const MatDBL &m);
        bool operator==(const MatDBL &m)const;
        bool operator!=(const MatDBL &m)const;
        MatDBL operator^(int n) const;
        MatDBL operator=(const MatDBL &m);
    };

}


#endif	/* MATRIXDECL_HPP */

