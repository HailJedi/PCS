#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

string S, T;

int main()
{
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    
    int C; cin >> C;
    for (int kase = 1; kase <= C; kase++) {
        cout << "Case " << kase << ": ";
        cin >> S >> T;
        
        int cnt_1_s = 0, cnt_1_t = 0;
        int pos = 0, neg = 0, m_pos = 0, m_neg = 0;
        for (int i = 0; i < S.length(); i++) {
            if (S[i] == '1') cnt_1_s++;
            if (T[i] == '1') cnt_1_t++;
            if (S[i] == '1' && T[i] == '0') pos++;
            if (S[i] == '0' && T[i] == '1') neg++;
            if (S[i] == '?') {
                if (T[i] == '0') m_pos++;
                else m_neg++;
            }
        }
        
        int ans = 0;
        
        if (cnt_1_s > cnt_1_t) ans = -1;
        else {
            ans = min(pos, neg);
            pos -= ans; neg -= ans;
            
            ans += m_neg + m_pos;
            
            ans += pos; m_neg -= pos;
            ans += neg; m_pos -= neg;
        }
        
        
        cout <<  ans << endl;
    }
    return 0;
}

