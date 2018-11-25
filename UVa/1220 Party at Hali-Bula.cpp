#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#define maxn 200+10
#define INF 1000000000
using namespace std;

map<string, int> ID;
int id = 0;
int GetID(string name) {
    if (ID.count(name)) return ID[name];
    else return ID[name] = id++;
}

int n;
string boss, subb;
vector<int> sub[maxn];
int d[maxn][2], f[maxn][2];

int dp(int p, int st) {
    if (sub[p].empty()) {
        f[p][st] = 1;
        return d[p][st] = st;
    }
    
    int &res = d[p][st], &uni = f[p][st];
    res = st; uni = 1;
    for (int i = 0; i < sub[p].size(); i++) {
        int s = sub[p][i];
        if (st == 0) { // not choose
            int v1 = dp(s, 0), v2 = dp(s, 1); // not choose and choose
            res += max(v1, v2);
            if (v1 == v2) uni = 0;
            if (v1 > v2 && f[s][0] == 0) uni = 0;
            if (v2 > v1 && f[s][1] == 0) uni = 0;
        } else { // choose
            res += dp(s, 0); // not choose
            if (f[s][0] == 0) uni = 0;
        }
    }
    return res;
}


int main () {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) sub[i].clear();
        ID.clear(); id = 0;
        cin >> boss; GetID(boss);
        for (int i = 2; i <= n; i++) {
            cin >> subb >> boss;
            int s = GetID(subb), b = GetID(boss);
            sub[b].push_back(s);
        }
        int v1 = dp(0, 0), v2 = dp(0, 1);
//        cout << v1 << ' ' << v2 << endl;
        cout << max(v1, v2) << ' ';
        if (v1 == v2 || (v1 > v2 && !f[0][0]) || (v2 > v1 && !f[0][1])) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}
