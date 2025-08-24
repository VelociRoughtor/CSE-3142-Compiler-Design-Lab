/*
    Write a program to recognize C++
    i) Keyword 
    ii) Identifier 
    iii) Operator 
    iv) Constant
*/

#include<bits/stdc++.h>
using namespace std;

unordered_set<string> keywords = {
    "int",
    "float",
    "double",
    "char",
    "if",
    "else",
    "while",
    "for",
    "do",
    "return",
    "break",
    "continue",
    "switch",
    "case",
    "default",
    "void",
    "long",
    "short",
    "signed",
    "unsigned",
    "static",
    "const",
    "struct",
    "class",
    "public",
    "private",
    "protected",
    "virtual",
    "true",
    "false",
    "bool",
    "namespace",
    "using",
    "new",
    "delete"
};

unordered_set<string> operators = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "=",
    "==",
    "!=",
    "<",
    ">",
    "<=",
    ">=",
    "&&",
    "||",
    "!",
    "++",
    "--",
    "+=",
    "-=",
    "*=",
    "/=",
    "%="
};

bool isIdentifier(const string &s) {
    if (!isalpha(s[0]) && s[0] != '_') {
        return false;
    }
    for (int i = 1; i < s.size(); i++) {
        if (!isalnum(s[i]) && s[i] != '_') {
            return false;
        }
    }
    return true;
}

bool isIntegerConstant(const string &s) {
    if (s.empty()) return false;
    for (char c: s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isFloatConstant(const string &s) {
    int dot = s.find('.');
    if (dot == string::npos) return false;
    if (dot == 0 || dot == (int)s.size() - 1) return false; 
    for (int i = 0; i < s.size(); i++) {
        if (i == dot) continue;
        if (!isdigit(s[i])) return false;
    }
    return true;
}


bool isCharConstant(const string &s) {
    return (s.size() == 3 && s[0] == '\'' && s[2] == '\'');
}

bool isStringConstant(const string &s) {
    return (s.size() >= 2 && s.front() == '"' && s.back() == '"');
}

bool isConstant(const string &s) {
    return (isIntegerConstant(s) || (isFloatConstant(s)) || isCharConstant(s) || isStringConstant(s));
}

int main(){
    freopen("07.input.txt", "r", stdin);
    freopen("07.output.txt", "w", stdout);

    string token;

    while (cin >> token) {
        if (keywords.count(token)) {
            cout << token << " : Keyword\n";
        } 
        else if (operators.count(token)) {
            cout << token << " : Operator\n";
        } 
        else if (isConstant(token)) {
            cout << token << " : Constant\n";
        } 
        else if (isIdentifier(token)) {
            cout << token << " : Identifier\n";
        } 
        else {
            cout << token << " : Invalid/Undefined\n";
        }
    }
    return 0;
}