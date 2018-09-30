#include <bits/stdc++.h>

using namespace std;

const int N = 20100;

struct object {
    bool isBase;
    int id;
    int x, y;
} obj[N], piv;

int n;
int ans[N];

bool cmp(object &o1, object &o2) {
    if (o1.y != o2.y) return o1.y < o2.y;
    return o1.x < o2.x;
}

bool cmp2(object &o1, object &o2) {
    return ((o1.x-piv.x)*(o2.y-piv.y) - (o1.y-piv.y)*(o2.x-piv.x)) < 0;
}

void solve(int l, int r) {
    if (l > r) return;
    int mn = min_element(obj+l, obj+r+1, cmp)-obj;
    swap(obj[l], obj[mn]);
    piv = obj[l];
    sort(obj+l+1, obj+r+1, cmp2);
    int ct1 = 0, ct2 = 0, mid = r;
    while (!(piv.isBase != obj[mid].isBase && ct1 == ct2)) {
        if (obj[mid].isBase == piv.isBase) ct1++;
        else ct2++;
        mid--;
    }
    if (piv.isBase) ans[obj[mid].id] = piv.id;
    else ans[piv.id] = obj[mid].id;
    solve(l+1, mid-1);
    solve(mid+1, r);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> obj[i].x >> obj[i].y;
        obj[i].isBase = false;
        obj[i].id = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> obj[i+n].x >> obj[i+n].y;
        obj[i+n].isBase = true;
        obj[i+n].id = i;
    }
    solve(1, 2*n);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}