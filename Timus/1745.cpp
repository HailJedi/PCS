#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;
const int L = 10000 + 5;

int f[N][L];
char str[L];
vector<int> ans;

bool update(int &x, int y) {
	if (x < y) {
		x = y;
		return true;
	}
	return false;
}

struct Bracket {
	int inc, id, len;
	int lk, rk, cmp;
	Bracket() {}
	bool operator < (const Bracket &br) const {
		int c1 = this->cmp, c2 = br.cmp;
		if (c1 == 1 && c2 == 1) {
			return this->rk < br.rk;
		}
		if (c1 == -1 && c2 == -1) {
			return this->lk > br.lk;
		}
		return c1 > c2;
	}
} brak[N];

void dfs(int i, int j) {
	if (i) {
		if (f[i][j] != f[i-1][j]) {
			dfs(i-1, j-brak[i].inc);
			ans.push_back(brak[i].id);
		} else {
			dfs(i-1, j);
		}
	}
}

int main() {
	int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
  	scanf("%s", str);
  	brak[i].len = strlen(str);
		stack<char> stk;
  	for (int j = 0; j < brak[i].len; j++) {
			if (!stk.empty() && stk.top() == '(' && str[j] == ')') {
				stk.pop();
			} else {
				stk.push(str[j]);
			}
  	}
		while (!stk.empty()) {
			if (stk.top() == '(') {
				brak[i].lk++;
			} else {
				brak[i].rk++;
			}
			stk.pop();
		}
		brak[i].inc = brak[i].lk - brak[i].rk;
		brak[i].cmp = brak[i].inc < 0 ? -1 : brak[i].inc == 0 ? 0 : 1;
  	brak[i].id = i;
  }
  sort(brak+1, brak+1+n);
  memset(f, -1, sizeof f);
  f[0][0] = 0;
  for (int i = 0; i < n; i++) {
  	for (int j = 0; j <  L; j++) {
  		if (f[i][j] != -1) {
				update(f[i+1][j], f[i][j]);
				if (j - brak[i+1].rk >= 0 && j + brak[i+1].inc < L) {
					update(f[i+1][j+brak[i+1].inc], f[i][j] + brak[i+1].len);
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
	printf("\n");
  return 0;
}
