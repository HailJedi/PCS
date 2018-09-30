#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 14;
ll stone[N], cpy[N];
ll ans;

int main() {
	for (int i = 0; i < N; i++) cin >> stone[i];
	for (int i = 0; i < N; i++) {
		int take = stone[i];
		memcpy(cpy, stone, sizeof(cpy));
		cpy[i] = 0;
		ll round = take / N;
		ll rest = take - round * N;
		for (int j = 0; j < N; j++) {
			cpy[j] += round;
			int dist = j > i ? j - i : j + N - i;
			if (dist <= rest) cpy[j]++;
		} 
		ll v = 0;
		for (int i = 0; i < N; i++) 
			if (!(cpy[i] & 1)) v += cpy[i];
		ans = max(ans, v);
	}
	cout << ans << endl;
	return 0;
}