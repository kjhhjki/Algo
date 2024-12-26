#include<bits/stdc++.h>
#define MAXN 2003
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long _ll;
const _ll P = 998244353;

_ll qpow(_ll x, _ll n)
{
    _ll res = 1ll, base = x;
    while(n)
    {
        if(n&1) res = res*base%P;
        base = base*base%P;
        n >>= 1;
    }
    return res;
}

_ll n,k,ans,res,x[MAXN],y[MAXN],inv[MAXN];
int main()
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    For(i,1,n) cin >> x[i] >> y[i], inv[i] = 1;
    For(i,1,n)
    {
        For(j,1,n) if(i != j) inv[i] = inv[i]*(x[i]-x[j])%P;
        inv[i] = y[i]*qpow(inv[i],P-2)%P;
    }
    For(i,1,n)
    {
        res = 1ll;
        For(j,1,n) if(i != j) res = res*(k-x[j])%P;
        ans = (ans+res*inv[i]%P)%P;
    }
    cout << (ans+P)%P;
    return 0;
}