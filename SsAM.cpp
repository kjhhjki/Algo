#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 102
#define For(i, a, b) for (int i = a; i <= b; ++i)
#define foR(i, a, b) for (int i = a; i >= b; --i)
#define ForE(i, u) for (int i = head[u]; i; i = e[i].nxt)
using namespace std;
typedef long long _ll;
/*
int tp,sn,q,m,f,cur,SsAM[MAXN][MAXM];
int s[MAXN],tn,t[MAXN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> tp >> sn >> q >> m;
    For(i,1,sn) cin >> s[i];
    foR(i,sn,1)
    {
        For(j,1,m) SsAM[i-1][j] = SsAM[i][j];
        SsAM[i-1][s[i]] = i;
    }
    while(q--)
    {
        cin >> tn;
        For(i,1,tn) cin >> t[i];
        cur = 0; f = 1;
        For(i,1,tn)
        {
            if (!SsAM[cur][t[i]])
            {   f = 0; break; }
            cur = SsAM[cur][t[i]];
        }
        if (f) cout << "Yes\n";
        else cout << "No\n";
    }
}
*/
int tp,sn,q,m,f,cur;
int s[MAXN],tn,t[MAXN];
vector<int> pos[MAXN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> tp >> sn >> q >> m;
    For(i,1,sn) cin >> s[i], pos[s[i]].push_back(i);
    while(q--)
    {
        cin >> tn; cur = 0; f = 1;
        For(i,1,tn) cin >> t[i];
        For(i,1,tn)
        {
            auto it = lower_bound(pos[t[i]].begin(),pos[t[i]].end(),cur+1);
            if(it == pos[t[i]].end())
            {   f = 0; break; }
            cur = *it;
        }
        if (f) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}