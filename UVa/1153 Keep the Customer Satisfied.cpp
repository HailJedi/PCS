#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 800000;
const int maxs = 1000;
const int maxd = 2000000;
typedef pair<int, int> Pair;
Pair customer[maxn];
int n;

bool cmp(const Pair &x, const Pair &y) {
    return (x.second < y.second)
        || (x.second == y.second && x.first < y.first);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    
    int T; cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> customer[i].first >> customer[i].second;
        sort(customer, customer+n, cmp);
        
        priority_queue<int> order;
        int time = 0;
        for (int i = 0; i < n; i++) {
            time += customer[i].first;
            order.push(customer[i].first);
            if (time > customer[i].second) {
                time -= order.top(); order.pop();
            }
        }
        
        cout << order.size() << endl;
        if (T) cout << endl;
    }
    return 0;
}

