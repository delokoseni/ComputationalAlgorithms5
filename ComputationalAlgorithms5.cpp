#include <iostream>
#include <cmath>
#include "exprtk.hpp"
#include <vector>

double GetFunctionValue(double Argument, std::string Function);
exprtk::expression<double> MakeExpression(exprtk::symbol_table<double> SymbolTable, std::string Function);
double MiddleRectangleMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function);
double TrapezoidMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function);
double SimpsonMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double BeginOfIntegration;
    std::cout << "Введите начальное значение для интегрирования: ";
    std::cin >> BeginOfIntegration;

    double EndOfIntegration;
    std::cout << "Введите конечное значение для интегрирования: ";
    std::cin >> EndOfIntegration;

    double NumberOfAmounts;
    std::cout << "Введите количество сумм: ";
    std::cin >> NumberOfAmounts;

    std::cout << "Введите функцию: ";
    std::string Function;
    std::cin >> Function;

    std::cout << "Результат, полученный методом средних прямоугольников: ";
    std::cout << MiddleRectangleMethod(BeginOfIntegration, EndOfIntegration, NumberOfAmounts, Function);
    std::cout << "\nРезультат, полученный методом трапеции: ";
    std::cout << TrapezoidMethod(BeginOfIntegration, EndOfIntegration, NumberOfAmounts, Function);
    std::cout << "\nРезультат, полученный методом Симпсона: ";
    std::cout << SimpsonMethod(BeginOfIntegration, EndOfIntegration, NumberOfAmounts, Function);
    return 0;
}

//Метод левых прямоугольников
double MiddleRectangleMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function)
{
    double H = (EndOfIntegration - BeginOfIntegration) / NumberOfAmounts; // Шаг разбиения = (b - a) / n
    double Result = 0.0;
    for (int i = 0; i < NumberOfAmounts; i++)
        Result += H * GetFunctionValue(BeginOfIntegration + i * H + H/2, Function);
    return Result;
}

//Метод трапеции
double TrapezoidMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function)
{
    double H = (EndOfIntegration - BeginOfIntegration) / NumberOfAmounts; // Шаг разбиения = (b - a) / n
    double Result = GetFunctionValue(BeginOfIntegration, Function) + GetFunctionValue(EndOfIntegration, Function); //f(a) + f(b)
    for (int i = 1; i < NumberOfAmounts - 1; i++)
        Result += 2 * GetFunctionValue(BeginOfIntegration + i * H, Function);
    return H/2 * Result;
}

//Метод Симпсона
double SimpsonMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function)
{
    if (NumberOfAmounts % 2 == 1)
        NumberOfAmounts += 1; //Чтобы при подсчете не "потерять" последнюю точку
    double H = (EndOfIntegration - BeginOfIntegration) / NumberOfAmounts; // Шаг разбиения = (b - a) / n
    double Result = GetFunctionValue(BeginOfIntegration, Function); //f(x[i-1])
    Result += 4 * GetFunctionValue(BeginOfIntegration + H, Function); //f(x[i-1]) + 4f(x[i])
    Result += GetFunctionValue(EndOfIntegration, Function); //f(x[i-1]) + 4f(x[i]) + f(x[i+1])
    for (int i = 1; i < NumberOfAmounts / 2; i++)
    {
        Result += 4 * GetFunctionValue(BeginOfIntegration + (2 * i + 1) * H, Function); //Нечётные
        Result += 2 * GetFunctionValue(BeginOfIntegration + 2 * i * H, Function); //Чётные
    }
    return H / 3 * Result;
}

//Получает таблицу по введенной в аналитическом виде функции
double GetFunctionValue(double Argument, std::string Function)
{
    exprtk::symbol_table<double> SymbolTable;
    //Заполнение таблицы символов
    SymbolTable.add_variable("x", Argument);
    SymbolTable.add_function("abs", abs);
    SymbolTable.add_function("sqrt", sqrt);
    SymbolTable.add_function("exp", exp);
    //Создается выражение, вычисляется значение функции
    exprtk::expression<double> Expression = MakeExpression(SymbolTable, Function);
    return (double)Expression;
}

//Создает выражение, вычисляется значение функции
exprtk::expression<double> MakeExpression(exprtk::symbol_table<double> SymbolTable, std::string Function)
{
    //Создается выражение
    exprtk::expression<double> Expression;
    Expression.register_symbol_table(SymbolTable);
    //Выражение компилируется с помощью парсера
    exprtk::parser<double> Parser;
    if (!Parser.compile(Function, Expression))
        std::cout << "Ошибка в выражении!\n";
    return Expression; //Возвращается выражение
}
