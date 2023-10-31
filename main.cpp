#include <iostream>
#include <cstring>
#include <cctype>
#include <stack>
#include <vector> 
#include <cmath>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

stack<char> operators;
stack<pair<char, bool> > operands;
map<char, int>map1;
map<string, bool> markMap;


/*void RemoveSpaces(string& s) {
    for (int i = 0; i < s.length(); i++) {
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    }
}*/

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
bool isOperator(char c)
{
    if ( c == '*')  // return true if the char is an operator  
        return true; 
    else if ( c == '+') 
        return true;
    else if ( c == '\'')
        return true; 
    else
        return false; 
}
bool evaluatePrefix(string exprsn)
{
    stack<bool> PrefixCalc;
 
    for (int i = exprsn.size() - 1; i >= 0; i--) {
 
        if (!isOperator(exprsn[i])) {
            if (exprsn[i+1]== '\'')
                continue;
            PrefixCalc.push(exprsn[i] - '0'); // push the value of zero or 1 not the char value
        }
        else if (exprsn[i]== '\''){  
            PrefixCalc.push(1-(exprsn[i-1] - '0')); // recieve the next char inverted 
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

void decToBinary(int n, int numOfVar, bool arr[]) 
{ 
    // array to store binary number 
    int binaryNum[numOfVar]; 
    // counter for binary array 
    int i = 0; 
    while (i < numOfVar) { 
        // storing remainder in binary array and the rest with 0
        if ( n <= 0) {
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
            arr[numOfVar-1-j] = binaryNum[j]; 
} 

string decToBinaryString(int n, int numOfVar) 
{ 
    // array to store binary number 
    int binaryNum[numOfVar]; 
    int arr[numOfVar];
    string output = "";
    // counter for binary array 
    int i = 0; 
    while (i < numOfVar) { 
        // storing remainder in binary array and the rest with 0
        if ( n <= 0) {
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
        arr[numOfVar-1-j] = binaryNum[j]; 
    for (int i = 0; i < numOfVar; i++)
        output += to_string(arr[i]);
    return output; 
} 


void mapVars(int numOfVars, string exp) {  // func that maps every char to a number so we can use it in evaluate a prefix exp 
    int j = 0;
    for (int i =0; i < exp.length(); i++) {
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
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

bool isAdjacent(string a,string b)
{
   int flag=0;
   for(int i=0;i<a.length();i++)
   {
       if(a[i]!=b[i])
        flag++;
   }
   if (flag == 1) 
    return true; 
   else 
    return false;
}

string repDontcare(string a,string b)
{
   string temp="";
   for(int i=0;i<a.length();i++)
        if(a[i]!=b[i])
            temp += "-";
        else
            temp += a[i];

   return temp;
}

int countNum1 (string x) {
    int counter = 0;
    for (int i = 0; i< x.length(); i++) 
        if (x[i]== '1')
            counter++;
    return counter;
}


vector <string> vsort (vector<string> vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = 0; j < vec.size() - i - 1; j++)
            if (countNum1(vec[j]) >countNum1(vec[j+1])) {
                string temp = vec[j]; 
                vec[j] = vec[j+1]; 
                vec[j+1] = temp;
            }
    }
    return vec;
}

void printv (vector<string> vec) {
    for (int i =0; i < vec.size(); i++) {
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
    return find(v.begin(), v.end(),s)!=v.end();
}
void mark(string s) { 
    // If a is true, then we have
    // not key-value mapped to K
    bool a = true;
    string c;
 
    // Traverse the map
    for (auto& it : markMap) {

        if (it.second == 0) {
            it.second = 1;
//            cout<< it.first;
//            a = false;
        }
    }
}

void reduce(map<int, vector<string>>& mintermGroups) {
    // Base case: If there is only one group, no further reduction is possible
    if (mintermGroups.empty()) {
        return;
    }
    map<int, vector<string>> nextGroup;
    vector<string> vtemp;

    for (int i = 0; i < mintermGroups.size() - 1; i++) {
        auto& group1 = mintermGroups[i];
        auto& group2 = mintermGroups[i + 1];

        for (const string& minterm1 : group1) {
            for (const string& minterm2 : group2) {
                if (isAdjacent(minterm1, minterm2)) {
                    if (!alreadyExists(vtemp,repDontcare(minterm1, minterm2)))
                        vtemp.push_back(repDontcare(minterm1, minterm2));
                }
            }
        }

        map<int, vector<string>> mtemp = groupMintermsByOnes(vtemp);
        nextGroup.insert(mtemp.begin(), mtemp.end());
        vtemp.clear();
    }

    // Print the current state of the groups

    printMintermGroups(mintermGroups);

    // Recursively reduce the next group
    reduce(nextGroup);
}




int main() {
    string s;
    // cout << "Enter Expression: " << endl;
    // cin >> s;
    //RemoveSpaces(s); // there's an error in RemoveSpaces line 13
   int numOfVar = 4; // number of variables 

    // above this line is all the checkers and the endproduct of them is a string in a prefix form  
    string prefixTest = "+++a*bc*ca*da"; // there's a problem in bar and a problem in displaying sop the plus in the end
    string tempPrefix = prefixTest; 
    mapVars(numOfVar, prefixTest); // map vars to their places in the tt 
    bool arrOfBinary[numOfVar];
    vector<vector<bool>> tt; // now we make a vector of vectors to put in the truth table 
    vector<string> minterms;
    // Inserting elements into vector 
    for (int i = 0; i < pow(2, numOfVar); i++) { 
        vector<bool> v1;   
        for (int j = 0; j < numOfVar +1; j++) { 
            decToBinary(i, numOfVar, arrOfBinary);
            v1.push_back(arrOfBinary[j]); 
        } 
        for (int i = 0; i < prefixTest.length(); i++) {
        if (map1[prefixTest[i]]!= 99) 
        tempPrefix[i] =  '0'+v1[map1[prefixTest[i]]]; 
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
    for (int i =0; i< pow(2, numOfVar); i++) {
        if (tt[i][numOfVar] == 1) {
            for (int j = 0; j < numOfVar ; j++) {
                if (tt[i][j] == 1) {
                   sop1 += printKey (map1, j);
                }
                else 
                   sop1 += printKey (map1, j) + "\'";
            } 
                sop1 += " +";
        }
    }
    for (int i=0; i < sop1.length()-2; i++)
        cout << sop1[i];

    cout << endl;
    string pos = "";
    for (int i =0; i< pow(2, numOfVar); i++) {
        if (tt[i][numOfVar] == 0) {
            pos += '(';
            for (int j = 0; j < numOfVar ; j++) {
                if (tt[i][j] == 1) {
                   pos += printKey (map1, j) + "\'"+ '+';
                }
                else 
                   pos += printKey (map1, j) + '+';
            } 
                pos +=')';
        }
    }
    cout <<"POS: "<< ReplaceAll(pos, string("+)"), string(")")); // Modify the POS string to remove the extra + 
    cout << endl << "Minterms:" << endl;
    for (int i =0; i< pow(2, numOfVar); i++) {
        if (tt[i][numOfVar] == 1) {
            minterms.push_back(decToBinaryString(i,numOfVar));
        }
    }
    for (int i = 0; i < minterms.size(); i++){
        cout << minterms[i] << endl;
    }

    /*vector<string> sortedMinterms; 
    sortedMinterms = vsort(minterms);
    cout << "Sorted Minterms: " << endl;
    printv(sortedMinterms); */




    map<int, vector<string>> mintermGroups = groupMintermsByOnes(minterms); // Map from int to vector of strings to map all the binaries to their number of ones 
    reduce(mintermGroups);

    return 0; 

}