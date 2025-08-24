/*
Write a program which converts a word of C++ program to its equivalent token.
RESULT:
Input: 646.45
Output: Float
Input: do
Output: Keyword
Input: 554
Output: Integer
Input: abc
Output: Identifier
Input: +
Output: Arithmetic Operator
*/
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
    "auto","break","case","char","const","continue","default","do","double",
    "else","enum","extern","float","for","goto","if","int","long","register",
    "return","short","signed","sizeof","static","struct","switch","typedef",
    "union","unsigned","void","volatile","while","class","public","private",
    "protected","virtual","template","this","namespace","using","new","delete",
    "try","catch","throw","inline","friend","operator","true","false","nullptr"
};

unordered_set<string> arithmetic_operator = {"+","-","*","/","%"};
unordered_set<string> relational_operator = {"==","!=","<",">","<=",">="};
unordered_set<string> logical_operator = {"&&","||","!"};
unordered_set<string> bitwise_operator = {"&","|","^","~","<<",">>"};
unordered_set<string> assignment_operator = {
    "=","+=","-=","*=","/=","%=","&=","|=","^=","<<=",">>="
};
unordered_set<string> increment_operator = {"++","--"};

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
    return (s.size() >= 3 && s.front() == '\'' && s.back() == '\'');
}

bool isStringConstant(const string &s) {
    return (s.size() >= 2 && s.front() == '"' && s.back() == '"');
}

bool isConstant(const string &s) {
    return isIntegerConstant(s) || isFloatConstant(s) || isCharConstant(s) || isStringConstant(s);
}

string operatorType(const string &s) {
    if (arithmetic_operator.count(s)) return "Arithmetic Operator";
    if (relational_operator.count(s)) return "Relational Operator";
    if (logical_operator.count(s)) return "Logical Operator";
    if (bitwise_operator.count(s)) return "Bitwise Operator";
    if (assignment_operator.count(s)) return "Assignment Operator";
    if (increment_operator.count(s)) return "Increment/Decrement Operator";
    return "";
}

int main(){
    freopen("08.input.txt", "r", stdin);
    freopen("08.output.txt", "w", stdout);

    string token;

    while (cin >> token) {
        cout << "Input: " << token << "\n";
        if (keywords.count(token)) {
            cout << "Output: Keyword\n\n";
        } 
        else if (!operatorType(token).empty()) {
            cout << "Output: " << operatorType(token) << "\n\n";
        } 
        else if (isConstant(token)) {
            if (isIntegerConstant(token)) cout << "Output: Integer\n\n";
            else if (isFloatConstant(token)) cout << "Output: Float\n\n";
            else if (isCharConstant(token)) cout << "Output: Character\n\n";
            else cout << "Output: String\n\n";
        } 
        else if (isIdentifier(token)) {
            cout << "Output: Identifier\n\n";
        } 
        else {
            cout << "Output: Invalid/Undefined\n\n";
        }
    }
    return 0;
}