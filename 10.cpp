#include <bits/stdc++.h>
using namespace std;

map<string, string> rules;
string stk = "", input;

void reduce() {
    bool reduced = true;
    while(reduced) {
        reduced = false;
        for (auto [lhs, rhs] : rules) {
            size_t pos = stk.rfind(lhs); 
            if (pos != string::npos) {
                stk.erase(pos, lhs.size());
                stk += rhs;
                cout << left << setw(15) << ('$' + stk)
                     << left << setw(15) << (input + '$')
                     << "Reduce " << lhs << " -> " << rhs << "\n";
                reduced = true;
                break;
            }
        }
    }
}

int main() {
    freopen("10.input.txt", "r", stdin);
    freopen("10.output.txt", "w", stdout);
    int n; 
    cin >> n; 
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string production;
        getline(cin, production);
        rules[production.substr(3)] = production[0]; 
    }

    cin >> input;

    cout << left << setw(15) << "Stack"
         << left << setw(15) << "Input"
         << "Action\n";

    cout << left << setw(15) << ('$' + stk)
         << left << setw(15) << (input + '$') 
         << "\n";

    while(!input.empty()) {
        stk += input[0];
        input.erase(0, 1);

        cout << left << setw(15) << ('$' + stk)
             << left << setw(15) << (input + '$')
             << "Shift " << stk.back() << "\n";

        reduce();
    }

    return 0;
}
