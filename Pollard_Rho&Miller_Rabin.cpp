#include <bits/stdc++.h>
#define MAXN 1000006
#define For(i, a, b) for (int i = a; i <= b; ++i)
using namespace std;
typedef long long _ll;
const _ll P = 998244353ll;

_ll T,n,max_factor;
_ll qpow(_ll x, _ll n, _ll P = ::P)
{
    _ll res = 1ll;
    while (n)
    {
        if (n & 1)
            res = (__int128)res * x % P;
        x = (__int128)x * x % P;
        n >>= 1;
    }
    return res;
}
bool Miller_Rabin(_ll p) 
{ 
    if(p < 2) return 0;
    if(p == 2) return 1;
    if(p == 3) return 1;
    _ll d = p - 1, r = 0;
    while(!(d & 1)) ++r, d >>= 1;
    for(_ll k = 0; k < 10; ++k) 
    {
        _ll a = rand() % (p - 2) + 2;
        _ll x = qpow(a, d, p);
        if(x == 1 || x == p - 1) continue;
        for(int i = 0; i < r - 1; ++i) 
        {
            x = (__int128)x * x % p;
            if(x == p - 1) break;
        }
            if(x != p - 1) return 0;
    }
    return 1;
}
_ll Pollard_Rho(_ll x)
{
    if(x == 4) return 2;
    _ll s = 0, t = 0;
    _ll c = (_ll)rand() % (x - 1) + 1;
    int step = 0, goal = 1;
    _ll val = 1;
    for (goal = 1;; goal *= 2, s = t, val = 1)
    {
        for (step = 1; step <= goal; ++step)
        {
            t = ((__int128)t * t + c) % x;
            val = (__int128)val * abs(t - s) % x;
            if ((step % 127) == 0)
            {
                _ll d = __gcd(val, x);
                if (d > 1)
                    return d;
            }
        }
        _ll d = __gcd(val, x);
        if (d > 1)
            return d;
    }
}
void fac(_ll x)
{
    if (x <= max_factor || x < 2)
        return;
    if (Miller_Rabin(x))
    {                                    
        max_factor = max(max_factor, x);
        return;
    }
    _ll p = x;
    while (p >= x)
        p = Pollard_Rho(x);
    while (!(x % p))
        x /= p;
    fac(x), fac(p);
}

void solve()
{
    srand(time(0));
    cin >> n; max_factor = 0;
    fac(n); n /= max_factor;
    if (n == 1) cout << "Prime\n";
    else        cout << max_factor << '\n';;
}

int main()
{
    freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--) solve();
    return 0;
}