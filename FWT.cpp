#include<bits/stdc++.h>
#define MAXN 1<<17^7
#define For(i,a,b) for(int (i)=(a);(i)<=(b);++(i))
#define foR(i,a,b) for(int (i)=(a);(i)>=(b);--(i))
using namespace std;
typedef long long _ll;
const _ll P = 998244353ll;    

inline _ll qpow(_ll x, int n)
{
    _ll res = 1;
    while (n)
    {
        if (n & 1)
            res = res * x % P;
        x = x * x % P;
        n >>= 1;
    }
    return res;
}

int T,n,m;
_ll a[MAXN],b[MAXN];
_ll fa[MAXN],fb[MAXN];

void AND(_ll *f, _ll x = 1)
{
    for(int mid = 2; mid <= n; mid <<= 1)
        for(int j = 0; j < n; j += mid)
            for(int k = j; k < j + (mid>>1); ++k)
                f[k] = (f[k] + f[k+(mid>>1)]*x + P) % P;
}
void IOR(_ll *f, _ll x = 1)
{
    for(int mid = 2; mid <= n; mid <<= 1)
        for(int j = 0; j < n; j += mid)
            for(int k = j; k < j + (mid>>1); ++k)
                f[k+(mid>>1)] = (f[k+(mid>>1)] + f[k]*x + P) % P;
}
void XOR(_ll *f, _ll x = 1)
{
    for(int mid = 2; mid <= n; mid <<= 1)
        for(int j = 0; j < n; j += mid)
            for(int k = j; k < j + (mid>>1); ++k)
            {
                f[k] = (f[k] + f[k+(mid>>1)] + P) % P;
                f[k+(mid>>1)] = (f[k] - f[k+(mid>>1)]*2%P + P) % P;
                f[k] = f[k] * x % P; f[k+(mid>>1)] = f[k+(mid>>1)] * x % P;
            }
}

void solve(int id)
{
    For(i,0,n-1) fa[i] = a[i], fb[i] = b[i];
    if(id == 1) 
    {
        AND(fa); AND(fb);
        For(i,0,n-1) fa[i] = fa[i] * fb[i] % P;
        AND(fa, P-1);
        For(i,0,n-1) printf("%lld ",fa[i]);
        putchar('\n');
    }
    else if(id == 2)
    {
        IOR(fa); IOR(fb);
        For(i,0,n-1) fa[i] = fa[i] * fb[i] % P;
        IOR(fa, P-1);
        For(i,0,n-1) printf("%lld ",fa[i]);
        putchar('\n');
    }
    else
    {
        XOR(fa); XOR(fb);
        For(i,0,n-1) fa[i] = fa[i] * fb[i] % P;
        XOR(fa, qpow(2,P-2));
        For(i,0,n-1) printf("%lld ",fa[i]);
        putchar('\n');
    }
}

int main()
{
    scanf("%d",&n);
    n = 1 << n;
    For(i,0,n-1) scanf("%lld",a+i);
    For(i,0,n-1) scanf("%lld",b+i);
    solve(2); solve(1); solve(3);
    return 0;
}