#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define INF 1e30
#define maxn 8
#define maxm 105
#define maxst 15000
using namespace std;

int m, n, s[maxn], k[maxn], kk;
double c, price[maxn][maxm];
char name[maxn][10];
double d[maxm][maxst];
int opt[maxm][maxst], pre[maxm][maxst];
int buy[maxst][maxn], sell[maxst][maxn];
vector< vector<int> > states;
map< vector<int>, int > ID;

void dfs(int stock, vector<int> &lots, int totlot) {
    if (stock == n) {
        ID[lots] = (int)states.size();
        states.push_back(lots);
        return;
    }
    for (int i = 0; i <= k[stock] && totlot + i <= kk; i++) {
        lots[stock] = i;
        dfs(stock+1, lots, totlot+i);
    }
}

void init() {
    vector<int> lots(n);
    states.clear();
    ID.clear();
    dfs(0, lots, 0);
    for (int s = 0; s < (int)states.size(); s++) {
        int totlot = 0;
        for (int i = 0; i < n; i++) totlot += states[s][i];
        for (int i = 0; i < n; i++) {
            buy[s][i] = sell[s][i] = -1;
            if (states[s][i] < k[i] && totlot < kk) {
                vector<int> newst = states[s];
                newst[i]++;
                buy[s][i] = ID[newst];
            }
            if (states[s][i] > 0) {
                vector<int> newst = states[s];
                newst[i]--;
                sell[s][i] = ID[newst];
            }
        }
    }
}

void update(int day, int s, int s2, double v, int o) {
    if (v > d[day+1][s2]) {
        d[day+1][s2] = v;
        opt[day+1][s2] = o;
        pre[day+1][s2] = s;
    }
}

double dp() {
    for (int day = 0; day <= m; day++)
        for (int s = 0; s < (int)states.size(); s++)
            d[day][s] = -INF;
    
    d[0][0] = c;
    for (int day = 0; day < m; day++) {
        for (int s = 0; s < (int)states.size(); s++) {
            double v = d[day][s];
            if (v < -1) continue;
            
            update(day, s, s, v, 0);
            for (int i = 0; i < n; i++) {
                if (sell[s][i] >= 0)
                    update(day, s, sell[s][i], v + price[i][day], -i-1);
                if (buy[s][i] >= 0 && v >= price[i][day] - 1e-3)
                    update(day, s, buy[s][i], v - price[i][day], i+1);
            }
        }
    }
    return d[m][0];
}

void print(int day, int s) {
    if (day == 0) return;
    print(day-1, pre[day][s]);
    if (opt[day][s] == 0) puts("HOLD");
    else if (opt[day][s] > 0) printf("BUY %s\n", name[opt[day][s]-1]);
    else printf("SELL %s\n", name[-opt[day][s]-1]);
}

int main() {
    int kase = 0;
    while (scanf("%lf%d%d%d", &c, &m, &n, &kk) == 4) {
        if (kase++ > 0) puts("");
        for (int i = 0; i < n; i++) {
            scanf("%s%d%d", name[i], &s[i], &k[i]);
            for (int j = 0; j < m; j++) {
                scanf("%lf", &price[i][j]);
                price[i][j] *= s[i];
            }
        }
        init();
        
        double ans = dp();
        printf("%.2lf\n", ans);
        print(m, 0);
    }
    return 0;
}
