#include <bits/stdc++.h>
#define MAXN 2100006  
#define For(I,A,B) for(int I = A; I <= B; ++I)
#define foR(I,A,B) for(int I = A; I >= B; --I)
#define ForE(I,u) for(int I = head[u]; I; I = e[I].nxt)
using namespace std;
typedef long long _ll;
const _ll INF = 0xFFFFFFFFFFFFll;

int tot,head[MAXN];
struct edge { int to,nxt; }e[MAXN];
inline void addEdge(int u, int v) 
{ 
    e[++tot].to = v; 
    e[tot].nxt = head[u]; 
    head[u] = tot; 
}

_ll n,m,u,v,x,y;
_ll sccs,cnt,dfn[MAXN],low[MAXN],scc[MAXN],in[MAXN];
stack<int> st;
bool ins[MAXN];
inline void build(int u, int x, int v, int y)
{
        if((!x)&&(!y))
        {
            addEdge(u+n,v);
            addEdge(v+n,u);
        }
        else if((!x)&&y)
        {
            addEdge(u+n,v+n);
            addEdge(v,u);
        }
        else if(x&&(!y))
        {
            addEdge(u,v);
            addEdge(v+n,u+n);
        }
        else
        {
            addEdge(u,v+n);
            addEdge(v,u+n);
        }
}
void tarjan(int u)
{
    low[u] = dfn[u] = ++cnt;
    st.push(u); ins[u] = 1;
    ForE(i,u)
    {
        int v = e[i].to;
        if(!dfn[v]) tarjan(v), low[u] = min(low[u],low[v]);
        else if(ins[v]) low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])
    {
        ++sccs;
        while(!st.empty())
        {
            v = st.top(); st.pop(); ins[v] = 0;
            scc[v] = sccs;
            if(u == v) break;
        }
    }
}

int main()
{
    freopen("in.txt","r",stdin); // freopen("out.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    For(i,1,m)
        cin >> u >> x >> v >> y, build(u,x,v,y);
    For(i,1,n<<1) if(!dfn[i]) tarjan(i);
    For(i,1,n)
        if(scc[i] == scc[i+n])
        {
            cout << "IMPOSSIBLE";
            return 0;
        }
    cout << "POSSIBLE\n";
    For(i,1,n)
    {
        if(scc[i] < scc[i+n]) cout << 0 << " ";
        else cout << 1 << " ";
    }
    return 0;
}