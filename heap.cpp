#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;
typedef long long _ll;

struct node
{
    _ll id,v;
    bool operator<(node b) { return v == b.v? id < b.id: v < b.v; };   
}a[MAXN];   

_ll n,m,f,x,y,rt[MAXN],lc[MAXN],rc[MAXN],d[MAXN] = {-1};
bool v[MAXN];

_ll find(_ll x) { return x == rt[x]? x: rt[x] = find(rt[x]); }
_ll merge(_ll x, _ll y)
{
    if(!x||!y) return x + y;
    if(a[y] < a[x]) swap(x,y);
    rc[x] = merge(rc[x],y);
    if(d[lc[x]] < d[rc[x]]) swap(lc[x],rc[x]);
    d[x] = d[lc[x]] + 1;
    return x;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        scanf("%lld",&a[i].v), a[i].id = i, rt[i] = i;  
    while(m--)
    {
        scanf("%lld%lld",&f,&x);
        if(f^1)
        {
            if(v[x]) { printf("-1\n"); continue; }
            x = find(x);
            printf("%lld\n",a[x].v);
            v[x] = 1;
            rt[lc[x]] = rt[rc[x]] = rt[x] = merge(lc[x],rc[x]);
            lc[x] = rc[x] = d[x] = 0;
        }
        else
        {
            scanf("%lld",&y);
            if(v[x] || v[y])  continue;
            x=find(x);  y=find(y);
            if(x != y)  rt[x] = rt[y] = merge(x,y);
        }
    }
    return 0;
}