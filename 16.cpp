#include<bits/stdc++.h>
using namespace std;

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*': 
        case '/': return 2;
        case '+':
        case '-': return 1;
        default : return 0;
    }
}

bool isRightAssociative(char op) {
    return (op == '^');
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

string infixToPostfix(string infix) {
    string postfix = "";
    stack<char> stk;

    for (char ch : infix) {
        if (ch == ' ') continue;
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            stk.push(ch);
        } else if (ch == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            if (!stk.empty()) stk.pop();
        } else if (isOperator(ch)) {
            while (!stk.empty() && isOperator(stk.top())) {
                if ((isRightAssociative(ch) && precedence(ch) < precedence(stk.top())) || 
                    !isRightAssociative(ch) && precedence(ch) <= precedence(stk.top())) {
                        postfix += stk.top();
                        stk.pop();
                } else {
                    break;
                }
            }
            stk.push(ch);
        }
    }
    while(!stk.empty()){
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}

int main(){
    freopen("16.input.txt", "r", stdin);
    freopen("16.output.txt", "w", stdout);

    string infix;
    getline(cin, infix);

    cout << "Enter infix expression : " << infix << endl;

    string postfix = infixToPostfix(infix);
    cout << "Postfix : " << postfix << endl;

    return 0;
}