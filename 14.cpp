#include<bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
vector<char> order;
map<char, set<char>> FIRST;
map<char, set<char>> FOLLOW;
set<char> visited;

void computeFIRST(char symbol) {
    if (visited.count(symbol)) return;
    
    visited.insert(symbol);
    for (string rhs: grammar[symbol]) {
        for (int i = 0; i < rhs.size(); i++) {
            char ch = rhs[i];

            // Case-1: terminal -> directly add
            if (!isupper(ch)) {
                FIRST[symbol].insert(ch);
                break;
            }

            // Case-2: nonterminal ->compute(first(nonterminal))
            computeFIRST(ch);
            
            bool hasEpsilon = false;
            for (char f: FIRST[ch]) {
                if (f == '@') hasEpsilon = true;
                else FIRST[symbol].insert(f);
            }
            if (!hasEpsilon) break;
            if (i == rhs.size() - 1) FIRST[symbol].insert('@');
        }
    }
}

void computeFOLLOW() {
    // Rule-1: start symbol gets $
    FOLLOW[order[0]].insert('$');

    bool changed = true;
    while (changed) {
        changed = false; // reset each pass

        for (auto &pr : grammar) {
            char lhs = pr.first;
            for (string rhs : pr.second) {
                for (int i = 0; i < rhs.size(); i++) {
                    char B = rhs[i];
                    if (!isupper(B)) continue; // only nonterminals

                    bool epsilonFound = true;
                    for (int j = i + 1; j < rhs.size(); j++) {
                        char next = rhs[j];
                        epsilonFound = false;

                        if (!isupper(next)) {
                            // next is terminal
                            if (!FOLLOW[B].count(next)) {
                                FOLLOW[B].insert(next);
                                changed = true;
                            }
                            break;
                        }

                        // Add FIRST(next) except epsilon
                        for (char f : FIRST[next]) {
                            if (f != '@' && !FOLLOW[B].count(f)) {
                                FOLLOW[B].insert(f);
                                changed = true;
                            }
                        }

                        if (FIRST[next].count('@')) {
                            epsilonFound = true;
                        } else break;
                    }

                    // If B is at the end or β ⇒ ε
                    if (epsilonFound || i == rhs.size() - 1) {
                        for (char f : FOLLOW[lhs]) {
                            if (!FOLLOW[B].count(f)) {
                                FOLLOW[B].insert(f);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("14.input.txt", "r", stdin);
    freopen("14.output.txt", "w", stdout);

    vector<char> terminal;
    string line;
    while(getline(cin, line)) {
        auto pos = line.find("->");
        if (pos == string::npos) continue;
        char lhs = line[0];
        string rhs = line.substr(pos + 2);
        string temp;
        for (char c: rhs) {
            if (c != ' ' && c != '\t' && c != '\r') {
                temp.push_back(c);
                if (!isupper(c)) terminal.push_back(c);
            }
        }
        grammar[lhs].push_back(temp);
        if (find(order.begin(), order.end(), lhs) == order.end()) order.push_back(lhs);
    }
    
    cout << "==== Parsed Grammar ====\n";
    for (char A: order) {
        cout << A << " -> ";
        for (int i = 0; i < grammar[A].size(); i++) {
            if (i) cout << " | ";
            cout << grammar[A][i];
        }
        cout << '\n';
    }
    cout << endl;


    // ==== FIRST Calculation ====
    for (char nt: order) {
        computeFIRST(nt);
    }
    cout << "==== FIRST Sets ====\n";
    for (char nt: order) {
        cout << "FIRST(" << nt << ") = {";
        int cnt = 0;
        for (char c: FIRST[nt]) {
            if (cnt) cout << ", ";
            cout << c;
            cnt++;
        }
        cout << "}\n";
    }
    cout << endl;


    // ==== FOLLOW Calculation ==== 
    cout << "==== FOLLOW Sets ====\n";
    computeFOLLOW();
    for (char nt: order) {
        cout << "FOLLOW(" << nt << ") = {";
        int cnt = 0;
        for (char c: FOLLOW[nt]) {
            if (cnt) cout << ", ";
            cout << c;
            cnt++;
        }
        cout << "}\n";
    }

    cout << "\n==== LL(1) Parsing Table ====\n";
    // step-1: collect all terminals except epsilon
    set<char> terminals;
    for (auto &p: grammar) {
        for (auto &rhs: p.second) {
            for (auto &c: rhs) {
                if (c != '@' && !isupper(c)) terminals.insert(c); 
            }
        }
    }
    terminals.insert('$');

    // step-2: build the parsing table
    map<pair<char, char>, string> parsingTable;
    for (auto &p: grammar) {
        char lhs = p.first;
        for (string &rhs: p.second) {
            set<char> firstAlpha;
            bool epsilonPossible = true;
            for (int i = 0; i < rhs.size(); i++) {
                char x = rhs[i];

                if (!isupper(x)) {
                    firstAlpha.insert(x);
                    epsilonPossible = false;
                    break;
                }

                for (char f: FIRST[x]) {
                    if (f != '@') firstAlpha.insert(f);
                }

                if (FIRST[x].find('@') == FIRST[x].end()) {
                    epsilonPossible = false;
                    break;
                }
            }
            if (epsilonPossible) firstAlpha.insert('@');

            // Rule 1: for each terminal in FIRST(alpha)
            for (char a: firstAlpha) {
                if (a != '@') {
                    parsingTable[{lhs, a}] = string(1, lhs) + " -> " + rhs;
                }
            }

            // Rule 2: if @ belongs to first alpha
            if (firstAlpha.find('@') != firstAlpha.end()) {
                for (char b: FOLLOW[lhs]) {
                    parsingTable[{lhs, b}] = string(1, lhs) + " -> @";
                }
            }
        }
    }

    // step-3: print LL(1) parsing table
    vector<char> termVec(terminals.begin(), terminals.end());
    int colWidth = 10;
    string horizontalLine = "+" + string(colWidth - 1, '-');
    for (int i = 0; i < termVec.size(); i++) horizontalLine += "+" + string(colWidth - 1, '-');
    horizontalLine += "+";

    // Print header
    cout << horizontalLine << "\n";
    cout << "|" << setw(colWidth - 1) << left << " ";
    for (char t : termVec) cout << "|" << setw(colWidth - 1) << left << t;
    cout << "|\n" << horizontalLine << "\n";

    // Print each row
    for (char A : order) {
        cout << "|" << setw(colWidth - 1) << left << A;
        for (char t : termVec) {
            auto key = make_pair(A, t);
            string cell = (parsingTable.find(key) != parsingTable.end()) ? parsingTable[key] : " ";
            cout << "|" << setw(colWidth - 1) << left << cell;
        }
        cout << "|\n" << horizontalLine << "\n";
    }

    return 0;
}