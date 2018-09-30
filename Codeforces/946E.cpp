#include <bits/stdc++.h>

using namespace std;

const int N = 200010;
string s, t;
int T, n;
int cnt[10], pr0[N];

bool check(int pos) {
    int c = accumulate(cnt, cnt+10, 0);
    if (c > n - pos) return false;
    if (pr0[n-c] - pr0[pos] > 0) return true;
    int nxt = 0;
    for (int i = n-c; i < n; i++, nxt++) {
        while (!cnt[nxt]) nxt++;
        if (s[i] > '0' + nxt) return true;
        if (s[i] < '0' + nxt) return false;
    }
    return false;
}

bool can(int pos) {
    int c = accumulate(cnt, cnt+10, 0);
    return n - pos >= c;
}

void fix(int pos) {
    int c = accumulate(cnt, cnt+10, 0);
    t += string(n-pos-c, '9');
    int nxt = 9;
    while (nxt >= 0) {
        while (nxt >= 0 && !cnt[nxt]) nxt--;
        if (nxt >= 0) {
            t += '0' + nxt;
            nxt--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> T;
    while (T--) {
        cin >> s;
        n = s.length();
        
        pr0[0] = 0;
        for (int i = 0; i < n; i++)
            pr0[i+1] = pr0[i] + (s[i] > '0');
        
        if (s[0] == '1' && pr0[n] == 1) {
            printf("%s\n", string(n-2, '9').c_str());
            continue;
        }

        if (s[0] == '1' && s[n-1] == '1' && pr0[n] == 2) {
            printf("%s\n", string(n-2, '9').c_str());
            continue;
        }

        memset(cnt, 0, sizeof(cnt));
        t = "";

        for (int i = 0; i < n; i++) {
            if (i + 1 < n) {
                cnt[s[i]-'0'] ^= 1;
                if (check(i+1)) {
                    t += s[i];
                    continue;
                }
                cnt[s[i]-'0'] ^= 1;
            }
            for (char c = s[i] - 1; c >= '0'; c--) {
                cnt[c-'0'] ^= 1;
                if (can(i+1)) {
                    t += c;
                    fix(i+1);
                    break;
                }
                cnt[c-'0'] ^= 1;
            }
            break;
        }
        printf("%s\n", t.c_str());
    }
    return 0;
}