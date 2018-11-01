#include "Calcu.hpp"

using namespace std;
namespace mylib {

    Calcu::Calcu(const std::string& str_f, const char& char_x) {
        setString(str_f);
        this->char_x = char_x;
    }

    /**
     * プッシュ
     * @param x 実数
     * @return 変数名の文字列
     */
    string Calcu::pushDouble(const double& x) {
        ostringstream os;
        os << "<" << size << ">";
        stock.push_back(x);
        ++size;
        return os.str();
    }

    /**
     * 変数以外の数字の検索
     * @param str 検索対象
     * @param pos 開始位置 一致した数字があった場合その位置を格納
     * @return 一致した数字(数字がないとき""を返す)
     */
    string Calcu::searchNumber(const string& str, string::size_type& pos) {
        string::size_type begin = pos, end, length = str.length();
        while (!isdigit(str[begin]) || (begin >= 1 && str[begin - 1] == '<')) {
            ++begin;
            if (length == begin)return "";
        }
        if (begin >= 2 && (str[begin - 1] == '-' || str[begin - 1] == '+')
                && (str[begin - 2] == '*' || str[begin - 2] == '/' || str[begin - 2] == '(' || str[begin - 2] == '^'))
            --begin;
        pos = begin;
        end = begin + 1;

        while (end < length && (isdigit(str[end]) || str[end] == '.'))
            ++end;

        return str.substr(begin, end - begin);
    }

    /**
     * 左右の実数を得る
     * @param str 対象文字列
     * @param start この位置の左右、見つかった先頭位置を返す
     * @param back 前にある実数
     * @param next 後ろにある実数
     * @return 一致した部分の文字列
     */
    string Calcu::getNumber(const string& str, string::size_type& start, double& back, double& next) {
        string::size_type i = start, j = start + 1;
        while (str[i] != '<') --i;
        back = stock[atoi(&str[i + 1])];
        next = stock[atoi(&str[start + 2])];
        while (str[j] != '>') ++j;

        string temp = str.substr(i, j - i + 1);
        start = i;
        return temp;
    }

    /**
     * 初等関数
     * @param str 関数のある文字列
     * @param option 関数番号
     */
    void Calcu::basicFunction(string& str, const int& option) {
#define CASE(function,str) {case function: str=#function;break;}
#define CONVERT(funcNum,function,d) {case funcNum:d=function(d);break;}

        string::size_type p, length;
        double d;
        string before, function, after;
        switch (option) {
                CASE(Asin, function);
                CASE(Acos, function);
                CASE(Atan, function);
                CASE(Sinh, function);
                CASE(Cosh, function);
                CASE(Tanh, function);
                CASE(Sin, function);
                CASE(Cos, function);
                CASE(Tan, function);
                CASE(Log, function);
                CASE(Abs, function);
                CASE(Sqrt, function);
                CASE(Ceil, function);
                CASE(Floor, function);
                CASE(Exp, function);
        }
        //小文字に変換
        function[0] += 'a' - 'A';
        length = function.length();
        while ((p = str.find(function)) != string::npos) {
            d = stock[atoi(&str[p + length + 1])];
            switch (option) {
                    CONVERT(Asin, asin, d);
                    CONVERT(Acos, acos, d);
                    CONVERT(Atan, atan, d);
                    CONVERT(Sinh, sinh, d);
                    CONVERT(Cosh, cosh, d);
                    CONVERT(Tanh, tanh, d);
                    CONVERT(Sin, sin, d);
                    CONVERT(Cos, cos, d);
                    CONVERT(Tan, tan, d);
                    CONVERT(Log, log, d);
                    CONVERT(Abs, fabs, d);
                    CONVERT(Sqrt, sqrt, d);
                    CONVERT(Ceil, ceil, d);
                    CONVERT(Floor, floor, d);
                    CONVERT(Exp, exp, d);
            }
            after = pushDouble(d);
            before = str.substr(p, str.find('>', p) - p + 1);
            firstReplace(str, before, after, p);
        }
#undef CASE
#undef CONVERT
    }

    char Calcu::getChar() const {
        return char_x;
    }

    std::string Calcu::getString() const {
        return str_f;
    }

    /**
     * 関数
     * @param x 実数
     * @return f(x)
     */
    double Calcu::func(const double &x) {
        stock.clear();
        size = 0;
        vector<double>(stock).swap(stock);
        string temp = str_f;
        allReplace(temp, char_x, pushDouble(x));
        temp = calculate(temp, true);
        return stock[atoi(&temp[1])];
    }

