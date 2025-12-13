#include <iostream>
#include "TArithmeticExpression.h"

using namespace std;

int main() {
    try {
        TArithmeticExpression expr("-(-1)");

        cout << "Infix: " << expr.GetInfix() << endl;
        cout << "Postfix: " << expr.GetPostfix() << endl;
        map<string, double> values;
        cout << "Result: " << expr.Calculate(values) << endl;

        TArithmeticExpression expr2("-12+(-1+12)*4");
        cout << "Infix: " << expr2.GetInfix() << endl;
        cout << "Postfix: " << expr2.GetPostfix() << endl;
        map<string, double> values2;
        cout << "Result: " << expr2.Calculate(values2) << endl;

        TArithmeticExpression expr3("(12+32)*4");
        cout << "Infix: " << expr3.GetInfix() << endl;
        cout << "Postfix: " << expr3.GetPostfix() << endl;
        map<string, double> values3;
        cout << "Result: " << expr3.Calculate(values3) << endl;

        TArithmeticExpression expr4("(12++32)*4");
        cout << "Infix: " << expr4.GetInfix() << endl;
        cout << "Postfix: " << expr4.GetPostfix() << endl;
        map<string, double> values4;
        cout << "Result: " << expr4.Calculate(values4) << endl;
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}