#include <iostream>
#include "TArithmeticExpression.h"

using namespace std;

int main() {
    try {
        TArithmeticExpression expr("(12+32)*4");

        cout << "Infix: " << expr.GetInfix() << endl;
        cout << "Postfix: " << expr.GetPostfix() << endl;

        // Для числового выражения values может быть пустым
        map<string, double> values;
        cout << "Result: " << expr.Calculate(values) << endl;

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}