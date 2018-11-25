#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int INF = 0x3f3f3f3f;

struct Student {
	int t, c, id;
	void *operator new(size_t, int t) {
		static Student pool[N*200], *p = pool;
		return p++;
	}
} *stu[N];

bool cmp(Student *st1, Student *st2) {
	return st1->t < st2->t;
}

struct Data {
	int f, lj, lk, ben;
	void *operator new(size_t, int f) {
		static Data pool[N*200], *p = pool;
		Data *ret = p++;
		ret->f = f;
		return ret;
	}
} *dat[N][5][5];

int path[N];

void dfs(int i, int j, int k) {
	if (i == 0) {
		return;
	}
	path[stu[i]->id] = dat[i][j][k]->ben;
	dfs(i-1, dat[i][j][k]->lj, dat[i][j][k]->lk);
}

int main() {
	freopen("read", "r", stdin);
	freopen("write", "w", stdout);
	
	int n, T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i <= n; i++) {
			stu[i] = new (0) Student;
			for (int s = 0; s < 25; s++) {
				dat[i][s%5][s/5] = new (INF) Data;
			}
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &stu[i]->t, &stu[i]->c);
			stu[i]->c = stu[i]->c / 10 - 1;
			stu[i]->id = i;
		}
		sort(stu+1, stu+1+n, cmp);
		dat[0][0][0]->f = 0;
		for (int i = 0; i < n; i++) {	
			int buf = 0;
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 5; k++) {
					if (dat[i][j][k]->f != INF) {
						if (i+1 < n && stu[i+1]->t == stu[i+2]->t) {
							buf = 1;
							if (dat[i+2][stu[i+1]->c][stu[i+2]->c]->f > dat[i][j][k]->f + abs(j-stu[i+1]->c) + abs(k-stu[i+2]->c)) {
								dat[i+2][stu[i+1]->c][stu[i+2]->c]->f = dat[i][j][k]->f + abs(j-stu[i+1]->c) + abs(k-stu[i+2]->c);
								dat[i+1][stu[i+1]->c][k]->lj = j;
								dat[i+1][stu[i+1]->c][k]->lk = k;
								dat[i+1][stu[i+1]->c][k]->ben = 1;
								dat[i+2][stu[i+1]->c][stu[i+2]->c]->lj = stu[i+1]->c;
								dat[i+2][stu[i+1]->c][stu[i+2]->c]->lk = k;
								dat[i+2][stu[i+1]->c][stu[i+2]->c]->ben = 2;
							}
							if (dat[i+2][stu[i+2]->c][stu[i+1]->c]->f > dat[i][j][k]->f + abs(j-stu[i+2]->c) + abs(k-stu[i+1]->c)) {
								dat[i+2][stu[i+2]->c][stu[i+1]->c]->f = dat[i][j][k]->f + abs(j-stu[i+2]->c) + abs(k-stu[i+1]->c);
								dat[i+1][j][stu[i+1]->c]->lj = j;
								dat[i+1][j][stu[i+1]->c]->lk = k;
								dat[i+1][j][stu[i+1]->c]->ben = 2;
								dat[i+2][stu[i+2]->c][stu[i+1]->c]->lj = j;
								dat[i+2][stu[i+2]->c][stu[i+1]->c]->lk = stu[i+1]->c;
								dat[i+2][stu[i+2]->c][stu[i+1]->c]->ben = 1;
							}	
						} else {
							if (dat[i+1][stu[i+1]->c][k]->f > dat[i][j][k]->f + abs(j-stu[i+1]->c)) {
								dat[i+1][stu[i+1]->c][k]->f = dat[i][j][k]->f + abs(j-stu[i+1]->c);
								dat[i+1][stu[i+1]->c][k]->f = j;
								dat[i+1][stu[i+1]->c][k]->f = k;
								dat[i+1][stu[i+1]->c][k]->f = 1;
							}
							if (dat[i+1][j][stu[i+1]->c]->f > dat[i][j][k]->f + abs(k-stu[i+1]->c)) {
								dat[i+1][j][stu[i+1]->c]->f = dat[i][j][k]->f + abs(k-stu[i+1]->c);
								dat[i+1][j][stu[i+1]->c]->lj = j;
								dat[i+1][j][stu[i+1]->c]->lk = k;
								dat[i+1][j][stu[i+1]->c]->ben = 2;
							}
						}
					}
				}
			}
			i += buf;
		}
		int ans = INF;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (dat[n][i][j]->f != INF) {
					ans = min(ans, dat[n][i][j]->f+i+j);
				}
			}
		}
		printf("%d\n", ans * 10 + 15 * n);
		for (int s = 0; s < 25; s++) {
			int j = s / 5, k = s % 5;
			if (dat[n][j][k]->f+j+k == ans) {
				dfs(n, j, k);
				break;
			}	
		}
		for (int i = 1; i <= n; i++) {
			printf("%d\n", path[i]);
		}
	}
	return 0;
}