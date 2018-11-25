#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

const int maxn = 50 + 5;
const int maxlen = 20 + 5;
const int maxs = 50*20 + 52 + 5;
const string epsilon = "";
const string dash = "-";

int n, L, ns;
string rule[maxn], sym[maxs];
string dp[maxs][maxlen];
int car[maxs], cdr[maxs];

struct Node {
    int x;
    string s;
    Node(int x, string s) : x(x), s(s) {}
    bool operator < (const Node &rhs) const {
        return s > rhs.s;
    }
};

struct Transform {
    int trans, empty;
    Transform(int t = 0, int e = 0) : trans(t), empty(e) {}
};
vector<Transform> trans[maxs];

map<string, int> sym2id;
int ID(const string &s) {
    if (!sym2id.count(s)) {
        sym2id[s] = ns;
        sym[ns++] = s;
    }
    return sym2id[s];
}

bool allLowerCase(const string &s) {
    for (int i = 0; i < s.length(); i++)
        if (!('a' <= s[i] && s[i] <= 'z')) return false;
    return true;
}

string min(const string &lhs, const string &rhs) {
    if (lhs == dash) return rhs;
    return lhs < rhs ? lhs : rhs;
}

int vis[maxs];
void search(const int len) {
    priority_queue<Node> que;
    for (int i = 0; i < ns; i++)
        if (dp[i][len] != dash) que.push(Node(i, dp[i][len]));
    memset(vis, 0, sizeof(vis));
    while (!que.empty()) {
        Node u = que.top(); que.pop();
        int x = u.x; string s = u.s;
        if (vis[x]) continue;
        vis[x] = 1;
        for (int i = 0; i < trans[x].size(); i++) {
            int tar = trans[x][i].trans;
            int emp = trans[x][i].empty;
            if (dp[emp][0] == epsilon && (dp[tar][len] == dash || dp[tar][len] > s)) {
                dp[tar][len] = s;
                que.push(Node(tar, s));
            }
        }
    }
}

void addIntermediateSymbol(const string &S) {
    if (S.length() < 2) return;
    int s = ID(S);
    int lft = ID(S.substr(0, 1));
    int rgt = ID(S.substr(1, S.length()-1));
    trans[lft].push_back(Transform(s, rgt));
    trans[rgt].push_back(Transform(s, lft));
    car[s] = lft; cdr[s] = rgt;
}

void clear() {
    memset(car, 0, sizeof(car));
    memset(cdr, 0, sizeof(cdr));
    ns = 0;
    for (int i = 0; i < maxs; i++)
        for (int j = 0; j <= L; j++) dp[i][j] = dash;
    dp[0][0] = epsilon;
    sym2id.clear();
    for (int i = 0; i < maxs; i++) trans[i].clear();
}

void readAndInit() {
    ID(epsilon);
    for (int i = 0; i < n; i++) {
        cin >> rule[i];
        int left = ID(rule[i].substr(0, 1));
        int right = ID(rule[i].substr(2));
        trans[right].push_back(Transform(left, ID(epsilon)));
        for (int j = 2; j < (int)rule[i].length(); j++)
            addIntermediateSymbol(rule[i].substr(j));
    }
}

void solve() {
    for (int len = 0; len <= L; len++) {
        for (int i = 0; i < ns; i++) {
            if (sym[i].length() == len && allLowerCase(sym[i])) dp[i][len] = sym[i];
            if (sym[i].length() < 2) continue;
            int s1 = car[i], s2 = cdr[i];
            for (int cut = 1; cut < len; cut++)
                if (dp[s1][cut] != dash && dp[s2][len-cut] != dash)
                    dp[i][len] = min(dp[i][len], dp[s1][cut] + dp[s2][len-cut]);
        }
        search(len);
    }
}

void write() {
    cout << dp[ID("S")][L] << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> n >> L && n) {
        clear();
        readAndInit();
        solve();
        write();
    }
    return 0;
}
