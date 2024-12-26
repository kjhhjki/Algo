#include<bits/stdc++.h>
#define MAXN 3000006
using namespace std;
typedef unsigned long long _ll;

const _ll P = 2281701377ll, G = 3ll, Gi = 760567126ll;
_ll limit, inv, r[MAXN<<2];
_ll qpow(_ll x, _ll n)
{
    _ll res = 1ll, base = x;
    while(n)
    {
        if(n&1)  (res*=base)%=P;
        n >>= 1; (base*=base)%=P;
    }
    return res;
}
void init(_ll n, _ll m)
{
    int l;
    for(limit = 1, l = 0; limit <= n + m; limit <<= 1, ++l);
    for(int i = 0; i < limit; ++i) r[i] = (r[i>>1]>>1)|((i&1)<<(l-1));
    inv = qpow(limit, P-2);
}
void NTT(_ll a[], int op)
{   
    for(int i = 0; i < limit; ++i)
        if(i < r[i])
            swap(a[i], a[r[i]]);
    for(int mid = 2; mid <= limit; mid <<= 1)
    {
        _ll wn = qpow(~op?G:Gi,(P-1)/mid);
        for(int j = 0; j < limit; j += mid)
        {
            _ll w = 1ll;
            for(int k = j; k < j+(mid>>1); ++k, (w*=wn)%=P)
            {
                _ll x = a[k], y = (w * a[k+(mid>>1)])%P;;
                a[k] = (x + y)%P;
                a[k+(mid>>1)] = (x - y + P)%P;
            }
        }
    }
    if(op == -1)
        for(int i = 0; i < limit; ++i)
            (a[i] *= inv) %= P;
}

class Bigint
{        
    private:
        static const _ll base = 100, width = 2;
    public:
        _ll len,a[MAXN];        
        Bigint operator+(Bigint&);
        Bigint& operator+=(Bigint&);
        Bigint operator*(Bigint);
        friend Bigint operator*(int,Bigint);
        friend Bigint operator*(Bigint,int);
        Bigint& operator=(int&);
        Bigint& operator=(Bigint&);
        friend ostream& operator<<(ostream&, Bigint);
        friend istream& operator>>(istream&, Bigint&);
        Bigint() { len = 0; memset(a,0,sizeof(a)); };
        Bigint(Bigint &x) { len = x.len; memcpy(a,x.a,sizeof(x.a)); }
        Bigint(int x)
        {  len = 0; memset(a,0,sizeof(a)); do { a[len++] = x % base; x /= base; } while(x);    }
};
char s[MAXN];
istream& operator>>(istream& is, Bigint &x)
{
    x.len = 0; char ch = getchar(); int n = 0; memset(x.a,0,sizeof(x.a));
    while(!isdigit(ch)) ch = getchar();
    while( isdigit(ch)) { s[++n] = ch^48; ch = getchar(); }
    while(n)
    {
        if(n>=x.width)
        {
            for(int i = x.width-1; i>=0; --i)
                x.a[x.len] = x.a[x.len]*10 + s[n-i];
            x.len++; n-=x.width;
        }
        else     
        {
            for(int i = 1; i <= n; ++i)
                x.a[x.len] = x.a[x.len]*10 + s[i];
            ++x.len;
            break;
        }
    }
    return is;
}
ostream & operator<<(ostream & os, Bigint x)
{
    os << x.a[x.len-1];
    for(int i = x.len-2; i>=0; --i)
        os << setw(x.width) << setfill('0') << (x.a[i]+x.base)%x.base;
    return os;
}
Bigint& Bigint::operator=(int &x)
{
    len = 0; memset(a,0,sizeof(a));
    do { a[len++] = x % base; x /= base; } while(x);
    return *this;
}
Bigint& Bigint::operator=(Bigint &x)
{
    len = x.len; memcpy(a,x.a,sizeof(x.a));
    return *this;
}
Bigint Bigint::operator+(Bigint &x)
{
    class Bigint res = 0;
    res.len = max(len,x.len);
    for(int i = 0; i <= res.len; ++i)
    {
        res.a[i] += x.a[i] + this->a[i];
        if(res.a[i] >= base)
            res.a[i+1]+=res.a[i]/base,res.a[i]%=base;
    }
    if(res.a[res.len+1]) ++res.len;
    return res;
}
Bigint& Bigint::operator+=(Bigint &x)
{
    len = max(len,x.len);
    for(int i = 0; i <= len; ++i)
    {
        a[i] += x.a[i];
        if(a[i] >= base)
            ++a[i+1],a[i]-=base;
    }
    if(a[len+1]) ++len;
    return *this;
}
Bigint Bigint::operator*(Bigint x)
{
    class Bigint res = *this;
    init(res.len,x.len); NTT(res.a,1); NTT(x.a,1);
    for(int i = 0; i < limit; ++i) res.a[i] = (res.a[i]*x.a[i])%P;
    NTT(res.a,-1);
    for(int i = 0; i < limit; ++i) res.a[i+1] += res.a[i]/base, res.a[i] %= base;
    for(res.len = limit; !res.a[res.len]&&res.len; --res.len);
    ++res.len;
    return res;
}
Bigint operator*(int x, Bigint a)
{
    class Bigint res = 0;
    for(int i = 0; i <= a.len; ++i)
        res.a[i] = a.a[i] * x;
    while(res.a[res.len]||res.len<a.len)
    {
        if(res.a[res.len]>=a.base)
            res.a[res.len+1] += res.a[res.len]/a.base,res.a[res.len]%=a.base;
        res.len++;
    }
    while(!res.a[res.len]&&res.len>1) res.len--;
    return res;
}
Bigint operator*(Bigint a, int x)
{
    class Bigint res = 0;
    for(int i = 0; i <= a.len; ++i)
        res.a[i] = a.a[i] * x;
    while(res.a[res.len]||res.len<a.len)
    {
        if(res.a[res.len]>=a.base)
            res.a[res.len+1] += res.a[res.len]/a.base,res.a[res.len]%=a.base;
        res.len++;
    }
    while(!res.a[res.len]&&res.len>1) res.len--;
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    class Bigint a,b;
    cin >> a >> b;
    cout << a*b;
    fclose(stdin);
    return 0;
}