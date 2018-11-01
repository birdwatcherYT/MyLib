#ifndef CALCU_HPP
#define	CALCU_HPP

#define _USE_MATH_DEFINES

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cfloat>
#include <climits>
#include <cctype>
#include "Utility.hpp"
#include "Typedefs.hpp"

namespace mylib {

    /**
     * 文字列から計算するクラス\n
     * Calcu(const std::string& str_f, const char &char_x = 'x'); \n
     */
    class Calcu {
    private:

        enum {
            Asin,
            Acos,
            Atan,
            Sinh,
            Cosh,
            Tanh,
            Sin,
            Cos,
            Tan,
            Log,
            Abs,
            Sqrt,
            Ceil,
            Floor,
            Exp,
            functions
        };
        std::string str_f;
        std::string str_diff;
        std::vector<double> stock;
        char char_x;
        unsigned size;

        std::string calculate(std::string str, const bool& first = false);
        std::string getNumber(const std::string &str, std::string::size_type& start, double &back, double &next);
        void basicFunction(std::string &str, const int& option);
        std::string pushDouble(const double& x);
        std::string searchNumber(const std::string &str, std::string::size_type& pos);
        std::string differential(std::string str);
        std::string getShiki(const std::string &str, std::string::size_type &start, std::string &back, std::string &next);
        void trim(std::string &str);
    public:
        Calcu(const std::string& str_f, const char &char_x = 'x');
        void setString(const std::string &str_f);
        void setChar(const char &char_x);
        char getChar()const;
        std::string getString()const;
        double func(const double &x);
        double calculate();
        double integrate(double a, double b, const double& width);
        double solver(double low, double high, const double &eps = 1e-12, const unsigned &countMax = INT_MAX);
        const std::string& differential();
        double differential(const double &x);
    };

}
#endif	/* CALCU_HPP */

