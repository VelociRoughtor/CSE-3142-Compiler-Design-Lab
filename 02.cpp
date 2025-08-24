/*
Write a program that read the following string:
“Munmun is the student of Computer Science & Engineering”.
a) Count how many vowels and Consonants are there?
b) Find out which vowels and consonants are existed in the above string?
c) Divide the given string into two separate strings, where one string only contains 
the words started with vowel, and another contains the words started with consonant.
*/

#include <bits/stdc++.h>
using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main() {
    freopen("02.input.txt", "r", stdin);
    freopen("02.output.txt", "w", stdout);
    string input;
    getline(cin, input);

    int vowelCount = 0, consonantCount = 0;
    string vowels = "", consonants = "";
    string vowelWords = "", consonantWords = "";
    string word = "";

    set<char> uniqueVowels, uniqueConsonants;

    for (char c : input) {
        if (isalpha(c)) {
            if (isVowel(c)) {
                vowelCount++;
                vowels += c;
                uniqueVowels.insert(tolower(c));
            } else {
                consonantCount++;
                consonants += c;
                uniqueConsonants.insert(tolower(c));
            }
            word += c;
        } 
        else {
            if (!word.empty()) {
                if (isVowel(word[0]))
                    vowelWords += word + " ";
                else
                    consonantWords += word + " ";
                word = "";
            }
        }
    }

    if (!word.empty()) {
        if (isVowel(word[0]))
            vowelWords += word + " ";
        else
            consonantWords += word + " ";
    }

    cout << "\nsolution of a:\n";    
    cout << "Number of vowels: " << vowelCount << endl;
    cout << "Number of consonants: " << consonantCount << endl;

    cout << "\nsolution of b:\n";
    cout << "The vowels are: " << vowels << endl;
    cout << "Unique vowels present: ";
    for (char v : uniqueVowels) cout << v << " ";
    cout << endl;
    cout << "The consonants are: " << consonants << endl;
    cout << "Unique consonants present: ";
    for (char c : uniqueConsonants) cout << c << " ";
    cout << endl;

    cout << "\nsolution of c:\n"; 
    cout << "Words starting with vowel: " << vowelWords << endl;
    cout << "Words starting with consonant: " << consonantWords << endl;

    return 0;
}
