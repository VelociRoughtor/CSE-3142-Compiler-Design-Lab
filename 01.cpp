/*
Write a C program that read the following string:
“Md. Tareq Zaman, Part-3, 2011”
a) Count number of words, letters, digits and other characters.
b) Separates letters, digits and others characters.
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("01.input.txt", "r", stdin);
    freopen("01.output.txt", "w", stdout);
    string input;
    getline(cin, input);

    int letters = 0, digits = 0, others = 0, words = 0;
    string lettersOnly = "", digitsOnly = "", othersOnly = "";
    bool flag = false;

    for (char c: input) {
        if (isalpha(c)) {
            letters++;
            lettersOnly += c;
            if (!flag) {
                words++;
                flag = true;
            }
        } else if (isdigit(c)) {
            digits++;
            digitsOnly += c;
            if (!flag) {
                words++;
                flag = true;
            }
        } else {
            others++;
            if (!isspace(c)) {
                othersOnly += c;
            }
            flag = false;
        }
    }

    cout << "Number of words: " << words << endl;
    cout << "Number of letters: " << letters << endl;
    cout << "Number of digits: " << digits << endl;
    cout << "Number of other characters: " << others << endl;

    cout << "\nThe letters are: " << lettersOnly << endl;
    cout << "The digits are: " << digitsOnly << endl;
    cout << "The other characters are: " << othersOnly << endl;

    return 0;
}