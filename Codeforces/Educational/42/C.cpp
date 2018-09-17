#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int maxn = 10;
char n[maxn];
int len, ans = 100;

int Hash(int remain) {
	int res = 0;
	for (int i = 1; i <= len; i++) {
		if (n[i] == 'a') continue;
		res = res * 10 + n[i] - '0';
	}
	return res >= pow(10, remain-1) ? res : -1;
}

bool isSquare(int x) {
	if (!~x) return false;
	return int(pow((int)sqrt(x), 2)) == x;
}

void dfs(int idx, int picked) {
	if (idx == len+1) {
		if (isSquare(Hash(len-picked)))
			ans = min(ans, picked);
		return;
	}
	char t = n[idx];
	n[idx] = 'a';
	dfs(idx+1, picked+1);
	n[idx] = t;
	dfs(idx+1, picked);
}

int main() {
	scanf("%s", n+1);
	len = strlen(n+1);
	dfs(1, 0);
	if (ans != 100) 
		printf("%d\n", ans);
	else puts("-1");
	return 0;
}