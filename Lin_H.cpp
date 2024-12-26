#include <bits/stdc++.h>
#define MAXN 300005
#define For(i, a, b) for (int i = (a), endi = (b); i <= endi; ++i)
#define foR(i, a, b) for (int i = (a), endi = (b); i >= endi; --i)
#define ForE(i, u) for (int i = head[u]; i; i = e[i].nxt)
using namespace std;
typedef long long _ll;
typedef unsigned long long ull;
typedef int ui;
typedef pair<int, int> pii;
typedef pair<_ll, _ll> pll;
typedef long double ld;

const ui P = 998244353, G = 3, Gi = 332748118, inv2 = 499122177;
ui qpow(ui x, ui n)
{
    ui res = 1;
    while(n)
    {
        if(n&1) res = 1ll*res*x%P;
        n >>= 1; x = 1ll*x*x%P; 
    }
    return res;
}
ui limit, inv, w[MAXN];
void init(ui n)
{
    limit = 2;
    while(limit < n) limit <<= 1;
    inv = qpow(limit,P-2);
}
void initw()
{
    for(ui i = 1; i < limit; i <<= 1)
    {
        ui wn = qpow(G, (P-1)/(i<<1));
        w[i] = 1;
        for(ui j = i+1; j < (i<<1); ++j)
            w[j] = 1ll*w[j-1]*wn%P;
    }
}
void NTT(ui a[])
{   
    for(ui mid = limit>>1; mid >= 1; mid >>= 1)
    {
        for(ui j = 0; j < limit; j += mid<<1)
        {
            for(ui k = j, s = mid; k < j+mid; ++k, ++s)
            {
                ui x = a[k], y = a[k+mid];
                a[k] = x+y>=P?x+y-P:x+y;
                a[k+mid] = 1ll*(x<y?P+x-y:x-y)*w[s]%P;
            }
        }
    }
}
void INTT(ui a[])
{
    for(ui mid = 1; mid < limit; mid <<= 1)
    {
        for(ui j = 0; j < limit; j += mid<<1)
        {
            for(ui k = j, s = mid; k < j+mid; ++k, ++s)
            {
                ui x = a[k], y = (1ll * w[s] * a[k+mid])%P;
                a[k] = x+y>=P?x+y-P:x+y;
                a[k+mid] = x<y?P+x-y:x-y;
            }
        }
    }
    reverse(a+1, a+limit);
    for(ui i = 0; i < limit; ++i)
        a[i] = 1ll*a[i]*inv%P;
}

void poly_mul(ui n, ui m, ui a[], ui b[])
{
    static ui c[MAXN]; copy(b,b+m+1,c);
    init((n+m+2)<<1); fill(c+m+1,c+limit,0);
    NTT(a); NTT(c);
    For(i,0,limit-1) a[i] = 1ll*a[i]*c[i]%P;
    INTT(a); 
}

void poly_inv(ui n, ui a[], ui b[])
{
    static ui c[MAXN];
    ui m = 1; b[0] = qpow(a[0], P-2); inv = inv2;
    while(m < n)
    {
        m <<= 1; limit = m<<1; inv = 1ll*inv*inv2%P;
        std::copy(a, a+m, c);
        std::fill(c+m, c+limit, 0);
        NTT(c); NTT(b);
        for(ui i = 0; i < limit; ++i)
            b[i] = (P+2 - 1ll*c[i]*b[i]%P)%P * b[i] % P;
        INTT(b);
        std::fill(b+m, b+limit, 0);
    }
}

void poly_div(ui n, ui m, ui a[], ui b[], ui q[], ui r[])
{
    static ui fr[MAXN], gr[MAXN], qr[MAXN], g[MAXN];
	init(n<<1);
    reverse_copy(a,a+n+1,fr); reverse_copy(b,b+m+1,gr);
    fill(fr+n-m+1,fr+limit,0); fill(gr+m+1,gr+limit,0); 
	fill(qr,qr+limit,0);
    poly_inv(n-m+1,gr,qr);
	init(n<<1); 
    fill(qr+n-m+1,qr+limit,0);
    init(n<<1); NTT(qr); NTT(fr);
    For(i,0,limit-1) qr[i] = 1ll*qr[i]*fr[i]%P;
    INTT(qr);
    reverse_copy(qr,qr+n-m+1,q);
	copy(b,b+m,g);
    init(n<<1); fill(g+m+1,g+limit,0); fill(q+n-m+1,q+limit,0);
	NTT(g); NTT(q);
    For(i,0,limit-1) r[i] = 1ll*g[i]*q[i]%P;
    INTT(r); 
    For(i,0,m-1) r[i] = a[i]<r[i]? P+a[i]-r[i]: a[i]-r[i];
}

ui n,m,k,f[MAXN],res[MAXN],base[MAXN],g[MAXN],q[MAXN],r[MAXN];
int x;
int main() 
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k; init(k<<2); initw();
    For(i,0,k-1) 
    {
        cin >> x;
        while(x<0) x += P;
        g[k-1-i] = P-x;
    }
    For(i,0,k-1) 
    {
        cin >> x;
        while(x<0) x += P;
        f[i] = x + P;
    }
    g[k] = 1; base[1] = 1; res[0] = 1;
    // For(i,0,k) cout << g[i] << " \n"[i==k];
    while(n)
    {
        if(n&1)
        {
            poly_mul(k,k,res,base);
            poly_div((k)<<1,k,res,g,q,r);
            copy(r,r+k,res);
            fill(res+k,res+limit,0);
        }
        // For(i,0,k-1) cout << base[i] << " \n"[i==k-1];
        poly_mul(k,k,base,base);
        poly_div((k)<<1,k,base,g,q,r);
        copy(r,r+k,base);
        fill(base+k,base+limit,0);
        n >>= 1;
    }
    ui ans = 0;
    For(i,0,k-1) ans = (ans + 1ll*res[i]*f[i]%P)%P;
    cout << ans;
    return 0;   
}