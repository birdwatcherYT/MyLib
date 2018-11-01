#include "Utility.hpp"

using namespace std;

namespace mylib {

    /**
     * ファイルから小数を得る
     * @param ifs
     * @param num 格納する変数
     * @return 成功したかどうか
     */
    bool readDouble(std::ifstream &ifs, double &num) {
        string str = "";
        char ch;
        while (!ifs.eof()) {
            ifs.get(ch);
            if (ch == '+' || ch == '-') {
                str += ch;
                if (ifs.eof())return false;
                ifs.get(ch);
                if (isdigit(ch)) {
                    str += ch;
                    while (!ifs.eof()) {
                        ifs.get(ch);
                        if (isdigit(ch) || ch == '.')
                            str += (char) ch;
                        else
                            break;
                    }
                    num = atof(str.c_str());
                    return true;
                } else {
                    str = "";
                }
            } else if (isdigit(ch)) {
                str += ch;
                while (!ifs.eof()) {
                    ifs.get(ch);
                    if (isdigit(ch) || ch == '.')
                        str += ch;
                    else
                        break;
                }
                num = atof(str.c_str());
                return true;
            }
        }
        return false;
    }

    /**
     * ファイルから整数を得る
     * @param ifs
     * @param num 格納する変数
     * @return 成功したかどうか
     */
    bool readInt(std::ifstream &ifs, int &num) {
        string str = "";
        char ch;
        while (!ifs.eof()) {
            ifs.get(ch);
            if (ch == '+' || ch == '-') {
                str += ch;
                if (ifs.eof()) return false;
                ifs.get(ch);
                if (isdigit(ch)) {
                    str += ch;
                    while (!ifs.eof()) {
                        ifs.get(ch);
                        if (isdigit(ch))
                            str += ch;
                        else
                            break;
                    }
                    num = atoi(str.c_str());
                    return true;
                } else {
                    str = "";
                }
            } else if (isdigit(ch)) {
                str += ch;
                while (!ifs.eof()) {
                    ifs.get(ch);
                    if (isdigit(ch))
                        str += ch;
                    else
                        break;
                }
                num = atoi(str.c_str());
                return true;
            }
        }
        return false;
    }

