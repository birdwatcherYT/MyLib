#ifndef MATRIXIMPL_HPP
#define	MATRIXIMPL_HPP

#include "MatrixDECL.hpp"

namespace mylib {

    template<class T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)const {
        return this->add(m);
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T>& m)const {
        return this->subtract(m);
    }

    template<class T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T>& m)const {
        return this->multiply(m);
    }

    template<class T>
    Matrix<T> operator*(const T& n, const Matrix<T> &m) {
        return m.multiply(n);
    }

    template<class T>
    Matrix<T> Matrix<T>::operator*(const Frac<T>& f) const {
        return this->multiply(f);
    }

    /**
     * 行列用オペレータ(i,jの要素を得る。ただし、係数は無視)
     * @param i
     * @return 
     */
    template<class T>
    T* Matrix<T>::operator[](const int& i) const {
        ASSERT(i<row, "Error : 範囲外の参照");
        return &num[i * col];
    }

    /**
     * ベクトル用オペレータ(i番目の要素を返す。ただし、係数は無視)
     * @param i
     * @return 
     */
    template<class T>
    T& Matrix<T>::operator()(const int& i) const {
        ASSERT(i < row*col, "Error : 範囲外の参照");
        return num[i];
    }

    /**
     * ベクトルの内積
     * @param v
     * @return 分数
     */
    template<class T>
    Frac<T> Matrix<T>::innerProduct(const Vec<T>& v)const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        Matrix<T> tmp = this->transpose().multiply(v);
        return tmp.f * tmp.num[0];
    }

    /**
     * 直積
     * @param v
     * @return 
     */
    template<class T>
    Matrix<T> Matrix<T>::outerProduct(const Vec<T> &v) const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        return this->multiply(v.transpose());
    }

    /**
     * 外積(クロス積)
     * @param v
     * @return 
     */
    template<class T>
    Vec<T> Matrix<T>::crossProduct(const Vec<T> &v) const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        ASSERT(row == v.row, "Error : 演算不能");

        Vec<T> ans(row);
        switch (row) {
            case 1:
                break;
            case 3:
                ans(0) = num[1] * v(2) - num[2] * v(1);
                ans(1) = num[2] * v(0) - num[0] * v(2);
                ans(2) = num[0] * v(1) - num[1] * v(0);
                break;
            case 7:
                ans(0) = num[1] * v(2) - num[2] * v(1) - num[3] * v(4) + num[4] * v(3) - num[5] * v(6) + num[6] * v(5);
                ans(1) = -num[0] * v(2) + num[2] * v(0) - num[3] * v(5) + num[4] * v(6) + num[5] * v(3) - num[6] * v(4);
                ans(2) = num[0] * v(1) - num[1] * v(0) - num[3] * v(6) - num[4] * v(5) + num[5] * v(4) + num[6] * v(3);
                ans(3) = num[0] * v(4) + num[1] * v(5) + num[2] * v(6) - num[4] * v(0) - num[5] * v(1) - num[6] * v(2);
                ans(4) = -num[0] * v(3) - num[1] * v(6) + num[2] * v(5) + num[3] * v(0) - num[5] * v(2) + num[6] * v(1);
                ans(5) = num[0] * v(6) - num[1] * v(3) - num[2] * v(4) + num[3] * v(1) + num[4] * v(2) - num[6] * v(0);
                ans(6) = -num[0] * v(5) + num[1] * v(4) - num[2] * v(3) + num[3] * v(2) - num[4] * v(1) + num[5] * v(0);
                break;
            default:
                ASSERT(0, "Error : クロス積を計算できません");
        }
        return ans;
    }

    /**
     * 外積(クロス積ではない。ウェッジ積)
     * @param v
     * @return 行列
     */
    template<class T>
    Matrix<T> Matrix<T>::wedgeProduct(const Vec<T>& v) const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        return (this->outerProduct(v))-(v.outerProduct(*this));
    }

    template<class T>
    bool Matrix<T>::isVector() const {
        return (col == 1);
    }

    template<class U>
    Matrix<U> operator*(const Frac<U>& f, const Matrix<U> &m) {
        return m.multiply(f);
    }

    template<class T>
    Matrix<T> Matrix<T>::operator*(const T& n)const {
        return this->multiply(n);
    }

    template<class T>
    Matrix<T> Matrix<T>::operator/(const T& n) const {
        return this->divide(n);
    }

    template<class T>
    Matrix<T> Matrix<T>::operator/(const Frac<T>& f) const {
        return this->divide(f);
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const {
        Matrix<T> ans = *this;
        ans.f = -f;
        ans.trim();
        return ans;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator+() const {
        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator ^(int n) const {
        ASSERT(row == col, "Error : 正方行列ではありません");

        Matrix<T> ans = createE(row), tmp = *this;
        if (n < 0) {
            n = -n;
            tmp = inverse();
        }
        if (n & 1)ans = tmp;

        while (n != 0) {
            tmp = tmp.multiply(tmp);
            if ((n >>= 1)&1)ans = ans.multiply(tmp);
        }
        return ans;
    }

    template<class U>
    std::ostream& operator<<(std::ostream& os, const Matrix<U>& m) {
        m.print(os);
        return os;
    }

    template<class T>
    Frac<T> Matrix<T>::trace() const {
        ASSERT(row == col, "Error : 正方行列ではありません");
        T sum = 0;
        for (int i = 0; i < row; ++i)
            sum += getIJ(i, i);
        return f*sum;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& m) {
        *this = this->add(m);
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& m) {
        *this = this->subtract(m);
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& m) {
        *this = this->multiply(m);
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
        if (row != m.row || col != m.col) {
            delete []num;
            row = m.row, col = m.col;
            num = new T[row * col];
        }

        f = m.f;
        memmove(&num[0], &m.num[0], row * col * sizeof (T));
        return *this;
    }

    template<class T>
    bool Matrix<T>::operator==(const Matrix<T>& m) const {
        return this->equal(m);
    }

    template<class T>
    bool Matrix<T>::operator!=(const Matrix<T>& m) const {
        return !this->equal(m);
    }

    template<class T>
    Frac<T> Matrix<T>::getCoefficient()const {
        return f;
    }

    /**
     * コピーコンストラクタ
     */
    template<class T>
    Matrix<T>::Matrix(const Matrix<T> &m) {

        row = m.row;
        col = m.col;

        f = m.f;

        int pro = row * col;
        num = new T[pro];

        memmove(&num[0], &m.num[0], sizeof (T) * pro);
    }

    /**
     * コンストラクタ(行列、ベクトル)
     * @param num 行列に与える初期値 
     * @param row 行
     * @param col 列 default=1 (default:ベクトル)
     * @param f 係数 default=ONE
     */
    template<class T>
    Matrix<T>::Matrix(const T *num, const int& row, const int& col, const Frac<T> &f) {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : 符号あり整数を指定してください");
        this->row = row;
        this->col = col;

        this->f = f;
        int pro = row*col;
        this->num = new T[pro];
        memmove(&this->num[0], &num[0], sizeof (T) * pro);
        this->trim();
    }

    /**
     * ベクトル用コンストラクタ
     * @param num 要素
     * @param row 要素数
     * @param f 係数
     */
    template<class T>
    Matrix<T>::Matrix(const T *num, const int& row, const Frac<T> &f) {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : 符号あり整数を指定してください");

        this->row = row;
        this->col = 1;
        this->f = f;

        this->num = new T[row];
        memmove(&this->num[0], &num[0], sizeof (T) * row);

        this->trim();
    }

    /**
     * コンストラクタ(成分はすべてゼロ),係数は1(行列、ベクトル)
     * @param row 行
     * @param col 列    default col = 1
     */
    template<class T>
    Matrix<T>::Matrix(const int& row, const int& col) {
        //ASSERT(TYPE_EQ(T, int) || TYPE_EQ(T, long) || TYPE_EQ(T, LLONG) || TYPE_EQ(T, BigInt), "Error : 符号あり整数を指定してください");

        this->row = row;
        this->col = col;
        f = Frac<T>::ONE;
        int pro = row*col;
        this->num = new T[pro];

        for (T *p = &num[0]; p != &num[pro]; ++p)
            *p = 0;
    }

    /**
     * ファイルから、行列を読み取る。形式は、\n
     * # 2 3 \n
     * scale: 1/5 \n
     * 1,2,3, \n
     * 4,5,6, \n
     * @param filename ファイル名
     */
    template<class T>
    Matrix<T>::Matrix(const char *filename) {
        std::ifstream ifs(filename);
        ASSERT(!ifs.fail(), "Error : ファイルがありません");

        const int maxsize = 1024;
        char str[maxsize] = "", *p;
        T number;
        ASSERT(ifs.good(), "Error : ファイルを開けません");

        //行、列
        while (ifs.get() != '#')
            ASSERT(!ifs.eof(), "Error : 正常に読み取れません");
        ifs.getline(str, maxsize - 1);
        p = str;
        ASSERT((p = readInt(p, row)) != NULL, "Error : 正常に読み取れません");
        if (readInt(p, col) == NULL)col = 1;
        num = new T[col * row];
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
        for (int i = 0; i < row; ++i) {
            memset(str, '\0', maxsize);
            ifs.getline(str, maxsize - 1);
            p = str;
            for (int j = 0; j < col; ++j)
                ASSERT((p = readInt(p, (*this)[i][j])) != NULL, "Error : 成分が足りません");
        }
        ifs.close();
    }

    /**
     * デストラクタ
     */
    template<class T>
    Matrix<T>::~Matrix() {
        delete []num;
    }

    /**
     * 整える
     */
    template<class T>
    void Matrix<T>::trim() {
        int i, j = -1, k = -1, pro = col * row;

        //係数は必ず正
        switch (f.getSign()) {
            case 0:
                for (T *p = &num[0]; p != &num[pro]; ++p)
                    *p = 0;
                f = Frac<T>::ONE;
                return;
            case -1:
                f = -f;
                for (i = 0; i < pro; ++i)num[i] = -num[i];
                break;
        }

        //ゼロでない２つを探す
        for (i = 0; i < pro; ++i)
            if (num[i] != 0) {
                j = i;
                break;
            }
        for (++i; i < pro; ++i)
            if (num[i] != 0) {
                k = i;
                break;
            }

        T gc;
        if (j >= 0 && k >= 0)
            gc = gcd(abs_f(num[j]), abs_f(num[k]));
        else if (j >= 0 && k < 0) {
            //成分が一つだけゼロでない
            f *= abs_f(num[j]);
            num[j] = (num[j] < 0) ? -1 : 1;
            return;
        } else {
            //成分が全部ゼロの時
            f = Frac<T>::ONE;
            return;
        }
        for (++i; i < pro; ++i) {
            if (gc == 1)break;
            if (num[i] != 0)
                gc = gcd(gc, abs_f(num[i]));
        }
        if (gc != 1) {
            f *= gc;
            for (i = 0; i < pro; ++i)
                num[i] /= gc;
        }
    }

    /**
     * i行に対して、nで割る
     * @param i
     * @param n
     */
    template<class T>
    void Matrix<T>::divLine(const int& i, T n) {
        if (n == 1)return;
        ASSERT(n != 0, "Error : ゼロで割れません");
        //割りきれるかどうか
        bool flag = true;
        for (int k = 0; k < col; ++k) {
            if (getIJ(i, k) % abs_f(n) != 0) {
                flag = false;
                break;
            }
        }
        //割り切れる
        if (flag) {
            for (int k = 0; k < col; ++k)
                setIJ(i, k, getIJ(i, k) / n);
        } else {
            f /= n;
            for (int j = 0; j < row; ++j) {
                if (j == i)continue;
                for (int k = 0; k < col; ++k)
                    setIJ(j, k, getIJ(j, k) * n);
            }
            trim();
        }
    }

    /**
     * i行をn倍する
     * @param i
     * @param n
     */
    template<class T>
    void Matrix<T>::mulLine(const int& i, T n) {
        for (int k = 0; k < col; ++k)
            setIJ(i, k, getIJ(i, k) * n);
        trim();
    }

    /**
     * i行をc倍する
     * @param i
     * @param c
     */
    template<class T>
    void Matrix<T>::mulLine(const int& i, Frac<T> c) {
        divLine(i, c.getBelow());
        mulLine(i, c.getAbove() * c.getSign());
    }

    /**
     * i行にj行のc倍を加える
     * @param i
     * @param j
     * @param c
     */
    template<class T>
    void Matrix<T>::addLine(const int& i, const int &j, Frac<T> c) {
        for (int k = 0; k < col; ++k)
            setIJ(i, k, getIJ(i, k) * c.getBelow() + getIJ(j, k) * c.getAbove() * c.getSign());
        divLine(i, c.getBelow());
        trim();
    }

    /**
     * 係数を無視した値を得る
     */
    template<class T>
    T Matrix<T>::getIJ(const int& i, const int& j)const {
        ASSERT(i < row && j<col, "Error : 範囲外の参照");
        return num[col * i + j];
    }

    /**
     * (i,j)のアドレスを得る
     */
    template<class T>
    T* Matrix<T>::getIJAdd(const int& i, const int& j)const {
        ASSERT(i < row && j<col, "Error : 範囲外の参照");
        return &num[col * i + j];
    }

    template<class T>
    int Matrix<T>::getRow() const {
        return row;
    }

    template<class T>
    int Matrix<T>::getCol() const {
        return col;
    }

    /**
     * (i,j)にnをセット。係数は無視。(trimしない)
     * @param n
     */
    template<class T>
    void Matrix<T>::setIJ(const int& i, const int& j, const T &n) {
        ASSERT(i < row && j<col, "Error : 範囲外の参照");
        num[col * i + j] = n;
    }

    template<class T>
    void Matrix<T>::swapLine(const int& i1, const int& i2) {
        if (i1 == i2)return;
        for (int i = 0; i < col; ++i)
            swap_f(getIJAdd(i1, i), getIJAdd(i2, i));
    }

    template<class T>
    Matrix<T> Matrix<T>::add(const Matrix<T> &m) const {
        ASSERT(col == m.col && row == m.row, "Error : 演算不能");
        Matrix<T> ans(row, col);
        T gc = gcd(f.getAbove(), m.f.getAbove())
                , lc = lcm(f.getBelow(), m.f.getBelow());
        ans.f.setValue(gc, lc);
        for (int i = 0, pro = col * row; i < pro; ++i) {
            ans.num[i] = (lc / f.getBelow()) *(f.getAbove() / gc) * num[i] * f.getSign()
                    + (lc / m.f.getBelow()) * (m.f.getAbove() / gc) * m.num[i] * m.f.getSign();
        }
        ans.trim();
        return ans;
    }

    template<class T>
    Matrix<T> Matrix<T>::subtract(const Matrix<T> &m)const {
        Matrix<T> tmp(row, col);
        tmp = m;
        tmp.f = -tmp.f;
        return add(tmp);
    }

    template<class T>
    Matrix<T> Matrix<T>::multiply(const Matrix<T> &m)const {
        ASSERT(col == m.row, "Error : 演算不能");
        Matrix<T> ans(row, m.col);
        T sum;
        ans.f = f * m.f;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < m.col; ++j) {
                sum = 0;
                for (int k = 0; k < col; ++k)
                    sum += getIJ(i, k) * m.getIJ(k, j);
                ans.setIJ(i, j, sum);
            }
        }
        ans.trim();
        return ans;
    }

    template<class T>
    Matrix<T> Matrix<T>::multiply(const T& n) const {
        Matrix<T> ans(row, col);
        ans = *this;
        ans.f *= n;
        ans.trim();
        return ans;
    }

    template<class T>
    Matrix<T> Matrix<T>::multiply(const Frac<T> &f) const {
        Matrix<T> ans(row, col);
        ans = *this;
        ans.f *= f;
        ans.trim();
        return ans;
    }

    template<class T>
    Matrix<T> Matrix<T>::divide(const T& n) const {
        ASSERT(n != 0, "Error : ゼロで割れません");
        Matrix<T> ans(row, col);
        ans = *this;
        ans.f /= n;
        ans.trim();
        return ans;
    }

    template<class T>
    Matrix<T> Matrix<T>::divide(const Frac<T>& f)const {
        Matrix<T> ans(row, col);
        ans = *this;
        ans.f /= f;
        ans.trim();
        return ans;
    }

    template<class T>
    void Matrix<T>::print(std::ostream &os) const {
        os << "# " << row << " " << col << std::endl;
        os << "scale: " << f << std::endl;
        for (int i = 0, pro = row * col; i < pro; ++i) {
            os << num[i] << ',';
            if ((i + 1) % col == 0)os << std::endl;
        }
    }

    /**
     * 係数無視した場合の(i,j)における余因子を計算
     */
    template<class T>
    T Matrix<T>::cofactorSub(const int& i, const int& j) const {
        ASSERT(row == col, "Error : 正方行列ではありません");
        if (row == 1) {
            if ((i + j) & 1) return -getIJ(i, j);
            else getIJ(i, j);
        }

        Matrix<T> tmp(row - 1, col - 1);

        for (int k = 0, index = 0; k < row; ++k) {
            if (k == i)continue;
            for (int m = 0; m < col; ++m) {
                if (m == j)continue;
                tmp.num[index++] = getIJ(k, m);
            }
        }

        if ((i + j) & 1) return -tmp.detSub();
        else return tmp.detSub();
    }

    /**
     * (i,j)での余因子
     * @param i
     * @param j
     */
    template<class T>
    Frac<T> Matrix<T>::cofactor(const int& i, const int& j) const {
        ASSERT(row == col, "Error : 正方行列ではありません");

        return cofactorSub(i, j) * f.pow(row - 1);
    }

    /**
     * 余因子行列 (性質：Aの逆行列 * detA = Aの余因子行列)
     */
    template<class T>
    Matrix<T> Matrix<T>::cofactorMatrix() const {
        Matrix<T> ans(row, col);
        ASSERT(row == col, "Error : 正方行列ではありません");

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                ans.setIJ(j, i, cofactorSub(i, j));
        }
        ans.f = f.pow(row - 1);
        ans.trim();
        return ans;
    }

    /**
     * 係数無視した時の行列式
     */
    template<class T>
    T Matrix<T>::detSub() const {
        ASSERT(row == col, "Error : 正方行列ではありません");

        T det, min, scale;
        det = 1;
        int i, j, k, minIndex, count;
        Matrix<T> t = *this;
        for (j = 0; j < col; ++j) {
            while (true) {
                count = 0;
                min = -1;
                for (i = j; i < row; ++i) {
                    if (t.getIJ(i, j) != 0) {
                        if (min < 0 || abs_f(t.getIJ(i, j)) < min) {
                            min = abs_f(t.getIJ(i, j));
                            minIndex = i;
                        }
                        ++count;
                    }
                }
                if (count == 0) {
                    det = 0;
                    return det;
                } else if (count == 1) {
                    det *= t.getIJ(minIndex, j);
                    if (minIndex != j) {
                        t.swapLine(j, minIndex);
                        det *= -1;
                    }
                    break;
                } else {
                    for (i = j; i < row; ++i) {
                        if (i == minIndex || (scale = t.getIJ(i, j) / t.getIJ(minIndex, j)) == 0)continue;
                        for (k = j; k < col; ++k)
                            *t.getIJAdd(i, k) -= scale * t.getIJ(minIndex, k);
                    }
                }
            }
        }
        return det;
    }

    /**
     * 行列式
     */
    template<class T>
    Frac<T> Matrix<T>::det() const {
        ASSERT(row == col, "Error : 正方行列ではありません");

        return detSub() * f.pow(row);
    }

    /**
     * 逆行列
     */
    template<class T>
    Matrix<T> Matrix<T>::inverse() const {
        ASSERT(row == col, "Error : 正方行列ではありません");

        T min, scale;
        int i, j, k, minIndex, count;
        Matrix<T> t = *this;
        Matrix<T> e = createE(row);

        for (j = 0; j < col; ++j) {
            while (true) {
                count = 0;
                min = -1;
                for (i = j; i < row; ++i) {
                    if (t.getIJ(i, j) != 0) {
                        if (min < 0 || abs_f(t.getIJ(i, j)) < min) {
                            min = abs_f(t.getIJ(i, j));
                            minIndex = i;
                        }
                        ++count;
                    }
                }
                if (count == 0) {
                    return Matrix<T>(row, col);
                } else if (count == 1) {
                    t.divLine(minIndex, min);
                    e.divLine(minIndex, min);
                    for (i = 0; i < row; ++i) {
                        if (i != minIndex && (scale = t.getIJ(i, j) / t.getIJ(minIndex, j)) != 0) {
                            for (k = 0; k < col; ++k) {
                                *t.getIJAdd(i, k) -= scale * t.getIJ(minIndex, k);
                                *e.getIJAdd(i, k) -= scale * e.getIJ(minIndex, k);
                            }
                        }
                    }
                    if (minIndex != j) {
                        //行の交換
                        t.swapLine(j, minIndex);
                        e.swapLine(j, minIndex);
                    }
                    break;
                } else {
                    for (i = j; i < row; ++i) {
                        if (i == minIndex || (scale = t.getIJ(i, j) / t.getIJ(minIndex, j)) == 0)continue;
                        for (k = 0; k < col; ++k) {
                            *t.getIJAdd(i, k) -= scale * t.getIJ(minIndex, k);
                            *e.getIJAdd(i, k) -= scale * e.getIJ(minIndex, k);
                        }
                    }
                }
            }
        }
        for (i = 0; i < row; ++i)
            e.divLine(i, t.getIJ(i, i));
        e.f /= t.f;
        e.trim();
        return e;
    }

    template<class T>
    int Matrix<T>::rank() const {
        int i, j, k, minIndex, count, notRank = 0, rank = 0;
        T min, scale;

        Matrix<T> t = *this;

        for (j = 0; j < col; ++j) {
            while (true) {
                if (j - notRank >= row) {
                    j = col;
                    break;
                }
                count = 0;
                min = -1;
                for (i = j - notRank; i < row; ++i) {
                    if (t.getIJ(i, j) != 0) {
                        if (min < 0 || abs_f(t.getIJ(i, j)) < min) {
                            min = abs_f(t.getIJ(i, j));
                            minIndex = i;
                        }
                        ++count;
                    }
                }
                if (count == 0) {
                    ++notRank;
                    break;
                } else if (count == 1) {
                    t.divLine(minIndex, t.getIJ(minIndex, j));
                    for (i = 0; i < row; ++i) {
                        if (i != minIndex && (scale = t.getIJ(i, j) / t.getIJ(minIndex, j)) != 0) {
                            for (k = 0; k < col; ++k)
                                *t.getIJAdd(i, k) -= scale * t.getIJ(minIndex, k);
                        }
                    }
                    t.swapLine(j - notRank, minIndex);
                    ++rank;
                    break;
                } else {
                    for (i = j - notRank; i < row; ++i) {
                        if (i == minIndex || (scale = t.getIJ(i, j) / t.getIJ(minIndex, j)) == 0)continue;
                        for (k = 0; k < col; ++k)
                            *t.getIJAdd(i, k) -= scale * t.getIJ(minIndex, k);
                    }
                }
            }
        }
        return rank;
    }

    template<class T>
    bool Matrix<T>::equal(const Matrix<T> &m) const {
        if (!f.equal(m.f))return false;
        if (col != m.col || row != m.row)return false;
        for (int i = 0, pro = row * col; i < pro; ++i)
            if (num[i] != m.num[i])return false;
        return true;
    }

    /**
     * 転置
     */
    template<class T >
    Matrix<T> Matrix<T>::transpose() const {
        Matrix<T> ans(col, row);
        ans.f = f;
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                ans.setIJ(j, i, getIJ(i, j));

        return ans;
    }

    /**
     * 単位行列を得る
     * @param n 行列のサイズ
     */
    template<class T >
    Matrix<T> Matrix<T>::createE(const int& n) {
        Matrix<T> e(n, n);
        e.f = Frac<T>::ONE;
        for (int i = 0; i < n; ++i)
            e.setIJ(i, i, 1);
        return e;
    }

    /**
     * 基本行列 n次単位行列のi行をc(c!=0)倍した行列
     * @param n
     * @param i
     * @param c
     * @return 
     */
    template<class T >
    Matrix<T> Matrix<T>::multiplyP(const int &n, const int &i, const Frac<T> &c) {
        Matrix<T> p = createE(n);
        p.mulLine(i, c);
        return p;
    }

    /**
     * 基本行列 n次単位行列のi行にj行のc倍を加えた行列
     * @param n
     * @param i
     * @param j
     * @param c
     * @return 
     */
    template<class T>
    Matrix<T> Matrix<T>::addP(const int &n, const int &i, const int &j, const Frac<T> &c) {
        Matrix<T> tmp(n, n);
        tmp.f = c;
        tmp[i][j] = 1;
        return (createE(n) + tmp);
    }

    /**
     * 基本行列 n次単位行列のi行とj行を入れ替えた行列
     * @param n
     * @param i
     * @param j
     * @return 
     */
    template<class T>
    Matrix<T> Matrix<T>::swapP(const int &n, const int &i, const int &j) {
        Matrix<T> p = createE(n);
        p.swapLine(i, j);
        return p;
    }

    /**
     * A x = b (変数の数と方程式の数が合わない時は最小二乗解をかえす)
     * @param A 係数行列
     * @param b 右辺ベクトル
     * @return x 方程式の解
     */
    template<class T>
    Vec<T> Matrix<T>::solver(Matrix<T> A, Vec<T> b) {
        ASSERT(A.row == b.row, "Error : 入力が正しくありません");
        if (A.row != A.col) {
            b = A.transpose() * b;
            A = A.transpose() * A;
        }

        T min, scale;
        int i, j, k, minIndex, count;

        for (j = 0; j < A.col; ++j) {
            while (true) {
                count = 0;
                min = -1;
                for (i = j; i < A.row; ++i) {
                    if (A.getIJ(i, j) != 0) {
                        if (min < 0 || abs_f(A.getIJ(i, j)) < min) {
                            min = abs_f(A.getIJ(i, j));
                            minIndex = i;
                        }
                        ++count;
                    }
                }
                if (count == 0) {
                    return Vec<T>(b.row, b.col);
                } else if (count == 1) {
                    A.divLine(minIndex, min);
                    b.divLine(minIndex, min);
                    for (i = 0; i < A.row; ++i) {
                        if (i != minIndex && (scale = A.getIJ(i, j) / A.getIJ(minIndex, j)) != 0) {
                            for (k = 0; k < A.col; ++k)
                                *A.getIJAdd(i, k) -= scale * A.getIJ(minIndex, k);
                            *b.getIJAdd(i, 0) -= scale * b.getIJ(minIndex, 0);
                        }
                    }
                    if (minIndex != j) {
                        //行の交換
                        A.swapLine(j, minIndex);
                        b.swapLine(j, minIndex);
                    }
                    break;
                } else {
                    for (i = j; i < A.row; ++i) {
                        if (i == minIndex || (scale = A.getIJ(i, j) / A.getIJ(minIndex, j)) == 0)continue;
                        for (k = 0; k < A.col; ++k)
                            *A.getIJAdd(i, k) -= scale * A.getIJ(minIndex, k);
                        *b.getIJAdd(i, 0) -= scale * b.getIJ(minIndex, 0);
                    }
                }
            }
        }
        for (i = 0; i < A.row; ++i)
            b.divLine(i, A.getIJ(i, i));
        b.f /= A.f;
        b.trim();
        return b;
    }

    /**
     * 階段行列
     * @return 
     */
    template<class T>
    Matrix<T> Matrix<T>::stairsMatrix() const {
        int i, j, k, minIndex, count, notRank = 0;
        Matrix<T> t = *this;
        T min, scale;
        for (j = 0; j < col; ++j) {
            while (true) {
                if (j - notRank >= row) {
                    j = col;
                    break;
                }
                count = 0;
                min = -1;
                for (i = j - notRank; i < row; ++i) {
                    if (t.getIJ(i, j) != 0) {
                        if (min < 0 || abs_f(t.getIJ(i, j)) < min) {
                            min = abs_f(t.getIJ(i, j));
                            minIndex = i;
                        }
                        ++count;
                    }
                }
                if (count == 0) {
                    ++notRank;
                    break;
                } else if (count == 1) {
                    t.divLine(minIndex, t.getIJ(minIndex, j));
                    for (i = 0; i < row; ++i) {
                        if (i != minIndex && (scale = t.getIJ(i, j) / t.getIJ(minIndex, j)) != 0) {
                            for (k = 0; k < col; ++k)
                                *t.getIJAdd(i, k) -= scale * t.getIJ(minIndex, k);
                        }
                    }
                    t.swapLine(j - notRank, minIndex);
                    break;
                } else {
                    for (i = j - notRank; i < row; ++i) {
                        if (i == minIndex || (scale = t.getIJ(i, j) / t.getIJ(minIndex, j)) == 0)continue;
                        for (k = 0; k < col; ++k)
                            *t.getIJAdd(i, k) -= scale * t.getIJ(minIndex, k);
                    }
                }
            }
        }
        t.f.setValue(1, 1);
        t.trim();
        return t;
    }

}


#endif	/* MATRIXIMPL_HPP */

