#include <bits/stdc++.h>
#define MAXN 200005
#define INF 0x7FFFFFFFFFFFFFFFll
#define For(I,A,B) for(int (I) = (A); (I) <= (B); ++(I))
#define foR(I,A,B) for(int (I) = (A); (I) >= (B); --(I))
#define ForE(i,u) for(int (i)=head[(u)]; (i); (i) = edge[(i)].nxt)
using namespace std;
typedef long long _ll;

_ll n,N,x1,x2,Y1,y2,ans,cnt,tot,a[MAXN*2],b[MAXN*2];
class Seg_Tree
{
    public:
        _ll sum[MAXN<<3], plt[MAXN<<3], lr[MAXN<<3], rr[MAXN<<3];
        inline void pushup(int i);
    public:
        void build(int i, int l, int r);
        void add(int i, _ll x, _ll y, _ll k);
}s;
inline void Seg_Tree::pushup(int i) 
{ 
    if(plt[i]>0) sum[i] = rr[i]-lr[i]; 
    else sum[i] = sum[i*2] + sum[i*2+1];
}
void Seg_Tree::build(int i, int l, int r)
{
    lr[i] = a[l]; rr[i] = a[r];  plt[i] = 0;
    if(r-l<=1) { sum[i] = 0; return; }
    int mid = (l+r)/2, ls = i*2, rs = i*2+1;
    build(ls,l,mid); build(rs,mid,r);
    pushup(i);
}
void Seg_Tree::add(int i, _ll x, _ll y, _ll k)
{
    if(x == lr[i] && rr[i] == y) { plt[i] += k; pushup(i); return; }
    if(rr[i*2] > x) add(i*2,x,min(y,rr[i*2]),k);
    if(lr[i*2+1] < y) add(i*2+1,max(x,lr[i*2+1]),y,k);
    pushup(i);
}

struct node
{
    _ll x,Y1,y2,k;
    node(int x=0, int Y1=0, int y2=0, int k=0):x(x),Y1(Y1),y2(y2),k(k){};
    bool operator<(const node &o) const { return x < o.x; }
}p[MAXN*2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n; N = n*2;
    For(i,1,n)
    {
        cin >> x1 >> Y1 >> x2 >> y2;
        p[i] = node(x1,Y1,y2,1);
        p[i+n] = node(x2,Y1,y2,-1);
        a[i] = Y1; a[i+n] = y2;
    }
    sort(a+1,a+1+(N));
    sort(p+1,p+1+(N));
    s.build(1,1,N);
    s.add(1,p[1].Y1,p[1].y2,p[1].k);
    For(i,2,N)
    {
        ans += s.sum[1]*(p[i].x-p[i-1].x);
        s.add(1,p[i].Y1,p[i].y2,p[i].k);
    }
    cout << ans;
    return 0;
}

/*
struct Tag
{
    i64 p;
    Tag(i64 _p = 0): p(_p) {}
    void apply(const Tag &t) { p += t.p; }
};
struct Info
{
    i64 mn; i32 cnt = 0;
    Info(i64 _s = 0, i32 _c = 0): mn(_s), cnt(_c) {}
    void apply(const Tag &t) { mn += t.p; }
    Info operator+(const Info &o) const 
    { 
        Info res(min(mn,o.mn), 0);
        if(mn == res.mn) res.cnt += cnt;
        if(o.mn == res.mn) res.cnt += o.cnt;
        return res;
    }
};

struct node
{
    i32 x = 0, y1 = 0, y2 = 0, k = 0;
    bool operator<(const node &o) const { return x < o.x; }
};

void solve()
{
    i32 n;
    cin >> n;
    i32 N = n << 1;
    vector<i32> y; vector<node> ln;
    For(i,1,n)
    {
        i32 x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ln.emplace_back(x1,y1,y2,1); ln.emplace_back(x2,y1,y2,-1);
        y.push_back(y1); y.push_back(y2);
    }
    sort(y.begin(), y.end());
    sort(ln.begin(), ln.end());
    vector<Info> info(N, {0});
    For(i,1,N-1) info[i].cnt = y[i]-y[i-1];
    SegmentTree<Info,Tag> st(info);
    auto find = [&](i32 x) { return lower_bound(y.begin(), y.end(), x) - y.begin()+1; };
    auto work = [&](i32 id)
    {
        auto [x,y1,y2,k] = ln[id];
        i32 l = find(y1), r = find(y2)-1;
        if(l > r) return;
        st.apply(l,r,k);
    };
    work(0);
    i64 ans(0);
    For(i,1,N-1)
    {
        auto [mn,cnt] = st.query(1,st.n);
        ans += 1ll * (y.back()-y[0] - (!mn)*cnt) * (ln[i].x-ln[i-1].x);
        work(i);
    }
    cout << ans << '\n';
}
*/