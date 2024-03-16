#include <iostream>
#include <cmath>
#include "exprtk.hpp"
#include <vector>

std::vector<std::vector<double>> GetTableByFunction(std::vector<double> Arguments, std::string ExpressionString);
std::vector<exprtk::expression<double>> MakeExpressionTable(std::vector<exprtk::symbol_table<double>> SymbolTable,
    std::string ExpressionString, int Size);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    return 0;
}

//Получает таблицу по введенной в аналитическом виде функции
std::vector<std::vector<double>> GetTableByFunction(std::vector<double> Arguments, std::string ExpressionString)
{
    std::vector<exprtk::symbol_table<double>> SymbolTable(Arguments.size());
    for (int i = 0; i < Arguments.size(); i++) { //Заполнение таблицы символов
        SymbolTable[i].add_variable("x", Arguments[i]);
        SymbolTable[i].add_function("abs", abs);
        SymbolTable[i].add_function("sqrt", sqrt);
        SymbolTable[i].add_function("exp", exp);
    }
    //Создаются выражения, вычисляются значения функции
    std::vector<exprtk::expression<double>> Expression = MakeExpressionTable(SymbolTable, ExpressionString, Arguments.size());
    std::vector<std::vector<double>> Table(2, std::vector<double>(Arguments.size()));
    // Заполняет таблицу аргументами и значениями функции
    for (int i = 0; i < Arguments.size(); i++)
    {
        Table[0][i] = Arguments[i];
        Table[1][i] = Expression[i].value();
    }
    return Table;
}

//Создает выражения, вычисляются значения функции
std::vector<exprtk::expression<double>> MakeExpressionTable(std::vector<exprtk::symbol_table<double>> SymbolTable,
    std::string ExpressionString, int Size)
{
    //Создается вектор выражений заданного размера
    std::vector<exprtk::expression<double>> Expression(Size);
    for (int i = 0; i < Size; i++)
        Expression[i].register_symbol_table(SymbolTable[i]);
    //Компилируется каждое выражение с помощью парсера
    exprtk::parser<double> Parser;
    for (int i = 0; i < Size; i++)
        if (!Parser.compile(ExpressionString, Expression[i]))
            std::cout << "Ошибка в выражении!\n";
    return Expression; //Возвращается вектор скомпилированных выражений
}
