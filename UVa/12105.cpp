#include <bits/stdc++.h>

using namespace std;

const int N = 128;
const int M = 3024;
const int dig[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int f[N][M];
int p[N][M];

int main() {
//	freopen("read", "r", stdin);
//	freopen("write", "w", stdout);
	
  int n, m, kase = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
    memset(f, -1, sizeof f);
    memset(p, 0, sizeof p);
    f[0][0] = 0;
    int max_len = 0;
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        if (f[i][j] != -1) {
          for (int k = 0; k < 10; k++) {
            int ii = i + dig[k], jj = (j*10+k) % m;
            f[ii][jj] = max(f[ii][jj], f[i][j] + 1);
          }
        }
      }
      max_len = max(max_len, f[i][0]);
    }
    for (int i = n; i >= 0; i--) {
      for (int j = 0; j < m; j++) {
        if (f[i][j] != -1) {
          for (int k = 0; k < 10; k++) {
            int ii = i + dig[k], jj = (j*10+k) % m;
            if (ii <= n && f[ii][jj] == f[i][j] + 1) {
              p[i][j] |= p[ii][jj];
            }
          }
        }
      }
      if (f[i][0] == max_len) {
        p[i][0] = 1;
      }
    }
    printf("Case %d: ", ++kase);
		vector<int> ans;
		int zero = 0;
    for (int i = 0, ii = 0, jj = 0; i < max_len; i++) {
      for (int k = 9; k >= 0; k--) {
        int iii = ii + dig[k], jjj = (jj*10 + k) % m;
        if (p[iii][jjj] && f[iii][jjj] == f[ii][jj] + 1) {
          ii = iii;
          jj = jjj;
					ans.push_back(k);
					zero |= k;
          break;
        }
      }
    }
    if (max_len == 0) {
      printf("-1");
    } else {
			if (zero == 0) {
				printf("0");
			} else {
				for (int i = 0; i < ans.size(); i++) {
					printf("%d", ans[i]);
				}
			}
		}
    puts("");
  }
  return 0;
}
