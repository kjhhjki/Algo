#include <bits/stdc++.h>
#define For(I,A,B) for(int (I) = (A); (I) <= (B); ++(I))
#define foR(I,A,B) for(int (I) = (A); (I) >= (B); --(I))
#define ForE(I,U)  for(int (I) = head[(U)]; (I); (I) = e[(I)].nxt)
#define MAXN 5003
#define MAXM 400005
using namespace std;

int head[MAXN],tot;
struct Edge
{
    int to,nxt,w;
    Edge(int to = 0, int nxt = 0, int w = 0):to(to),nxt(nxt),w(w){}
}e[MAXM];
void addEdge(int u, int v, int w)
{
    e[++tot] = Edge(v,head[u],w); 
    head[u] = tot;
}

struct Node 
{
    int to,w;
    Node(int to = 0, int w = 0):to(to),w(w){}
    bool operator<(const struct Node &b) { return w < b.w; };
};
class heap
{
    private:
        Node a[MAXM];
        int cnt = 0;
    public:
        void up(int i){ while(i>1 && a[i]<a[i>>1]) swap(a[i],a[i>>1]),i>>=1; }
        void down(int i);
        void ins(Node x) { a[++cnt] = x; up(cnt); }
        Node front(){ return a[1]; }
        void del(){ a[1] = a[cnt--]; down(1); }
        int e(){ return cnt; }
        bool empty(){ return cnt == 0; }
};
void heap::down(int i)
{
    int m = i, l = i << 1, r = l ^ 1;
    if(l<=cnt && a[l] < a[m]) m = l;
    if(r<=cnt && a[r] < a[m]) m = r;
    if(m != i)  swap(a[i],a[m]),down(m);
}

bool vis[MAXN];
int prim(int n)
{
    int u, k, res = 0;
    heap q; q.ins(Node(1,0));                             //堆优化
    while(n--)
    {
        u = q.front().to; k = q.front().w; q.del();      //取出最小新增节点
        vis[u] = 1;                                      //标记是否在生成树中
        ForE(i,u) 
            if(!vis[e[i].to]) 
                q.ins(Node(e[i].to,e[i].w));             //加入新增边
        while(q.e()&&vis[q.front().to]) q.del();         //删除已加入节点
        res += k;
        if(q.empty()&&n) return -1;                      //是否连通
    }
    return res;
}

int n,m,b,a,k;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // freopen("in.txt","r",stdin);
    cin >> n >> m;
    while(m--)
    {
        cin >> a >> b >> k;
        addEdge(a,b,k); addEdge(b,a,k);
    }
    m = prim(n);
    if(m == -1) cout << "orz";
    else cout << m;
    return 0;
}