#define LOCAL

#ifdef LOCAL
#undef EULAR
#include <bits/stdc++.h>
#define MAXN 500005
#define For(i, a, b) for (int i = (a), endi = (b); i <= endi; ++i)
#define foR(i, a, b) for (int i = (a), endi = (b); i >= endi; --i)
#define ForE(i, u) for (int i = head[u]; i; i = e[i].nxt)
using namespace std;
typedef long long _ll;
typedef long double ld;

struct Edge { int to, nxt; } e[MAXN<<1];
int tot, head[MAXN];
inline void add_edge(int u, int v) { e[++tot] = (Edge){v, head[u]}; head[u] = tot; }

int n,m,s,u,v;
int T,dfn[MAXN];
int st[23][MAXN];

void dfs(int u, int pre)
{
    dfn[u] = ++T; st[0][T] = pre;
    ForE(i,u)
        if (e[i].to != pre)
            dfs(e[i].to,u);
}

inline int check(int u, int v)
{
    return dfn[u] < dfn[v] ? u : v;
}
void init()
{
    For(i,1,22)
        for (int j = 1; j + (1<<i) - 1 <= T; ++j)
            st[i][j] = check(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
int query(int l, int r)
{
    int k = log2(r-l);
    return check(st[k][l+1],st[k][r-(1<<k)+1]);
}

int main()
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> s;
    For(i,2,n)
    {
        cin >> u >> v;
        add_edge(u,v); add_edge(v,u);
    }
    dfs(s,0); init();
    while(m--)
    {
        cin >> u >> v;
        int l = dfn[u], r = dfn[v];
        if (l > r) swap(l,r);        
        cout << (u==v?u:query(l,r)) << '\n';
    }
    return 0;
}
#endif


#ifdef EULER
#ifndef LOCAL
#include <bits/stdc++.h>
#define MAXN 500005
#define For(i, a, b) for (int i = (a), endi = (b); i <= endi; ++i)
#define foR(i, a, b) for (int i = (a), endi = (b); i >= endi; --i)
#define ForE(i, u) for (int i = head[u]; i; i = e[i].nxt)
using namespace std;
typedef long long _ll;
typedef long double ld;

struct Edge { int to, nxt; } e[MAXN<<1];
int tot, head[MAXN];
inline void add_edge(int u, int v) { e[++tot] = (Edge){v, head[u]}; head[u] = tot; }

int n,m,s,u,v;
int T,mp[MAXN<<1],dep[MAXN],dfn[MAXN];

void dfs(int u, int pre)
{
    mp[++T] = u; dfn[u] = T;
    ForE(i,u)
    {
        int v = e[i].to;
        if (v == pre) continue;
        dep[v] = dep[u] + 1;
        dfs(v,u);
        mp[++T] = u;
    }
}

int st[23][MAXN<<1];
inline int check(int u, int v)
{
    return dep[u] < dep[v] ? u : v;
}
void init()
{
    For(i,1,T) st[0][i] = mp[i];
    For(i,1,22)
        for (int j = 1; j + (1<<i) - 1 <= T; ++j)
            st[i][j] = check(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
int query(int l, int r)
{
    int k = log2(r-l+1);
    return check(st[k][l],st[k][r-(1<<k)+1]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> s;
    dep[s] = 0;
    For(i,2,n)
    {
        cin >> u >> v;
        add_edge(u,v); add_edge(v,u);
    }
    dfs(s,0); init();
    while(m--)
    {
        cin >> u >> v;
        int l = dfn[u], r = dfn[v];
        if (l > r) swap(l,r);        
        cout << query(l,r) << '\n';
    }
    return 0;
}
#endif
#endif