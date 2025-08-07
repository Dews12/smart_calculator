#include <iostream>
#include <stack>
#include <cctype>
#include <cstdlib> 

using namespace std;


struct Exp
{
    char type;
    double val;
};

int Calc(stack<Exp>& Stack_dig, stack<Exp>& Stack_op, Exp& subject) {
    double a, b, c;
    a = Stack_dig.top().val;
    Stack_dig.pop();
    switch (Stack_op.top().type) {
    case '+':
        b = Stack_dig.top().val;
        Stack_dig.pop();
        c = a + b;
        subject.type = '0';
        subject.val = c;
        Stack_dig.push(subject);
        Stack_op.pop();
        break;

    case '-':
        b = Stack_dig.top().val;
        Stack_dig.pop();
        c = b - a;
        subject.type = '0';
        subject.val = c;
        Stack_dig.push(subject);
        Stack_op.pop();
        break;

    case '*':
        b = Stack_dig.top().val;
        Stack_dig.pop();
        c = a * b;
        subject.type = '0';
        subject.val = c;
        Stack_dig.push(subject);
        Stack_op.pop();
        break;

    case '/':
        b = Stack_dig.top().val;
        if (a == 0) {
            cout << "\nDivision by zero" << endl;
            return 1;
        }
        else {

            Stack_dig.pop();
            c = b / a;
            subject.type = '0';
            subject.val = c;
            Stack_dig.push(subject);
            Stack_op.pop();
            break;
        }
    default:
        cout << "\nReading error" << endl;
        return 1;
        break;
    }

    return 0;
}

int priority(char Ch) {
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/') return 2;
    return 0;
}


int main()
{
    char Ch;
    double value;
    int negative = 1;

    stack<Exp> Stack_dig;
    stack<Exp> Stack_op;
    Exp subject;

    while (1) {
        Ch = cin.peek();
        int next = Ch;
        if (Ch == '\n' || next == EOF) break;
        if (isspace(Ch)) {
            cin.ignore();
            continue;
        }
        if (Ch >= '0' && Ch <= '9' || Ch == '-' && negative == 1) {
            subject.type = '0';
            cin >> subject.val;
            Stack_dig.push(subject);
            negative = 0;
            continue;
        }
        if (Ch == '+'  || Ch == '-' && negative == 0 || Ch == '*' || Ch == '/') {
            if (Stack_op.size() == 0) {
                subject.type = Ch;
                subject.val = 0;
                Stack_op.push(subject);
                cin.ignore();
                continue;
            }
            if (Stack_op.size() != 0 && priority(Ch) > priority(Stack_op.top().type)) {
                subject.type = Ch;
                subject.val = 0;
                Stack_op.push(subject);
                cin.ignore();
                continue;
            }
            if (Stack_op.size() != 0 && priority(Ch) <= priority(Stack_op.top().type)) {
                if (Calc(Stack_dig, Stack_op, subject) == 1) { return 1; }
                continue;
            }

        }
        if (Ch == '(') {
            subject.type = Ch;
            subject.val = 0;
            Stack_op.push(subject);
            cin.ignore();
            negative = 1;
            continue;
        }
        if (Ch == ')') {
            while (Stack_op.top().type != '(') {
                if (Calc(Stack_dig, Stack_op, subject) == 1) { return 1; }
                else continue;
            }
            Stack_op.pop();
            cin.ignore();
            continue;
        }
        else {
            cout << "\nIncorrect input" << endl;
            return 1;
        }

    };

    while (Stack_op.size() != 0) {
        if (Calc(Stack_dig, Stack_op, subject) == 1) {
            return 1;
        }
        else continue;
    }
    cout << "Result: " << Stack_dig.top().val << endl;
    return 0;
}