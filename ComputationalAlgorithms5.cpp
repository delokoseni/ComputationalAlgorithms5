#include <iostream>
#include <cmath>
#include "exprtk.hpp"
#include <vector>

double GetFunctionValue(double Argument, std::string Function);
exprtk::expression<double> MakeExpression(exprtk::symbol_table<double> SymbolTable, std::string Function);
double MiddleRectangleMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function);
double MiddleRectangleMethodWA(double BeginOfIntegration, double EndOfIntegration, double Epsilon, std::string Function);
double TrapezoidMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function);
double TrapezoidMethodWA(double BeginOfIntegration, double EndOfIntegration, double Epsilon, std::string Function);
double SimpsonMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfAmounts, std::string Function);
double SimpsonMethodWA(double BeginOfIntegration, double EndOfIntegration, double Epsilon, std::string Function);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Choise;
    std::cout << "Выберите режим." << std::endl;
    std::cout << "1) С постоянным выбором шага интегрирования." << std::endl;
    std::cout << "2) С автоматическим выбором шага интегрирования." << std::endl;
    std::cout << "Ваш выбор: ";
    std::cin >> Choise;

    //Для первого и второго режима
    double BeginOfIntegration, EndOfIntegration;
    std::string Function;

    std::cout << "Введите начальное значение для интегрирования: ";
    std::cin >> BeginOfIntegration;

    std::cout << "Введите конечное значение для интегрирования: ";
    std::cin >> EndOfIntegration;

    std::cout << "Введите функцию: ";
    std::cin >> Function;

    double NumberOfSplits; //Только для первого режима

    double Epsilon; //Только для второго режима

    switch (Choise)
    {
    case 1:
        std::cout << "Введите число разбиений: ";
        std::cin >> NumberOfSplits;

        std::cout << "Результат, полученный методом средних прямоугольников: ";
        std::cout << MiddleRectangleMethod(BeginOfIntegration, EndOfIntegration, NumberOfSplits, Function);
        std::cout << "\nРезультат, полученный методом трапеции: ";
        std::cout << TrapezoidMethod(BeginOfIntegration, EndOfIntegration, NumberOfSplits, Function);
        std::cout << "\nРезультат, полученный методом Симпсона: ";
        std::cout << SimpsonMethod(BeginOfIntegration, EndOfIntegration, NumberOfSplits, Function);
        break;
    case 2:
        std::cout << "Введите погрешность: ";
        std::cin >> Epsilon;

        double Result;
        Result = MiddleRectangleMethodWA(BeginOfIntegration, EndOfIntegration, Epsilon, Function);
        std::cout << "Результат, полученный методом средних прямоугольников: ";
        std::cout << Result << std::endl << std::endl;
        Result = TrapezoidMethodWA(BeginOfIntegration, EndOfIntegration, Epsilon, Function);
        std::cout << "Результат, полученный методом трапеции: ";
        std::cout << Result << std::endl << std::endl;
        Result = SimpsonMethodWA(BeginOfIntegration, EndOfIntegration, Epsilon, Function);
        std::cout << "Результат, полученный методом Симпсона: ";
        std::cout << Result;
        break;
    default:
        std::cout << "Режим не был выбран." << std::endl;
        break;
    }
    return 0;
}

//Метод левых прямоугольников с постоянным шагом интегрирования
double MiddleRectangleMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfSplits, std::string Function)
{
    double H = (EndOfIntegration - BeginOfIntegration) / NumberOfSplits; //Шаг разбиения = (b - a) / n
    double Result = 0.0;
    for (int i = 0; i < NumberOfSplits; i++)
        Result += H * GetFunctionValue(BeginOfIntegration + i * H + H / 2, Function);
    return Result;
}

