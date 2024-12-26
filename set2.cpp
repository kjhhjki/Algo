#include<stdio.h>
#include<ctype.h>
#include<iostream>
using namespace std;

inline char nr()
{
    static char buf[1<<20],*p1,*p2;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    int x=0,f=1; char ch = nr();
    while(!isdigit(ch)) { if(ch=='-') f=-1; ch=nr(); }
    while(isdigit(ch)) { x=x*10+(ch^48); ch=nr(); }
    return x*f;
}
inline void nw(char ch)
{
    static char ob[1<<20],*op=ob;
    op-ob == 1<<20 || !ch ? fwrite(ob,1,op-ob,stdout), op=ob,(ch?*op++=ch:0): *op++=ch;
}
inline void write(int x)
{
    int n=0; char s[37];  
    if(x<0) { nw('-'); x *= -1; }
    do { s[n++] = x % 10 ^48; x /= 10; } while(x);
    do { nw(s[--n]); } while(n);
    nw('\n');
}

