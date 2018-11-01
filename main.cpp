#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdio>
#include <fstream>
#include "MyLib.hpp"

using namespace std;
using namespace mylib;

inline Complex<double> f(const Complex<double>& z);
inline Complex<double> c(const double &t);

int main(int argc, char **argv) {
    /*
    LLONG p = 208457429, q = 304209343, e = 30713208764482633, d, n = 63414697519559147;
    LLONG p1q1 = (p - 1)*(q - 1), x, y;
    extendEuclid(e, p1q1, x, y);
    d = x + p1q1;
    BigInt C = 33963736291445231;
    cout << d << endl << C.powMod(d, n);
    return 0;
     */

    //使い方------------------------------------
    cout << "BigInt-------------------------------------------------------------" << endl;
    int num[] = {1234, 5678}; //4桁ずつ
    BigInt big1(12345), //数値による初期化(long longまで)
            big2("-987654"); //文字列による初期化(基本的に上限はない)
    BigInt big3(num, ELEMENTS_OF(num), -1), //配列による初期化 引数:(配列、個数、符号)
            big4; //宣言のみ
    big4 = 5; //あとから代入(long longまで)


    //演算(int)と同じ
    cout << big1 + big2 << endl;
    cout << big1 - big2 << endl;
    cout << big1 * big2 << endl;
    cout << big3 / big2 << endl;
    cout << big3 % big4 << endl;
    cout << BigInt::fact(123) << endl;

    cout << "BigDec-------------------------------------------------------------" << endl;
    BigDec dec1(123), //整数で初期化
            dec2("3.14"), //小数の文字列で初期化
            dec3(big1, -4); //BigInt*10^-4で初期化
    //演算
    cout << dec1 + dec2 << endl;
    cout << dec1 - dec2 << endl;
    cout << dec1 * dec2 << endl;
    cout << dec1 / dec2 << endl; //小数点30桁までの精度(default)
    cout << dec1.divide(dec2, 50) << endl; //小数点50桁までの精度
    cout << dec1 % dec2 << endl;
    cout << -dec3 << endl;
    cout << BigDec::sqrt(dec2) << endl;
    cout << BigDec::pow(dec2, dec1) << endl;
    cout << BigDec::log(dec1).round(2) << endl;

    cout << "Frac<整数>,FracInt,FracLong,FracLLong,FracBig----------------------" << endl;
    Frac<int> fra1(3, 4); //   3/4
    FracInt fra2(-2, -4); //  -2/-4 = 1/2  Frac<int>と同等
    cout << fra2 << endl; //約分されている
    cout << fra1 + fra2 << endl;
    cout << fra1 - fra2 << endl;
    cout << fra1 * fra2 << endl;
    cout << fra1 / fra2 << endl;

    cout << "Complex<double>,Complex<Frac<整数> >,CompDBL,CompInt,CompLong...---" << endl;
    Complex<double> com1(1.23, 3.33), //1.23+3.33i
            com2(3, 4); //3+4i
    Complex<Frac<int> > com3(fra1, fra2); //  3/4 + 1/2 i
    CompInt com4(fra2, fra1); //   1/2 + 3/4 i
    cout << com1 + com2 << endl; //同じ型同士で演算可能
    cout << com1 - com2 << endl;
    cout << com1 * com2 << endl;
    cout << com1 / com2 << endl;
    cout << com3 * com4 << endl;
    cout << CompDBL::complexIntegrate(f, c, 0, 2 * M_PI, 0.00048828125) << endl; //複素線積分

    cout << "Matrix<整数>,Mat<整数>,MatInt,MatLong,MatLLong,MatBig---------------" << endl;
    int m1[] = {
        1, 2, 3,
        -1, 5, 6,
        7, 3, 1
    };
    int m2[] = {
        1, 2, 3,
        7, 8, 4
    };
    int m3[] = {
        -1, 2, 3,
        3, -4, 5,
        7, 6, -8
    };

    Matrix<int> mat1(m1, 3, 3); //係数1
    Mat<int> mat2(m2, 2, 3, fra1); //係数は3/4
    MatInt mat3(m3, 3, 3); // Mat<int> と同じ
    cout << mat1;
    cout << mat2;
    cout << mat2 * mat1;
    cout << mat2 + mat2;
    cout << mat1 - mat3;
    cout << mat1.inverse(); //  .関数 でアクセスできる
    cout << mat2.transpose();
    cout << mat2.rank() << endl;
    cout << mat1.det() << endl;

    cout << "Vec<整数>----------------------------------------------------------" << endl;
    long v1[] = {
        1,
        2,
        3
    };
    long v2[] = {
        4,
        5,
        6
    };
    Vec<long> vec1(v1, 3), //係数1
            vec2(v2, 3, Frac<long>(1, 2)); //係数 1/2
    cout << vec1 + vec2;
    cout << vec1.innerProduct(vec2) << endl; //内積

    cout << "MatDBL,VecDBL------------------------------------------------------" << endl;
    double md1[] = {
        1.1, 2.2, 3.3,
        -1.2, 3.6, 6.2,
        9.9, 4.7, 2.7
    };
    MatDBL mat4(md1, 3, 3);
    cout << mat4.inverse();
    cout << mat4.cofactorMatrix();
    cout << (mat4^3);
    double vd1[] = {
        1.3,
        2.1,
        3.1
    };
    double vd2[] = {
        -1.6,
        2.4,
        -3.3
    };
    MatDBL vec_1(vd1, 3), vec_2(vd2, 3), vec_3(3);
    cout << (vec_3 = vec_1.crossProduct(vec_2));
    cout << "内積=" << vec_2.innerProduct(vec_1) << endl;
    cout << (vec_3 + vec_2);

    cout << "Poly<整数>,PolyInt,PolyLong,PolyLLong,PolyBig----------------------" << endl;
    int p1[] = {1, 2, 4};
    int p2[] = {5, 2, 3, 3, 1};
    int p3[] = {1, 3, 2};
    Poly<int> pol1(p1, 2), //x^2+2x+4  (配列,最高次)
            pol2(p2, 4, fra1); //(5x^4+2x^3+3x^2) * 3/4
    PolyInt pol3(p3, 2);
    cout << pol1 + pol2;
    cout << pol1 - pol2;
    cout << pol1 * pol2;
    cout << pol2 / pol1;
    cout << pol2 % pol1;
    cout << pol3.factrization();
    cout << pol1.value(2) << endl;

    cout << "MathSet<型>,Set<型>------------------------------------------------" << endl;
    int s1[] = {1, 1, 2, 3, 4}, s2[] = {1, 3, 5};
    Set<int> set1(s1, ELEMENTS_OF(s1)),
            set2(s2, ELEMENTS_OF(s2)),
            set3;
    cout << set1 << endl;
    cout << set2 << endl;
    cout << set1 + set2 << endl;
    cout << set1 - set2 << endl;
    cout << set1.intersecSet(set2) << endl;
    cout << set1.directProduct(set2) << endl;
    cout << set2.powerSet() << endl;
    cout << set3 << endl;
    cout << set3.powerSet() << endl;

    cout << "Calcu--------------------------------------------------------------" << endl;
    Calcu ca("x^3+x-e^x+8");
    cout << ca.differential() << endl//微分
            << ca.differential(1) << endl; //微分値
    ca.setString("(4.0-(2+1))*3+x^2*sin(x)");
    cout << ca.func(-1.2) << endl;
    ca.setString("x*x+cos(x)");
    cout << "積分値=" << ca.integrate(0, 1, 0.001953125) << endl; //定積分
    ca.setString("x^3+x-1");
    cout << "x=" << ca.solver(0, 1) << endl; //  =0 の解  (二分法)

    cout << "Utility.h----------------------------------------------------------" << endl;
    cout << gcd(12, 30) << endl;
    cout << "10C4=" << combination<long long>(10, 4) << endl;
    cout << "100C50=" << combination<BigInt>(100, 50) << endl;
    cout << "gcd(12,15)=" << gcd(12, 15) << endl;

    cout << "List.h-------------------------------------------------------------" << endl;
    List<int> list1;

    for (int i = 0; i < 100; ++i)
        list1.pushTail(i);
    list1.erase(list1.begin() + 3ULL);
    list1.remove(10);
    list1.insert(list1.begin() + 5ULL, 100);
    list1.popHead();
    list1.pushHead(10);
    list1.resize(110, 0);
    list1.reverse();
    cout << list1;

    //最小二乗法
    VecDBL v = MatDBL::approximate("data", 40, 2);
    for (int i = 0; i < v.getRow(); ++i)
        cout << ((v(i) < 0) ? "" : "+") << v(i) << "*x**" << i;

    //円分多項式-------------------------------
    const static int N = 100;
    ofstream file;
    file.open("result.txt");
    Poly<int> phi[N];
    for (int i = 1; i < N; ++i) {
        phi[i] = Poly<int>(i);
        phi[i].set(FracInt::ONE);
        phi[i].set(1, 0);
        phi[i].set(-1, i);
    }
    for (int i = 2; i < N; ++i) {
        for (int j = 1; j < i; ++j)
            if (i % j == 0)
                phi[i] = phi[i].divide(phi[j]);
    }
    for (int i = 1; i < N; ++i)
        file << "Φ" << i << "=" << phi[i] << endl;
    file.close();
    return 0;
}

/**
 * 被積分関数
 */
inline Complex<double> f(const Complex<double>& z) {
    return z.inverse();
}

/**
 * 積分経路関数
 */
inline Complex<double> c(const double &t) {
    return Complex<double>(cos(t), sin(t));
}
