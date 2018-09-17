#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100010;

typedef long long ll;

ll x[maxn], y[maxn];
int n;

bool OnLine(int a, int b, int c) { // return true if a, b, c are collinear
	return (y[a] - y[c]) * (x[a] - x[b]) == (y[a] - y[b]) * (x[a] - x[c]);
}

bool Check(int a, int b) { // suppose a and b are on same line
	vector<int> vec;
	for (int i = 1; i <= n; i++)
		if (!OnLine(i, a, b)) vec.push_back(i);
	for (int i = 2; i < vec.size(); i++)
		if (!OnLine(vec[0], vec[1], vec[i])) return false;
	return true;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> x[i] >> y[i];

	if (n <= 4 || Check(1, 2) || Check(2, 3) || Check(1, 3))
		cout << "YES";
	else cout << "NO";

	return 0;
}