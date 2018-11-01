#include "BigInt.hpp"

using namespace std;
namespace mylib {

    const BigInt BigInt::ZERO;
    const BigInt BigInt::ONE(1);
    const BigInt BigInt::TWO(2);
    const BigInt BigInt::THREE(3);
    const BigInt BigInt::SIX(6);
    const BigInt BigInt::TEN(10);
    const BigInt BigInt::TEN2(100);
    const BigInt BigInt::TEN3(1000);

    BigInt BigInt::toBigInt(const LLONG &n) {
        return BigInt(n);
    }

    BigInt BigInt::operator ^(const int& n) const {
        return pow(n);
    }

    /**
     * コンストラクタ
     */
    BigInt::BigInt() {
        num = (int*) malloc(sizeof (int));
        ASSERT(num != NULL, "Error : メモリ確保失敗");
        *num = sign = 0;
        size = 1;
    }

    BigInt::~BigInt() {
        free(num);
    }

    /**
     * サイズ確保するコンストラクタ
     * @param size
     * @param tmp
     */
    BigInt::BigInt(const int &size, const bool &tmp) {
        this->size = size;
        num = (int*) calloc(sizeof (int), this->size);
        ASSERT(num != NULL, "Error : メモリ確保失敗");
        sign = 0;
    }

    BigInt::BigInt(std::string str) {
        string::size_type s;

        if ((s = str.find('.')) != string::npos)
            str = str.substr(0, s);

        switch (str[0]) {
            case '-':
                sign = -1;
                str = str.substr(1);
                break;
            case '+':
                sign = 1;
                str = str.substr(1);
                break;
            default:
                sign = 1;
                break;
        }

        int len = str.length();
        size = (int) ceil(len / 4.0);

        num = (int*) malloc(sizeof (int)*size);
        ASSERT(num != NULL, "Error : メモリ確保失敗");
        int i, j = size - 1;

        for (i = len - KETA; i > 0; i -= KETA)
            num[j--] = atoi(str.substr(i, KETA).c_str());
        num[j] = atoi(str.substr(0, KETA + i).c_str());

        if (absCompare(*this, ZERO) == 0)sign = 0;
    }

    /**
     * コンストラクタ
     * @param num BigIntにしたい整数
     */
    BigInt::BigInt(const LLONG &n) {
        num = (int*) malloc(sizeof (int));
        ASSERT(num != NULL, "Error : メモリ確保失敗");
        *num = sign = 0;
        size = 1;
        if (n == 0LL) return;
        LLONG t = n;
        num[0] = abs_f(t) % LIMIT;
        while (1) {
            t /= LIMIT;
            if (t == 0LL)break;
            resize(size + 1);
            memmove(&num[1], num, sizeof (int)*(size - 1));
            num[0] = abs_f(t) % LIMIT;
        }
        if (n < 0LL)sign = -1;
        else sign = 1;
    }

    BigInt::BigInt(const BigInt& n) {
        size = n.size;
        sign = n.sign;
        num = (int*) malloc(sizeof (int)*size);
        memmove(num, n.num, sizeof (int)*size);
    }

    /**
     * コンストラクタ
     * @param num int配列
     * @param size 配列の個数
     * @param sign 正:1,負:-1,零:0 (default :1)
     */
    BigInt::BigInt(const int* num, int size, const int& sign) {
        this->size = size;
        this->num = (int*) malloc(sizeof (int) * this->size);
        memmove(this->num, num, sizeof (int) * this->size);
        trim();
        setSign(sign);
    }

    /**
     * 配列の値を格納
     * @param num int配列
     * @param sign 正:1,負:-1,零:0
     * @param size 配列の個数
     */
    void BigInt::setValue(const int *num, const int& sign, int size) {
        resize(size);
        memmove(this->num, num, sizeof (int) * this->size);
        trim();
        setSign(sign);
    }

    /**
     * 配列のサイズ変更
     * @param size
     */
    void BigInt::resize(int size) {
        if (size == this->size)return;
        num = (int*) realloc(num, sizeof (int) * size);
        ASSERT(num != NULL, "Error : メモリ確保失敗");
        if (size > this->size)
            memset(num + this->size, 0, sizeof (int)*(size - this->size));
        this->size = size;
    }

    /**
     * 先頭にあるゼロを消去。その分メモリ解放
     */
    void BigInt::trim() {
        int i = getHeadIndex();
        if (i != 0) {
            size -= i;
            memmove(num, &num[i], size * sizeof (int));
            resize(size);
        }
    }

