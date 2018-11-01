#include "Matrix.hpp"
using namespace std;
namespace mylib {

    /**
     * ファイルから、行列を読み取る。形式は、\n
     * # 2 3\n
     * 1,2,3,\n
     * 4,5,6,\n
     * @param filename ファイル名
     */
    MatDBL::MatDBL(const char* filename) {
        std::ifstream ifs(filename);
        ASSERT(!ifs.fail(), "Error : ファイルがありません");

        const int maxsize = 1024;
        char str[maxsize] = "", *p;
        ASSERT(ifs.good(), "Error : ファイルを開けません");

        //行、列
        while (ifs.get() != '#')
            ASSERT(!ifs.eof(), "Error : 正常に読み取れません");
        ifs.getline(str, maxsize - 1);
        p = str;
        ASSERT((p = readInt(p, row)) != NULL, "Error : 正常に読み取れません");
        if (readInt(p, col) == NULL)col = 1;
        num = new double[col * row];
        //成分
        for (int i = 0; i < row; ++i) {
            memset(str, '\0', maxsize);
            ifs.getline(str, maxsize - 1);
            p = str;
            for (int j = 0; j < col; ++j)
                ASSERT((p = readDouble(p, (*this)[i][j])) != NULL, "Error : 成分が足りません");
        }
    }

    /**
     * コンストラクタ(行列、ベクトル)
     * @param num 行列に与える初期値 
     * @param row 行
     * @param col 列 default=1 (default:ベクトル)
     */
    MatDBL::MatDBL(const double* num, const int& row, const int& col) {
        this->row = row;
        this->col = col;
        int pro = row*col;
        this->num = new double[pro];
        memmove(this->num, num, sizeof (double)*pro);
    }

    /**
     * コンストラクタ(成分はすべてゼロ),(行列、ベクトル)
     * @param row 行
     * @param col 列    default col = 1
     */
    MatDBL::MatDBL(const int& row, const int& col) {
        this->row = row;
        this->col = col;
        int pro = row * col;
        this->num = new double[pro];
        for (double *p = &num[0]; p != &num[pro]; ++p)
            *p = 0.0;
    }

    /**
     * コピーコンストラクタ
     */
    MatDBL::MatDBL(const MatDBL& m) {
        this->row = m.row;
        this->col = m.col;
        int pro = row * col;
        this->num = new double[pro];
        memmove(num, m.num, sizeof (double)*pro);
    }

    /**
     * デストラクタ
     */
    MatDBL::~MatDBL() {
        delete []num;
    }

    int MatDBL::getRow()const {
        return row;
    }

    int MatDBL::getCol()const {
        return col;
    }

    MatDBL MatDBL::add(const MatDBL& m) const {
        ASSERT(row == m.row && col == m.col, "Error : 演算不能");
        MatDBL ans(row, col);
        for (int i = 0, pro = row * col; i < pro; ++i)
            ans.num[i] = num[i] + m.num[i];
        return ans;
    }

    MatDBL MatDBL::subtract(const MatDBL& m) const {
        ASSERT(row == m.row && col == m.col, "Error : 演算不能");
        MatDBL ans(row, col);
        for (int i = 0, pro = row * col; i < pro; ++i)
            ans.num[i] = num[i] - m.num[i];
        return ans;
    }

