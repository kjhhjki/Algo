#include <bits/stdc++.h>
#define MAXN 52
#define MAXM 52
#define For(i, a, b) for (int i = (a), endi = (b); i <= endi; ++i)
#define foR(i, a, b) for (int i = (a), endi = (b); i >= endi; --i)
#define ForE(i, u) for (int i = head[u]; i; i = e[i].nxt)
using namespace std;
typedef long long _ll;
typedef unsigned long long ull;
typedef int ui;
typedef pair<int, int> pii;
typedef pair<_ll, _ll> pll;
typedef long double ld;

struct edge { int to,nxt; } e[MAXN<<1];
int tot,head[MAXN];
inline void add_edge(int u, int v) { e[++tot] = {v,head[u]}; head[u] = tot; }

// Multiple Solution
const ull mask = chrono::steady_clock::now().time_since_epoch().count();
ull func(ull x) 
{
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

ull hsh[2][MAXN];
ull dfs(int u, int pre)
{
    hsh[0][u] = 1;
    ForE(i,u)
    {
        int v = e[i].to;
        if(v == pre) continue;
        hsh[0][u] += func(dfs(v,u));
    }
    return hsh[0][u];
}
void dp(int u, int pre)
{
    if(pre) hsh[1][u] = hsh[0][u] + func(hsh[1][pre]-func(hsh[0][u]));
    else hsh[1][u] = hsh[0][u];
    ForE(i,u)
    {
        int v = e[i].to;
        if(v == pre) continue;
        dp(v,u);
    }
}
int m,n,p[MAXN];
ull ans[MAXM];
void solve(int i)
{
    cin >> n;
    tot = 0; fill(head+1,head+1+n,0);
    For(i,1,n) 
    {
        cin >> p[i];
        if(p[i]) add_edge(i,p[i]), add_edge(p[i],i);
    }
    dfs(1,0);
    dp(1,0);
    For(u,1,n) ans[i] = max(ans[i], hsh[1][u]);
}
int main() 
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> m;
    For(i,1,m) solve(i);
    For(i,1,m) For(j,1,m) 
        if(ans[i] == ans[j])
        {   cout << j << '\n'; break; }
    return 0;   
}
