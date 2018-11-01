#include "BigDec.hpp"

using namespace std;
namespace mylib {

    const int BigDec::DEFAULT_ACCURACY = 30;
    const BigDec BigDec::ZERO(0);
    const BigDec BigDec::ONE(1);
    const BigDec BigDec::TWO(2);
    const BigDec BigDec::THREE(3);
    const BigDec BigDec::FOUR(4);
    const BigDec BigDec::HALF("0.5");
    const BigDec BigDec::PI("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067");
    const BigDec BigDec::E("2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427");
    const BigDec BigDec::LN2("0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687");
    const BigDec BigDec::PI2 = PI * 2;

    std::ostream &operator<<(std::ostream &os, const BigDec &d) {
        d.print(false, os);
        return os;
    }

    int BigDec::getSign() const {
        return bigint.getSign();
    }

    void BigDec::print(bool exp, std::ostream& os) const {
        if (exp) {
            os << bigint << 'E' << scale;
        } else {
            if (bigint.getSign() < 0)os << '-';

            int keta = bigint.getKeta(), point = -1, size = bigint.getSize();
            if (scale < 0) {
                if (-scale >= keta) {
                    os << "0.";
                    for (int i = -scale - keta; i > 0; --i)os << '0';
                } else {
                    point = (BigInt::KETA * size + scale) / BigInt::KETA;
                }
            }
            for (int i = 0; i < bigint.getSize(); ++i) {
                if (point == i) {
                    bool flag = false;
                    int tmp;
                    for (int j = 0; j < BigInt::KETA; ++j) {
                        if (size * BigInt::KETA + scale == BigInt::KETA * i + j)os << '.';
                        tmp = getNumberI(bigint.getNum(i), 3 - j);
                        if (i != 0 || tmp != 0)flag = true;
                        if (flag) os << tmp;
                    }
                } else if (i == 0) {
                    os << bigint.getNum(i);
                } else {
                    os << setw(BigInt::KETA) << setfill('0') << bigint.getNum(i);
                }
            }
            if (scale > 0)
                for (int i = 0; i < scale; ++i) os << '0';
        }
    }

    BigDec::BigDec() {
        scale = 0;
    }

    BigDec::BigDec(const LLONG &n) {
        scale = 0;
        bigint = BigInt::toBigInt(n);
    }

    BigDec::BigDec(std::string str) {
        int len = str.length(), i = len - 1;
        while (i >= 0 && str[i] != '.')--i;

        if (i < 0) {
            scale = 0;
        } else {
            scale = -(len - i - 1);
            str = str.substr(0, i) + str.substr(i + 1);
        }
        bigint = BigInt(str);
    }

    /**
     * 
     * @param bigint
     * @param scale (default=0)
     */
    BigDec::BigDec(const BigInt& bigint, const int& scale) {
        this->bigint = bigint;
        this->scale = scale;
    }

    BigDec BigDec::operator+(const BigDec& d) const {
        BigDec ans;
        if (scale < d.scale) {
            ans = d.changeScale(scale);
            ans.bigint = ans.bigint + bigint;
        } else {
            ans = changeScale(d.scale);
            ans.bigint = ans.bigint + d.bigint;
        }
        return ans;
    }

    BigDec BigDec::operator-(const BigDec& d) const {
        BigDec tmp(-d.bigint, d.scale);
        return (*this+tmp);
    }

    BigDec BigDec::operator*(const BigDec& d) const {
        return BigDec(bigint * d.bigint, scale + d.scale);
    }

    BigDec BigDec::operator/(const BigDec& d) const {
        return divide(d);
    }

    BigDec BigDec::operator%(const BigDec& d) const {
        if (*this == d)return ZERO;
        if (abs() < d.abs())return *this;
        BigDec ans;
        if (scale < d.scale) {
            ans = d.changeScale(scale).abs();
            ans = subtract(divide(ans, 0).multiply(ans));
        } else {
            ans = changeScale(d.scale).abs();
            ans = ans.subtract(ans.divide(d.abs(), 0).multiply(d.abs()));
        }
        if (ans.bigint != BigInt::ZERO)ans.bigint.setSign(bigint.getSign());
        return ans;
    }

