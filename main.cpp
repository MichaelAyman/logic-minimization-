#include <iostream>
#include <cstring>
#include <cctype>
#include <stack>
#include <queue>
#include <vector> 
#include <cmath>
#include <map>
#include <sstream>
#include <algorithm>
#include <set>


using namespace std;

stack<char> operators;
stack<pair<char, bool> > operands;
map<char, int>map1;



int order(char C)
{
    if (C == '+')
        return 1;
    else if (C == '*')
        return 2;
    return 0;
}

bool validOperator(char c)
{
    return (c == '+' || c == '*' || c == '(' || c == ')');
}

string infixToPrefix(string s)
{
    string prefix, postf;
    stack<char> ord;

    reverse(s.begin(), s.end());

    for (int i = 0; i < s.length(); i++) {

        if (s[i] == '(') {
            s[i] = ')';
        }
        else if (s[i] == ')') {
            s[i] = '(';
        }
    }
    s = '(' + s + ')';

    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i]) || isdigit(s[i]) || s[i] == '\'')
            postf += s[i];

        else if (s[i] == '(')
            ord.push('(');

        else if (s[i] == ')') {
            while (ord.top() != '(') {
                postf += ord.top();
                ord.pop();
            }
            ord.pop();
        }
        else {
            if (validOperator(ord.top())) {
                    while (!ord.empty() && order(s[i]) < order(ord.top())) {
                        postf += ord.top();
                        ord.pop();
                    }
                ord.push(s[i]);
            }
            }
    }
    while (!ord.empty()) {
            postf += ord.top();
            ord.pop();
    }

        prefix = postf;

        reverse(prefix.begin(), prefix.end());

        return prefix;

}

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


bool POS (string& s) {
    string s2 = "";
    if (!CheckValidBrackets(s)) {
        return 0;
    }
    if (s[0] != '(') { return 0; }
    s2 = "(";
    for (int i = 1; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            if (s[i] == '+') { s2 += s.substr(i, 1); }
            else if (s[i] == ')') { s2 += ')'; s2 += '*'; }
            else if (s[i] == '(' || s[i] == '\'') { s2 += s.substr(i, 1); }
            else { return 0; }
        }
        else {
            if (isalpha(s[i - 1]) || s[i - 1] == '\'') {
                s2 += '*' + s.substr(i, 1);
            }
            else{
            s2 += s.substr(i, 1);}
        }
    }
    s = s2;
    return 1;
}


bool SOP (string& s) {

    if (!CheckValidBrackets(s)) {
        return 0;
    }
    if (!isalpha(s[0])) { return 0; }
    string s2 = s.substr(0, 1);
    for (int i = 1; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            if (s[i] == '+') { s2 += s[i]; }
            else if (s[i] == '(' || s[i] == '\'') { s2 += s[i]; }
            else { return 0; }
        }
        else {
            if (isalpha(s[i - 1]) || s[i - 1] == '\'') {
                s2 += '*' + s.substr(i, 1);
            }
            else {
                s2 += s.substr(i, 1);
            }
        }
    }
    s = s2;
    return 1;
}


bool isOperator(char c)
{
    if (c == '*')  // return true if the char is an operator  
        return true;
    else if (c == '+')
        return true;
    else if (c == '\'')
        return true;
    else
        return false;
}
bool evaluatePrefix(string exprsn)
{
    stack<bool> PrefixCalc;

    for (int i = exprsn.size() - 1; i >= 0; i--) {

        if (!isOperator(exprsn[i])) {
            if (exprsn[i + 1] == '\'')
                continue;
            PrefixCalc.push(exprsn[i] - '0'); // push the value of zero or 1 not the char value
        }
        else if (exprsn[i] == '\'') {
            PrefixCalc.push(1 - (exprsn[i - 1] - '0')); // recieve the next char inverted 
        }
        else {

            // Operator encountered
            // Pop two elements from Stack
            bool o1 = PrefixCalc.top();
            PrefixCalc.pop();
            bool o2 = PrefixCalc.top();
            PrefixCalc.pop();

            // calc the value

            switch (exprsn[i]) {
            case '+':
                PrefixCalc.push(o1 | o2);
                break;
            case '*':
                PrefixCalc.push(o1 * o2);
                break;
            default:
                cout << "Operator not identified";
            }
        }
    }

    return PrefixCalc.top();
}

