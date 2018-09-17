#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;
const int INF = 0x3f3f3f3f;

int bit[N];

int lowbit(int x) {
  return x & -x;
}

void add(int p) {
  for (; p < N; p += lowbit(p)) {
    bit[p]++;
  }
}

int sum(int p) {
  int ret = 0;
  for (; p; p -= lowbit(p)) {
    ret += bit[p];
  }
  return ret;
}

int lim[N], nxt[N];
vector< pair<int, int> > dragon;

int main() {
  // freopen("read.in", "r", stdin);
  int n;
  scanf("%d", &n);
  memset(lim, INF, sizeof lim);
  int d;
  for (int i = 2; i <= n; i++) {
    char s[10];
    scanf("%s %d", s, &d);
    if (s[0] == 'd') {
      dragon.push_back(make_pair(d, i));
    } else {
      lim[i] = d-1;
    }
  }
  sort(dragon.begin(), dragon.end(), greater< pair<int, int> >());
  lim[n] = INF;
  nxt[n] = n;
  for (int i = n-1; i >= 2; i--) {
    if (lim[i] == -1) {
      printf("-1\n");
      return 0;
    }
    if (lim[i] >= lim[i+1]) {
      nxt[i] = nxt[i+1];
      lim[i] = lim[i+1];
    } else {
      nxt[i] = i;
    }
  }
  int ans = 0;
  vector<int> killed;
  for (int i = 0; i < (int)dragon.size(); i++) {
    int mon = dragon[i].first, pos = dragon[i].second;
    if (sum(nxt[pos]) < lim[nxt[pos]]) {
      add(pos);
      ans += mon;
      killed.push_back(pos);
    }
  }
  for (int i = 2; i <= n; i++) {
    // printf("%d %d %d\n", i, sum(i), lim[i]);
    assert(sum(i) <= lim[i]);
  }
  if ((int)killed.size() >= d) {
    printf("%d\n", ans);
    printf("%d\n", (int)killed.size());
    sort(killed.begin(), killed.end());
    for (int i = 0; i < (int)killed.size(); i++) {
      printf("%d ", killed[i]);
    }
    printf("\n");
  } else {
    printf("-1\n");
  }
  return 0;
}
