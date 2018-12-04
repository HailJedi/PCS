/*
Created 2018-12-04
"Vijos1382寻找主人 Necklace"
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

char str1[N], str2[N];

int minpos(char *s) {
	int n = strlen(s);
	int i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n) {
		int dif = s[(i+k)%n] - s[(j+k)%n];
		if (dif == 0) {
			k++;
		} else {
			if (dif > 0) {
				i += k+1;
			} else {
				j += k+1;
			}
			k = 0;
			i += i == j;
		}
	}
	return min(i, j);
}

int main() {
	scanf("%s %s", str1, str2);
	int n = strlen(str1);	
	int m1 = minpos(str1), m2 = minpos(str2);
	for (int p1 = m1, p2 = m2, i = 1; i <= n; i++) {
		if (str1[p1] != str2[p2]) {
			puts("No");
			return 0;
		}
		p1 = (p1 + 1) % n;
		p2 = (p2 + 1) % n;
	}
	puts("Yes");
	for (int i = 1; i <= n; i++) {
		printf("%c", str1[m1]);
		m1 = (m1 + 1) % n;
	}
	puts("");
	return 0;
}
