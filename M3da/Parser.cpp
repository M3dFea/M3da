#include "Parser.h"
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '^') {
        return 3;
    }
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    case '^': return pow(a, b);
    }
    return 0;
}



double evaluate(string expression)
{
    stack<double> values;
    stack<char> ops;
    bool bExp = false;
    for (int i = 0; i < expression.length(); i++) {
        bExp = false;
        if (expression[i] == ' ') {
            continue;
        }
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        else if (isdigit(expression[i]) ||
            expression[i] == '.' ||
            expression[i] == 'e' ||
            expression[i] == 'E') {

            double val = 0;
            char Num[] = "          ";
            int iNC = 0;
            while (i < expression.length() && (isdigit(expression[i]) ||
                expression[i] == '.' ||
                (expression[i] == '+' && bExp) ||
                (expression[i] == '-' && bExp) ||
                expression[i] == 'e' ||
                expression[i] == 'E'))

            {
                if ((expression[i] == 'e' || expression[i] == 'E'))
                    bExp = true;
                else
                    bExp = false;
                Num[iNC] = expression[i];
                iNC++;
                i++;
            }
            val = atof(Num);
            values.push(val);
            cout << Num << endl;
            bExp = false;
            i--;
        }
        else if (expression[i] == ')') {
            while (ops.top() != '(') {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop();
        }
        else if (expression[i] == '^') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
        else {
            if (values.empty())
            {
                return(0); //error
            }
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }
    if (values.empty())
    {
        return(0);   //error
    }
    while (!ops.empty()) {
        double val2 = values.top();
        values.pop();
        double val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}