    /**
     * ファイルから整数を得る
     * @param fp
     * @param num 格納する変数
     * @return 成功したかどうか
     */
    bool readInt(FILE *fp, int &num) {
        string str = "";
        int ch;
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '+' || ch == '-') {
                str += (char) ch;
                if ((ch = fgetc(fp)) == EOF)
                    return false;
                if (isdigit(ch)) {
                    str += (char) ch;
                    while ((ch = fgetc(fp)) != EOF) {
                        if (isdigit(ch))
                            str += (char) ch;
                        else
                            break;
                    }
                    num = atoi(str.c_str());
                    return true;
                } else {
                    str = "";
                }
            } else if (isdigit(ch)) {
                str += (char) ch;
                while ((ch = fgetc(fp)) != EOF) {
                    if (isdigit(ch))
                        str += (char) ch;
                    else
                        break;
                }
                num = atoi(str.c_str());
                return true;
            }
        }
        return false;
    }

    /**
     * ファイルから小数を得る
     * @param fp
     * @param num 格納する変数
     * @return 成功したかどうか
     */
    bool readDouble(FILE *fp, double &num) {
        string str = "";
        int ch;
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '+' || ch == '-') {
                str += (char) ch;
                if ((ch = fgetc(fp)) == EOF)
                    return false;
                if (isdigit(ch)) {
                    str += (char) ch;
                    while ((ch = fgetc(fp)) != EOF) {
                        if (isdigit(ch) || ch == '.')
                            str += (char) ch;
                        else
                            break;
                    }
                    num = atof(str.c_str());
                    return true;
                } else {
                    str = "";
                }
            } else if (isdigit(ch)) {
                str += (char) ch;
                while ((ch = fgetc(fp)) != EOF) {
                    if (isdigit(ch) || ch == '.')
                        str += (char) ch;
                    else
                        break;
                }
                num = atof(str.c_str());
                return true;
            }
        }
        return false;
    }

    /**
     * 文字列から整数を得る
     * @param str
     * @param num 格納する変数
     * @return 数字最後の次の位置のポインタ、数字が無いときはNULL
     */
    char* readInt(char* str, BigInt &number) {
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
                    number = BigInt(tmp);
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
                number = BigInt(tmp);
                return str;
            }
        }
        return NULL;
    }

    /**
     * 文字列から小数を得る
     * @param str
     * @param num 格納する変数
     * @return 数字最後の次の位置のポインタ、数字が無いときはNULL
     */
    char* readDouble(char* str, double &number) {
        string tmp = "";
        char ch;
        while ((ch = *str++) != '\0') {
            if (ch == '+' || ch == '-') {
                tmp += ch;
                if ((ch = *str++) == '\0')
                    return NULL;
                if (isdigit(ch)) {
                    tmp += ch;
                    while ((ch = *str++) != '\0') {
                        if (isdigit(ch) || ch == '.')
                            tmp += ch;
                        else
                            break;
                    }
                    number = atof(tmp.c_str());
                    return str;
                } else {
                    tmp = "";
                }
            } else if (isdigit(ch)) {
                tmp += ch;
                while ((ch = *str++) != '\0') {
                    if (isdigit(ch) || ch == '.')
                        tmp += ch;
                    else
                        break;
                }
                number = atof(tmp.c_str());
                return str;
            }
        }
        return NULL;
    }

    /**
     * double 型の比較
     * @param a
     * @param b
     * @return 
     */
    bool DBLeq(const double &a, const double &b) {
        if (a - DBL_EPSILON < b && b < DBL_EPSILON + a)return true;
        else return false;
    }

    /**
     * flagを満たさない時、メッセージを表示し、終了する
     * @param flag
     * @param message
     * @param file
     * @param function
     * @param line
     */
    void inner::assert(bool flag, const char* message, const char* file, const char* function, const int& line) {
        if (!flag) {
            std::cerr << message << std::endl << "(" << file << " " << line << "行目 " << function << "関数 内から)" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    /**
     * タイマー(プロセス時間)
     * 奇数回目で計測開始、偶数回目で計測終了、結果をかえす
     * @return 
     */
    double processTimer() {
        static clock_t start, end;
        static bool flag = true;
        if (flag) {
            flag = false;
            start = clock();
            return -1;
        } else {
            end = clock();
            flag = true;
            return (double) (end - start) / CLOCKS_PER_SEC;
        }
    }

    /**
     * タイマー(実際の時間)
     * 奇数回目で計測開始、偶数回目で計測終了、結果をかえす
     * @return 
     */
    time_t timer() {
        static time_t start, end;
        static bool flag = true;
        if (flag) {
            flag = false;
            time(&start);
            return -1;
        } else {
            time(&end);
            flag = true;
            return (end - start);
        }
    }

    /**
     * [min,max]区間の整数値を返す
     * @param min
     * @param max
     * @return 
     */
    int getRandom(const int &min, const int &max) {
        static bool flag = true;
        if (flag) {
            srand((unsigned) time(NULL));
            flag = false;
        }
        //return min + rand() % (max + 1);
        return min + (int) (rand()*(max - min + 1.0) / (RAND_MAX + 1.0));
    }

    /**
     * f(x)=0の解を返す([low,high]の閉区間にある解を返す。f(x)は[low,high]で単調増加(減少)な関数)
     * @param func 関数
     * @param low 
     * @param high 
     * @param eps 打ち切り誤差 default=1e-12
     * @param countMax 試行回数上限 default=INT_MAX
     * @return 解 (f(low)*f(high)>0ならエラーとしてDBL_MAXを返す)
     */
    double solver(double (*func) (const double&), double low, double high, const double &eps, const unsigned &countMax) {
        double mid, fHigh = func(high), fLow = func(low), fMid;
        ULLONG count = 0ULL;
        if (DBLeq(fHigh, 0.0))return high;
        if (DBLeq(fLow, 0.0))return low;
        if (!((fHigh > 0.0)^(fLow > 0.0)))return DBL_MAX;

        while (true) {
            mid = (high + low) / 2.0, fMid = func(mid);
            ++count;
            if ((fHigh > 0.0)^(fMid > 0.0))
                low = mid, fLow = fMid;
            else if ((fMid > 0.0)^(fLow > 0.0))
                high = mid, fHigh = fMid;
            if (count == countMax || fabs(fMid) <= eps)
                break;
        }
        return mid;
    }

    /**
     * シンプソン則による定積分
     * @param func 被積分関数
     * @param a 積分開始位置
     * @param b 積分終点位置
     * @param width 分割幅
     * @return 積分値
     */
    double integrate(double (*func)(const double&), double a, double b, const double& width) {
        if (width <= 0.0 || DBLeq(a, b))return 0.0;

        int flag = 1;
        if (a > b) {
            swap_f(a, b);
            flag = -1;
        }

        double OddSum = 0.0, EvenSum = 0.0;

        ULLONG n = (ULLONG) ((b - a) / (2.0 * width)), end = 2ULL * n - 3ULL;

        for (ULLONG k = 1ULL; k <= end; k += 2ULL) {
            OddSum += func(a + width * k);
            EvenSum += func(a + width * (k + 1ULL));
        }

        return width * (func(a) + func(b) + 4.0 * (OddSum + func(b - width)) + 2.0 * EvenSum) / 3.0 * flag;
    }

    /**
     * 対象文字列をすべて置換
     * @param text 対象文字列
     * @param before 置換したい文字列
     * @param after この文字列に置き換え
     */
    void allReplace(std::string& text, const std::string& before, const std::string & after) {
        string::size_type Pos(text.find(before));
        while (Pos != string::npos) {
            text.replace(Pos, before.length(), after);
            Pos = text.find(before, Pos + after.length());
        }
    }

    /**
     * 左右がアルファベットでない1文字を文字列に置換
     * @param text 対象文字列
     * @param ch 置換したい文字
     * @param after この文字列に置換
     */
    void allReplace(std::string &text, const char& ch, const std::string & after) {
        string::size_type pos(text.find(ch));
        while (pos != string::npos) {
            if (onlyChar(text, pos))
                text.replace(pos, 1, after);
            pos = text.find(ch, pos + 1);
        }
    }

    /**
     * 一致した文字列を前から1つだけ置換
     * @param text 対象文字列
     * @param before 置換したい文字列
     * @param after この文字列に置き換え
     * @param pos この位置以降 default=0
     */
    void firstReplace(std::string& text, const std::string& before, const std::string& after, const std::string::size_type & pos) {
        string::size_type index = text.find(before, pos);
        if (index != string::npos) {
            text.replace(index, before.length(), after);
        }
    }

    /**
     * 左右にアルファベットが無いかどうか
     * @param text 対象文字列
     * @param pos この位置の左右
     * @return 
     */
    bool onlyChar(const std::string &text, const std::string::size_type & pos) {
        bool f1 = true, f2 = true;
        if (pos > 0)
            f1 = !isalpha(text[pos - 1]);

        if (pos + 1 < text.size())
            f2 = !isalpha(text[pos + 1]);

        return f1&&f2;
    }

    bool onlyChar(const char *text, const unsigned &pos) {
        bool f1 = true, f2 = true;
        if (pos > 0)
            f1 = !isalpha(text[pos - 1]);
        if (pos + 1 < strlen(text))
            f2 = !isalpha(text[pos + 1]);
        return f1&&f2;
    }

    /**
     * posの両隣が数字でない時、true
     * @param text
     * @param pos
     * @return 
     */
    bool onlyNum(const std::string &text, const std::string::size_type & pos) {
        bool f1 = true, f2 = true;
        if (pos > 0)
            f1 = !(isdigit(text[pos - 1]));
        if (pos + 1 < text.size())
            f2 = !(isdigit(text[pos + 1]));

        return f1&&f2;
    }

    bool onlyNum(const char *text, const unsigned& pos) {
        bool f1 = true, f2 = true;
        if (pos > 0)
            f1 = !(isdigit(text[pos - 1]));
        if (pos + 1 < strlen(text))
            f2 = !(isdigit(text[pos + 1]));
        return f1&&f2;
    }

    /**
     * 対応するカッコの位置を返す
     * @param str 検索文字列
     * @param startPos この位置のカッコに対して
     * @return 対応するカッコの位置
     */
    std::string::size_type bracketSearch(const std::string &str, std::string::size_type startPos) {
        int count = 1;
        bool leftBracket;
        char ch1, ch2;
        if (str[startPos] == '(') {
            leftBracket = true;
            ch1 = '(';
            ch2 = ')';
        } else if (str[startPos] == ')') {
            leftBracket = false;
            ch1 = ')';
            ch2 = '(';
        } else {
            return string::npos;
        }

        while (count != 0) {
            if (leftBracket)
                ++startPos;
            else
                --startPos;
            if (str[startPos] == ch1) {
                ++count;
            } else if (str[startPos] == ch2) {
                --count;
            } else if (str[startPos] == '\0' || startPos == 0) {
                return string::npos;
            }
        }
        return startPos;
    }

    char *bracketSearch(char *startKakko) {
        int count = 1;
        bool leftKakko;
        char ch1, ch2;

        switch (*startKakko) {
            case '(':
                leftKakko = true;
                ch1 = '(';
                ch2 = ')';
                break;
            case ')':
                leftKakko = false;
                ch1 = ')';
                ch2 = '(';
                break;
            default:
                return NULL;
        }
        while (count != 0) {
            if (leftKakko)
                ++startKakko;
            else
                --startKakko;
            if (*startKakko == ch1) {
                ++count;
            } else if (*startKakko == ch2) {
                --count;
            } else if (*startKakko == '\0' || startKakko == NULL) {
                return NULL;
            }
        }
        return startKakko;
    }

    void factorization(ULLONG n, std::ostream & os) {

        os << n << " = ";
        if (n <= 3ULL) {
            os << n << std::endl;
            return;
        }
        while ((n % 2ULL) == 0ULL) {
            n /= 2ULL;
            if (n == 1ULL) {
                os << "2" << std::endl;
                return;
            }
            os << "2 * ";
        }

        ULLONG d = 3ULL;
        while (1) {
            if ((n % d) == 0ULL) {
                n /= d;
                if (n == 1ULL)break;
                os << d << " * ";
            } else {
                d += 2ULL;
            }
        }
        os << d << std::endl;
    }

    bool isPrime(ULLONG n) {
        if (n < 2ULL) return false;
        if (n == 2ULL)return true;
        if ((n % 2ULL) == 0ULL)return false;

        ULLONG end = (ULLONG) sqrt((double) n);
        for (ULLONG i = 3ULL; i <= end; i += 2ULL) {
            if ((n % i) == 0ULL) return false;
        }
        return true;
    }

    /**
     * 整数の10^iの係数を返す
     * @param n 整数
     * @param i 
     * @return 
     */
    int getNumberI(const LLONG &n, const int &i) {
        if (i < 0)return -1;
        LLONG tens = power_f(10LL, i);
        return (int) ((n % (tens * 10LL)) / tens);
    }

}