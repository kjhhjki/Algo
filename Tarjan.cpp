//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define MAXN 500005
#define MAXM 4000005
using namespace std;
typedef long long _ll;

struct edge { int to,nxt; } e[MAXM];
int cnt = 1,head[MAXN];
inline void addEdge(int u, int v)
{   
    e[++cnt].to = v;
    e[cnt].nxt  = head[u];
    head[u] = cnt;
}

int n,m,x,y,t,res;
int dfn[MAXN],low[MAXN],dcc[MAXN];
bool b[MAXM];
vector<vector<int>> ans;

//tarjan for e-dcc
void tarjan(int u, int ed)
{
    dfn[u] = low[u] = ++t;
    for(int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(!dfn[v])
        {
            tarjan(v,i);
            if(dfn[u] < low[v])
                b[i] = b[i^1] = 1;
            low[u] = min(low[u],low[v]);
        }
        else if(i^1 != ed) low[u] = min(low[u],dfn[v]);
    }
}
// dfs for e-dcc
void dfs(int u, int cc)
{
    dcc[u] = cc;
    ans[cc-1].push_back(u);
    for(int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(dcc[v]||b[i]) continue;
        dfs(v,cc);
    }
}

void tarjan(int u, int in) {
  low[u] = dfn[u] = ++bcc_cnt;
  st.push(u), vis[u] = 1;
  for (int i = hd[u]; i; i = e[i].nt) {
    int v = e[i].to;
    if (i == (in ^ 1)) continue;
    if (!dfn[v])
      tarjan(v, i), low[u] = min(low[u], low[v]);
    else if (vis[v])
      low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    vector<int> t;
    t.push_back(u);
    while (st.top() != u) t.push_back(st.top()), vis[st.top()] = 0, st.pop();
    st.pop(), ans.push_back(t);
  }
}

// tarjan for v-dcc
int s[MAXN],top,rt;
void tarjan(int u)
{
    dfn[u] = low[u] = ++t;
    s[++top] = u;
    if(u==rt && !head[u]) { ans.push_back(vector<int>()); ans[res++].push_back(u); return; }
    int c = 0,d;
    for(int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
            if(low[v] >= dfn[u])
            {
                ++c;
                if(x^rt||c>1) b[i] = 1; ans.push_back(vector<int>());
                do { d = s[top--]; ans[res].push_back(d); } while(d != v);
                ans[res++].push_back(u);
            }
        }
        low[u] = min(low[u],dfn[v]);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    while(m--) { scanf("%d%d",&x,&y); if(x^y) addEdge(x,y),addEdge(y,x); }
    for(int i = 1; i <= n; ++i)
        if(!dfn[i])
            tarjan(i,0);
    for(int i = 1; i <= n; ++i)
        if(dcc[i])
            dfs(i,++res);
    printf("%d\n",res);
    for(int i = 0; i < res; ++i)
    {
        printf("%d",ans[i].size());
        for(int j = 0; j < ans[i].size(); ++j)
            printf(" %d",ans[i][j]);
        putchar('\n');
    }
    return 0;
}