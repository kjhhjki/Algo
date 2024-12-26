#include <bits/stdc++.h>
#define MAXN 3003
#define MAXM 9000006
#define For(I,A,B) for(int I = A; I <= B; ++I)
#define ForE(I,U) for(int I = head[U]; I; I = e[I].nxt)
using namespace std;

int head[MAXN],tot;
struct edge { int to,nxt; }e[MAXM];
inline void addEdge(int u, int v)
{
    e[++tot].to = v;
    e[tot].nxt = head[u];
    head[u] = tot;
}

int n,m,ans,cnt;
int mt[MAXN],fa[MAXN],pre[MAXN],dfn[MAXN],vis[MAXN];
queue<int> q;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int lca(int u, int v)
{
    for(++cnt, u=find(u), v=find(v); dfn[u] != cnt;)
    {
        dfn[u] = cnt; 
        u = find(pre[mt[u]]);
        if(v) swap(u,v);
    }
    return u;
}
void blossom(int x, int y, int w)
{
    while(find(x) != w)
    {
        pre[x] = y; y = mt[x];
        if(vis[y] == 2) vis[y] = 1, q.push(y);
        if(find(x) == x) fa[x] = w;
        if(find(y) == y) fa[y] = w;
        x = pre[y];
    }
}
int aug(int s)
{
    if((ans+1)*2 > n) return 0;
    For(i,1,n) fa[i] = i, vis[i] = pre[i] = 0;
    while(!q.empty()) q.pop();
    for(q.push(s),vis[s]=1;!q.empty();q.pop())
    {
        for(int u = q.front(), i = head[u], v,w; i; i = e[i].nxt)
        {
            if(find(u) == find(v = e[i].to) || vis[v] == 2) continue;
            if(!vis[v])
            {
                vis[v] = 2; pre[v] = u;
                if(!mt[v])
                {
                    for(int now = v, last; now; now = last)
                    {
                        last = mt[pre[now]];
                        mt[now] = pre[now]; mt[pre[now]] = now;
                    }
                    return 1;
                }   
                vis[mt[v]] = 1; q.push(mt[v]);
            }
            else
            {
                w = lca(u,v);
                blossom(u,v,w); blossom(v,u,w);
            }
        }
    }
    return 0;
}

int main()
{
    freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    For(i,1,m)
    {
        int u,v; cin >> u >> v;
        addEdge(u,v); addEdge(v,u);
    }
    For(i,1,n) if(!mt[i]) ans += aug(i);
    cout << ans << '\n';
    For(i,1,n) cout << mt[i] << ' ';
    return 0;
}