    void Calcu::setString(const std::string& str_f) {
        this->str_f = str_f;
        this->str_diff = "";
        allReplace(this->str_f, " ", "");
        allReplace(this->str_f, "-+", "-");
        allReplace(this->str_f, "+-", "-");
        allReplace(this->str_f, "++", "+");
        allReplace(this->str_f, "--", "+");
    }

    void Calcu::setChar(const char& char_x) {
        this->char_x = char_x;
    }

    /**
     * xなどの文字が無い文字列の計算
     * @return 
     */
    double Calcu::calculate() {
        stock.clear();
        size = 0;
        vector<double>(stock).swap(stock);
        string temp = calculate(str_f, true);
        return stock[atoi(&temp[1])];
    }

    /**
     * 文字列の計算
     * @param str
     * @param first 初回のみtrue default=false
     * @return 計算結果の文字列(変数名で表される)
     */
    string Calcu::calculate(string str, const bool& first) {
        string::size_type p1, p2, p3;
        string shiki1, shiki2, shiki3;
        double d1, d2;

        if (first) {

            //数字を変数に置き換え ex 1.4 -> <2>
            p1 = 0;
            while ((shiki1 = searchNumber(str, p1)) != "") {
                firstReplace(str, shiki1, pushDouble(atof(shiki1.c_str())), p1);
                p1 = str.find('>', p1 + 1);
            }
            allReplace(str, "pi", pushDouble(M_PI));
            allReplace(str, 'e', pushDouble(M_E));

            //累乗の置換 (^ -> $)
            p1 = 0;
            while ((p1 = str.find('^', p1)) != string::npos) {
                //^の左側
                if (str[p1 - 1] == ')') {
                    p2 = bracketSearch(str, p1 - 1);
                    if (isalpha(str[p2 - 1])) {
                        while (isalpha(str[p2 - 1])) {
                            --p2;
                            if (p2 == 0)break;
                        }
                        if (!isalpha(str[p2]))
                            ++p2;
                    }
                } else if (str[p1 - 1] == '>') {
                    p2 = p1;
                    while (str[p2] != '<')
                        --p2;
                } else {
                    //sumやproの中身の変数がオペランドの時
                    p2 = p1 - 1;
                }
                //^の右側
                if (str[p1 + 1] == '(') {
                    p3 = bracketSearch(str, p1 + 1);
                } else if (isalpha(str[p1 + 1]) && !onlyChar(str, p1 + 1)) {
                    p3 = bracketSearch(str, str.find('(', p1 + 1));
                } else if (str[p1 + 1] == '<') {
                    p3 = p1;
                    while (str[p3] != '>')
                        ++p3;
                } else {
                    //sumやproの中身の変数がオペランドの時
                    p3 = p1 + 1;
                    if (str[p3] == '-' || str[p3] == '+')++p3;
                }
                shiki1 = str.substr(p2, p1 - p2);
                shiki2 = str.substr(p1 + 1, p3 - p1);
                firstReplace(str, shiki1 + "^" + shiki2, "((" + shiki1 + ")$(" + shiki2 + "))", p2);
                p1 = p2;
            }
        }

        //ΣとΠ
        for (int k = 0; k < 2; ++k) {
            string type;
            if (k) type = "pro";
            else type = "sum";

            while ((p1 = str.find(type)) != string::npos) {
                char ch;
                p2 = str.find('=', p1);
                p3 = str.find('{', p2);
                ch = str[p2 - 1];

                int start = (int) stock[atoi(&str[p2 + 2])], end = (int) stock[atoi(&str[p3 + 2])];
                p2 = str.find('(', p3);
                p3 = bracketSearch(str, p2);
                shiki1 = str.substr(p1, p3 - p1 + 1);
                shiki2 = str.substr(p2, p3 - p2 + 1);
                if (k) d1 = 1;
                else d1 = 0;
                for (int i = start; i <= end; ++i) {
                    shiki3 = shiki2;
                    allReplace(shiki3, ch, pushDouble(i));
                    shiki3 = calculate(shiki3);
                    if (k)
                        d1 *= stock[atoi(&shiki3[1])];
                    else
                        d1 += stock[atoi(&shiki3[1])];
                }
                firstReplace(str, shiki1, pushDouble(d1), p1);
            }
        }

        //カッコの計算
        while ((p1 = str.find('(')) != string::npos) {
            p2 = bracketSearch(str, p1);
            shiki1 = str.substr(p1, p2 - p1 + 1);
            shiki2 = calculate(str.substr(p1 + 1, p2 - p1 - 1));
            firstReplace(str, shiki1, shiki2, p1);
        }


        //累乗計算-----------------------------------------------------------
        while ((p1 = str.find('$')) != string::npos) {
            shiki1 = getNumber(str, p1, d1, d2);
            firstReplace(str, shiki1, pushDouble(pow(d1, d2)), p1);
        }
        //初等関数の計算
        for (int i = 0; i < functions; ++i) {
            basicFunction(str, i);
        }

        //*,/の計算
        while (1) {
            p1 = str.find('*');
            p2 = str.find('/');
            if (p1 != string::npos && p2 != string::npos) {
                if (p1 > p2)
                    p1 = string::npos;
                else
                    p2 = string::npos;
            }
            if (p1 != string::npos) {
                shiki1 = getNumber(str, p1, d1, d2);
                firstReplace(str, shiki1, pushDouble(d1 * d2), p1);
            } else if (p2 != string::npos) {
                shiki1 = getNumber(str, p2, d1, d2);
                firstReplace(str, shiki1, pushDouble(d1 / d2), p2);
            } else {
                break;
            }
        }

        //+,-の計算
        d1 = 0;
        if (str[0] == '-')
            d1 = -stock[atoi(&str[2])];
        else if (str[0] == '+')
            d1 = stock[atoi(&str[2])];
        else
            d1 = stock[atoi(&str[1])];
        p1 = str.find('<', 2);
        while (p1 != string::npos) {
            if (str[p1 - 1] == '+')
                d1 += stock[atoi(&str[p1 + 1])];
            else
                d1 -= stock[atoi(&str[p1 + 1])];
            p1 = str.find('<', p1 + 2);
        }
        return pushDouble(d1);
    }

