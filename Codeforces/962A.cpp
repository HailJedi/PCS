#include <cstdio>

using namespace std;

const int maxn = 200010;
int a[maxn];

int main() {
	int n;
	scanf("%d", &n);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		sum += a[i];
	}

	int half = (sum+1) / 2;
	sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += a[i];
		if (sum >= half) {
			printf("%d\n", i);
			break;
		}
	}

	return 0;
}