/*
    10. Write a program to implement a shift reducing parsing. 
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("10.input.txt", "r", stdin);
    freopen("10.output.txt", "w", stdout);

    vector<string> input;
    string token;
    while (cin >> token) input.push_back(token);
    input.push_back("$");

    vector<string> stack;
    int i = 0, step = 1;

    int stepWidth = 8, stackWidth = 50, inputWidth = 50, actionWidth = 30;

    auto printLine = [&]() {
        cout << "+" << string(stepWidth,'-')
             << "+" << string(stackWidth,'-')
             << "+" << string(inputWidth,'-')
             << "+" << string(actionWidth,'-') << "+\n";
    };

    auto printRow = [&](int step, vector<string>& stack, vector<string>& input, int i, string action) {
        string stackStr, inputStr;
        for (auto &s : stack) stackStr += s + " ";
        for (int j = i; j < input.size(); j++) inputStr += input[j] + " ";
        cout << "| " << setw(stepWidth-1) << left << step
             << "| " << setw(stackWidth-1) << left << stackStr
             << "| " << setw(inputWidth-1) << left << inputStr
             << "| " << setw(actionWidth-1) << left << action
             << "|\n";
    };

    printLine();
    cout << "| " << setw(stepWidth-1) << left << "Step"
         << "| " << setw(stackWidth-1) << left << "Stack"
         << "| " << setw(inputWidth-1) << left << "Input"
         << "| " << setw(actionWidth-1) << left << "Action"
         << "|\n";
    printLine();

    while (true) {
        bool reduced = false;

        if (stack.size() >= 3) {
            if (stack[stack.size()-3] == "E" && stack[stack.size()-2] == "+" && stack[stack.size()-1] == "E") {
                stack.pop_back(); stack.pop_back(); stack.pop_back();
                stack.push_back("E");
                printRow(step++, stack, input, i, "Reduce: E → E+E");
                reduced = true;
            }
            else if (stack[stack.size()-3] == "E" && stack[stack.size()-2] == "*" && stack[stack.size()-1] == "E") {
                stack.pop_back(); stack.pop_back(); stack.pop_back();
                stack.push_back("E");
                printRow(step++, stack, input, i, "Reduce: E → E*E");
                reduced = true;
            }
            else if (stack[stack.size()-3] == "(" && stack[stack.size()-2] == "E" && stack[stack.size()-1] == ")") {
                stack.pop_back(); stack.pop_back(); stack.pop_back();
                stack.push_back("E");
                printRow(step++, stack, input, i, "Reduce: E → (E)");
                reduced = true;
            }
        }

        if (!reduced && !stack.empty() && stack.back() == "a") {
            stack.pop_back();
            stack.push_back("E");
            printRow(step++, stack, input, i, "Reduce: E → a");
            reduced = true;
        }

        if (stack.size() == 1 && stack[0] == "E" && input[i] == "$") {
            printRow(step++, stack, input, i, "Accept!!!");
            break;
        }

        if (!reduced) {
            if (i < input.size()-1) { 
                stack.push_back(input[i]);
                printRow(step++, stack, input, i, "Shift");
                i++;
            } else {
                printRow(step++, stack, input, i, "Rejected!!!");
                break;
            }
        }
    }

    printLine();
    return 0;
}
