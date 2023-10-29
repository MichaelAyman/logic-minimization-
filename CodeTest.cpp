#include <iostream>
#include <string>
#include <cctype>
#include <stack>

using namespace std;

stack<char> operators;
stack<pair<char, bool> > operands;

void RemoveSpaces(string& s) {
    for (int i = 0; i < s.length(); i++) {
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    }
}

bool IsComp (char next) {
    if (next == '\'') { return 1; }
    else { return 0; }
}

void CopyStack() {}

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
    stack<char> tempOperators;
    stack<pair<char, bool> > tempOperands;
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
    operators = tempOperators;
    operands = tempOperands;
    return 1;
}

bool POS (string s) {
    stack<char> tempOperators;
    stack<pair<char, bool> > tempOperands;
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
    return 1;
}

int main() {
    string s;
    cout << "Enter Expression: " << endl;
    cin >> s;
    RemoveSpaces(s);
    return 0;
}
