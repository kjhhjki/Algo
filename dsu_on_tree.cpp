#include <bits/stdc++.h>
#define MAXN 100005
#define MAXK 10000007
#define INF 0x7FFFFFFF
#define For(I,A,B) for(int I = (A); I <= (B); ++I)
#define foR(I,A,B) for(int I = (A); I >= (B); --I)
#define ForE(I,A) for(int I = head[(A)]; I; I = e[I].nxt)
using namespace std;
typedef long long _ll;

struct Edge { int to, nxt, w; } e[MAXN<<1];
int tot,head[MAXN];
inline void addEdge(int u, int v, int w) { e[++tot] = (Edge){v,head[u],w}; head[u] = tot; }

int n,m,u,v,w,rt,Size,T,top,s[MAXN],ans[MAXN];
int query[MAXN];
int sz[MAXN],d[MAXN],mx[MAXN],dis[MAXN];
bool vis[MAXN],jud[MAXK];
void dfs1(int u, int pre)
{
    sz[u] = 1; mx[u] = 0;
    ForE(i,u)
    {
        int v = e[i].to;
        if(vis[v] || v == pre) continue;
        dfs1(v,u);
        sz[u] += sz[v];
        mx[u] = max(mx[u],sz[v]);
    }
    mx[u] = max(mx[u],Size-sz[u]);
    if(mx[u] < mx[rt]) rt = u;
}
void dfs2(int u, int pre)
{
    if(dis[u] >= MAXK) return;
    d[++T] = dis[u];
    ForE(i,u)
    {
        int v = e[i].to;
        if(vis[v] || v == pre) continue;
        dis[v] = dis[u] + e[i].w;
        dfs2(v,u);
    }
}
void solve(int u)
{
    ForE(i,u)
    {
        int v = e[i].to;
        if(vis[v]) continue;
        T = 0; dis[v] = e[i].w;
        dfs2(v,u);
        For(j,1,T) For(k,1,m)
            if(query[k] >= d[j]) 
                ans[k] |= jud[query[k]-d[j]];
        For(j,1,T) 
            jud[s[++top]=d[j]] = 1;
    }
    while(top) jud[s[top--]] = 0;
}
void dsu(int u)
{
    vis[u] = jud[0] = 1;
    solve(u);
    ForE(i,u)
    {
        int v = e[i].to;
        if(vis[v]) continue;
        Size = sz[v]; mx[rt=0] = n;
        dfs1(v,u);
        dsu(rt);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m; Size = n;
    For(i,2,n) cin >> u >> v >> w, addEdge(u,v,w), addEdge(v,u,w);
    For(i,1,m) cin >> query[i];
    mx[rt=0] = n;
    dfs1(1,-1);
    dsu(rt);    
    For(i,1,m) cout << (ans[i] ? "AYE" : "NAY") << '\n';
    return 0;
}