    /**
     * 符号をセット(基本的には、trim()を実行してから呼ぶ)
     * @param sign 正：１、負：-1、零：０、
     */
    void BigInt::setSign(int sign) {
        if (sign > 0)this->sign = 1;
        else if (sign < 0)this->sign = -1;
        else this->sign = 0;
        //trimされてないと、ここでおかしくなる
        if (num[0] == 0)this->sign = 0;
        else if (this->sign == 0)this->sign = 1;
    }

    /**
     * 配列の大きさを返す
     */
    int BigInt::getSize()const {
        return size;
    }

    /**
     * 符号を返す
     * @return 正:1,負:-1,零:0
     */
    int BigInt::getSign() const {
        return sign;
    }

    /**
     * i番目の要素を得る。iがサイズを超えていると、0を返す。
     * @param i
     * @return
     */
    int BigInt::getNum(const int& i) const {
        return ( (i >= 0 && i < size) ? num[i] : 0);
    }

    /**
     * 表示
     */
    void BigInt::print(std::ostream &os) const {
        using namespace std;

        if (sign < 0)os << "-";
        int *p = num;
        os << *p;
        for (++p; p != &num[size]; ++p)
            os << setw(KETA) << setfill('0') << *p;
    }

    /**
     * 足し算
     */
    BigInt BigInt::add(const BigInt &n)const {
        if (sign == 0) return n;
        if (n.sign == 0)return *this;

        BigInt ans((size > n.size) ? (size + 1) : (n.size + 1), true);
        if (!((sign > 0) ^(n.sign > 0))) {//同符号
            int carry = 0;
            for (int i = ans.size - 1, j = size - 1, k = n.size - 1; i >= 0; --i, --j, --k) {
                ans.num[i] = getNum(j) + n.getNum(k) + carry;
                (ans.num[i] < LIMIT) ? carry = 0 : (ans.num[i] -= LIMIT, carry = 1);
            }
            ans.trim();
            ans.setSign(sign);
        } else {
            int flag = absCompare(*this, n);
            int borrow = 0;
            switch (flag) {
                case 1:
                    for (int i = ans.size - 1, j = size - 1, k = n.size - 1; i >= 0; --i, --j, --k) {
                        ans.num[i] = getNum(j) - n.getNum(k) - borrow;
                        (ans.num[i] >= 0) ? borrow = 0 : (ans.num[i] += LIMIT, borrow = 1);
                    }
                    ans.trim();
                    if (sign < 0)ans.setSign(-1);
                    else ans.setSign(1);
                    break;
                case -1:
                    for (int i = ans.size - 1, j = size - 1, k = n.size - 1; i >= 0; --i, --j, --k) {
                        ans.num[i] = n.getNum(k) - getNum(j) - borrow;
                        (ans.num[i] >= 0) ? borrow = 0 : (ans.num[i] += LIMIT, borrow = 1);
                    }
                    ans.trim();
                    if (sign > 0)ans.setSign(-1);
                    else ans.setSign(1);
                    break;
                default:
                    return ZERO;
            }
        }
        return ans;
    }

    BigInt BigInt::subtract(const BigInt &n) const {
        return this->add(-n);
    }

    /**
     * 絶対値での大きさ比較 \n
     * |a|=|b|:0    \n
     * |a|＞|b|:1   \n
     * |a|＜|b|:-1  \n
     */
    int BigInt::absCompare(const BigInt &a, const BigInt &b) {
        if (a.size > b.size)return 1;
        if (a.size < b.size)return -1;

        for (int i = 0; i < a.size; ++i) {
            if (a.num[i] > b.num[i])return 1;
            else if (a.num[i] < b.num[i])return -1;
        }
        return 0;
    }

    /**
     * 先頭から探索し、初めて0でない数が出てきた位置のインデックスを返す
     * ZEROの場合はsize-1を返す
     */
    int BigInt::getHeadIndex() const {
        for (int *p = num; p != &num[size]; ++p)
            if (*p != 0)return p - num;
        return size - 1;
    }

    /**
     * 値が等しいかどうか返す
     */
    bool BigInt::equal(const BigInt &n) const {
        if (sign != n.sign || size != n.size) return false;
        for (int i = 0; i < size; ++i)
            if (num[i] != n.num[i])return false;
        return true;
    }

