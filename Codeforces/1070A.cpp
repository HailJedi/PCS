/*
Created 2018-10-23
*/

#include <bits/stdc++.h>

using namespace std;

const int D = 500 + 5;
const int S = 5000 + 5;

int d, s;
int pre[D*S];

int hsh(int d, int s) {
	return d * S + s;
}

void print(int st) {
	if (pre[st] != -1) {
		print(pre[st]);
	}
	printf("%d", pre[st] == -1 ? st % S : st % S - pre[st] % S);
}

int main() {
	scanf("%d %d", &d, &s);
	queue<int> q;
	for (int i = 1; i <= 9; i++) {
		if (i <= s && pre[hsh(i%d, i)] == 0) {
			pre[hsh(i%d, i)] = -1;
			q.push(hsh(i%d, i));
		}
	}
	int tar = hsh(0, s);
	while (!q.empty()) {
		int st = q.front();
		q.pop();
		if (st == tar) {
			print(tar);
			return 0;
		}
		int r = st / S, t = st % S;
		for (int i = 0; i < 10; i++) {
			if (i+t <= s) { 
				int new_st = hsh((r*10+i)%d, i+t);
				if (pre[new_st] == 0) {
					pre[new_st] = st;
					q.push(new_st);
				}
			}
		}
	}
	printf("-1\n");
	return 0;
}
