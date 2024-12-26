#include <bits/stdc++.h>
#define MAXN 100005
#define SQRT 352
#define For(I,A,B) for(int I = A; I <= B; ++I)
#define foR(I,A,B) for(int I = A; I >= B; --I)
using namespace std;
typedef long long _ll;
int P = 571373ll;

inline char nr()
{
    static char buf[1<<21],*p1,*p2;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline _ll read()
{
    _ll  x=0ll,f=1ll; char ch = nr();
    while(!isdigit(ch)) { if(ch=='-') f=-1ll; ch=nr(); }
    while(isdigit(ch)) { x=(x<<3)+(x<<1)+(ch^48); ch=nr(); }
    return x*f;
}
inline void nw(char ch)
{
    static char ob[1<<21],*op=ob;
    op-ob == 1<<21 || !ch ? fwrite(ob,1,op-ob,stdout), *(op=ob)++=ch: *op++=ch;
}
inline void write(_ll x)
{
    int n=0; char s[37];  
    if(x<0) { nw('-'); x *= -1; }
    do { s[n++] = x % 10 ^48; x /= 10; } while(x);
    do { nw(s[--n]); } while(n);
    nw('\n');
}

int a[MAXN];
struct node
{
    int l,r,id,len;
    int plt,mlt,sum;
    int a[SQRT];
};
class block
{
    private:
        int blk,len;
        node a[SQRT];
        inline void pushdown(int i);
    public:
        void init(int n) { len = sqrt(n); blk = ceil(1.0*n/len); }
        void build(int n);
        void add(int l, int r, int x);
        void mul(int l, int r, _ll x);
        _ll query(int l, int r);
}b;
inline void block::pushdown(int i)
{
    if(a[i].plt == 0 && a[i].mlt == 1) return;
    For(j,1,a[i].len)
        a[i].a[j] = (1ll*a[i].a[j]*a[i].mlt + a[i].plt)%P;
    a[i].mlt = 1; a[i].plt = 0;
}
void block::build(int n)
{
    init(n);
    For(i,1,blk)
    {
        a[i].l = (i-1)*len+1;
        a[i].r = (i==blk)?n:i*len;
        a[i].len = a[i].r-a[i].l+1;
        a[i].plt = 0, a[i].mlt = 1;
        For(j,1,a[i].len)
            a[i].a[j] = ::a[a[i].l+j-1];
        a[i].sum = 0;
        For(j,1,a[i].len)
            a[i].sum = (a[i].sum+a[i].a[j])%P;
    }
}
void block::add(int l, int r, int x)
{
    int bl = (l-1)/len+1, br = (r-1)/len+1;
    pushdown(bl); pushdown(br);
    if(bl == br)
    {
        For(i,l,r)
            a[bl].a[i-a[bl].l+1] = (a[bl].a[i-a[bl].l+1]+x)%P;
        a[bl].sum = (a[bl].sum+x*(r-l+1))%P;
        return;
    }
    For(i,l,a[bl].r)
        a[bl].a[i-a[bl].l+1] = (a[bl].a[i-a[bl].l+1]+x)%P;
    For(i,bl+1,br-1)
        a[i].sum = (a[i].sum+x*a[i].len)%P, a[i].plt = (a[i].plt+x)%P;
    For(i,a[br].l,r)
        a[br].a[i-a[br].l+1] = (a[br].a[i-a[br].l+1]+x)%P;
    a[bl].sum = (a[bl].sum+x*(a[bl].r-l+1))%P;
    a[br].sum = (a[br].sum+x*(r-a[br].l+1))%P;
}
void block::mul(int l, int r, _ll x)
{
    int bl = (l-1)/len+1, br = (r-1)/len+1;
    pushdown(bl);
    if(bl == br)
    {
        For(i,l,r)
            a[bl].a[i-a[bl].l+1] = a[bl].a[i-a[bl].l+1]*x%P;
        a[bl].sum = 0;
        For(j,1,a[bl].len)
            a[bl].sum = (a[bl].sum+a[bl].a[j])%P;
        return;
    }
    pushdown(br);
    For(i,l,a[bl].r)
        a[bl].a[i-a[bl].l+1] = a[bl].a[i-a[bl].l+1]*x%P;
    For(i,bl+1,br-1)
        a[i].sum = a[i].sum*x%P, a[i].plt = a[i].plt*x%P, a[i].mlt = a[i].mlt*x%P;
    For(i,a[br].l,r)
        a[br].a[i-a[br].l+1] = a[br].a[i-a[br].l+1]*x%P;
    a[bl].sum = 0;
    For(j,1,a[bl].len)
        a[bl].sum = (a[bl].sum+a[bl].a[j])%P;
    a[br].sum = 0;
    For(j,1,a[br].len)
        a[br].sum = (a[br].sum+a[br].a[j])%P;
}
_ll block::query(int l, int r)
{
    int bl = (l-1)/len+1, br = (r-1)/len+1;
    _ll ans = 0ll;
    if(bl == br)
    {
        For(i,l,r)
            ans = (ans+1ll*a[bl].a[i-a[bl].l+1]*a[bl].mlt)%P;
        ans = (ans+a[bl].plt*(r-l+1))%P;
        return ans;
    }
    For(i,l,a[bl].r)
        ans = (ans+1ll*a[bl].a[i-a[bl].l+1]*a[bl].mlt)%P;
    For(i,bl+1,br-1)
        ans = (ans+a[i].sum)%P;
    For(i,a[br].l,r)
        ans = (ans+1ll*a[br].a[i-a[br].l+1]*a[br].mlt)%P;
    ans = (ans + a[bl].plt*(a[bl].r-l+1) + a[br].plt*(r-a[br].l+1))%P;
    return ans;
}
int n,m,l,r,op;
int main()
{
    freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);
    n = read(); m = read(); P = read();
    For(i,1,n) a[i] = read()%P;
    b.build(n);
    while(m--)
    {
        op = read(); l = read(); r = read();
        if(op == 1) b.mul(l,r,read()%P);
        else if(op == 2) b.add(l,r,read()%P);
        else write(b.query(l,r));
    }
    nw(0);
    return 0;
}