    /**
     * 比較 \n
     * a=b:0    \n
     * a＞b:1   \n
     * a＜b:-1  \n
     */
    int BigInt::compare(const BigInt &a, const BigInt &b) {
        int flag = absCompare(a, b);
        switch (flag) {
            case 1:
                if (a.sign < 0)return -1;
                else if (a.sign > 0)return 1;
                else return ((b.sign > 0) ? -1 : 1);
            case -1:
                if (b.sign < 0)return 1;
                else if (b.sign > 0)return -1;
                else return ((a.sign > 0) ? 1 : -1);
            default:
                if (a.sign < b.sign)return -1;
                else if (a.sign > b.sign)return 1;
                else return 0;
        }
    }

    /**
     * BigIntegerとint(大きさが9999まで)の掛け算
     */
    BigInt BigInt::mulInt(const int& n) const {
        int absn = abs_f(n);
        ASSERT(absn < LIMIT, "Error : 9999までにしてください");
        if (n == 0 || sign == 0)return ZERO;

        BigInt ans(size + 1, true);
        int carry = 0, tmp;
        for (int i = ans.size - 1, j = size - 1; i >= 0; --i, --j) {
            tmp = getNum(j) * absn + carry;
            ans.num[i] = tmp % LIMIT;
            carry = tmp / LIMIT;
        }
        ans.trim();
        //異符号
        if ((sign > 0) ^ (n > 0)) ans.setSign(-1);
        else ans.setSign(1);
        return ans;
    }

    /**
     * BigIntegerとint(大きさが9999まで)の割り算
     */
    BigInt BigInt::divInt(const int& n) const {
        int absn = abs_f(n);
        ASSERT(n != 0 && absn < LIMIT, "Error : ゼロで割れません");
        if (sign == 0 || (size == 1 && num[0] < absn))return ZERO;

        BigInt ans(size, true);
        int remainder = 0;
        for (int i = 0; i < size; ++i) {
            ans.num[i] = (num[i] + remainder) / absn;
            remainder = ((num[i] + remainder) % absn) * LIMIT;
        }
        ans.trim();
        //異符号
        if ((sign > 0) ^ (n > 0)) ans.setSign(-1);
        else ans.setSign(1);
        return ans;
    }

    /**
     * 指定サイズでの最大値を得る
     * @param size
     */
    BigInt BigInt::getMax(int size) {
        BigInt max(size, true);
        for (int *p = max.num; p != &max.num[size]; ++p)
            *p = LIMIT - 1;
        return max;
    }

    /**
     * 配列をk個だけ左へずらす
     */
    BigInt BigInt::shiftLeft(const int& k) const {
        if (k <= 0)return *this;
        BigInt ans(size + k, true);

        memmove(ans.num, num, size * sizeof (int));
        ans.trim();
        ans.setSign(sign);
        return ans;
    }

    /**
     * 配列をk個だけ右へずらす
     */
    BigInt BigInt::shiftRight(const int& k) const {
        if (k <= 0)return *this;
        if (k >= size) return ZERO;
        BigInt ans(size - k, true);

        memmove(ans.num, num, sizeof (int)*ans.size);
        ans.trim();
        ans.setSign(sign);
        return ans;
    }

    BigInt BigInt::multiply(const BigInt &n) const {
        if (sign == 0 || n.sign == 0)return ZERO;

        BigInt ans(size + n.size, true);
        int carry, tmp, i, j, k;
        for (i = size - 1; i >= 0; --i) {
            carry = 0;
            for (j = n.size - 1, k = ans.size - (size - i); j >= 0; --j, --k) {
                tmp = (ans.num[k] + n.num[j] * num[i] + carry);
                ans.num[k] = tmp % LIMIT;
                carry = tmp / LIMIT;
            }
            ans.num[k] = carry;
        }
        ans.trim();
        if ((sign > 0) ^ (n.sign > 0))ans.setSign(-1);
        else ans.setSign(1);
        return ans;
    }

