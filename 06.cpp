/*
Build a lexical analyzer implementing the following regular expressions:
Character variable =ch_(a-z|A-Z|0-9)(a-z|A-Z|0-9)*
Binary variable = bn_(a-z|A-Z|0-9)(a-z|A-Z|0-9)* 
Binary Number = 0(0|1)(0|1)*
Invalid Input or Undefined = Otherwise
*/

#include<bits/stdc++.h>
using namespace std;

bool validSuffix(const string &s) {
    if (!isalnum(s[3])) return false;
    for (int i = 4; i < s.size(); i++) {
        if (!isalnum(s[i])){
            return false;
        }
    }
    return true;
}

bool isCharacterVariable (const string &s) {
    if (s.size() < 4) return false;
    return (s.substr(0, 3) == "ch_" && validSuffix(s));
}

bool isBinaryVariable (const string &s) {
    if (s.size() < 4) return false;
    return (s.substr(0, 3) == "bn_" && validSuffix(s));
}

bool isBinaryNumber(const string &s) {
    if (s.size() < 2 || s[0] != '0') return false;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != '0' && s[i] != '1') return false;
    }
    return true;
}

int main(){
    freopen("06.input.txt", "r", stdin);
    freopen("06.output.txt", "w", stdout);

    string token;
    while (cin >> token) {
        if (isCharacterVariable(token)) {
            cout << token << " : Character Variable\n";
        } else if (isBinaryVariable(token)) {
            cout << token << " : Binary Variable\n";
        } else if (isBinaryNumber(token)) {
            cout << token << " : Binary Number\n";
        } else {
            cout << token << " : Invalid/Undefined\n";
        }
    }
    
    return 0;
}