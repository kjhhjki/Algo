#include<bits/stdc++.h>
#define MAXN 3003
#define MAXM 9003
#define For(i,a,b) for(int i=a;i<=b;i++)
#define foR(i,a,b) for(int i=a;i>=b;i--)
#define ForE(i,u)  for(int i=head[u];i;i=e[i].nxt)
using namespace std;
typedef long long _ll;
const _ll INF = 1000000000;

typedef struct node 
{
    _ll d,p;
    bool operator<(struct node b) { return d < b.d; };
} Node;
class heap
{
    private:
        Node a[MAXM<<1];
        int cnt = 0;
    public:
        void up(int i){ while(i>1 && a[i]<a[i>>1]) swap(a[i],a[i>>1]),i>>=1; }
        void down(int i);
        void ins(_ll d, _ll p) { a[++cnt].d = d; a[cnt].p = p; up(cnt); }
        Node front(){ return a[1]; }
        void del(){ a[1] = a[cnt--]; down(1); }
        int e(){ return cnt; }
        void fresh() { cnt = 0; }
}q;
void heap::down(int i)
{
    int m = i, l = i << 1, r = l ^ 1;
    if(l<=cnt && a[l] < a[m]) m = l;
    if(r<=cnt && a[r] < a[m]) m = r;
    if(m != i)  swap(a[i],a[m]),down(m);
}

int head[MAXN],cnt = 1;
struct edge { int to,nxt,w; } e[MAXM<<1];
void addEdge(int u, int v, _ll w)
{
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    head[u]=cnt;
}

_ll n,m,u,v,w,h[MAXN],dis[MAXN],vis[MAXN],tot[MAXN];
_ll ans;
int spfa(int u)
{
    queue<int> q;
    for(int i = 1; i <= n; ++i)
        h[i] = INF;
    q.push(u); h[u] = 0; vis[u] = 1;
    while(!q.empty())
    {
        u = q.front(); q.pop();
        vis[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt)
        {
            v = e[i].to; w = e[i].w;
            if(h[v] > h[u] + w)
            {
                h[v] = h[u] + w;
                if(!vis[v])
                {
                    vis[v] = 1, q.push(v);
                    if(++tot[v] >= n+1) return 0;
                }
            }
        }
    }
    return 1;
}
Node a;
void dij(int u)
{
    q.fresh(); memset(vis,0,sizeof(vis));
    For(i,1,n) dis[i] = INF;
    q.ins(0,u); dis[u] = 0;
    while(q.e())
    {
        a = q.front(); q.del();
        u = a.p;
        if(vis[u]) continue;
        vis[u] = 1;
        ForE(i,u)
        {
            v = e[i].to; w = e[i].w;
            if(dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if(!vis[v]) q.ins(dis[v],v);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    For(i,1,m)
    {
        int u,v,w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }
    For(i,1,n) addEdge(0,i,0);
    if(!spfa(0)) return cout << "-1", 0;
    For(u,1,n)
        ForE(i,u)
            e[i].w += h[u] - h[e[i].to];
    For(i,1,n)
    {
        ans = 0ll;
        dij(i);
        For(j,1,n)
        {
            if(dis[j] != INF)
                ans += (dis[j] + h[j] - h[i]) * j;
            else
                ans += INF * j;
        }
        cout << ans << '\n';
    }
    return 0;
}