void decToBinary(int n, int numOfVar,  vector<bool> &arr) 
{ 
    //cout << numOfVar;
    // array to store binary number 
    vector<int> binaryNum(numOfVar); 
    // counter for binary array 
    int i = 0;
    while (i < numOfVar) {
        // storing remainder in binary array and the rest with 0
        if (n <= 0) {
            binaryNum[i] = 0;
            i++;
            continue;
        }
        else {
            binaryNum[i] = n % 2;
            n = n / 2;
            i++;
        }
    }
    // return the new array inversed
    for (int j = i - 1; j >= 0; j--)
        arr[numOfVar - 1 - j] = binaryNum[j];
}

string decToBinaryString(int n, int numOfVar)
{
    // array to store binary number 
    vector<int> binaryNum(numOfVar); 
    vector<int> arr(numOfVar);
    string output = "";
    // counter for binary array 
    int i = 0;
    while (i < numOfVar) {
        // storing remainder in binary array and the rest with 0
        if (n <= 0) {
            binaryNum[i] = 0;
            i++;
            continue;
        }
        else {
            binaryNum[i] = n % 2;
            n = n / 2;
            i++;
        }
    }
    // return the new array inversed
    for (int j = i - 1; j >= 0; j--)
        arr[numOfVar - 1 - j] = binaryNum[j];
    for (int i = 0; i < numOfVar; i++)
        output += to_string(arr[i]);
    return output;
}

int binToDec(string s) {
    int decimalValue = 0;
    int powerOfTwo = 1; // Initialize with 2^0

    // Start from the rightmost (least significant) bit and move left
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '1') {
            decimalValue += powerOfTwo;
        }
        powerOfTwo *= 2; // Double the power for the next bit position
    }

    // Ensure that the number of bits matches the specified number

    return decimalValue;
}


void mapVars(int numOfVars, string exp) {  // func that maps every char to a number so we can use it in evaluate a prefix exp 
    int j = 0;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '+' || exp[i] == '*' || exp[i] == '\'') {
            map1[exp[i]] = 99;
        }
        else {
            if (map1.find(exp[i]) == map1.end()) { // map and increment only if not mapped before
                map1[exp[i]] = j;
                j++;
            }
        }
    }
}

string printKey(map<char, int>& Map,
    int K)
{

    // If a is true, then we have
    // not key-value mapped to K
    bool a = true;
    string c;

    // Traverse the map
    for (auto& it : Map) {

        // If mapped value is K,
        // then print the key value
        if (it.second == K) {
            c = it.first;
            a = false;
            //            cout<< it.first;
            //            a = false;
        }
    }

    // If there is not key mapped with K,
    // then print -1
    if (a) {
        cout << "-1";
    }
    return c;
}


string ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);

        start_pos += to.length(); 
    }
    return str;
}

bool isAdjacent(string a, string b)
{
    int flag = 0;
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] != b[i])
            flag++;
    }
    if (flag == 1)
        return true;
    else
        return false;
}

string repDontcare(string a, string b)
{
    string temp = "";
    for (int i = 0; i < a.length(); i++)
        if (a[i] != b[i])
            temp += "-";
        else
            temp += a[i];

    return temp;
}

int countNum1(string x) {
    int counter = 0;
    for (int i = 0; i < x.length(); i++)
        if (x[i] == '1')
            counter++;
    return counter;
}


vector <string> vsort(vector<string> vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = 0; j < vec.size() - i - 1; j++)
            if (countNum1(vec[j]) > countNum1(vec[j + 1])) {
                string temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
    }
    return vec;
}

void printv(vector<string> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << endl;
    }
}


map<int, vector<string>> groupMintermsByOnes(const vector<string>& minterms) { // group Minterms by ones 
    map<int, vector<string>> mintermGroups;
    for (const string& minterm : minterms)
        mintermGroups[countNum1(minterm)].push_back(minterm);
    return mintermGroups;
}

void printMintermGroups(const map<int, vector<string>>& mintermGroups) {
    for (const auto& group : mintermGroups) {
        cout << "----------------------" << endl;
        for (const string& minterm : group.second) {
            cout << minterm << " ";
        }
        cout << endl;
    }
}
bool alreadyExists(vector<string> v, string s) {
    return find(v.begin(), v.end(), s) != v.end();
}
void mark(string s, map<string, bool>& markedMap) {
    // If a is true, then we have
    // not key-value mapped to K
    // Traverse the map
    for (auto& it : markedMap) {
        if (it.second == 0) {
            it.second = 1;
        }
    }
}

