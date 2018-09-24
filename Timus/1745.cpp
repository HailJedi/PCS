#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int L = 10000 + 5;

int f[N][L];
char str[L];
vector<int> ans;
bool pre[N][L];

bool update(int &x, int y) {
	if (x < y) {
		x = y;
		return true;
	}
	return false;
}

struct Bracket {
	int val, mn_val, id, len;
	Bracket() {}
	bool operator < (const Bracket &br) const {
		if (mn_val != br.mn_val) {
		    return mn_val > br.mn_val;
		}
		if (val != br.val) {
		    return val > br.val;
		}
		return len > br.len;
	}
} brak[N];

void dfs(int i, int j) {
	if (i) {
		if (pre[i][j] == true) {
			dfs(i-1, j-brak[i].val);
			ans.push_back(brak[i].id);
		} else {
			dfs(i-1, j);
		}
	}
}

int main() {
	int n, tot_len = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
  	scanf("%s", str);
  	brak[i].len = strlen(str);
  	brak[i].val = 0;
  	brak[i].mn_val = 1e9;
  	tot_len += brak[i].len;
  	for (int j = 0; j < brak[i].len; j++) {
  		brak[i].val += (str[j] == '(' ? 1 : -1);
  		if (brak[i].val < 0) {
      		brak[i].mn_val = (brak[i].mn_val == -1e9 ? brak[i].val : min(brak[i].mn_val, brak[i].val));
  		}
  	}
  	brak[i].id = i;
  }
  sort(brak+1, brak+1+n);
  memset(f, -1, sizeof -1);
  f[0][0] = 0;
  for (int i = 0; i < n; i++) {
  	for (int j = 0; j <= tot_len; j++) {
  		if (f[i][j] != -1) {
  			if (update(f[i+1][j], f[i][j])) {
  				pre[i+1][j] = false;
  			}
  			if (j + brak[i+1].mn_val >= 0 && update(f[i+1][j+brak[i+1].val], f[i][j] + brak[i+1].len)) {
  				pre[i+1][j+brak[i+1].val] = true;
  			}
  		}
  	}
  }
  if (f[n][0] == -1) {
  	printf("0 0\n");
  	return 0;
  }
  dfs(n, 0);
  printf("%d %d\n", f[n][0], (int)ans.size());
  for (int i = 0; i < (int)ans.size(); i++) {
  	printf("%d ", ans[i]);
  }
  return 0;
}
