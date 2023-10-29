#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <queue>

using namespace std;

stack<char> operators;
stack<pair<char, bool> > operands;

void RemoveSpaces(string& s) {
    string temp = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            temp += s[i];
        }
    }
    s = temp;
}

bool IsComp (char next) {
    if (next == '\'') { return 1; }
    else { return 0; }
}

void CopyOperators(queue<char> tempOperators) {
    while (!operators.empty()) {
        operators.pop();
    }
    while (!tempOperators.empty()) {
        operators.push(tempOperators.front());
        tempOperators.pop();
    }
}

void CopyOperands(queue<pair<char, bool> > tempOperands) {
    while (!operators.empty()) {
        operators.pop();
    }
    while (!tempOperands.empty()) {
        operands.push(tempOperands.front());
        tempOperands.pop();
    }
}

bool CheckValidBrackets(string s) {
    stack<char> c;
    char k;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            c.push(s[i]);
        }
        else if (s[i] == ')') {
            if (!c.size()) {
                return false;
            }
            if (c.top() == '(') {
                k = ')';
            }
            c.pop();
        }
    }
    if (c.size()) {
        return 0;
    }
    return 1;
}

bool SOP (string s) {
    bool previschar = 1;
    queue<char> tempOperators;
    queue<pair<char, bool> > tempOperands;
    if (!isalpha(s[0])) { return 0; }
    for (int i = 1; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            if (s[i] == '+') {
                tempOperators.push('+');
            }
            else { return 0; }
        }
        else {
            tempOperators.push('*');
            if (i + 1 < s.length() && IsComp(s[i + 1])) {
                tempOperands.push({ s[i], 1 });
                i++;
            }
            else {
                tempOperands.push({ s[i], 0 });
            }
        }
    }
    CopyOperands(tempOperands);
    CopyOperators(tempOperators);
    return 1;
}

bool POS (string s) {
    queue<char> tempOperators;
    queue<pair<char, bool> > tempOperands;
    if (!CheckValidBrackets(s)) {
        return 0;
    }
    if (s[0] != '(') { return 0; }
    for (int i = 1; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            if (s[i] == ')'){ 
                tempOperators.push('*'); 
                
            }
            else if (s[i] != '(') { return 0; }
        }
        else {
            if (s[i] == '+') { tempOperators.push('+'); }
            else {
                if (i + 1 < s.length() && IsComp(s[i + 1])) {
                    tempOperands.push({ s[i], 1 });
                    i++;
                }
                else {
                    tempOperands.push({ s[i], 0 });
                }
            }
        }
    }
    CopyOperands(tempOperands);
    CopyOperators(tempOperators);
    return 1;
}

int main() {
    string s;
    cout << "Enter Expression: " << endl;
    getline(cin, s);
    RemoveSpaces(s);
    cout << s;
}