void reduce(map<int, vector<string>>& mintermGroups, map<string, bool>& markedMap, map<string, string>& pi) {
    // Base case: If there is only one group, no further reduction is possible
    if (mintermGroups.empty())
        return;

        for (auto it = mintermGroups.begin(); it != mintermGroups.end(); it++)
            for (int i = 0; i < it->second.size(); i++) {
                markedMap.insert({it->second[i], 0});
            }
    string s1 = ""; 
    string s2 = "";

    map<int, vector<string>> nextGroup;
    vector<string> vtemp;

    for (int i = 0; i < mintermGroups.size() - 1; i++) {
        auto& group1 = mintermGroups[i];
        auto& group2 = mintermGroups[i + 1];

        for (const string& minterm1 : group1) {
            for (const string& minterm2 : group2) {
                if (isAdjacent(minterm1, minterm2)) {
                    for (auto it = markedMap.begin(); it != markedMap.end(); it++) { // mark the minterms 
                        if (it->first == minterm1)
                            it->second = 1;
                        if (it->first == minterm2)
                            it->second = 1;
                    }
                    if (!alreadyExists(vtemp, repDontcare(minterm1, minterm2))) {
                        vtemp.push_back(repDontcare(minterm1, minterm2));
                        for (auto it = pi.begin(); it != pi.end(); it++) {
                            if (it->first == minterm1)
                                s1 = it->second;
                            if (it->first == minterm2)
                                s2 = it->second;
                        }
                        pi.insert({ repDontcare(minterm1, minterm2), s1 + "-" + s2 });
                    }
                }
            }
        }

        map<int, vector<string>> mtemp = groupMintermsByOnes(vtemp);
        nextGroup.insert(mtemp.begin(), mtemp.end());
        vtemp.clear();
    }

    // Print the current state of the groups

    // Recursively reduce the next group
    reduce(nextGroup, markedMap, pi);
}



vector<string> srtingtominterms(string s1);