    BigDec BigDec::operator ^(const int& n) const {
        return power_f(*this, n);
    }

    BigDec& BigDec::operator+=(const BigDec& d) {
        *this = *this+d;
        return *this;
    }

    BigDec& BigDec::operator-=(const BigDec& d) {
        *this = *this-d;
        return *this;
    }

    BigDec& BigDec::operator*=(const BigDec& d) {
        *this = *this*d;
        return *this;
    }

    BigDec& BigDec::operator/=(const BigDec& d) {
        *this = *this / d;
        return *this;
    }

    BigDec& BigDec::operator%=(const BigDec& d) {
        *this = *this % d;
        return *this;
    }

    BigDec& BigDec::operator+=(const BigInt& n) {
        *this = *this +BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator-=(const BigInt& n) {
        *this = *this -BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator*=(const BigInt& n) {
        *this = *this *BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator/=(const BigInt& n) {
        *this = *this / BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator%=(const BigInt& n) {
        *this = *this % BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator+=(const LLONG& n) {
        *this = *this % BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator-=(const LLONG& n) {
        *this = *this % BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator*=(const LLONG& n) {
        *this = *this % BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator/=(const LLONG& n) {
        *this = *this % BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator%=(const LLONG& n) {
        *this = *this % BigDec(n);
        return *this;
    }

    BigDec BigDec::add(const BigDec& d) const {
        return *this+d;
    }

    BigDec BigDec::subtract(const BigDec& d) const {
        return *this-d;
    }

    BigDec BigDec::multiply(const BigDec& d) const {
        return *this*d;
    }

    /**
     * 割り算
     * @param d 
     * @param accu 小数点以下 accu 以上の精度(default=30)
     * @return 
     */
    BigDec BigDec::divide(const BigDec& d, const int &accuracy) const {
        int i = (int) ceil((double) (accuracy + scale - d.scale) / BigInt::KETA);
        if (i > 0)
            return BigDec(bigint.shiftLeft(i) / d.bigint, -i * BigInt::KETA + scale - d.scale);
        else
            return BigDec(bigint.shiftRight(-i) / d.bigint, -i * BigInt::KETA + scale - d.scale);
    }

    /**
     * 割り算
     * @param d 
     * @param accu 小数点以下 accu 以上の精度(default=30)
     * @return 
     */
    BigDec BigDec::divide(const BigInt& n, const int &accuracy) const {
        return divide(BigDec(n), accuracy);
    }

    /**
     * 小さいスケールに変換
     * @param newScale
     * @return 
     */
    BigDec BigDec::changeScale(const int& newScale) const {
        BigDec ans;
        int i;
        if (scale < newScale) {
            return BigDec();
        } else {
            ans = *this;
            i = scale - newScale;
        }
        ans.bigint = ans.bigint.shiftLeft(i / BigInt::KETA);
        switch (i % BigInt::KETA) {
            case 1:
                ans.bigint = ans.bigint.multiply(BigInt::TEN);
                break;
            case 2:
                ans.bigint = ans.bigint.multiply(BigInt::TEN2);
                break;
            case 3:
                ans.bigint = ans.bigint.multiply(BigInt::TEN3);
                break;
        }
        ans.scale = newScale;
        return ans;
    }

    BigDec BigDec::abs() const {
        return (bigint < 0) ? (- * this) : (*this);
    }

    BigDec BigDec::inverse(const int &accuracy) const {
        return ONE.divide(*this, accuracy);
    }

    /**
     * accuracy程度の精度に丸める(切り捨て)
     * @param accuracy
     * @return 
     */
    BigDec BigDec::round(const int& accuracy) const {
        return this->divide(BigDec::ONE, accuracy);
    }

    double BigDec::toDouble() const {
        string str = toString(*this);
        return atof(str.c_str());
    }

    int BigDec::toInt() const {
        string str = toString(*this);
        return atoi(str.c_str());
    }

    long BigDec::toLong() const {
        string str = toString(*this);
        return atol(str.c_str());
    }

    LLONG BigDec::toLLong() const {
        string str = toString(*this);
        return atoll(str.c_str());
    }

    BigInt BigDec::toBigInt() const {
        string str = toString(*this);
        return BigInt(str);
    }

    BigDec BigDec::exp(const BigDec& x, const int &accuracy) {
        int flag = x.getSign();
        BigDec _x;

        switch (flag) {
            case 1:
                _x = x;
                break;
            case -1:
                _x = -x;
                break;
            default:
                return ONE;
        }

        BigDec ans = ONE, add = _x, limit(BigInt::ONE, -accuracy);
        BigInt n = BigInt::ONE;

        while (add.abs() >= limit) {
            ans = ans + add;
            ++n;
            add = (add * _x).divide(n, accuracy + 2);
        }

        if (flag < 0) ans = ONE.divide(ans, accuracy);

        return ans.round(accuracy);
    }

    BigDec BigDec::log(const BigDec& x, const int& accuracy) {
        ASSERT(x.getSign() > 0, "Error : logの真数は正にしてください");
        BigDec _x = x, ans;
        LLONG k = 0LL;
        int flag = (x - BigDec::ONE).getSign();
        switch (flag) {
            case 1:
                while (_x >= TWO)
                    _x = _x * HALF, ++k;
                break;
            case -1:
                while (_x < ONE)
                    _x = _x * TWO, --k;
                break;
            default:
                return ONE;
        }

        ans = LN2 * BigDec(k);

        _x = (_x - ONE).divide(_x + ONE, accuracy + 2);
        BigInt n = BigInt::THREE;
        BigDec tmp = _x, xx = _x*_x, pow = xx*_x, add = pow.divide(n, accuracy + 2), limit(BigInt::ONE, -accuracy);

        while (add >= limit) {
            tmp += add;
            pow *= xx;
            ++n;
            add = pow.divide(++n, accuracy + 2);
        }
        ans += tmp*TWO;
        return ans.round(accuracy);
    }

    BigDec BigDec::cos(const BigDec& x, const int& accuracy) {
        BigInt n = BigInt::TWO;
        BigDec _x = x % PI2, ans = ONE, xx = -(_x * _x), add = xx*HALF, limit(BigInt::ONE, -accuracy);
        while (add.abs() >= limit) {
            ans += add;
            add = (add * xx).divide((++n) * (++n), accuracy + 2);
        }
        return ans.round(accuracy);
    }

    BigDec BigDec::sin(const BigDec& x, const int& accuracy) {
        BigInt n = BigInt::THREE;
        BigDec _x = x % PI2, ans = _x, xx = -(_x * _x), add = (xx * _x).divide(BigInt::SIX, accuracy + 2)
                , limit(BigInt::ONE, -accuracy);
        while (add.abs() >= limit) {
            ans += add;
            add = (add * xx).divide((++n) * (++n), accuracy + 2);
        }
        return ans.round(accuracy);
    }

    BigDec BigDec::tan(const BigDec& x, const int& accuracy) {
        return sin(x, accuracy + 2).divide(cos(x, accuracy + 2), accuracy + 2).round(accuracy);
    }

    BigDec BigDec::sinh(const BigDec& x, const int& accuracy) {
        if (x.getSign() == 0) return ZERO;

        BigInt n = BigInt::THREE;
        BigDec ans = x, xx = x*x, add = (xx * x).divide(BigInt::SIX, accuracy + 2), limit(BigInt::ONE, -accuracy);
        while (add.abs() >= limit) {
            ans = ans.add(add);
            add = (add * xx).divide((++n)*(++n), accuracy + 2);
        }
        return ans.round(accuracy);
    }

    BigDec BigDec::cosh(const BigDec& x, const int& accuracy) {
        if (x.getSign() == 0) return ONE;

        BigInt n = BigInt::TWO;
        BigDec ans = ONE, xx = x*x, add = xx *HALF, limit(BigInt::ONE, -accuracy);
        while (add.abs() >= limit) {
            ans = ans.add(add);
            add = (add * xx).divide((++n)*(++n), accuracy + 2);
        }
        return ans.round(accuracy);
    }

    BigDec BigDec::tanh(const BigDec& x, const int& accuracy) {
        return sinh(x, accuracy + 2).divide(cosh(x, accuracy + 2), accuracy + 2).round(accuracy);
    }

    BigDec BigDec::asin(const BigDec& x, const int& accuracy) {
        int flag = (x - ONE).getSign(), flag2 = (x + ONE).getSign();

        if (flag == 0)
            return PI * HALF;
        else if (flag2 == 0)
            return -PI * HALF;
        else
            ASSERT(flag > 0 || flag2 < 0, "Error : asinの定義域は[-1,1]");

        BigInt n = BigInt::TWO;
        BigDec ans = x, xx = x*x, pow = xx * x*HALF,
                add = pow.divide(THREE, accuracy + 2), limit(BigInt::ONE, -accuracy);
        while (add.abs() >= limit) {
            ans += add;
            ++n, ++n;
            pow *= xx * BigDec(n - BigInt::ONE).divide(n, accuracy + 2);
            add = pow.divide(n + BigInt::ONE, accuracy + 2);
        }
        return ans.round(accuracy);

    }

    BigDec BigDec::acos(const BigDec& x, const int& accuracy) {
        int flag = (x - ONE).getSign(), flag2 = (x + ONE).getSign();

        if (flag == 0)
            return ZERO;
        else if (flag2 == 0)
            return PI;
        else
            ASSERT(flag > 0 || flag2 < 0, "Error : asinの定義域は[-1,1]");

        return (PI * HALF - asin(x, accuracy)).round(accuracy);
    }

    BigDec BigDec::atan(const BigDec& x, const int& accuracy) {
        int flag = (x - ONE).getSign(), flag2 = (x + ONE).getSign();

        if (flag == 0) return PI.divide(FOUR, accuracy + 2);
        else if (flag2 == 0) return -PI.divide(FOUR, accuracy + 2);

        BigInt n = BigInt::THREE;
        BigDec ans, xx, add, pow, _x, limit(BigInt::ONE, -accuracy);
        if (flag < 0 && flag2 > 0) {//|x|<1
            ans = x;
            xx = -x*x;
            pow = xx*x;
            add = pow.divide(n, accuracy + 2);
        } else {//|x|>1
            _x = ONE.divide(x, accuracy + 2);
            ans = (x > ZERO) ? PI * HALF - _x : -PI * HALF - _x;
            xx = -_x*_x;

            pow = -xx*_x;
            add = pow.divide(n, accuracy + 2);
        }
        while (add.abs() >= limit) {
            ans += add;
            pow *= xx;
            ++n;
            add = pow.divide(++n, accuracy + 2);
        }
        return ans.round(accuracy);
    }

    BigDec BigDec::pow(const BigDec& x, const BigDec& a, const int& accuracy) {
        ASSERT(x.getSign() > 0, "Error : powの底は正にしてください");
        return exp(a * log(x, accuracy + 2), accuracy);
    }

    BigDec BigDec::sqrt(const BigDec& x, const int& accuracy) {
        if (x.getSign() == 0) return ZERO;
        ASSERT(x.getSign() > 0, "Error : ルートの中は非負にしてください");
        //開平方
        string str = toString(x), ans = "";
        string::size_type index;
        bool firstOne; //先頭1つ
        int integer;
        BigInt temp, tmp, part;

        if ((index = str.find('.')) != string::npos) {
            firstOne = (index & 1);
            int i = str.length() - index - 1;
            if (i & 1)
                ++i, str += "0";

            for (i >>= 1; i < accuracy; ++i)
                str += "00";
        } else {
            firstOne = (str.length() & 1);
            str += ".";
            for (int i = 0; i < accuracy; ++i)
                str += "00";
        }
        index = 0;
        if (firstOne) {
            integer = str[index++] - '0';
            int i;
            for (i = 3; i >= 0; --i)
                if (integer >= i * i)break;
            ans += toString(i);
            part = BigInt(integer - i * i);
            temp = BigInt(i + i);
        }

        while (str[index] != '\0') {
            if (str[index] == '.') {
                ans += ".";
                ++index;
                continue;
            }

            temp *= BigInt::TEN;
            part *= BigInt::TEN2;
            integer = 10 * (str[index++] - '0');
            integer += (str[index++] - '0');
            part += integer;

            for (int i = 9; i >= 0; --i) {
                if (part >= (tmp = temp.add(i).mulInt(i))) {
                    part -= tmp;
                    temp += (i << 1); //temp += 2 * i;
                    ans += toString(i);
                    break;
                }
            }
        }
        return BigDec(ans);
    }

    BigDec BigDec::asinh(const BigDec& x, const int& accuracy) {
        return log(sqrt(x * x + ONE, accuracy + 2) + x, accuracy);
    }

    BigDec BigDec::acosh(const BigDec& x, const int& accuracy) {
        ASSERT(x >= ONE, "Error : acoshの定義域はx>=1");
        return log(sqrt(x * x - ONE, accuracy + 2) + x, accuracy);
    }

    BigDec BigDec::atanh(const BigDec& x, const int& accuracy) {
        ASSERT(x.abs() < ONE, "Error : atanhの定義域は|x|<1");
        return log((x + ONE).divide(ONE - x, accuracy + 2), accuracy + 2) * HALF;
    }

    BigDec BigDec::operator+(const BigInt& n) const {
        return *this+BigDec(n);
    }

    BigDec BigDec::operator-(const BigInt& n) const {
        return *this-BigDec(n);
    }

    BigDec BigDec::operator*(const BigInt& n) const {
        return *this*BigDec(n);
    }

    BigDec BigDec::operator/(const BigInt& n) const {
        return *this / BigDec(n);
    }

    BigDec BigDec::operator%(const BigInt& n) const {
        return *this % BigDec(n);
    }

    BigDec BigDec::operator+(const LLONG& n) const {
        return *this +BigDec(n);
    }

    BigDec BigDec::operator-(const LLONG& n) const {
        return *this -BigDec(n);
    }

    BigDec BigDec::operator*(const LLONG& n) const {
        return *this *BigDec(n);
    }

    BigDec BigDec::operator/(const LLONG& n) const {
        return *this / BigDec(n);
    }

    BigDec BigDec::operator%(const LLONG& n) const {
        return *this % BigDec(n);
    }

    BigDec operator+(const BigInt& n, const BigDec& d) {
        return BigDec(n) + d;
    }

    BigDec operator-(const BigInt& n, const BigDec& d) {
        return BigDec(n) - d;
    }

    BigDec operator*(const BigInt& n, const BigDec& d) {
        return BigDec(n) * d;
    }

    BigDec operator/(const BigInt& n, const BigDec& d) {
        return BigDec(n) / d;
    }

    BigDec operator%(const BigInt& n, const BigDec& d) {
        return BigDec(n) % d;
    }

    BigDec operator+(const LLONG& n, const BigDec& d) {
        return BigDec(n) + d;
    }

    BigDec operator-(const LLONG& n, const BigDec& d) {
        return BigDec(n) - d;
    }

    BigDec operator*(const LLONG& n, const BigDec& d) {
        return BigDec(n) * d;
    }

    BigDec operator/(const LLONG& n, const BigDec& d) {
        return BigDec(n) / d;
    }

    BigDec operator%(const LLONG& n, const BigDec& d) {
        return BigDec(n) % d;
    }

    bool operator<(const BigInt& n, const BigDec& d) {
        return BigDec(n) < d;
    }

    bool operator>(const BigInt& n, const BigDec& d) {
        return BigDec(n) > d;
    }

    bool operator<=(const BigInt& n, const BigDec& d) {
        return BigDec(n) <= d;
    }

    bool operator>=(const BigInt& n, const BigDec& d) {
        return BigDec(n) >= d;
    }

    bool operator==(const BigInt& n, const BigDec& d) {
        return BigDec(n) == d;
    }

    bool operator!=(const BigInt& n, const BigDec& d) {
        return BigDec(n) != d;
    }

    bool operator<(const LLONG& n, const BigDec& d) {
        return BigDec(n) < d;
    }

    bool operator>(const LLONG& n, const BigDec& d) {
        return BigDec(n) > d;
    }

    bool operator<=(const LLONG& n, const BigDec& d) {
        return BigDec(n) <= d;
    }

    bool operator>=(const LLONG& n, const BigDec& d) {
        return BigDec(n) >= d;
    }

    bool operator==(const LLONG& n, const BigDec& d) {
        return BigDec(n) == d;
    }

    bool operator!=(const LLONG& n, const BigDec& d) {
        return BigDec(n) != d;
    }

    bool BigDec::operator<(const BigDec& d) const {
        BigDec tmp;
        if (scale < d.scale) {
            tmp = d.changeScale(scale);
            return BigInt::compare(bigint, tmp.bigint) < 0;
        } else {
            tmp = changeScale(d.scale);
            return BigInt::compare(tmp.bigint, d.bigint) < 0;
        }
    }

    bool BigDec::operator>(const BigDec& d) const {
        BigDec tmp;
        if (scale < d.scale) {
            tmp = d.changeScale(scale);
            return BigInt::compare(bigint, tmp.bigint) > 0;
        } else {
            tmp = changeScale(d.scale);
            return BigInt::compare(tmp.bigint, d.bigint) > 0;
        }
    }

    bool BigDec::operator<=(const BigDec& d) const {
        BigDec tmp;
        if (scale < d.scale) {
            tmp = d.changeScale(scale);
            return BigInt::compare(bigint, tmp.bigint) <= 0;
        } else {
            tmp = changeScale(d.scale);
            return BigInt::compare(tmp.bigint, d.bigint) <= 0;
        }
    }

    bool BigDec::operator>=(const BigDec& d) const {
        BigDec tmp;
        if (scale < d.scale) {
            tmp = d.changeScale(scale);
            return BigInt::compare(bigint, tmp.bigint) >= 0;
        } else {
            tmp = changeScale(d.scale);
            return BigInt::compare(tmp.bigint, d.bigint) >= 0;
        }
    }

    bool BigDec::operator==(const BigDec& d) const {
        BigDec tmp;
        if (scale < d.scale) {
            tmp = d.changeScale(scale);
            return BigInt::compare(bigint, tmp.bigint) == 0;
        } else {
            tmp = changeScale(d.scale);
            return BigInt::compare(tmp.bigint, d.bigint) == 0;
        }
    }

    bool BigDec::operator!=(const BigDec& d) const {
        return !(*this == d);
    }

    bool BigDec::operator<(const BigInt& n) const {
        return (*this < BigDec(n));
    }

    bool BigDec::operator>(const BigInt& n) const {
        return (*this > BigDec(n));
    }

    bool BigDec::operator<=(const BigInt& n) const {
        return (*this <= BigDec(n));
    }

    bool BigDec::operator>=(const BigInt& n) const {
        return (*this >= BigDec(n));
    }

    bool BigDec::operator==(const BigInt& n) const {
        return (*this == BigDec(n));
    }

    bool BigDec::operator!=(const BigInt& n) const {
        return (*this != BigDec(n));
    }

    bool BigDec::operator<(const LLONG& d) const {
        return (*this < BigDec(d));
    }

    bool BigDec::operator>(const LLONG& d) const {
        return (*this > BigDec(d));
    }

    bool BigDec::operator<=(const LLONG& d) const {
        return (*this <= BigDec(d));
    }

    bool BigDec::operator>=(const LLONG& d) const {
        return (*this >= BigDec(d));
    }

    bool BigDec::operator==(const LLONG& d) const {
        return (*this == BigDec(d));
    }

    bool BigDec::operator!=(const LLONG& d) const {
        return (*this != BigDec(d));
    }

    BigDec BigDec::operator-() const {
        return BigDec(-bigint, scale);
    }

    BigDec BigDec::operator+() const {
        return *this;
    }

    BigDec& BigDec::operator=(const BigInt& n) {
        *this = BigDec(n);
        return *this;
    }

    BigDec& BigDec::operator=(const LLONG& n) {
        *this = BigDec(n);
        return *this;
    }

    BigDec BigDec::operator++() {
        if (scale == 0)++bigint;
        else *this = *this+BigDec::ONE;
        return *this;
    }

    BigDec BigDec::operator++(int n) {
        BigDec tmp = *this;
        if (scale == 0)++bigint;
        else *this = *this+BigDec::ONE;
        return tmp;
    }

    BigDec BigDec::operator--() {
        if (scale == 0)--bigint;
        else *this = *this-BigDec::ONE;
        return *this;
    }

    BigDec BigDec::operator--(int n) {
        BigDec tmp = *this;
        if (scale == 0)--bigint;
        else *this = *this-BigDec::ONE;
        return tmp;
    }

}
