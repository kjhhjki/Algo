#include <bits/stdc++.h>
#define MAXN 65
#define For(i,a,b) for(_ll i = (a); i <= (b); ++i)
#define foR(i,a,b) for(_ll i = (a); i >= (b); --i)
using namespace std;
typedef long long _ll;

_ll n,x,a[MAXN],p[MAXN];

bool add(_ll x)
{
    foR(i,63,0)
        if(x & (1ll << i))
        {
            if(!p[i]) { p[i] = x; return 1; }
            x ^= p[i];
        }
    return 0;
}
_ll query()
{
    _ll ans = 0ll;
    foR(i,63,0) ans = max(ans,ans ^ p[i]);
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    For(i,1,n)
        cin >> x, add(x);
    cout << query();
    return 0; 
}