#include <bits/stdc++.h>
#define MAXN 400005
#define For(i, a, b) for (int i = (a), endi = (b); i <= endi; ++i)
#define foR(i, a, b) for (int i = (a), endi = (b); i >= endi; --i)
#define ForE(i, u) for (int i = head[u]; i; i = e[i].nxt)
using namespace std;
typedef long long _ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int, int> pii;
typedef pair<_ll, _ll> pll;
typedef long double ld;

const ui P = 998244353, G = 3, Gi = 332748118, inv2 = 499122177;

inline char nr()
{
	static char buf[1<<22],*p1,*p2;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2)?EOF:*p1++;
}
ui read()
{
	ui x=0; char ch = nr();
	while(!isdigit(ch)) ch=nr(); 
	while(isdigit(ch)) { x=(x<<3)+(x<<1)+(ch^48); ch=nr(); }
	return x;
}
string strread()
{
	string s; char ch = nr();
	while(!isdigit(ch)) ch=nr(); 
	while(isdigit(ch)) s.push_back(ch), ch=nr();
	return s;
}

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

ui invi[MAXN];
void intg(ui a[], ui n)
{
    foR(i,n-1,1) a[i] = 1ll*a[i-1]*invi[i]%P;
    a[0] = 0;
}
void der(ui a[], ui n)
{
    For(i,1,n-1) a[i-1] = 1ll*a[i]*i%P;
    a[n-1] = 0;
}
ui c[MAXN];
void poly_inv(ui n, ui a[], ui b[])
{
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
ui aa[MAXN],b[MAXN];
void poly_ln(ui n, ui a[])
{
    init(n<<1);
    copy(a,a+n,aa); fill(aa+n,aa+limit,0);
    fill(b,b+limit,0);
    der(a,n); 
    poly_inv(n,aa,b);
    init(n<<1), NTT(a), NTT(b);
    For(i,0,limit-1) a[i] = 1ll*a[i]*b[i]%P;
    INTT(a);
    intg(a,n);
}
ui lnb[MAXN];
void poly_exp(ui n, ui a[], ui b[])
{
    ui m = 1; b[0] = 1;
    while(m < n)
    {
        m <<= 1;
        copy(b, b+m, lnb);
        poly_ln(m,lnb);
        init(m<<1);
        For(i,0,m-1) lnb[i] = a[i]<lnb[i]? P+a[i]-lnb[i]: a[i]-lnb[i];
        fill(lnb+m,lnb+limit,0);
        ++lnb[0];
        NTT(b); NTT(lnb);
        for(ui i = 0; i < limit; ++i)
            b[i] = 1ll*b[i]*lnb[i]%P;
        INTT(b);
        std::fill(b+m, b+limit, 0);
    }
}

void poly_pow(ui n, ui k1, ui k2, ui f, ui a[], ui res[])
{
    ui pos = 0;
    while(pos < n && !a[pos]) ++pos;
    if(pos >= n || (pos && f) || 1ll*pos*k1 >= n) return;
    
    ui inv0,a0;
	inv0 = qpow(a[pos], P-2); a0 = a[pos];
	for(ui i = pos; i < n; ++i) a[i] = 1ll*a[i]*inv0%P;
    copy(a+pos,a+n,a);

    init(n<<1); initw();
    For(i,0,limit-1) invi[i] = qpow(i,P-2);
    poly_ln(n-pos*k1,a);
    For(i,0,n-pos*k1-1) a[i] = 1ll*a[i]*k1%P;
    poly_exp(n-pos*k1,a,res);

    a0 = qpow(a0,k2);
    For(i,0,n-k1*pos-1) res[i] = 1ll*res[i]*a0%P;
    copy(res,res+n-k1*pos,res+k1*pos);
    fill(res,res+k1*pos,0);
}

ui n,k1,k2,f,a[MAXN],res[MAXN];
string s;
int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    n = read(); s = strread();
    For(i,0,n-1) a[i] = read();
    for(ui i = 0; s[i]; ++i)
	{
		k1 = ((10ll*k1)+(s[i]^48))%P;
		k2 = ((10ll*k2)+(s[i]^48))%(P-1);
		if(k1 >= n) f = 1;
	}
    poly_pow(n,k1,k2,f,a,res);
    For(i,0,n-1) cout << res[i] << ' ';
    return 0;
}