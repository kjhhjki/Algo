#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
inline char nr()
{
    static char buf[1<<20],*p1,*p2;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    int x = 0; char ch = nr();
    while(!isdigit(ch)) ch = nr();
    while(isdigit(ch)) { x = (x<<3)+(x<<1)+(ch^48); ch = nr(); }
    return x;
}
inline void nw(char ch)
{
    static char ob[1<<20],*op=ob;
    op-ob==1<<20||!ch ? fwrite(ob,1,op-ob,stdout),*(op=ob)++=ch: *op++=ch;
}
inline void write(int x)
{
    char s[37]; int t=0;
    do { s[t++]=x%10; x/=10; } while(x);
    do { nw(s[--t]^48); } while(t);
    nw('\n');
}

int n,m,l,r,st[21][MAXN];
void init()
{
    for(int i = 1; (1<<i) <= n; ++i)
        for(int j = 1; j+(1<<i)-1 <= n; ++j)
            st[i][j] = max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
int query(int l, int r)
{
    int t = (int) log2(r-l+1);
    return max(st[t][l],st[t][r-(1<<t)+1]);
}

int main()
{
    n = read(); m = read();
    for(int i = 1; i <= n; ++i)
        st[0][i] = read();
    init();
    while(m--)
        l = read(), r = read(), write(query(l,r));
    nw(0);
    return 0;
}