#include <iostream>
#include <cmath>
#include "exprtk.hpp"
#include <vector>

double GetFunctionValue(double Argument, std::string ExpressionString);
exprtk::expression<double> MakeExpression(exprtk::symbol_table<double> SymbolTable, std::string ExpressionString);
double LeftRectangleMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts);
double TrapezoidMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts);
double SimpsonMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Введите функцию: ";
    std::string Function;
    std::cin >> Function;
    std::cout << GetFunctionValue(0.5, Function);
    return 0;
}

//Получает таблицу по введенной в аналитическом виде функции
double GetFunctionValue(double Argument, std::string ExpressionString)
{
    exprtk::symbol_table<double> SymbolTable;
    //Заполнение таблицы символов
    SymbolTable.add_variable("x", Argument);
    SymbolTable.add_function("abs", abs);
    SymbolTable.add_function("sqrt", sqrt);
    SymbolTable.add_function("exp", exp);
    //Создается выражение, вычисляется значение функции
    exprtk::expression<double> Expression = MakeExpression(SymbolTable, ExpressionString);
    return (double)Expression;
}

//Создает выражения, вычисляются значения функции
exprtk::expression<double> MakeExpression(exprtk::symbol_table<double> SymbolTable, std::string ExpressionString)
{
    //Создается вектор выражений заданного размера
    exprtk::expression<double> Expression;
    Expression.register_symbol_table(SymbolTable);
    //Компилируется выражение с помощью парсера
    exprtk::parser<double> Parser;
    if (!Parser.compile(ExpressionString, Expression))
        std::cout << "Ошибка в выражении!\n";
    return Expression; //Возвращается выражение
}