    /**
     * 答えがintになる時のみ、使える。符号は無視。
     */
    int BigInt::divSub(const BigInt &n, BigInt &pro) const {
        if (absCompare(*this, n) < 0)return 0;

        int ans;
        bool flag = true;
        LLONG base = (LLONG) LIMIT;

        if (size == n.size) {
            switch (n.size) {
                case 1:
                    ans = (num[0] / n.num[0]);
                    break;
                case 2:
                    ans = (int) ((num[0] * base + num[1]) / (n.num[0] * base + n.num[1]));
                    break;
                case 3:
                    ans = (int) ((num[0] * base * base + num[1] * base + num[2]) / (n.num[0] * base * base + n.num[1] * base + n.num[2]));
                    break;
                case 4:
                    ans = (int) ((num[0] * base * base * base + num[1] * base * base + num[2] * base + num[3])
                            / (n.num[0] * base * base * base + n.num[1] * base * base + n.num[2] * base + n.num[3]));
                    break;
                default:
                    ans = (int) ((num[0] * base * base * base + num[1] * base * base + num[2] * base + num[3])
                            / (n.num[0] * base * base * base + n.num[1] * base * base + n.num[2] * base + n.num[3]));
                    flag = false;
                    break;
            }
        } else {
            switch (n.size) {
                case 1:
                    ans = (int) ((num[0] * base + num[1]) / n.num[0]);
                    break;
                case 2:
                    ans = (int) ((num[0] * base * base + num[1] * base + num[2]) / (n.num[0] * base + n.num[1]));
                    break;
                case 3:
                    ans = (int) ((num[0] * base * base * base + num[1] * base * base + num[2] * base + num[3])
                            / (n.num[0] * base * base + n.num[1] * base + n.num[2]));
                    break;
                default:
                    ans = (int) ((num[0] * base * base * base + num[1] * base * base + num[2] * base + num[3])
                            / (n.num[0] * base * base + n.num[1] * base + n.num[2]));
                    flag = false;
                    break;
            }
        }

        // pro = n * ans
        int carry = 0, tmp, i, j;
        pro.size = n.size + 1, *pro.num = 0;
        for (i = pro.size - 1, j = n.size - 1; i >= 0; --i, --j) {
            tmp = n.getNum(j) * ans + carry;
            pro.num[i] = tmp % LIMIT;
            carry = tmp / LIMIT;
        }
        if (*pro.num == 0) {
            --pro.size;
            memmove(pro.num, pro.num + 1, sizeof (int)*pro.size);
        }

        if (flag)return ans;
        while (absCompare(pro, *this) > 0) {
            --ans;
            // pro = n * ans
            *pro.num = 0;
            for (i = pro.size - 1, j = n.size - 1; i >= 0; --i, --j) {
                tmp = n.getNum(j) * ans + carry;
                pro.num[i] = tmp % LIMIT;
                carry = tmp / LIMIT;
            }
            if (*pro.num == 0) {
                --pro.size;
                memmove(pro.num, pro.num + 1, sizeof (int)*pro.size);
            }
        }
        return ans;
    }

    BigInt BigInt::divide(const BigInt &n) const {
        if (absCompare(*this, n) < 0)return ZERO; //分母のほうが大きい時
        if (n.size == 1)return divInt(*n.num * n.sign);

        BigInt part(n.size + 1, true), pro(part.size + 1, true);
        int ansSize = size - n.size + 1, *thisP = num + n.size, borrow, i, j;

        memmove(part.num, num, sizeof (int)*n.size);
        part.size = n.size;

        if (absCompare(part, n) < 0) {
            part.num[part.size++] = *thisP++;
            --ansSize;
        }
        BigInt ans(ansSize, true);
        int *ansP = ans.num;

        while (true) {
            *ansP = part.divSub(n, pro);

            if (*ansP != 0) {
                //part = part - tmp 
                borrow = 0;
                for (i = part.size - 1, j = pro.size - 1; i >= 0; --i, --j) {
                    part.num[i] -= (pro.getNum(j) + borrow);
                    (part.num[i] >= 0) ? borrow = 0 : (part.num[i] += LIMIT, borrow = 1);
                }
                i = part.getHeadIndex();
                if (i != 0) {
                    part.size -= i;
                    memmove(part.num, part.num + i, sizeof (int)*part.size);
                }
            }
            ++ansP;
            if (thisP == num + size)break;
            part.num[part.size++] = *thisP++;
        }

        if ((sign > 0) ^ (n.sign > 0)) ans.setSign(-1);
        else ans.setSign(1);

        return ans;
    }

    /**
     * インクリメント
     */
    void BigInt::increment() {
        if (sign < 0) {
            int borrow = 1;
            for (int i = size - 1; i >= 0; --i) {
                num[i] -= borrow;
                if (num[i] >= 0) {
                    borrow = 0;
                    break;
                } else {
                    num[i] += LIMIT;
                    borrow = 1;
                }
            }
            trim();
            //-1から0になった時、符号を変える
            setSign(-1);
        } else {
            int carry = 1;
            for (int i = size - 1; i >= 0; --i) {
                num[i] += carry;
                if (num[i] < LIMIT) {
                    carry = 0;
                    break;
                } else {
                    num[i] -= LIMIT;
                    carry = 1;
                    if (i == 0) {
                        resize(size + 1);
                        memmove(&num[1], num, sizeof (int)*(size - 1));
                        num[0] = carry;
                    }
                }
            }
            sign = 1;
        }
    }

