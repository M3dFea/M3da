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

bool isOp(char op)
{
    switch (op) {
    case '+': return (true);
    case '-': return (true);
    case '*': return (true);
    case '/': return (true);
    case '^': return (true);
    }
    return (false);
}

bool isOp2(char op)
{
    switch (op) {
    case '+': return (true);
    case '-': return (true);
    case '*': return (true);
    case '/': return (true);
    case '^': return (true);
    case '(': return (true);
    case 'e': return (true);
    case 'E': return (true);
    }
    return (false);
}

//Check to see if the operator is actually meant
//to part os the number i.e -1.2 or +1.2
//                          (-1.2.....
//                          *(-1.2.....
//                          ^(-1.2+2....
// 
bool isPartofNumber(string expression, int iC )
{
    int i;
    bool brc = false;
    if ((expression[iC] == '+') || (expression[iC] == '-'))
    {
        if (iC == 0)
        {
            brc = true;
        }
        else if (iC>0)
        {
            if (isOp2(expression[iC-1])==true)
                brc = true;
        }
    }
    return (brc);
}

double evaluate(string expression)
{
    stack<double> values;
    stack<char> ops;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;
        }
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        else if (isdigit(expression[i]) ||
                 isPartofNumber(expression, i) ||
                 expression[i] == '.') 
        {

            double val = 0;
            char Num[] = "                    ";
            int iNC = 0;
            while (i < expression.length() && 
                  (isdigit(expression[i]) ||
                   isPartofNumber(expression, i) ||
                   expression[i] == '.' ||
                   expression[i] == 'e' ||
                   expression[i] == 'E'))

            {
                Num[iNC] = expression[i];
                iNC++;
                i++;
            }
            val = atof(Num);
            values.push(val);
            //cout << Num << endl;
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
        else {
            if (values.empty())
            {
                return(0); //error
            }
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                if (values.size() < 2)
                    return(0); //error
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (isOp(expression[i]))
              ops.push(expression[i]);
        }
    }
    if (values.empty())
    {
        return(0);   //error
    }
    while (!ops.empty()) {
        if (values.size() < 2)
            return(0); //error
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
