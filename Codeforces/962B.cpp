#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 200010;
char seats[maxn];
int emp[maxn];
int n, a, b;

int main() {
	scanf("%d %d %d", &n, &a, &b);
	scanf("%s", seats+1);

	int blk = 0, i = 1;
	while (i <= n) {
		if (seats[i] == '.') {
			blk++;
			do {
				emp[blk]++;
				i++;	
			} while(seats[i] == '.');
		} else {
			while (seats[i] == '*') i++;
		}
	}

	// for (int i = 1; i <= blk; i++)
		// cout << emp[i] << ' ';
	// puts("");

	int sum = 0;
	for (int i = 1; i <= blk; i++) {
		if (!a && !b) break;
		if (emp[i] & 1) {
			if (a > b) swap(a, b);
			int ta = min(a, emp[i]/2);
			int tb = min(b, emp[i]/2+1);
			sum += ta + tb;
			a -= ta; b -= tb;
		} else {
			int ta = min(a, emp[i]/2);
			int tb = min(b, emp[i]/2);
			sum += ta + tb;
			a -= ta; b -= tb;
		}
	}
	printf("%d\n", sum);
	return 0;
}