    /**
     * デクリメント
     */
    void BigInt::decrement() {
        if (sign > 0) {
            int borrow = 1;
            for (int i = size - 1; i >= 0; --i) {
                num[i] -= borrow;
                if (num[i] >= 0) {
                    borrow = 0;
                    break;
                } else {
                    num[i] += LIMIT;
                    borrow = 1;
                }
            }
            trim();
            //1から0になった時、符号を変える
            setSign(1);
        } else {
            int carry = 1;
            for (int i = size - 1; i >= 0; --i) {
                num[i] += carry;
                if (num[i] < LIMIT) {
                    carry = 0;
                    break;
                } else {
                    num[i] -= LIMIT;
                    carry = 1;
                    if (i == 0) {
                        resize(size + 1);
                        memmove(&num[1], num, sizeof (int)*(size - 1));
                        num[0] = carry;
                    }
                }
            }
            sign = -1;
        }
    }

    /**
     * mod計算
     * @param n
     * @return 余り
     */
    BigInt BigInt::mod(const BigInt &n) const {
        if (absCompare(*this, ZERO) == 0)return ZERO;
        if (absCompare(*this, n) < 0)return *this; //分母のほうが大きい時

        BigInt ans = n.abs();

        ans = subtract(divide(ans).multiply(ans));

        if (absCompare(ans, ZERO) != 0) ans.setSign(sign);
        return ans;
    }

    BigInt BigInt::abs() const {
        return (sign < 0) ? -(*this) : (*this);
    }

    BigInt BigInt::operator+(const BigInt &n) const {
        return this->add(n);
    }

    BigInt BigInt::operator-(const BigInt &n) const {
        return this->subtract(n);
    }

    BigInt BigInt::operator*(const BigInt &n)const {
        return this->multiply(n);
    }

    BigInt BigInt::operator/(const BigInt &n) const {
        return this->divide(n);
    }

    BigInt BigInt::operator%(const BigInt &n)const {
        return this->mod(n);
    }

    /**
     * 前置インクリメント
     */
    BigInt BigInt::operator++() {
        increment();
        return *this;
    }

    /**
     * 後置インクリメント
     */
    BigInt BigInt::operator++(int n) {
        BigInt ans = *this;
        increment();
        return ans;
    }

    /**
     * 前置デクリメント
     */
    BigInt BigInt::operator--() {
        decrement();
        return *this;
    }

    /**
     * 後置デクリメント
     */
    BigInt BigInt::operator--(int n) {
        BigInt ans = *this;
        decrement();
        return ans;
    }

    BigInt &BigInt::operator+=(const BigInt &n) {
        *this = this->add(n);
        return *this;
    }

    BigInt &BigInt::operator-=(const BigInt &n) {
        *this = this->subtract(n);
        return *this;
    }

    BigInt &BigInt::operator*=(const BigInt &n) {
        *this = this->multiply(n);
        return *this;
    }

    BigInt &BigInt::operator/=(const BigInt &n) {
        *this = this->divide(n);
        return *this;
    }

    BigInt &BigInt::operator%=(const BigInt &n) {
        *this = this->mod(n);
        return *this;
    }

    BigInt BigInt::operator-()const {
        BigInt ans = *this;
        ans.setSign(-ans.sign);
        return ans;
    }

    BigInt BigInt::pow(const int& k) const {
        if (k < 0)return ZERO;
        BigInt ans = ONE, tmp = *this;
        int exp = k;
        if (exp & 1)ans = tmp;
        while (exp != 0) {
            tmp *= tmp;
            if ((exp >>= 1)&1)ans *= tmp;
        }
        return ans;
    }

    /**
     * @param k 指数( >0 )
     * @param m 法 ( >0 )
     * @return (*this)^k mod m
     */
    BigInt BigInt::powMod(const LLONG &k, const LLONG &m) const {
        if (k < 0)return ZERO;
        BigInt n(m);
        BigInt ans = ONE, tmp = this->mod(n);
        LLONG exp = k;
        if (exp & 1)ans = tmp;
        while (exp != 0LL) {
            tmp = (tmp * tmp).mod(n);
            if ((exp >>= 1)&1)ans = (ans * tmp).mod(n);
        }
        return ans;
    }

    double BigInt::toDouble() const {
        string str = toString(*this);
        return atof(str.c_str());
    }

