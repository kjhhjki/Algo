//#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define MAXN 501
#define MAXM 500005

struct Edge
{ int nxt,to; }edge[MAXM];
int head[MAXN],cnt=1;
inline void addEdge(int u, int v)
{
    edge[++cnt].to = v;
    edge[cnt].nxt = head[u];
    head[u] = cnt;
}

int mat[MAXN],vis[MAXN];
bool dfs(int u, int t)
{
    if(vis[u] == t) return 0;
    vis[u] = t;
    for(int i = head[u]; i; i = edge[i].nxt)
        if((!mat[edge[i].to]) || dfs(mat[edge[i].to],t))      
        {   mat[edge[i].to] = u; return 1;  } 
    return 0;
}

int matl[MAXN],matr[MAXN],pre[MAXN];
void push(int v)
{
    int t;
    while(v)
    {
        t = matl[pre[v]];
        matl[pre[v]] = v;
        matr[v] = pre[v];
        v = t;
    }
}
bool bfs(int s)
{
    memset(vis,0,sizeof(vis)); memset(pre,0,sizeof(pre));
    queue<int> q; int u; q.push(s);
    while(!q.empty())
    {
        u = q.front(); q.pop();
        for(int i = head[u]; i; i = edge[i].nxt)
        {
            int v = edge[i].to;
            if(vis[v]) continue;
            vis[v] = 1; pre[v] = u;
            if(matr[v]) q.push(matr[v]);
            else { push(v); return 1; }
        }
    }
    return 0;
}

int n,m,e,a,b,ans;
int main()
{
    freopen("in.txt","r",stdin);
    cin >> n >> m >> e;
    for(int i = 1; i <= e; ++i)
        cin >> a >> b, addEdge(a,b);
    for(int i = 1; i <= n; ++i)
        if(bfs(i))
            ++ans;
    cout << ans;
    fclose(stdin);
    return 0;
}