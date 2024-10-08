#include "calc.h"

namespace App {

Calc::Calc() {}

// calculates total value
double Calc::getTotal() {
    if (symbols.empty() && currentNumber == "") {
        return 0;
    }
    // no need to add current number
    if (lastSymbolIsOperator == true) {
        return total;
    }
    // result is the only number available
    else if (symbols.empty()) {
        return std::stod(currentNumber);
    }
    else { // add current number to total
        std::string lastOperator = symbols.top();
        if (lastOperator == "+") {
            total = total + std::stod(currentNumber);
        } else if (lastOperator == "-") {
            total = total - std::stod(currentNumber);
        } else if (lastOperator == "*") {
            total = total * std::stod(currentNumber);
        } else {
            total = total / std::stod(currentNumber);
        }
        return total;
    }
}

// add a new symbol to the current expression
void Calc::addSymbol(const std::string symbol) {
    // symbol is an operator
    if (operators[symbol] == true) {
        // cannot have two operators next to one another or start an expression with one
        if (lastSymbolIsOperator == true || currentExpression == "") {
            return;
        } else {
            lastSymbolIsOperator = true;

            if (symbols.empty()) {
                total = std::stod(currentNumber);
            } else {
                std::string lastOperator = symbols.top();
                if (lastOperator == "+") {
                    total = total + std::stod(currentNumber);
                } else if (lastOperator == "-") {
                    total = total - std::stod(currentNumber);
                } else if (lastOperator == "*") {
                    total = total * std::stod(currentNumber);
                } else {
                    total = total / std::stod(currentNumber);
                }
            }

            // add completed number to expression and symbols stack
            currentExpression += " " + symbol;
            symbols.push(currentNumber);
            currentNumber = "";

            symbols.push(symbol);
        }
    } else { // symbol is a digit
        if (lastSymbolIsOperator) {
            currentExpression += " "; // space for formatting purposes
        }

        currentNumber += symbol;
        currentExpression += symbol;
        lastSymbolIsOperator =  false;
    }

}


// TODO: Implement calculator backspace
void Calc::removeLastSymbol() {
    if (symbols.empty()) {
        return;
    }

    std::string removedSymbol = symbols.top();
    symbols.pop();

    // symbol is a number
    if (operators[removedSymbol] == false) {
        if (symbols.empty()) {
            total = 0;
            currentExpression = "";
            return;
        } else {
            // reverse last operator on expression total
            std::string lastOperator = symbols.top();
            if (lastOperator == "+") {
                total = total - std::stod(removedSymbol);
            } else if (lastOperator == "-") {
                total = total + std::stod(removedSymbol);
            } else if (lastOperator == "*") {
                total = total / std::stod(removedSymbol);
            } else {
                total = total * std::stod(removedSymbol);
            }

            // remove number and preceeding space from expression
            currentExpression = currentExpression.substr(0,currentExpression.size() - removedSymbol.size() - 1);
        }
    } else {
        // remove operator and preceeding space from expression
        currentExpression = currentExpression.substr(0,currentExpression.size() - 2);
    }
}

// reset calculator state
void Calc::clear() {
    total = 0;
    currentNumber = "";
    currentExpression = "";
    lastSymbolIsOperator = false;
    while (!symbols.empty()) {
        symbols.pop();
    }
}

}
