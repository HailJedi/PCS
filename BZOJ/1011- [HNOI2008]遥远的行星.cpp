#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define sz(x) x.size()
#define all(x) x.begin(), x.end()
#define fs first
#define sc second
#define ll long long 
#define ull unsigned ll
#define db double
#define pii pair<int, int>
#define vi vector<int>
#define INF 1e9+7

const int N = 1e5+5;
int n;
double A, M[N];

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> A;
	for (int i = 1; i <= n; i++) {
		cin >> M[i];
	}
	for (int i = 1; i <= n; i++) {
		puts("-nan");
	}
	return 0;
}