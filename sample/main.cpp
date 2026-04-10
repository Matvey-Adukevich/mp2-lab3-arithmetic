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

        cout << "\n" << endl;

        TArithmeticExpression expr10("-(-1)");
        cout << "Infix: " << expr10.GetInfix() << endl;
        cout << "Postfix: " << expr10.GetPostfix() << endl;
        Expr* tree = expr10.MakeTree();
        PrintVisitor pv;
        tree->accept(&pv);
        CalcVisitor cv;
        std::cout << " RESULT: " << tree->accept(&cv) << std::endl;
        delete tree;

        cout << "\n" << endl;

        TArithmeticExpression expr2("-12+(-1+12)*4");
        cout << "Infix: " << expr2.GetInfix() << endl;
        cout << "Postfix: " << expr2.GetPostfix() << endl;
        map<string, double> values2;
        cout << "Result: " << expr2.Calculate(values2) << endl;

        cout << "\n" << endl;

        TArithmeticExpression expr20("-12+(-1+12)*4");
        cout << "Infix: " << expr20.GetInfix() << endl;
        cout << "Postfix: " << expr20.GetPostfix() << endl;
        Expr* tree2 = expr20.MakeTree();
        PrintVisitor pv2;
        tree2->accept(&pv2);
        CalcVisitor cv2;
        std::cout << " RESULT: " << tree2->accept(&cv2) << std::endl;
        delete tree2;

        cout << "\n" << endl;

        TArithmeticExpression expr3("(12+32)*4");
        cout << "Infix: " << expr3.GetInfix() << endl;
        cout << "Postfix: " << expr3.GetPostfix() << endl;
        map<string, double> values3;
        cout << "Result: " << expr3.Calculate(values3) << endl;

        TArithmeticExpression expr4("(12--32)*4");
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