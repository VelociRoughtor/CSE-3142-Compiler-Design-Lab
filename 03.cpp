/*
Write a program that abbreviates the following code:
CSE-3141 as Computer Science & Engineering, 3rd year, 1st semester, Compiler Design, Theory.
*/

#include <bits/stdc++.h>
using namespace std;

void printAbbreviation(const string &input, const string &deptName, const string &courseCode) {
    map<string, string> departments = {
        {"CSE", "Computer Science & Engineering"},
        {"ICE", "Information & Communication Engineering"}
    };

    map<char, string> year = {
        {'1', "1st"},
        {'2', "2nd"},
        {'3', "3rd"},
        {'4', "4th"}
    };

    map<char, string> semester = {
        {'1', "1st"},
        {'2', "2nd"}
    };

    map<char, string> subject = {
        {'1', "Software Engineering"},
        {'2', "Database Management Systems"},
        {'3', "Web Engineering"},
        {'4', "Compiler Design"},
        {'5', "Engineering Ethics and Environmental Protection"},
        {'6', "Communication Engineering"}
    };

    map<char, string> course = {
        {'1', "Theory"},
        {'2', "Lab"}
    };

    cout << input << " : "
        << departments[deptName] << ", "
        << year[courseCode[0]] << " year, "
        << semester[courseCode[1]] << " semester, "
        << subject[courseCode[2]] << ", "
        << course[courseCode[3]] << endl;
}

int main() {
    freopen("03.input.txt", "r", stdin);
    freopen("03.output.txt", "w", stdout);
    string input;

    while (cin >> input) {
        string deptName = "", courseCode = "";
        int i = 0;
        while (i < input.size() && input[i] != '-') {
            deptName += input[i];
            i++;
        }
        if (i < input.size())
        courseCode = input.substr(i + 1);
        printAbbreviation(input, deptName, courseCode);
    }

    return 0;
}
