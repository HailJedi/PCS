#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int maxn = 30;
int id;
map<string, int> name2id;
string id2name[maxn];

int ID(string name) {
	if (!name2id.count(name)) {
		name2id[name] = id;
		id2name[id++] = name;
	}
	return name2id[name];
}

int calCir[maxn][maxn];
int calLog[maxn][maxn];
int N, M;

int main() {
	int kase = 0;
	while (cin >> N >> M && N) {
		string calf, calt;
		name2id.clear(); id = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				calCir[i][j] = calLog[i][j] = 0;
		for (int i = 1; i <= M; i++) {
			cin >> calf >> calt;
			int id1 = ID(calf), id2 = ID(calt);
			calLog[id1][id2] = 1;
		}

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++) 
					calLog[i][j] |= (calLog[i][k] & calLog[k][j]);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				calCir[i][j] = (calLog[i][j] & calLog[j][i]);

		if (kase) cout << endl;
		cout << "Calling circles for data set " << ++kase << ":" << endl;;
		int done[maxn] = {0};
		for (int i = 0; i < N; i++) {
			if (done[i]) continue;
			cout << id2name[i];
			done[i] = 1;
			for (int j = 0; j < N; j++) if (!done[j]) {
				if (calCir[i][j]) {
					cout << ", " << id2name[j];
					done[j] = 1;
				}
			}
			cout << endl;
		}
	}
	return 0;
}