#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;

int n, b;
pair<int, int> snow[N];
pair< pair<int, int>, int> boot[N];

int bit[N];

int lowbit(int x) {
  return x & -x;
}

int sum(int p) {
  int ret = 0;
  for (; p; p -= lowbit(p)) {
    ret += bit[p];
  }
  return ret;
}

void add(int p) {
  for (; p < N; p += lowbit(p)) {
    bit[p]++;
  }
}

set<int> dist;
int dist_cnt[N];

int get_right(int p) {
  int cur = sum(p);
  int l = p, r = n;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (sum(mid) > cur) {
      r = mid;
    } else {
      l = mid;
    }
  }
  return r;
}

int get_left(int p) {
  int cur = sum(p);
  int l = 0, r = p;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (sum(mid) < cur) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return r;
}

void inc(int dis) {
  dist_cnt[dis]++;
  if (dist_cnt[dis] == 1) {
    dist.insert(-dis);
  }
}

void dec(int dis) {
  dist_cnt[dis]--;
  if (dist_cnt[dis] == 0) {
    dist.erase(-dis);
  }
}

void insert(int p) {
  int lp = get_left(p);
  int rp = get_right(p);
  add(p);
  dec(rp - lp);
  inc(p - lp);
  inc(rp - p);
}

int ans[N];

int main() {
  freopen("snowboots.in", "r", stdin);
  freopen("snowboots.out", "w", stdout);
  scanf("%d %d", &n, &b);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &snow[i].first);
    snow[i].second = i;
  }
  for (int i = 1; i <= b; i++) {
    scanf("%d %d", &boot[i].first.first, &boot[i].first.second); // s, d
    boot[i].second = i;
  }
  sort(snow+1, snow+1+n);
  sort(boot+1, boot+1+b);
  add(1);
  add(n);
  inc(n-1);
  int p = 1;
  for (int i = 1; i <= b; i++) {
    while (p <= n && snow[p].first <= boot[i].first.first) {
      if (snow[p].first != 0 || (snow[p].second != 1 && snow[p].second != n)) {
        insert(snow[p].second);
      }
      p++;
    }
    int max_dist = -(*dist.begin());
    ans[boot[i].second] = (boot[i].first.second >= max_dist);
  }
  for (int i = 1; i <= b; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
