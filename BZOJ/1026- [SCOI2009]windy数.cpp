#include <iostream>
#include <cmath>

using namespace std;

int cnt[20][10];
int a, b;

void Prepare() {
	for (int i = 0; i <= 9; i++)
		cnt[1][i] = 1;
	for (int i = 2; i <= 10; i++) 
		for (int j = 0; j <= 9; j++) 
			for (int k = 0; k <= 9; k++) 
				if (abs(j-k) >= 2) 
					cnt[i][j] += cnt[i-1][k];
}

int digit[20];
int Calc(int up) {
	if (!up) return 0;
	int ret = 0, dig = 0;
	while (up) {
		digit[++dig] = up % 10;
		up /= 10;
	}
	for (int i = dig; i >= 1; i--) {
		if (i <= dig-2 && abs(digit[i+1]-digit[i+2]) <= 1) break;
		for (int j = 0+(i==dig); j < digit[i]+(i==1); j++)
			if (i == dig || abs(j-digit[i+1]) >= 2)
				ret += cnt[i][j];
	}
	for (int i = 1; i < dig; i++)
		for (int j = 1; j <= 9; j++)
			ret += cnt[i][j];
	return ret;
}

int main() {
	Prepare();
	cin >> a >> b;
	cout << Calc(b) - Calc(a-1) << endl;
	return 0;
}