#include <iostream>
#include <cstring>
using namespace std;

string str;
string oprt = "*+-";
char temp[20];

int calculate(int l, int r, string n_str) {
    if (l + 1 == r) return n_str[l] - '0';
    bool ok = true;
    for (int i = l; i < r; i++) {
        if (n_str[i] == '+') {
            ok = false;
            return calculate(l, i, n_str) + calculate(i+1, r, n_str);
        }
        if (n_str[i] == '-') {
            ok = false;
            int j = i+1;
            while (j != n_str.size()) {
                if (n_str[j] == '-') n_str[j] = '+';
                else if (n_str[j] == '+') n_str[j] = '-';
                j++;
            }
            return calculate(l, i, n_str) - calculate(i+1, r, n_str);
        }
    }
    for (int i = l; i < r; i++) {
        if (n_str[i] == '*') {
            ok = false;
            return calculate(l, i, n_str) * calculate(i+1, r, n_str);
        }
    }
    if (ok) {
        int res = 0;
        for (int i = l; i < r; i++) {
            res = res * 10 + n_str[i] - '0';
        }
        return res;
    }
    return 0;
}

bool is_operator(char ch) {
    return oprt.find(ch) < 3;
}

bool qualify(string n_str) {
    for (int i = 0; i < n_str.size(); i++) {
        if (i == (int)n_str.size()-1 && is_operator(n_str[i])) return false; //{ cout << "can't have an operator at end!\n"; return false; }
        if (!i && n_str[i] == '0' && !is_operator(n_str[i+1])) return false; //{ cout << "can't have an zero at beginning!\n"; return false; }
        if (!i && is_operator(n_str[i])) return false; //{ cout << "can't have an initial operator!\n"; return false; }
        if (is_operator(n_str[i-1]) && n_str[i] == '0' && !is_operator(n_str[i+1]) && i != (int)n_str.size()-1) return false; //{ cout << "can't have an initial zero!\n"; return false; }
    }
    return true;
}

bool try_cal(int d) {
    string n_str; n_str.clear();
//    str.push_back('1'); d++;
    for (int i = 0; i < d; i++)
        n_str.push_back(temp[i]);
//    cout << n_str << endl;
    
    if (calculate(0, (int)n_str.size(), n_str) != 2000) return false;
    
//    cout << n_str << endl;
    
    if (!qualify(n_str)) return false;
    
    return true;
}

int kase;
void output(int d) {
    cout << "  ";
    for (int i = 0; i < d; i++)
        cout << temp[i];
    cout << '=' << endl;
}

bool dfs(int cur_d, int cur_idx, bool ok) {
    if (cur_idx == str.size()) {
        if (try_cal(cur_d)) {
            output(cur_d);
            return true;
        }
        return false;
    }
    
    bool update = false;
    
    for (int i = 0; i < 4; i++) {
        
        if (i != 3 && ok) {
            temp[cur_d] = oprt[i];
            if (dfs(cur_d+1, cur_idx, false)) update = true;
        }
        
        if (i == 3) {
            temp[cur_d] = str[cur_idx];
            if (dfs(cur_d+1, cur_idx+1, true)) update = true;
        }
        
    }
    
    return update;
}

void debug() {
    string _str;
    cin >> _str;
    cout << (qualify(_str) ? "qualified!\n" : "unqualified!\n");
}

//#define local

int main() {
    ios::sync_with_stdio(false);
#ifdef local
    freopen("result.txt", "w", stdout);
#endif
    
//    while (true) { debug(); }
    
    while (cin >> str && str[0] != '=') {
        
//        cout << calculate(0, (int)str.size(), str) << endl; continue;
        
        cout << "Problem " << ++kase << endl;
        str.pop_back();
        
        if (str == "2000") { cout << "  IMPOSSIBLE\n"; continue; }
        
        if (!dfs(0, 0, false)) cout << "  IMPOSSIBLE\n";
    }
    
    return 0;
}
