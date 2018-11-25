#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
//#define strlen(s) (sizeof(s)/6)
using namespace std;

string x, y, z;
string stx = "##", sty = "##", stz = "####";
string xyz;
string patt = "*0123456789#";
string num = "0123456789";

map<string, vector<int> > lib;

string standarlize(string x, int size) {
    string sx = "##";
    if (size == 2) {
        if (x.length() == 2) sx = x;
        if (x.length() == 1) sx[1] = x[0];
    }
    if (size == 4) {
        sx += "##";
        if (x.length() == 1) sx[3] = x[0];
        if (x.length() == 2) { sx[3] = x[1]; sx[2] = x[0]; }
        if (x.length() == 3) { sx[3] = x[2]; sx[2] = x[1]; sx[1] = x[0]; }
        if (x.length() == 4) sx = x;
    }
    
    return sx;
}

int maxd;

string int_to_string(int num) {
    string res = "##";
    if (num == 0) return "#0";
    if (num >= 1) res[1] = char(num % 10 + '0');
    if (num >= 10) res[0] = char(num / 10 + '0');
    return res;
}

bool match(string comp, int val) {
    string str = int_to_string(val);
    for (int i = 1; i >= 0; i--) {
        if (comp[i] == '#' && str[i] == '#') return true;
        if (comp[i] == '#' || str[i] == '#') return false;
        if (comp[i] == '*' || str[i] == '*') continue;
        if (comp[i] != str[i]) return false;
    }
    return true;
}

bool compare(string cmp, int val) { // compare a 4-size string with an Int, see if literally same
    if (val == 0) {
        if ((cmp[3] == '0'|| cmp[3] == '*') && cmp[2] == '#') return true;
        return false;
    }
    string cmp2 = "####";
    int iter = 3;
    while (val) {
        cmp2[iter--] = char(val % 10 + '0');
        val /= 10;
    }
    //cout << "cmp :" << cmp << endl;
    //cout << "cmp2: " << cmp2 << endl;
    for (int i = 0; i <= 3; i++) {
        if (cmp[i] == '*' && cmp2[i] != '#') continue;
        if (cmp2[i] != cmp[i]) return false;
    }
    return true;
}

bool one_and_only_solution() {
    string xx = "", yy = "", zz = "";
    xx += xyz[0]; xx += xyz[1];
    yy += xyz[2]; yy += xyz[3];
    zz += xyz[4]; zz += xyz[5];
    zz += xyz[6]; zz += xyz[7];
    
    //cout << "separating...\n" << xx << ' ' << yy << ' ' << zz << endl;
 
    int cnt = 0;
    for (int i = 0; i < (int)lib[xx].size(); i++) { // TO DO
        for (int j = 0; j <(int)lib[yy].size(); j++) { // TO DO
            int v1 = lib[xx][i], v2 = lib[yy][j];
            int v3 = v1 * v2;
            if (!compare(zz, v3)) continue;
            //cout << "find " << v1 << " * " << v2 << " = " << v3 << endl;
            cnt++;
            if (cnt >= 2) return false;
        }
    }
    //cout << "find " << cnt << " solution(s)!\n";
    
    return cnt == 1;
}

bool dfs(int d, int cur) {
    if (d == maxd) {
        if (one_and_only_solution())
            return true;
        else
            return false;
    }
    
    if (cur == 8) return false;
    
    string cpy = xyz; //cout << cpy << endl;
    for (int i = 0; i <= 10; i++) {
        if (xyz[cur] == patt[i] || xyz[cur] == '#') {
            if (dfs(d, cur+1)) return true;
        } else {
            xyz[cur] = patt[i];
            if (dfs(d+1, cur+1)) return true;
        }
        xyz = cpy;
    }
    
    return false;
}

void init() {
    stx = standarlize(x, 2);
    sty = standarlize(y, 2);
    stz = standarlize(z, 4);
    //cout << "x, y, z are " << x << ' ' << y << ' ' << z << endl;
    //cout << "standard x, y, z are " << stx << ' ' << sty << ' ' << stz << endl;
    xyz.clear();
    xyz += stx; xyz += sty; xyz += stz;
    //cout << "xyz is " << xyz << endl;
}

int kase = 0;

void solve() {
    init();
    
    for (maxd = 0; ; maxd++) {
        if (dfs(0, 0)) break;
    }
    
    
    cout << "Case " << ++kase << ": ";
    for (int i = 0; i <= 1; i++) {
        if (xyz[i] == '#') continue;
        cout << xyz[i];
    } cout << ' ';
    for (int i = 2; i <= 3; i++) {
        if (xyz[i] == '#') continue;
        cout << xyz[i];
    } cout << ' ';
    for (int i = 4; i <= 7; i++) {
        if (xyz[i] == '#') continue;
        cout << xyz[i];
    } cout << endl;
}

void create_data() {
    lib.clear();
    string base = "  ";
    for (int i = 0; i <= 11; i++)
        for (int j = 0; j <= 11; j++) {
            base[0] = patt[i]; base[1] = patt[j];
            for (int k = 0; k <= 99; k++) {
                if (match(base, k)) {
                    lib[base].push_back(k);
                }
            }
        }
}

void debug() {
    cout << compare("####", 1) << endl;
    //string test1 = "#1", test2 = "*1";
    //for (int i = 0; i < (int)lib[test1].size(); i++) cout << lib[test1][i] << ' '; cout << endl;
    //for (int i = 0; i < (int)lib[test2].size(); i++) cout << lib[test2][i] << ' '; cout << endl;
    //cout << compare("##**", 11) << endl;
    xyz = "1212#111";
    cout << one_and_only_solution() << endl;
}

int main() {
    
    create_data();
    
    //debug(); return 0;
    
    //cout << "finished!\n";
    //return 0;
    
    while(cin >> x && x[0] != '0') {
        cin >> y >> z;
        solve();
    }
    return 0;
}