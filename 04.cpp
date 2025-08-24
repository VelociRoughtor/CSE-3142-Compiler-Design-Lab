/*
Build a lexical analyzer implementing the following regular expressions:
Integer variable = (i-n|I-N)(a-z|A-Z|0-9)*
ShortInt Number = (1-9)|(1-9)(0-9)|(1-9)(0-9)(0-9)|(1-9)(0-9)(0-9)(0-9)
LongInt Number = (1-9)(0-9)(0-9)(0-9)(0-9)+
Invalid Input or Undefined = Otherwise
*/

#include<bits/stdc++.h>
using namespace std;

bool isIntegerVariable(const string &s) {
    if (s.empty()) return false;
    char first = tolower(s[0]);
    if (first < 'i' || first > 'n') return false;
    for (int i = 1; i < s.size(); i++) {
        if (!isalnum(s[i])) {
            return false;
        }
    }
    return true;
}

bool isShortInteger(const string &s) {
    if (s.empty()) return false;
    if (!isdigit(s[0]) || s[0] == '0') return false;
    if (s.size() > 4) return false;
    for (char c: s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isLongInteger(const string &s) {
    if (s.empty()) return false;
    if (!isdigit(s[0]) || s[0] == '0') return false;
    if (s.size() < 5) return false;
    for (char c: s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main(){
    freopen("04.input.txt", "r", stdin);
    freopen("04.output.txt", "w", stdout);
    string token;
    
    while (cin >> token) {
        if (isIntegerVariable(token)) {
            cout << token << " : Integer Variable\n";
        } else if (isShortInteger(token)) {
            cout << token << " : Short Integer Number\n";
        } else if (isLongInteger(token)) {
            cout << token << " : Long Integer Number\n";
        } else {
            cout << token << " : Invalid Input or Undefined\n";
        }
    } 
    return 0;
}