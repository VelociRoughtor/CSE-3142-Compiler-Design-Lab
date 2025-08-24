/*
Build a lexical analyzer implementing the following regular expressions:
Float variable = (a-h|A-H|o-z|O-Z)(a-z|A-Z|0-9)*
Float Number   = 0.(0-9)(0-9)|(1-9)(0-9)*.(0-9)(0-9)
Double Number  = 0.(0-9)(0-9)(0-9)+|(1-9)(0-9)*.(0-9)(0-9)(0-9)+
Invalid Input or Undefined = Otherwise
*/

#include <bits/stdc++.h>
using namespace std;

bool isFloatVariable(const string &s) {
    if (s.empty()) return false;

    if (!isalpha(s[0]) || (tolower(s[0]) >= 'i' && tolower(s[0]) <= 'n')) {
        return false;
    }

    for (int i = 1; i < (int)s.size(); i++) {
        if (!isalnum(s[i])) return false;
    }
    return true;
}

bool isFloatNumber(const string &s) {
    int dot = s.find('.');
    if (dot == string::npos) return false;

    string integerPart = s.substr(0, dot);
    string fractionPart = s.substr(dot + 1);

    if (fractionPart.size() != 2) return false;
    for (char c : fractionPart) {
        if (!isdigit(c)) return false;
    }

    if (integerPart == "0") return true;
    if (integerPart[0] >= '1' && integerPart[0] <= '9') {
        for (char c : integerPart.substr(1)) {
            if (!isdigit(c)) return false;
        }
        return true;
    }
    return false;
}

bool isDoubleNumber(const string &s) {
    int dot = s.find('.');
    if (dot == string::npos) return false;

    string integerPart = s.substr(0, dot);
    string fractionPart = s.substr(dot + 1);

    if (fractionPart.size() < 3) return false;
    for (char c : fractionPart) {
        if (!isdigit(c)) return false;
    }

    if (integerPart == "0") return true;
    if (integerPart[0] >= '1' && integerPart[0] <= '9') {
        for (char c : integerPart.substr(1)) {
            if (!isdigit(c)) return false;
        }
        return true;
    }
    return false;
}

int main() {
    freopen("05.input.txt", "r", stdin);
    freopen("05.output.txt", "w", stdout);

    string token;
    while (cin >> token) {
        if (isFloatVariable(token)) {
            cout << token << " : Float Variable\n";
        } else if (isFloatNumber(token)) {
            cout << token << " : Float Number\n";
        } else if (isDoubleNumber(token)) {
            cout << token << " : Double Number\n";
        } else {
            cout << token << " : Invalid/Undefined\n";
        }
    }

    return 0;
}