map<string, vector<string>> EPI(vector<string> minterms, map<string, bool> markedMap, map<string, string> pi)
{
    map<string, vector<string>> EPI;

    for (int j = 0; j < minterms.size(); j++)
    {
        string tempmin = to_string(binToDec(minterms[j]));
        vector<string> vtemp;
        string tempEPI;
        vector<string> PItemp;
        bool flag = true;
        for (auto it = markedMap.begin(); it != markedMap.end(); it++) {
            if (it->second == 0)
                for (auto it2 = pi.begin(); it2 != pi.end(); it2++)
                    if (it->first == it2->first)
                    {
                        vector<string> minterms = srtingtominterms(it2->second);
                        for (int i = 0; i < minterms.size(); i++)
                        {

                            PItemp.push_back(minterms[i]);
                            if (!alreadyExists(vtemp, minterms[i]) && tempmin == minterms[i])
                            {
                                vtemp.push_back(minterms[i]);
                                tempEPI = it2->first;

                            }
                            else if (alreadyExists(vtemp, minterms[i]) && tempmin == minterms[i])
                            {
                                flag = false;
                                PItemp = {};
                            }


                        }


                    }

        }

        if (flag)
            EPI.insert({ tempEPI,PItemp });
    }

    return EPI;

}
vector<string> NotfoundMT(map<string, vector<string>> EPI, vector<string> minterms)
{
    vector<string> NotfoundMT;

    for (int j = 0; j < minterms.size(); j++)
    {
        bool flag = true;
        string tempmin = to_string(binToDec(minterms[j]));
        for (auto it = EPI.begin(); it != EPI.end(); it++)
        {
            vector<string> PI = it->second;
            for (int i = 0; i < PI.size(); i++)
                if (PI[i] == tempmin)
                {
                    flag = false;
                }

        }
        if (flag)
            NotfoundMT.push_back(tempmin);
    }
    return NotfoundMT;
}
vector<string> srtingtominterms(string s1)
{
    vector<string> minterms;
    string s2 = "";
    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] != '-' && i != s1.length() - 1)
        {
            s2 += s1[i];
        }
        else if (i == s1.length() - 1)
        {
            s2 += s1[i];
            minterms.push_back(s2);
            s2 = "";
        }
        else
        {
            minterms.push_back(s2);
            s2 = "";
        }

    }
    return minterms;

}
vector<string> miniexpress(vector<string> NotfoundMT, map<string, bool> markedMap, map<string, vector<string>> EPI, vector<string> minterms, map<string, string> pi)
{
    vector<string>dominatedRow;
    vector<string>dominatingCol;
    map<string, vector<string>> PITb;
    vector<string > EPITemp;
    vector<string > PITbTemp;

    for (auto& x : EPI)
    {
        EPITemp.push_back(x.first);
    }
    for (auto it = markedMap.begin(); it != markedMap.end(); it++)
    {
        if (it->second == 0)
            for (auto it2 = pi.begin(); it2 != pi.end(); it2++)
            {
                if (it->first == it2->first && !alreadyExists(EPITemp, it2->first))
                {
                    string PITEMP = it2->first;
                    for (auto& x : PITb)
                    {
                        PITbTemp.push_back(x.first);
                    }
                    if (!alreadyExists(PITbTemp, PITEMP))
                        PITb.insert({ PITEMP, srtingtominterms(pi[PITEMP]) });

                }
            }
    }
    for (auto& x : PITb)
    {
        PITbTemp.push_back(x.first);
    }
    for (int j = 0; j < size(PITbTemp); j++)
    {
        for (int l = j + 1; l < size(PITbTemp) - 1; l++)
        {
            vector<string>first = PITb[PITbTemp[j]];
            vector<string>second = PITb[PITbTemp[l]];
            sort(first.begin(), first.end());
            sort(second.begin(), second.end());
            if (includes(first.begin(), first.end(), second.begin(), second.end()))
                dominatedRow.push_back(PITbTemp[l]);
            else if (includes(second.begin(), second.end(), first.begin(), first.end()))
                dominatedRow.push_back(PITbTemp[j]);

        }
    }
    map<string, vector<string>> columns;
    for (int n = 0; n < size(NotfoundMT); n++)
    {
        columns.insert({ NotfoundMT[n], vector<string>() });
        for (int j = 0; j < size(PITbTemp); j++)
            if (alreadyExists(PITb[PITbTemp[j]], NotfoundMT[n]))
                columns[NotfoundMT[n]].push_back(PITbTemp[j]);
    }
    for (int r = 0; r < size(NotfoundMT); r++)
    {
        for (int s = r + 1; s < size(NotfoundMT) - 1; s++)
        {
            vector<string>first = columns[NotfoundMT[r]];
            vector<string>second = columns[NotfoundMT[s]];
            sort(first.begin(), first.end());
            sort(second.begin(), second.end());
            if (includes(first.begin(), first.end(), second.begin(), second.end()))
                dominatingCol.push_back(NotfoundMT[r]);
            else if (includes(second.begin(), second.end(), first.begin(), first.end()))
                dominatingCol.push_back(NotfoundMT[s]);

        }
    }
    for (int k = 0; k < size(dominatedRow); k++)
    {
        PITb.erase(dominatedRow[k]);

    }
    for (int d = 0; d < size(PITbTemp); d++)
    {
        for (int f = 0; f < size(dominatingCol); f++)
        {
            if (find(PITb[PITbTemp[d]].begin(), PITb[PITbTemp[d]].end(), dominatingCol[f]) != PITb[PITbTemp[d]].end())
                PITb[PITbTemp[d]].erase(find(PITb[PITbTemp[d]].begin(), PITb[PITbTemp[d]].end(), dominatingCol[f]));
        }
    }
    vector<pair<string, vector<string>>> sorted;
    for (auto itr = PITb.begin(); itr != PITb.end(); ++itr)
        sorted.push_back(*itr);

    sort(sorted.begin(), sorted.end(), [=](pair<string, vector<string>>& a, pair<string, vector<string>>& b)
        {
            return a.second.size() > b.second.size();
        }
    );
    map<string, bool> included;
    for (int a = 0; a < size(minterms); a++)
    {
        included.insert({ minterms[a], false });
    }
    vector<string> sortedvector;
    for (auto& x : sorted)
    {
        sortedvector.push_back(x.first);
    }
    vector<string> PIsolution;
    for (int c = 0; c < size(sortedvector); c++)
    {
        bool flag = false;
        for (int d = 0; d < size(PITb[sortedvector[c]]); d++)
        {
            if (!included[PITb[sortedvector[c]][d]])
            {
                flag = true;
                included[PITb[sortedvector[c]][d]] = true;
            }
        }
        if (flag)
            PIsolution.push_back(sortedvector[c]);

    }
    for (int t = 0; t < size(EPITemp); t++)
    {
        PIsolution.push_back(EPITemp[t]);
    }
    return PIsolution;

}

