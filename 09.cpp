/*
Write a program that will check an English sentence given in present indefinite form 
to justify whether it is syntactically valid or invalid according to the following Chomsky 
Normal Form: 
S -> SUB PRED 
SUB -> PN | P 
PRED -> V | V N 
PN -> Sagor | Selim | Salma | Nipu 
P -> he | she | i | we | you | they 
N -> book | cow | dog | home | grass | rice | mango 
V -> read | eat | take | run | write
*/

#include<bits/stdc++.h>
using namespace std;

set<string> PN = {"Sagor", "Selim", "Salma", "Nipu"};
set<string> P = {"he", "she", "I", "we", "you", "they"};
set<string> N = {"book", "cow", "dog", "home", "grass", "rice", "mango"};
set<string> V = {"read", "eat", "take", "run", "write"};

bool validity(vector<string> &sentence) {
    if (sentence.size() < 2 || sentence.size() > 3) return false;
    
    string sub = sentence[0];
    string verb = sentence[1];

    if (sentence.size() == 2) {
        return ((PN.count(sub) || PN.count(sub)) && V.count(verb));
    } else if (sentence.size() == 3) {
        string noun = sentence[2];
        return ((PN.count(sub) || PN.count(sub)) && V.count(verb) && N.count(noun));
    }
    return false;
}

void print(vector<string> &sentence) {
    for (auto word: sentence) {
        cout << word << " ";
    }
}

int main(){
    freopen("09.input.txt", "r", stdin);
    freopen("09.output.txt", "w", stdout);

    string line;

    while(getline(cin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        vector<string> sentence;
        string word;

        while(ss >> word) {
            sentence.push_back(word);
        }

        print(sentence);

        if (validity(sentence)) {
            cout << ": Valid sentence\n";
        } else {
            cout << ": Invalid sentence\n";
        }
    }

    return 0;
}