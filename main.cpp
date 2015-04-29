#include <bits/stdc++.h>

using namespace std;

const string allS = "()0123456789/*-+%";
const string intS = "0123456789";
const string signS = "/*-+%";

string s;
bool maybeUnary = true;
vector <char> op;
vector <int> value;
int balance = 0;

bool check(char c, string S) { //true -- exist i: S[i] == c, else false
    for (int i = 0; i < S.size(); i++) {
        if (c == S[i]) return true;
    }
    return false;
}

int calculation(char oper) { // if (!maybeUnary) return f(x,y), else return f(x);
    op.pop_back();
    if (oper < 0) {
        int x = value.back(); value.pop_back();
        if (-oper == '-') return -x; else return x;
    } else {
    int y = value.back(); value.pop_back();
    int x = value.back(); value.pop_back();
    if (oper == '+') return x + y;
    if (oper == '/')
        if (y != 0) return x / y; else {cerr << "division by zero"; exit(0);}
    if (oper == '*') return x * y;
    if (oper == '-') return x - y;
    if (oper == '%')
        if (y != 0) return x % y; else {cerr << "division by zero"; exit(0);}
    }
}

int priority(char c) { // calculation sign priority
    if (c < 0) return 3;
    if (c == '+' || c == '-') return 1;
    if (c == '%' || c == '/' || c == '*') return 2;
    else return -1;
}

int solution() { // general solution
    int i = 0;
    while (i < s.size()) {
        if (s[i] == ' ') {
            i++;
            continue;
        } else
        if (!check(s[i], allS)) {cerr << "invalid symbol"; exit(0);} else
        if (s[i] == '(') {
            balance++;
            maybeUnary = true;
            op.push_back(s[i]);
        } else
        if (s[i] == ')') {
            balance--;
            if (balance < 0) {cerr << "invalid bracket expression"; exit(0);};
            maybeUnary = false;
            while (op.back() != '(') {
                value.push_back(calculation(op.back()));
            }
            op.pop_back();
        } else
        if (check(s[i], intS)) {
            string valueS = "";
            valueS += s[i];
            while (check(s[i + 1], intS)) {
                valueS += s[++i];
            }
            value.push_back(atoi(valueS.c_str()));
            maybeUnary = false;
        } else
        if (check(s[i], signS)) {
            char z = s[i];
            if (maybeUnary && (z == '+' || z == '-')) z = -z; else
            if (maybeUnary && !(z == '+' || z == '-')) {cerr << "invalid sign expression"; exit(0);};
            while (op.size() > 0 &&
                   ((z >= 0 && priority(op.back()) >= priority(z)) ||
                   (z < 0 && priority(op.back()) > priority(z)))) {
                value.push_back(calculation(op.back()));
            }
            op.push_back(z);
            maybeUnary = true;
        }
        i++;
    }
    if (balance != 0) {cerr << "invalid brackets placement"; exit(0);}
    while (!op.empty()) {
        value.push_back(calculation(op.back()));
    }
    return value.back();
}

int main() {
    getline(cin, s);
    istringstream iss(s);// "abc   asb fb  " ==> "abc", "asb", "fb"
    s = "";
    bool f = true;
    while (iss) {
        string sub;
        iss >> sub;
        if (sub.size() == 0) continue;
        s += sub + " ";
    }
    cout << solution();
}