int main() {

    string s1;
    set<char> charSet;
    cout << "Enter Expression: " << endl;
    getline(cin, s1);
    RemoveSpaces(s1);
    string prefix = "";

    if (SOP(s1) || POS(s1)) {
        prefix = infixToPrefix(s1);
        cout << prefix << endl;
    }
    for (int i = 0; i < prefix.length(); i++) {
        if (!isOperator(prefix[i]))
            charSet.insert(prefix[i]);
    }


    int numOfVar = charSet.size(); // number of variables 
    map<string, bool> markedMap;
    map<string, string> pi;
    // above this line is all the checkers and the endproduct of them is a string in a prefix form  
    string prefixTest = prefix; // there's a problem in bar and a problem in displaying sop the plus in the end
    string tempPrefix = prefixTest;
    mapVars(numOfVar, prefixTest); // map vars to their places in the tt 
    vector<bool> arrOfBinary(numOfVar);
    vector<vector<bool>> tt; // now we make a vector of vectors to put in the truth table 
    vector<string> minterms;
    // Inserting elements into vector 

    for (int i = 0; i < pow(2, numOfVar); i++) {
        vector<bool> v1;
        for (int j = 0; j < numOfVar + 1; j++) {
            decToBinary(i, numOfVar, arrOfBinary);
            v1.push_back(arrOfBinary[j]);
        }
        for (int i = 0; i < prefixTest.length(); i++) {
            if (map1[prefixTest[i]] != 99)
                tempPrefix[i] = '0' + v1[map1[prefixTest[i]]];
        }
        //  cout << tempPrefix << endl;
        v1[numOfVar] = evaluatePrefix(tempPrefix); // store the Value of my Function in the last bit of my vector 
        tt.push_back(v1);
    }
    // Displaying the 2D vector 
    for (int i = 0; i < tt.size(); i++) {
        for (int j = 0; j < tt[i].size(); j++)
            cout << tt[i][j] << " ";
        cout << endl;
    }

    string sop1 = "";
    cout << "SOP: ";
    for (int i = 0; i < pow(2, numOfVar); i++) {
        if (tt[i][numOfVar] == 1) {
            for (int j = 0; j < numOfVar; j++) {
                if (tt[i][j] == 1) {
                    sop1 += printKey(map1, j);
                }
                sop1 += " +";
            }
        }
        for (int i = 0; i < sop1.length() - 2; i++)
            cout << sop1[i];

        cout << endl;
        string pos = "";
        for (int i = 0; i < pow(2, numOfVar); i++) {
            if (tt[i][numOfVar - 1] == 0) {
                pos += '(';
                for (int j = 0; j < numOfVar; j++) {
                    if (tt[i][j] == 1) {
                        pos += printKey(map1, j) + "\'" + '+';
                    }
                    else
                        pos += printKey(map1, j) + '+';
                }
                pos += ')';
            }
        }
        cout << "POS: " << ReplaceAll(pos, string("+)"), string(")")); // Modify the POS string to remove the extra + 
        cout << endl << "Minterms:" << endl;
        for (int i = 0; i < pow(2, numOfVar); i++) {
            if (tt[i][numOfVar - 1] == 1) {
                minterms.push_back(decToBinaryString(i, numOfVar));
            }
        }
        for (int i = 0; i < minterms.size(); i++) {
            cout << minterms[i] << endl;
        }

        /*vector<string> sortedMinterms;
        sortedMinterms = vsort(minterms);
        cout << "Sorted Minterms: " << endl;
        printv(sortedMinterms); */



        for (int i = 0; i < minterms.size(); i++) {
            pi.insert({ minterms[i],to_string(binToDec(minterms[i])) });
        }
        map<int, vector<string>> mintermGroups = groupMintermsByOnes(minterms); // Map from int to vector of strings to map all the binaries to their number of ones 
        reduce(mintermGroups, markedMap, pi);


        // for (auto it = markedMap.begin(); it != markedMap.end(); it++){
        //             cout << it->first << " " ;
        //             cout << it->second << endl;
        // }
        // for (auto it = pi.begin(); it != pi.end(); it++){
        //             cout << it->first << " " ;
        //             cout << it->second << endl;
        // }
        cout << endl << "PI's are: " << endl;
        for (auto it = markedMap.begin(); it != markedMap.end(); it++) {
            if (it->second == 0)
                for (auto it2 = pi.begin(); it2 != pi.end(); it2++)
                    if (it->first == it2->first)
                        cout << it2->second << " (" << it2->first << ")" << endl;
        }


        cout << "EPI's are: " << endl;
        map<string, vector<string>> EPI1 = EPI(minterms, markedMap, pi);
        for (auto it = EPI1.begin(); it != EPI1.end(); it++)
            cout << it->first << " ";
        cout << endl;
        cout << "The minterms that are not covered by the essential PIs are: " << endl;
        vector<string> PI1 = NotfoundMT(EPI1, minterms);
        for (int b = 0; b < PI1.size(); b++)
            cout << PI1[b] << " ";
        cout << endl;
        cout << "Minimized expression:" << endl;
        vector<string> miniexpress1 = miniexpress(PI1, markedMap, EPI1, minterms, pi);
        cout << miniexpress1[0];
        for (int b = 1; b < miniexpress1.size(); b++)
            cout << " + " << miniexpress1[b];
        cout << endl;

    }
    return 0;

}