    MatDBL MatDBL::multiply(const MatDBL& m) const {
        ASSERT(col == m.row, "Error : 演算不能");
        MatDBL ans(row, m.col);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < m.col; ++j) {
                for (int k = 0; k < col; ++k)
                    ans[i][j] += (*this)[i][k] * m[k][j];
            }
        }
        return ans;
    }

    /**
     * 行列用オペレータ(i,jの要素を得る)
     * @param i
     * @return 
     */
    double* MatDBL::operator[](const int& i) const {
        ASSERT(i<row, "Error : 範囲外の参照");
        return &num[i * col];
    }

    /**
     * ベクトル用オペレータ(i番目の要素を返す。ただし、係数は無視)
     * @param i
     * @return 
     */
    double& MatDBL::operator()(const int& i) const {
        ASSERT(i < row*col, "Error : 範囲外の参照");
        return num[i];
    }

    MatDBL MatDBL::operator+() const {
        return *this;
    }

    MatDBL MatDBL::operator-() const {
        MatDBL ans(row, col);
        for (int i = 0, pro = row * col; i < pro; ++i)
            ans.num[i] = -num[i];
        return ans;
    }

    MatDBL MatDBL::operator+(const MatDBL& m) const {
        return this->add(m);
    }

    MatDBL MatDBL::operator-(const MatDBL& m) const {
        return this->subtract(m);
    }

    MatDBL MatDBL::operator*(const MatDBL& m) const {
        return this->multiply(m);
    }

    MatDBL MatDBL::operator*(const double& f) const {
        MatDBL ans(row, col);
        for (int i = 0, pro = row * col; i < pro; ++i)
            ans.num[i] = num[i] * f;
        return ans;
    }

    MatDBL MatDBL::operator/(const double& f) const {
        ASSERT(DBLeq(f, 0), "Error : ゼロで割れません");
        MatDBL ans(row, col);
        for (int i = 0, pro = row * col; i < pro; ++i)
            ans.num[i] = num[i] / f;
        return ans;
    }

    MatDBL operator*(const double& f, const MatDBL &m) {
        return m*f;
    }

    MatDBL& MatDBL::operator+=(const MatDBL& m) {
        *this = *this+m;
        return *this;
    }

    MatDBL& MatDBL::operator-=(const MatDBL& m) {
        *this = *this-m;
        return *this;
    }

    MatDBL& MatDBL::operator*=(const MatDBL& m) {
        *this = *this*m;
        return *this;
    }

    bool MatDBL::operator!=(const MatDBL& m) const {
        return !(*this == m);
    }

    bool MatDBL::operator==(const MatDBL& m) const {
        if (row != m.row || col != m.col)return false;
        for (int i = 0, pro = row * col; i < pro; ++i)
            if (!DBLeq(num[i], m.num[i]))return false;
        return true;
    }

    MatDBL MatDBL::operator ^(int n) const {
        ASSERT(row == col, "Error : 正方行列ではありません");
        MatDBL ans = createE(row), tmp = *this;
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

    MatDBL MatDBL::operator=(const MatDBL& m) {
        if (row != m.row || col != m.col) {
            delete []num;
            row = m.row, col = m.col;
            num = new double[row * col];
        }

        memmove(&num[0], &m.num[0], row * col * sizeof (double));
        return *this;
    }

    double MatDBL::getIJ(const int& i, const int& j) {
        ASSERT(i < row && j<col, "Error : 範囲外の参照");
        return num[i * col + j];
    }

    /**
     * i行に対して、fで割る
     * @param i
     * @param f
     */
    void MatDBL::divLine(const int& i, double f) {
        if (DBLeq(f, 1))return;
        ASSERT(!DBLeq(f, 0), "Error : ゼロで割れません");
        for (int j = 0; j < col; ++j)
            (*this)[i][j] /= f;
    }

    /**
     * i行をf倍する
     * @param i
     * @param f
     */
    void MatDBL::mulLine(const int& i, double f) {
        if (DBLeq(f, 1))return;
        for (int j = 0; j < col; ++j)
            (*this)[i][j] *= f;
    }

    /**
     * i行にj行のc倍を加える
     * @param i
     * @param j
     * @param c
     */
    void MatDBL::addLine(const int& i, const int& j, double c) {
        if (DBLeq(c, 0))return;
        for (int k = 0; k < col; ++k)
            (*this)[i][k] += (*this)[j][k] * c;
    }

    void MatDBL::swapLine(const int& i1, const int& i2) {
        if (i1 == i2)return;
        for (int k = 0; k < col; ++k)
            swap_f((*this)[i1][k], (*this)[i2][k]);
    }

    /**
     * 転置
     * @return 
     */
    MatDBL MatDBL::transpose() const {
        MatDBL ans(col, row);
        for (int i = 0; i < col; ++i)
            for (int j = 0; j < row; ++j)
                ans[i][j] = (*this)[j][i];
        return ans;
    }

    void MatDBL::print(std::ostream& os) const {
        os << "# " << row << " " << col << endl;
        for (int i = 0, pro = row * col; i < pro; ++i) {
            os << num[i] << ',';
            if ((i + 1) % col == 0)os << std::endl;
        }
    }

    double MatDBL::trace() const {
        ASSERT(col == row, "Error : 正方行列ではありません");
        double ans = 0.0;
        for (int i = 0; i < row; ++i)
            ans += (*this)[i][i];
        return ans;
    }

    bool MatDBL::isVector() const {
        return (col == 1);
    }

    /**
     * j列のstart行からで最も絶対値が大きいもののインデックスを返す
     * @param j
     * @param start 開始行
     * @return 
     */
    int MatDBL::selectPivot(const int& j, const int &start) const {
        int index = start;
        double max = abs_f((*this)[index][j]);
        for (int i = start + 1; i < row; ++i) {
            if (max < abs_f((*this)[i][j])) {
                index = i;
                max = abs_f((*this)[i][j]);
            }
        }
        return index;
    }

    /**
     * 行列式
     * @return 
     */
    double MatDBL::det() const {
        ASSERT(row == col, "Error : 正方行列ではありません");
        MatDBL t = *this;
        int index;
        double div, det = 1;
        for (int j = 0; j < col; ++j) {
            index = t.selectPivot(j, j);
            div = t[index][j];
            if (DBLeq(div, 0))return 0.0;
            t.swapLine(j, index);
            t.divLine(j, div);
            det *= div;
            for (int i = j + 1; i < row; ++i) {
                div = -t[i][j];
                t.addLine(i, j, div);
            }
        }
        return det;
    }

    /**
     * (i,j)での余因子
     * @param i
     * @param j
     */
    double MatDBL::cofactor(const int& i, const int& j)const {
        ASSERT(row == col, "Error : 正方行列ではありません");
        if (row == 1) {
            if ((i + j) & 1) return -(*this)[i][j];
            else return (*this)[i][j];
        }
        MatDBL tmp(row - 1, col - 1);
        for (int k = 0, index = 0; k < row; ++k) {
            if (k == i)continue;
            for (int m = 0; m < col; ++m) {
                if (m == j)continue;
                tmp.num[index++] = (*this)[k][m];
            }
        }

        if ((i + j) & 1) return -tmp.det();
        else return tmp.det();
    }

    /**
     * 余因子行列 (性質：Aの逆行列 * detA = Aの余因子行列)
     */
    MatDBL MatDBL::cofactorMatrix() const {
        ASSERT(row == col, "Error : 正方行列ではありません");
        MatDBL ans(row, col);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                ans[j][i] = cofactor(i, j);
        }
        return ans;
    }

    /**
     * ベクトルの内積
     * @param v
     * @return 分数
     */
    double MatDBL::innerProduct(const VecDBL& v) const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        MatDBL tmp = this->transpose().multiply(v);
        return tmp.num[0];
    }

    /**
     * 直積
     * @param v
     * @return 
     */
    MatDBL MatDBL::outerProduct(const VecDBL& v) const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        return this->multiply(v.transpose());
    }

    /**
     * 外積(クロス積)
     * @param v
     * @return 
     */
    VecDBL MatDBL::crossProduct(const VecDBL& v) const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        ASSERT(row == v.row, "Error : 演算不能");

        VecDBL ans(row);
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
    MatDBL MatDBL::wedgeProduct(const VecDBL& v) const {
        ASSERT(isVector() && v.isVector(), "Error : ベクトルではありません");
        return (this->outerProduct(v))-(v.outerProduct(*this));
    }

    /**
     * 逆行列
     * @return 
     */
    MatDBL MatDBL::inverse() const {
        ASSERT(row == col, "Error : 正方行列ではありません");
        MatDBL t = *this, e = createE(row);
        int index;
        double div;
        for (int j = 0; j < col; ++j) {
            index = t.selectPivot(j, j);
            div = t[index][j];
            ASSERT(!DBLeq(div, 0), "Error : 逆行列をもちません");
            t.swapLine(j, index);
            e.swapLine(j, index);
            t.divLine(j, div);
            e.divLine(j, div);

            for (int i = 0; i < row; ++i) {
                if (i == j)continue;
                div = -t[i][j];
                t.addLine(i, j, div);
                e.addLine(i, j, div);
            }
        }
        return e;
    }

    /**
     * A x = b (変数の数と方程式の数が合わない時は最小二乗解をかえす)
     * @param A 係数行列
     * @param b 右辺ベクトル
     * @return x 方程式の解
     */
    VecDBL MatDBL::solver(MatDBL A, VecDBL b) {
        ASSERT(A.row == b.row, "Error : 入力が正しくありません");
        if (A.row != A.col) {
            b = A.transpose() * b;
            A = A.transpose() * A;
        }

        int index;
        double div;
        for (int j = 0; j < A.col; ++j) {
            index = A.selectPivot(j, j);
            div = A[index][j];
            ASSERT(!DBLeq(div, 0), "Error : 逆行列をもちません");
            A.swapLine(j, index);
            b.swapLine(j, index);
            A.divLine(j, div);
            b.divLine(j, div);

            for (int i = 0; i < A.row; ++i) {
                if (i == j)continue;
                div = -A[i][j];
                A.addLine(i, j, div);
                b.addLine(i, j, div);
            }
        }
        return b;
    }

    /**
     * 最小二乗法 \n
     *  n \n
     * Σ(Ck * x^k) \n
     * k=0 \n
     * で近似する
     * @param filename ファイル名
     * @param length データの長さ
     * @param n n次近似
     * @return 多項式の係数ベクトル
     */
    VecDBL MatDBL::approximate(const char *filename, const int &length, const int &n) {
        std::ifstream file(filename);
        ASSERT(!file.fail(), "Error : ファイルがありません");

        double tmp, t;
        MatDBL A(length, n + 1);
        VecDBL b(length);

        for (int i = 0; i < length; ++i) {
            tmp = 1.0;
            ASSERT(readDouble(file, t), "Error : データが足りません");
            ASSERT(readDouble(file, b(i)), "Error : データが足りません");
            for (int j = 0; j < n + 1; ++j) {
                A[i][j] = tmp;
                tmp *= t;
            }
        }
        return MatDBL::solver(A, b);
    }

    MatDBL MatDBL::createE(const int& n) {
        MatDBL e(n, n);
        for (int i = 0; i < e.row; ++i)
            e[i][i] = 1.0;
        return e;
    }

    /**
     * 基本行列 n次単位行列のi行にj行のc倍を加えた行列
     * @param n
     * @param i
     * @param j
     * @param c
     * @return 
     */
    MatDBL MatDBL::addP(const int& n, const int& i, const int& j, const double& c) {
        MatDBL tmp(n, n);
        tmp[i][j] = c;
        return (createE(n) + tmp);
    }

    /**
     * 基本行列 n次単位行列のi行をc(c!=0)倍した行列
     * @param n
     * @param i
     * @param c
     * @return 
     */
    MatDBL MatDBL::multiplyP(const int& n, const int& i, const double& c) {
        MatDBL p = createE(n);
        p.mulLine(i, c);
        return p;
    }

    /**
     * 基本行列 n次単位行列のi行とj行を入れ替えた行列
     * @param n
     * @param i
     * @param j
     * @return 
     */
    MatDBL MatDBL::swapP(const int& n, const int& i, const int& j) {
        MatDBL p = createE(n);
        p.swapLine(i, j);
        return p;
    }

    std::ostream& operator<<(std::ostream& os, const MatDBL& m) {
        m.print();
        return os;
    }

}
