#include <bits/stdc++.h>
#define For(i,a,b) for(int i = (a), endi = (b); i <= endi; ++i)
#define foR(i,a,b) for(int i = (a), endi = (b); i >= endi; --i)
using namespace std;

using int = int;
using i64 = long long;

const int P = 998244353;
const i64 INF = 0x7ffffffffffffll;

struct Mod_Pers_Seg_Tree
{
    int sz, T = 0;
    std::vector<int> rt;
    std::vector<int> cnt,ls,rs;

    Mod_Pers_Seg_Tree(int rts = 0, int _sz = 0) { init(rts,_sz); }
    void init(int rts = 0, int _sz = 0) 
    { 
        sz = _sz; int lgs = 32 - __builtin_clz(sz), lgr = 32 - __builtin_clz(rts), lg = lgs * lgr / 2;
        rt.assign(rts+1,0);
        cnt.assign(rts * lg, 0); ls.assign(rts * lg, 0); rs.assign(rts * lg, 0);
    }

    void modify(int &i, int l, int r, int k, int v)
    {
        if(!i) i = ++T;
        if(T >= cnt.size()) cnt.push_back(0), ls.push_back(0), rs.push_back(0);
        cnt[i] += v;
        if(l == r) return; 
        int mid = (l+r)>>1;
        if(k <= mid) modify(ls[i],l,mid,k,v);
        else modify(rs[i],mid+1,r,k,v);
    }

    int lowbit(int x) { return x&-x; }
    void add(int i, int k, int v)
    {
        while(i < rt.size()) 
            modify(rt[i],1,sz,k,v), i += lowbit(i);
    }
    int query(int l, int r, int k, vector<int> &L, vector<int> &R)
    {
        if(l == r) return l;
        int mid = (l+r)>>1, sum = 0;
        for(auto x: L) sum -= cnt[ls[x]];
        for(auto x: R) sum += cnt[ls[x]];
        if(k <= sum)
        {
            for(auto &x: L) x = ls[x];
            for(auto &x: R) x = ls[x];
            return query(l,mid,k,L,R);
        }
        else
        {
            for(auto &x: L) x = rs[x];
            for(auto &x: R) x = rs[x];
            return query(mid+1,r,k-sum,L,R);
        }
    }
    int query(int l, int r, int k)
    {
        std::vector<int> L,R;
        while(l) L.push_back(rt[l]), l -= lowbit(l);
        while(r) R.push_back(rt[r]), r -= lowbit(r);
        return query(1,sz,k,L,R);
    }
};

struct Query { char op; int l,r,k; };

void solve()
{
    int n,m;
    cin >> n >> m;
    vector<int> a(n+1),b(n);
    vector<Query> q(m+1);
    For(i,1,n) cin >> a[i], b[i-1] = a[i]; 
    For(i,1,m) 
    {
        cin >> q[i].op >> q[i].l >> q[i].r;
        if(q[i].op == 'Q') cin >> q[i].k;
        else b.push_back(q[i].r);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    For(i,1,n) a[i] = lower_bound(b.begin(),b.end(),a[i]) - b.begin() + 1;
    For(i,1,m) if(q[i].op == 'C') q[i].r = lower_bound(b.begin(),b.end(),q[i].r) - b.begin() + 1;
    Mod_Pers_Seg_Tree mpst(n,b.size());
    For(i,1,n) mpst.add(i,a[i],1);
    For(i,1,m)
    {
        if(q[i].op == 'C') mpst.add(q[i].l,a[q[i].l],-1), mpst.add(q[i].l,a[q[i].l]=q[i].r,1);
        else cout << b[mpst.query(q[i].l-1,q[i].r,q[i].k)-1] << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1; 
    // cin >> T;
    
    while(T--) solve();
    return 0;
}