//Метод левых прямоугольников с автоматическим выбором шага интегрирования
double MiddleRectangleMethodWA(double BeginOfIntegration, double EndOfIntegration, double Epsilon, std::string Function)
{
    int NumberOfSplits = 2; //Число разбиений
    int Count = 0; //Счётчик количества шагов интегрирования
    double Result = 0.0;
    double Error = 1.0 + Epsilon; //Погрешность
    while (Error > Epsilon)
    {
        double OldResult = Result;
        Result = MiddleRectangleMethod(BeginOfIntegration, EndOfIntegration, NumberOfSplits, Function);
        Error = fabs(Result - OldResult);
        NumberOfSplits *= 2;
        Count++;
    }
    std::cout << "Количество шагов интегрирования: " << Count - 1 << std::endl;
    std::cout << "Итоговое число разбиений: " << NumberOfSplits / 4 << std::endl;
    return Result;
}

//Метод трапеции с постоянным шагом интегрирования
double TrapezoidMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfSplits, std::string Function)
{
    double H = (EndOfIntegration - BeginOfIntegration) / NumberOfSplits; //Шаг разбиения = (b - a) / n
    double Result = GetFunctionValue(BeginOfIntegration, Function) + GetFunctionValue(EndOfIntegration, Function); //f(a) + f(b)
    for (int i = 1; i < NumberOfSplits; i++)
        Result += 2 * GetFunctionValue(BeginOfIntegration + i * H, Function);
    return H / 2 * Result;
}

//Метод трапеции с автоматическим выбором шага интегрирования
double TrapezoidMethodWA(double BeginOfIntegration, double EndOfIntegration, double Epsilon, std::string Function)
{
    int NumberOfSplits = 2; //Число разбиений
    int Count = 0; //Счётчик количества шагов интегрирования
    double Result = 0.0;
    double Error = 1.0; //Погрешность
    while (Error > Epsilon)
    {
        double OldResult = Result;
        Result = TrapezoidMethod(BeginOfIntegration, EndOfIntegration, NumberOfSplits, Function);
        Error = fabs(Result - OldResult);
        NumberOfSplits *= 2;
        Count++;
    }
    std::cout << "Количество шагов интегрирования: " << Count - 1 << std::endl;
    std::cout << "Итоговое число разбиений: " << NumberOfSplits / 4 << std::endl;
    return Result;
}

//Метод Симпсона с постоянным шагом интегрирования
double SimpsonMethod(double BeginOfIntegration, double EndOfIntegration, int NumberOfSplits, std::string Function)
{
    if (NumberOfSplits % 2 == 1)
        NumberOfSplits += 1; //Чтобы при подсчете не "потерять" последнюю точку
    double H = (EndOfIntegration - BeginOfIntegration) / NumberOfSplits; //Шаг разбиения = (b - a) / n
    double Result = GetFunctionValue(BeginOfIntegration, Function); //f(x[i-1])
    Result += 4 * GetFunctionValue(BeginOfIntegration + H, Function); //f(x[i-1]) + 4f(x[i])
    Result += GetFunctionValue(EndOfIntegration, Function); //f(x[i-1]) + 4f(x[i]) + f(x[i+1])
    for (int i = 1; i < NumberOfSplits / 2; i++)
    {
        Result += 4 * GetFunctionValue(BeginOfIntegration + (2 * i + 1) * H, Function); //Нечётные
        Result += 2 * GetFunctionValue(BeginOfIntegration + 2 * i * H, Function); //Чётные
    }
    return H / 3 * Result;
}

//Метод Симпсона с автоматическим выбором шага интегрирования
double SimpsonMethodWA(double BeginOfIntegration, double EndOfIntegration, double Epsilon, std::string Function)
{
    int NumberOfSplits = 2; //Число разбиений, = 2 чтобы при подсчете не "потерять" последнюю точку
    int Count = 0; //Счётчик количества шагов интегрирования
    double Result = 0.0;
    double Error = 1.0; //Погрешность
    while (Error > Epsilon)
    {
        double OldResult = Result;
        Result = SimpsonMethod(BeginOfIntegration, EndOfIntegration, NumberOfSplits, Function);
        Error = fabs(Result - OldResult);
        NumberOfSplits *= 2;
        Count++;
    }
    std::cout << "Количество шагов интегрирования: " << Count - 1 << std::endl;
    std::cout << "Итоговое число разбиений: " << NumberOfSplits / 4 << std::endl;
    return Result;
}

//Получает значение введенной в аналитическом виде функции
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