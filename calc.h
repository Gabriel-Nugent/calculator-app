#ifndef CALC_H
#define CALC_H

#include <stack>
#include <string>
#include <unordered_map>

namespace App {

class Calc
{
public:
    Calc();

    double getTotal();
    std::string getExpression() {return currentExpression;}

    void addSymbol(const std::string symbol);
    void removeLastSymbol();
    void clear();
private:
    // map for quick access of operators
    std::unordered_map<std::string, bool> operators{
        {"+", true},
        {"-", true},
        {"/", true},
        {"*", true}
    };

    double total = 0;
    std::string currentNumber = "";
    std::string currentExpression = "";
    std::stack<std::string> symbols; // for storing operators and numbers
    bool lastSymbolIsOperator = false;
};

}

#endif // CALC_H
