#include <bits/stdc++.h>
#define MAXN 100005
#define For(I,A,B) for(int (I) = (A); (I) <= (B); ++(I))
#define foR(I,A,B) for(int (I) = (A); (I) >= (B); --(I))
using namespace std;
typedef long long _ll;
typedef pair<_ll,_ll> pll;

_ll qpow(_ll x, _ll n, _ll p)
{
    _ll res = 1; x %= p;
    while(n)
    {
        if(n&1) res = res * x % p;
        x = x * x % p;
        n >>= 1;
    }
    return res;
}

struct node
{
    int l,r;
    mutable _ll val;
    node(int l = 0, int r = 0, _ll val = 0):l(l),r(r),val(val){}
    bool operator < (const node &rhs) const { return l < rhs.l; }
};
class Chtholly_Tree
{
    private:
        set<node> s;
        typedef set<node>::iterator It;
        It split(int pos)
        {
            It it = s.lower_bound(node(pos)); 
            if(it != s.end() && it->l == pos) return it;
            --it;
            int l = it->l, r = it->r; _ll v = it->val;
            s.erase(it); s.insert(node(l,pos-1,v));
            return s.insert(node(pos,r,v)).first;
        }
    public:
        void setn(int n, _ll a[]) { s.clear(); For(i,1,n) s.insert(node(i,i,a[i])); }
        void assign(int,int,_ll);
        void add(int,int,_ll);
        _ll kth(int,int,int);
        _ll query(int,int,_ll,_ll);
}s;
void Chtholly_Tree::assign(int l, int r, _ll val)
{
    It itr = split(r+1), itl = split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,val));
}
void Chtholly_Tree::add(int l, int r, _ll val)
{
    It itr = split(r+1), itl = split(l);
    for(It it = itl; it != itr; ++it) it->val += val;
}   
_ll Chtholly_Tree::kth(int l, int r, int k)
{
    vector<pll> v;
    It itr = split(r+1), itl = split(l);
    for(It it = itl; it != itr; ++it) v.push_back(make_pair(it->val,it->r-it->l+1));
    sort(v.begin(),v.end());
    for(auto i : v)
    {
        k -= i.second;
        if(k <= 0) return i.first;
    }
    return -1;
}
_ll Chtholly_Tree::query(int l, int r, _ll x, _ll p)
{
    _ll ans = 0;
    It itr = split(r+1), itl = split(l);
    for(It it = itl; it != itr; ++it) ans = (ans + (it->r-it->l+1)*qpow(it->val,x,p)) % p;
    return ans;
}

_ll seed;
_ll rnd(_ll p)
{
    _ll res = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return res%p+1;
}

_ll n,m,op,l,r,x,y,vmax,cnt,a[MAXN];
int main()
{
    freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);
    cin >> n >> m >> seed >> vmax;
    For(i,1,n) a[i] = rnd(vmax);
    s.setn(n,a);
    while(m--)
    {
        op =  rnd(4); l = rnd(n); r = rnd(n);
        if(l > r) swap(l,r);
        if(op == 3) x = rnd(r-l+1);
        else x = rnd(vmax);
        if(op == 4) y = rnd(vmax);
        if(op == 1) s.add(l,r,x);
        if(op == 2) s.assign(l,r,x);
        if(op == 3) printf("%lld\n",s.kth(l,r,x)), ++cnt;
        if(op == 4) printf("%lld\n",s.query(l,r,x,y)), ++cnt;
    }
    return 0;
}