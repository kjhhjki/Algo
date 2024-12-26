#include <bits/stdc++.h>
#define For(i,a,b) for(i32 i = (a), endi = (b); i <= endi; ++i)
#define foR(i,a,b) for(i32 i = (a), endi = (b); i >= endi; --i)
#define ForE(i,u)  for(i32 i = head[u]; i; i = e[i].nxt)
using namespace std;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using f64 = long double;

const i32 MAXN = 2e5+5;
const i32 P = 998244353;
const i64 INF = 0x7ffffffffffffll;

i32 len,blk;
struct Query
{
    i32 l,r,id;
    i32 bl,br;
    bool operator<(const Query &o) const 
    { 
        if(bl != o.bl) return l < o.l;
        return r < o.r;
    }
}query[MAXN];

i32 n,m,k,a[MAXN],b[MAXN],fst[MAXN],lst[MAXN],Ans[MAXN],vis[MAXN];
vector<i32> clr;
i32 brute(i32 l, i32 r)
{
    i32 res = 0;
    For(i,l,r) 
        if(!vis[a[i]]) vis[a[i]] = i;
        else res = max(res,i-vis[a[i]]);
    For(i,l,r) vis[a[i]] = 0;
    return res;
}
void clear()
{
    for(auto x: clr) lst[x] = fst[x] = 0;
    clr.clear();
}
void addr(i32 pos, i32 &ans)
{
    if(!fst[a[pos]]) clr.push_back(a[pos]), fst[a[pos]] = pos;
    else ans = max(ans, pos - fst[a[pos]]);
    lst[a[pos]] = pos;
}
void addl(i32 pos, i32 &ans)
{
    if(!lst[a[pos]]) lst[a[pos]] = pos;
    else ans = max(ans, lst[a[pos]] - pos);
}
void del(i32 pos)
{
    if(lst[a[pos]] == pos) lst[a[pos]] = 0;
}
void solve()
{
    cin >> n; len = sqrt(n); blk = n/len + !!(n%len);
    For(i,1,n) cin >> a[i], b[i] = a[i];
    cin >> m;
    For(i,1,m) cin >> query[i].l >> query[i].r, query[i].id = i, 
                query[i].bl = query[i].l/len+1, query[i].br = query[i].r/len+1;
    sort(b+1,b+1+n);
    k = unique(b+1,b+1+n) -b-1;
    For(i,1,n) a[i] = lower_bound(b+1,b+1+k,a[i]) - b;
    sort(query+1,query+1+m);
    for(i32 i = 1, j = 1; j <= blk; ++j)
    {
        i32 br = min(n, j*len), l = br + 1, r = l-1, ans = 0;
        
        for(; query[i].bl == j; ++i)
        {
            if(query[i].br == j)
            {
                Ans[query[i].id] = brute(query[i].l, query[i].r);
                continue;
            }
            while(r < query[i].r) addr(++r, ans);
            i32 tmp = ans, _l = l;
            while(_l > query[i].l) addl(--_l, tmp);
            Ans[query[i].id] = tmp;
            while(_l < l) del(_l++);
        }
        clear();
    }
    For(i,1,m)
        cout << Ans[i] << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    i32 T = 1; 
    // cin >> T;
    
    while(T--) solve();
    return 0;
}