#include <bits/stdc++.h>
#define MAXN 100005
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
const int INF = 0x7fffffff;

inline char nr()
{
    static char buf[1<<23],*p1,*p2;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    int x=0; char ch = nr();
    while(!isdigit(ch)) { ch=nr(); }
    while(isdigit(ch)) { x=(x<<3)+(x<<1)+(ch^48); ch=nr(); }
    return x;
}

int qpow(int x, int n, int P)
{
    int res = 1;
    while(n)
    {
        if(n&1) res = 1ll*res*x%P;
        x = 1ll*x*x%P; n >>= 1;
    }
    return res;
}

_ll exgcd(_ll a, _ll b, _ll &x, _ll &y)
{
    x = 1; y = 0;
    _ll q, x1 = 0, y1 = 1, a1 = a, b1 = b, x2,y2,b2;
    while(b1)
    {
        q = a1 / b1;
        x2 = x1;     x1 = x - q * x1;    x = x2;
        y2 = y1;     y1 = y - q * y1;    y = y2;
        b2 = b1;     b1 = a1 - q * b1;   a1 = b2;
    }
    return a1;
}
_ll inv(_ll a, _ll p)
{
    _ll x = 0, y = 0;
    exgcd(a,p,x,y);
    return (x%p+p)%p;
}


pii p[MAXN];
int bsgs(int a, int b, int P)
{
    int k = ceil(sqrt(P));
    p[0] = pii(b,0);
    For(i,1,k) p[i] = pii(1ll*p[i-1].first*a%P,i);
    sort(p, p+1+k, [](const pii &a, const pii &b) { return a.first==b.first? a.second > b.second: a.first < b.first; }); 
    p[k+1] = pii(-1,0);
    int tmp = qpow(a,k,P);
    int x = 1;
    For(i,1,k)
    {
        x = 1ll*x*tmp%P;
        auto it = lower_bound(p,p+1+k,pii(x,0));
        if(x == it->first) return i*k-it->second;
    }
    return INF;
}
int exbsgs(int a, int b, int P)
{
    int g; int tmp = 1, k = 0;
    if(b == 1 || P == 1) return 0;
    while((g = __gcd(a,P)) > 1)
    {
        if(b%g) return INF;
        P /= g; b /= g;
        tmp = 1ll*tmp*(a/g)%P; ++k;
        if(tmp == b%P) return k;
    }
    int ans = bsgs(a,1ll*b*inv(tmp,P)%P,P);
    if(ans < INF) return ans + k;
    else return INF;
}

int a,b,P;
int main() 
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    while(1)
    {
        a = read(); P = read(); b = read();
        if(!a || !b || !P) break;
        if (b==1 || P==1) { cout << "0\n"; continue; }
        int ans = exbsgs(a%P,b%P,P);
        if(ans < INF) cout << ans << '\n';
        else cout << "No Solution\n";
    }
    return 0;   
}
