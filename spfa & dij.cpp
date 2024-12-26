//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 500005
using namespace std;
typedef long long _ll;
const int INF = 2147483647;

typedef struct node 
{
    int d,p;
    bool operator<(struct node b) { return d < b.d; };
} Node;
class heap
{
    private:
        Node a[MAXM];
        int cnt = 0;
    public:
        void up(int i){ while(i>1 && a[i]<a[i>>1]) swap(a[i],a[i>>1]),i>>=1; }
        void down(int i);
        void ins(int d, int p) { a[++cnt].d = d; a[cnt].p = p; up(cnt); }
        Node front(){ return a[1]; }
        void del(){ a[1] = a[cnt--]; down(1); }
        int e(){ return cnt; }
};
void heap::down(int i)
{
    int m = i, l = i << 1, r = l ^ 1;
    if(l<=cnt && a[l] < a[m]) m = l;
    if(r<=cnt && a[r] < a[m]) m = r;
    if(m != i)  swap(a[i],a[m]),down(m);
}

struct edge { int to,nxt,w; } e[MAXM];
int cnt,head[MAXN];
inline void addEdge(int u, int v, int w)
{   
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt  = head[u];
    head[u] = cnt;
}

int n,m,s,x,y,w,d[MAXN],v[MAXN];
void spfa(int u)
{
    queue<int> q;
    memset(v,0,sizeof(v));
    for(int i = 1; i <= n; ++i)
        d[i] = INF;
    q.push(u); d[u] = 0; v[u] = 1;
    while(!q.empty())
    {
        u = q.front(); q.pop();
        v[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt)
        {
            x = e[i].to; w = e[i].w;
            if(d[x] > d[u] + w)
            {
                d[x] = d[u] + w;
                if(!v[x])
                    v[x] = 1, q.push(x);
            }
        }
    }
}
void dij(int u)
{
    heap a; Node b;
    memset(v,0,sizeof(v));
    for(int i = 1; i <= n; ++i)
        d[i] = INF;
    d[u] = 0; a.ins(0,u);
    while(a.e())
    {
        b = a.front(); a.del();
        u = b.p;
        if(v[u]) continue;
        v[u] = 1;
        for(int i = head[u]; i; i = e[i].nxt)
        {
            x = e[i].to; w = e[i].w;
            if(d[x] > d[u] + w)
            {
                d[x] = d[u] + w;
                if(!v[x])
                    a.ins(d[x],x);
            }
        }
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&s);
    while(m--)
        scanf("%d%d%d",&x,&y,&w),addEdge(x,y,w);
    dij(s);
    for(int i = 1; i <= n; ++i)
        printf("%d ",d[i]);
    return 0;
}