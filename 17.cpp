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

string parseStatement(vector<string> &tokens, int &i) {
    if (i < tokens.size() && tokens[i] == "if") {
        i++;

        string condition = "";
        while (i < tokens.size() && tokens[i] != "then") {
            condition += tokens[i];
            i++;
        }

        string condPost = infixToPostfix(condition);

        i++;
        string statement1 = parseStatement(tokens, i);

        i++;
        string statement2 = parseStatement(tokens, i);

        return condPost + statement1 + statement2 + "?";
    } else {
        string expression = "";
        while (i < tokens.size() && tokens[i] != "else" && tokens[i] != "then" && tokens[i] != ".") {
            expression += tokens[i];
            i++;
        }
        return infixToPostfix(expression);
    }
}

int main(){
    freopen("17.input.txt", "r", stdin);
    freopen("17.output.txt", "w", stdout);

    string line;
    getline(cin,line);

    vector<string> tokens;
    string temp = "";
    for(char ch: line){
        if(ch == ' '){
            if(!temp.empty()){ 
                tokens.push_back(temp); 
                temp=""; 
            }
        } else {
            temp+=ch;
        }
    }

    if(!temp.empty()) {
        tokens.push_back(temp);
    }

    int i=0;
    string result = parseStatement(tokens,i);

    cout << "Postfix : " << result << endl;

    return 0;
}