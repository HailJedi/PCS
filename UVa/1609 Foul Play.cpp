#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1024 + 5;
char table[maxn][maxn];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) scanf("%s", table[i]+1);
        
        vector<int> win, lose;
        for (int i = 2; i <= n; i++)
            if (table[1][i] == '1') win.push_back(i);
            else lose.push_back(i);
        
        int nt = n;
        while (nt > 1) {
            vector<int> win2, lose2, final;
            
            // phase 1
            for (int i = 0; i < lose.size(); i++) {
                int tlose = lose[i];
                bool match = false;
                for (int j = 0; j < win.size(); j++) {
                    int &twin = win[j];
                    if (twin > 0 && table[twin][tlose] == '1') {
                        printf("%d %d\n", twin, tlose);
                        win2.push_back(twin);
                        twin = 0;
                        match = true;
                        break;
                    }
                }
                if (!match) final.push_back(tlose);
            }
            
            // phase 2
            bool first = true;
            for (int i = 0; i < win.size(); i++) {
                int twin = win[i];
                if (twin > 0) {
                    if (first) { printf("1 %d\n", twin); first = false; }
                    else final.push_back(twin);
                }
            }
            
            //phase 3/4
            for (int i = 0; i < final.size(); i += 2) {
                printf("%d %d\n", final[i], final[i+1]);
                int keep = final[i];
                if (table[final[i+1]][final[i]] == '1') keep = final[i+1];
                if (table[1][keep] == '1') win2.push_back(keep);
                else lose2.push_back(keep);
            }
            win = win2;
            lose = lose2;
            nt >>= 1;
        }
    }
    return 0;
}