    /**
     * シンプソン則による定積分
     * @param a 積分開始位置
     * @param b 積分終点位置
     * @param width 分割幅
     * @return 積分値
     */
    double Calcu::integrate(double a, double b, const double& width) {
        if (width <= 0.0 || DBLeq(a, b))return 0;

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
     * f(x)=0の解を返す([low,high]の閉区間にある解を返す。f(x)は[low,high]で単調増加(減少)な関数)
     * @param low 
     * @param high 
     * @param eps 打ち切り誤差 default=1e-12
     * @param countMax 試行回数上限 default=INT_MAX
     * @return 解 (f(low)*f(high)>0ならエラーとしてDBL_MAXを返す)
     */
    double Calcu::solver(double low, double high, const double &eps, const unsigned &countMax) {
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
     * 微分
     * @return 微分した式を返す
     */
    const std::string& Calcu::differential() {
        str_diff = differential(str_f);
        trim(str_diff);
        return str_diff;
    }

    /**
     * 微分(再帰部分)
     * @param str
     * @return 
     */
    std::string Calcu::differential(std::string str) {
        string::size_type p1, p2;
        string shiki1, shiki2, shiki3, shiki4;

        trim(str);

        // + -
        p1 = p2 = 0;
        while (1) {
            if (str[p1] == '(')p1 = bracketSearch(str, p1);
            else if (str[p1] == '+' || str[p1] == '-') {
                shiki1 = str.substr(p2, p1 - p2);
                shiki2 = differential(shiki1);
                firstReplace(str, shiki1, shiki2, p2);
                p2 = p1 + 1 + (shiki2.length() - shiki1.length());
                p1 = p2;
            } else if (str[p1] == '\0') {
                if (p2 == 0)break;
                shiki1 = str.substr(p2);
                shiki2 = differential(shiki1);
                firstReplace(str, shiki1, shiki2, p2);
                return"(" + str + ")";
            } else
                ++p1;
        }

        //   /
        p1 = 0;
        while (str[p1] != '\0') {
            if (str[p1] == '(')p1 = bracketSearch(str, p1);
            else if (str[p1] == '/') {
                shiki1 = str.substr(0, p1);
                shiki2 = str.substr(p1 + 1);
                trim(shiki1);
                trim(shiki2);
                shiki3 = differential(shiki1);
                if (shiki2.find(char_x) != string::npos) {
                    shiki4 = differential(shiki2);
                    str = "(" + shiki3 + "*(" + shiki2 + ")-(" + shiki1 + ")*" + shiki4 + ")/" + "(" + shiki2 + ")^2";
                } else {
                    str = shiki3 + "/(" + shiki2 + ")";
                }
                return "(" + str + ")";
            }
            ++p1;
        }

        //  *
        p1 = 0;
        while (str[p1] != '\0') {
            if (str[p1] == '(')p1 = bracketSearch(str, p1);
            else if (str[p1] == '*') {
                shiki1 = str.substr(0, p1);
                shiki2 = str.substr(p1 + 1);
                trim(shiki1);
                trim(shiki2);
                shiki3 = differential(shiki1);
                shiki4 = differential(shiki2);
                str = shiki3 + "*(" + shiki2 + ")+(" + shiki1 + ")*" + shiki4;
                return "(" + str + ")";
            }
            ++p1;
        }

        if ((p1 = str.find('^')) != string::npos) {
            //    F(x)^G(x)
            shiki1 = str.substr(0, p1);
            shiki2 = str.substr(p1 + 1);
            if (shiki2.find(char_x) != string::npos && shiki1.find(char_x) != string::npos) {
                trim(shiki1);
                trim(shiki2);
                shiki3 = differential(shiki1);
                shiki4 = differential(shiki2);
                str = str + "*(log(" + shiki1 + ")*" + shiki4 + "+((" + shiki2 + ")*" + shiki3 + ")/" + shiki1 + ")";
                return "(" + str + ")";
            } else if (shiki1.find(char_x) != string::npos) {
                //F(x)^n
                str = differential(shiki1) + "*" + shiki2
                        + "*" + shiki1 + "^(" + shiki2 + "-1)";
            } else if (shiki2.find(char_x) != string::npos)
                //a^F(x)
                str = differential(shiki2) + "*log(" + shiki1 + ")*" + str;
        }

        shiki1 = str.substr(0, 3);
        shiki2 = str.substr(0, 4);
        if (shiki1 == "sin") {
            str = "cos" + str.substr(3) + "*" + differential(str.substr(3));
        } else if (shiki1 == "cos") {
            str = "-sin" + str.substr(3) + "*" + differential(str.substr(3));
        } else if (shiki1 == "tan") {
            str = differential(str.substr(3)) + "/" + "(cos" + str.substr(3) + ")^2";
        } else if (shiki1 == "log") {
            str = differential(str.substr(3)) + "/" + str.substr(3);
        } else if (shiki1 == "exp") {
            str = differential(str.substr(3)) + "*" + str;
        } else if (shiki2 == "asin") {
            str = differential(str.substr(4)) + "/sqrt(1-" + str.substr(4) + "^2)";
        } else if (shiki2 == "acos") {
            str = "-" + differential(str.substr(4)) + "/sqrt(1-" + str.substr(4) + "^2)";
        } else if (shiki2 == "atan") {
            str = differential(str.substr(4)) + "/(1+" + str.substr(4) + "^2)";
        } else if (shiki2 == "sqrt") {
            str = differential(str.substr(4)) + "/(2*" + str + ")";
        }

        //定数
        if (str.find(char_x) == string::npos)return "0";
        //x
        shiki1 = char_x + '\0';
        if (str == shiki1)return "1";
        trim(str);
        str = "(" + str + ")";
        return str;
    }

    double Calcu::differential(const double& x) {
        stock.clear();
        size = 0;
        vector<double>(stock).swap(stock);
        if (str_diff == "")str_diff = differential();
        string temp = str_diff;
        allReplace(temp, char_x, pushDouble(x));
        temp = calculate(temp, true);
        return stock[atoi(&temp[1])];
    }

    /**
     * 式を整える
     * @param str
     */
    void Calcu::trim(std::string& str) {
        string::size_type p1, p2, p3;
        string st0, st1, st2;

        while (str[0] == '(' && bracketSearch(str, 0) + 1 == str.length())
            str = str.substr(1, str.length() - 2);

        allReplace(str, "log(e)", "1");


        // shiki1/shiki2*shiki3 -> shiki1*shiki3/shiki2
        p1 = 0;
        while ((p1 = str.find('/', p1)) != string::npos) {
            p2 = p1 + 1;
            if (str[p2] == '(')p2 = bracketSearch(str, p2);
            while (str[p2] != '\0' && str[p2] != '*' && str[p2] != '/' && str[p2] != '+' && str[p2] != '-' && str[p2] != ')') {
                ++p2;
                if (str[p2] == '(')p2 = bracketSearch(str, p2);
            }
            if (str[p2] == '*') {
                p3 = p2;
                getShiki(str, p2, st1, st2);
                firstReplace(str, "*" + st2, "", p3);
                firstReplace(str, "/", "*" + st2 + "/", p1);
            } else if (str[p2] == '/') {
                getShiki(str, p2, st1, st2);
                firstReplace(str, st1 + "/" + st2, "(" + st1 + "*" + st2 + ")", p2);
            } else {
                ++p1;
            }
        }
        // 0 * / ^
        p1 = 0;
        while ((p1 = str.find('0', p1)) != string::npos) {
            if (p1 >= 1 && str[p1 - 1] == '^' && onlyNum(str, p1)) {
                --p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, "1", p1);
            } else if (str[p1 + 1] == '^' && onlyNum(str, p1)) {
                ++p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, "0", p1);
            } else if (p1 >= 1 && str[p1 - 1] == '*' && onlyNum(str, p1)) {
                --p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, "0", p1);
            } else if (str[p1 + 1] == '*' && onlyNum(str, p1)) {
                ++p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, "0", p1);
            } else if (str[p1 + 1] == '/' && onlyNum(str, p1)) {
                ++p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, "0", p1);
            } else {
                ++p1;
            }
        }

        // 1 * / ^
        p1 = 0;
        while ((p1 = str.find('1', p1)) != string::npos) {
            if (p1 >= 1 && str[p1 - 1] == '^' && onlyNum(str, p1)) {//  ^1
                --p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, st1, p1);
            } else if (str[p1 + 1] == '^' && onlyNum(str, p1)) {//  1^
                ++p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, "1", p1);
            } else if (p1 >= 1 && str[p1 - 1] == '*' && onlyNum(str, p1)) {//  *1
                --p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, st1, p1);
            } else if (str[p1 + 1] == '*' && onlyNum(str, p1)) {//  1*
                ++p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, st2, p1);
            } else if (p1 >= 1 &&str[p1 - 1] == '/' && onlyNum(str, p1)) {//  /1
                --p1;
                st0 = getShiki(str, p1, st1, st2);
                firstReplace(str, st0, st1, p1);
            } else {
                ++p1;
            }
        }
        // 0 + -
        p1 = 0;
        while ((p1 = str.find('0', p1)) != string::npos) {
            if (onlyNum(str, p1)) {
                if (str[p1 + 1] == '+') {
                    firstReplace(str, "0+", "", p1);
                    continue;
                } else if (str[p1 + 1] == '-') {
                    firstReplace(str, "0-", "-", p1);
                    continue;
                }
            }
            if (p1 >= 1 && onlyNum(str, p1)) {
                if (str[p1 - 1] == '+') {
                    firstReplace(str, "+0", "", p1 - 1);
                    --p1;
                    continue;
                } else if (str[p1 - 1] == '-') {
                    firstReplace(str, "-0", "", p1 - 1);
                    --p1;
                    continue;
                }
            }
            ++p1;
        }
        // ((shiki)) -> (shiki)
        p1 = 0;
        while ((p1 = str.find("((", p1)) != string::npos) {
            p2 = bracketSearch(str, p1);
            p3 = bracketSearch(str, p1 + 1);
            if (p3 + 1 == p2) {
                firstReplace(str, "))", ")", p3);
                firstReplace(str, "((", "(", p1);
            } else
                ++p1;
        }

        //(x) -> x
        p1 = 0;
        st1 = char_x;
        st0 = "(" + st1 + ")";
        while ((p1 = str.find(st0, p1)) != string::npos) {
            if (p1 == 0 || !isalpha(str[p1 - 1]))
                firstReplace(str, st0, st1, p1);
            else
                ++p1;
        }

        allReplace(str, "+-", "-");
        allReplace(str, "--", "+");
    }

    /**
     * startの左右の式を得る。
     * @param str 対象文字列
     * @param start この位置の左右、見つかった先頭位置を返す
     * @param back 前にある式
     * @param next あとに続く式
     * @return 一致部分、式全体
     */
    std::string Calcu::getShiki(const std::string& str, std::string::size_type& start, std::string& back, std::string& next) {
        string::size_type p1 = start - 1, p2 = start + 1;
        //left
        if (str[p1] == ')') {
            p1 = bracketSearch(str, p1);
            while (p1 >= 1 && isalpha(str[p1 - 1]))--p1;
        } else if (isdigit(str[p1])) {
            while (p1 >= 1 && (isdigit(str[p1 - 1]) || str[p1 - 1] == '.')) --p1;
        }
        //right
        if (str[p2] == '(') {
            p2 = bracketSearch(str, p2);
        } else if (isdigit(str[p2])) {
            while (isdigit(str[p2 + 1]) || str[p2 + 1] == '.') ++p2;
        } else if (!onlyChar(str, p2)) {
            p2 = bracketSearch(str, str.find('(', p2));
        }
        next = str.substr(start + 1, p2 - start);
        back = str.substr(p1, start - p1);
        start = p1;
        return str.substr(p1, p2 - p1 + 1);
    }

}
