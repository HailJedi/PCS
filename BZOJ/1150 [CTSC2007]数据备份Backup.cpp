#include <iostream>
#include <queue>
using namespace std;

const int maxn = 100000+5;
const int INF = 1<<30;

struct Cable {
    int len, pre, nxt, id;
    Cable(int l=0, int p=0, int n=0, int id=0) {
        len = l; pre = p; nxt = n; id = id;
    }
    bool operator < (const Cable &rhs) const {
        return len > rhs.len;
    }
} cables[maxn*2];

int n, k, c1, c2, id;
priority_queue<Cable> que;
bool deleted[maxn*2];

int main() {
    cin >> n >> k;
    Cable &begin = cables[0], &end = cables[n];
    begin.len = end.len = INF;
    begin.id = 0; end.id = n;
    begin.nxt = 1; end.nxt = n;
    begin.pre = 0; end.pre = n-1;
    cin >> c1;
    for (int i = 1; i <= n-1; i++) {
        cin >> c2;
        Cable &_new = cables[i];
        _new.len = c2-c1; _new.pre = i-1;
        _new.nxt = i+1; _new.id = ++id;
        que.push(_new); c1 = c2;
    }
    int ans = 0;
    while (k--) {
        while (deleted[que.top().id]) que.pop();
        int mid = que.top().id; que.pop();
        ans += cables[mid].len;
        deleted[cables[mid].pre] = deleted[cables[mid].nxt] = 1;
        cables[mid].len = cables[cables[mid].pre].len + cables[cables[mid].nxt].len - cables[mid].len;
        cables[mid].pre = cables[cables[mid].pre].pre;
        cables[mid].nxt = cables[cables[mid].nxt].nxt;
        cables[cables[mid].pre].nxt = mid;
        cables[cables[mid].nxt].pre = mid;
        que.push(cables[mid]);
    }
    cout << ans << endl;
    return 0;
}
