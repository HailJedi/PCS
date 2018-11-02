#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e5+5;
 
int st;
stack<int*> addr;
stack<int> val;
 
void change(int &old, int nw) {
    addr.push(&old);
    val.push(old);
    st++;
    old = nw;
}
 
void rollback(int old) {
    while (st > old) {
        st--;
        *addr.top() = val.top();
        addr.pop();
        val.pop();
    }
}

int C;
char info[N][10];
int r1[N], r2[N], c1[N], c2[N];
map<pair<int, int>, int> showtime;
bool ans[N];
vector< pair<int, int> > event[N << 2], quest[N << 2];
 
void add_event(int o, int l, int r, int el, int er, int p1, int p2) {
    if (el <= l && r <= er) {
        event[o].push_back(make_pair(p1, p2));
    } else {
        int mid = (l + r) >> 1;
        if (mid >= el) {
            add_event(o << 1, l, mid, el, er, p1, p2);
        }
        if (mid + 1 <= er) {
            add_event(o << 1 | 1, mid+1, r, el, er, p1, p2);
        }
    }
}
 
void add_query(int o, int l, int r, int tim, int p1, int p2) {
    if (l == r) {
        quest[o].push_back(make_pair(p1, p2));
    } else {
        int mid = (l + r) >> 1;
        if (tim <= mid) {
            add_query(o << 1, l, mid, tim, p1, p2);
        } else {
            add_query(o << 1 | 1, mid+1, r, tim, p1, p2);
        }
    }
}
 
int ask;
int fa[N << 1], rnk[N << 1];
 
int find(int x) {
    return x == fa[x] ? x : find(fa[x]);
}
 
bool same(int x, int y) {
    return find(x) == find(y);
}
 
void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        if (rnk[x] < rnk[y]) {
            change(fa[x], y);
            change(rnk[y], rnk[y] + rnk[x]);
        } else {
            change(fa[y], x);
            change(rnk[x], rnk[x] + rnk[y]);
        }
    }
}
 
void solve(int o, int l, int r) {
    int cur = st;
    for (int i = 0; i < event[o].size(); i++) {
        pair<int, int> &e = event[o][i];
        unite(e.first, e.second);
    }
    if (l == r) {
        for (int i = 0; i < quest[o].size(); i++) {
            pair<int, int> &e = quest[o][i];
            ans[++ask] = same(e.first, e.second);
        }
    } else {
        int mid = (l + r) >> 1;
        solve(o << 1, l, mid);
        solve(o << 1 | 1, mid+1, r);
    }
    rollback(cur);
}
 
int main() {
    scanf("%d", &C);
    int tim = 0;
    while (++tim) {
        scanf("%s", info[tim]);
        if (info[tim][0] == 'E') {
            break;
        } else {
            scanf("%d %d %d %d", &r1[tim], &c1[tim], &r2[tim], &c2[tim]);
        }
    }
    int scale = tim;
    tim = 0;
    while (++tim < scale) {
        int p1 = (r1[tim] - 1) * C + c1[tim], p2 = (r2[tim]- 1) * C + c2[tim];
        if (p1 > p2) swap(p1, p2);
        if (info[tim][0] == 'O') {
            showtime[make_pair(p1, p2)] = tim;
        } else
        if (info[tim][0] == 'C') {
            add_event(1, 1, scale, showtime[make_pair(p1, p2)], tim, p1, p2);
            showtime.erase(make_pair(p1, p2));
        } else {
            add_query(1, 1, scale, tim, p1, p2);
        }
    }
    for (map<pair<int, int>, int>::iterator it = showtime.begin(); it != showtime.end(); ++it) {
        add_event(1, 1, scale, it->second, scale, it->first.first, it->first.second);
    }
    ask = 0;
    for (int i = 1; i <= 2 * C; i++) {
        fa[i] = i;
        rnk[i] = 1;
    }
    solve(1, 1, scale);
    for (int i = 1; i <= ask; i++) {
        puts(ans[i] ? "Y" : "N");
    }
    return 0;
}