    int BigInt::toInt() const {
        string str = toString(*this);
        return atoi(str.c_str());
    }

    long BigInt::toLong() const {
        string str = toString(*this);
        return atol(str.c_str());
    }

    LLONG BigInt::toLLong() const {
        string str = toString(*this);
        return atoll(str.c_str());
    }

    /**
     * n!
     * @param n 9999まで
     */
    BigInt BigInt::fact(const int& n) {
        if (n <= 1)return ONE;
        ASSERT(n < LIMIT, "Error : 9999までにしてください");

        BigInt ans = ONE;
        for (int i = 2; i <= n; ++i)
            ans = ans.mulInt(i);

        return ans;
    }

    /**
     * 何桁の数か返す
     */
    int BigInt::getKeta() const {
        //0の場合
        if (num[0] == 0)return 1;

        int keta = (size - 1) * KETA;
        for (int i = 1; i < LIMIT; i *= 10) {
            if (num[0] / i == 0) break;
            ++keta;
        }
        return keta;
    }

    std::ostream& operator<<(std::ostream &os, const BigInt& n) {
        n.print(os);
        return os;
    }

    bool BigInt::operator==(const BigInt &n) const {
        return equal(n);
    }

    bool BigInt::operator<(const BigInt &n)const {
        return (compare(*this, n) < 0);
    }

    bool BigInt::operator>(const BigInt &n) const {
        return (compare(*this, n) > 0);
    }

    bool BigInt::operator<=(const BigInt &n)const {
        return (compare(*this, n) <= 0);
    }

    bool BigInt::operator>=(const BigInt &n) const {
        return (BigInt::compare(*this, n) >= 0);
    }

    bool BigInt::operator!=(const BigInt& n) const {
        return !equal(n);
    }

    BigInt &BigInt::operator=(const BigInt& n) {
        resize(n.size);
        sign = n.sign;
        memmove(num, n.num, sizeof (int)*size);
        return *this;
    }

    BigInt &BigInt::operator=(const LLONG& n) {
        *this = BigInt(n);
        return *this;
    }

    bool BigInt::operator!=(const LLONG& n)const {
        return !equal(BigInt(n));
    }

    bool BigInt::operator==(const LLONG& n) const {
        return equal(BigInt(n));
    }

    bool BigInt::operator<(const LLONG& n) const {
        return compare(*this, BigInt(n)) < 0;
    }

    bool BigInt::operator<=(const LLONG& n)const {
        return compare(*this, BigInt(n)) <= 0;
    }

    bool BigInt::operator>(const LLONG& n)const {
        return compare(*this, BigInt(n)) > 0;
    }

    bool BigInt::operator>=(const LLONG& n)const {
        return compare(*this, BigInt(n)) >= 0;
    }

    BigInt BigInt::operator+(const LLONG& n) const {
        return add(BigInt(n));
    }

    BigInt BigInt::operator-(const LLONG& n) const {
        return subtract(BigInt(n));
    }

    BigInt BigInt::operator*(const LLONG& n) const {
        return multiply(BigInt(n));
    }

    BigInt BigInt::operator/(const LLONG& n) const {
        return divide(BigInt(n));
    }

    BigInt BigInt::operator%(const LLONG& n) const {
        return mod(BigInt(n));
    }

    BigInt operator+(const LLONG &n, const BigInt &b) {
        return BigInt(n).add(b);
    }

    BigInt operator-(const LLONG &n, const BigInt &b) {
        return BigInt(n).subtract(b);
    }

    BigInt operator*(const LLONG &n, const BigInt &b) {
        return BigInt(n).multiply(b);
    }

    BigInt operator/(const LLONG &n, const BigInt &b) {
        return BigInt(n).divide(b);
    }

    BigInt operator%(const LLONG &n, const BigInt &b) {
        return BigInt(n).mod(b);
    }

    BigInt &BigInt::operator+=(const LLONG& n) {
        *this = add(BigInt(n));
        return *this;
    }

    BigInt &BigInt::operator-=(const LLONG& n) {
        *this = subtract(BigInt(n));
        return *this;
    }

    BigInt &BigInt::operator*=(const LLONG& n) {
        *this = multiply(BigInt(n));
        return *this;
    }

    BigInt &BigInt::operator/=(const LLONG& n) {
        *this = divide(BigInt(n));
        return *this;
    }

    BigInt &BigInt::operator%=(const LLONG& n) {
        *this = mod(BigInt(n));
        return *this;
    }

}

