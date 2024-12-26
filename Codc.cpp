#include <bits/stdc++.h>
#define MAXN 100005
#define For(I,A,B) for(int I = (A), endi = (B); I <= endi; ++I)
#define foR(I,A,B) for(int I = (A), endi = (B); I >= endi; --I)
#define ForE(I,U)  for(int i = head[U]; i; i = e[i].nxt)
using namespace std;
typedef long long _ll;
const int INF = 0x7ffffff;

struct edge { int to,nxt,w; } e[MAXN<<1];
struct Edge { int u,v,w; } E[MAXN<<1];
int t,head[MAXN];
inline void add_edge(int u, int v, int w) 
{ 
    e[++t] = (edge){v,head[u],w}, head[u] = t; 
    E[t] = (Edge){u,v,w};
}

int n,m,s,u,v,w,dis[MAXN];
int T,dfn[MAXN],low[MAXN],tot,st[MAXN],top;
int sccs,scc[MAXN],sz[MAXN];
bool ins[MAXN];
void tarjan(int u)
{
    dfn[u] = low[u] = ++T;
    st[++top] = u; ins[u] = 1;
    ForE(i,u)
    {
        int v = e[i].to;
        if(!dfn[v]) tarjan(v), low[u] = min(low[u],low[v]);
        else if(ins[v]) low[u] = min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        ++sccs;
        do
        {
            v = st[top--]; ins[v] = 0;
            scc[v] = sccs; ++sz[sccs];
            if(v == u) break;
        } while (top);
    }
}
int in[MAXN];
queue<int> q; 
void topo()
{
    int cnt = 0;
    For(u,1,sccs)
        if(!in[u])
            q.push(u), ++cnt, dis[u] = 1;
    while(!q.empty())
    {
        u = q.front(); q.pop();
        ForE(i,u)
        {
            int v = e[i].to;
            dis[v] = max(dis[v],dis[u]+e[i].w);
            if(--in[v] == 0) q.push(v), ++cnt;
        }
    }
}

_ll ans;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    while(m--)
    {
        cin >> w >> u >> v;
        if(w == 1) add_edge(u,v,0), add_edge(v,u,0);
        if(w == 2) add_edge(u,v,1);
        if(w == 3) add_edge(v,u,0);
        if(w == 4) add_edge(v,u,1);
        if(w == 5) add_edge(u,v,0);
    }
    for(int i = 1; i <= n; ++i)
        if(!dfn[i])
            tarjan(i);
    fill(head,head+n+1,0); m = t; t = 0;
    For(i,1,m)
    {
        u = E[i].u, v = E[i].v, w = E[i].w;
        if(scc[u] == scc[v])
        {
            if(w == 1) 
                { cout << -1; return 0; }
        }
        else add_edge(scc[u],scc[v],w), ++in[scc[v]];
    }
    topo();
    For(i,1,sccs) ans += dis[i]*sz[i];
    cout << ans;
    return 0;
}