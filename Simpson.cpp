#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld EPI = 1e-6;

ld a,b,c,d,L,R;
inline ld f(ld x) { return (c*x+d)/(a*x+b); }
inline ld simpson(ld l, ld r) { return (r-l)*(f(l)+f(r)+4*f((l+r)/2))/6; }
ld asr(ld l, ld r, ld epi, ld ans)
{
    ld mid = (l+r)/2, la = simpson(l,mid), ra = simpson(mid,r);
    if(abs(la+ra-ans) < 15.0*epi) return la+ra+(la+ra-ans)/15;
    return asr(l,mid,epi/2,la)+asr(mid,r,epi/2,ra);
}
int main()
{
    scanf("%Lf%Lf%Lf%Lf%Lf%Lf",&a,&b,&c,&d,&L,&R);
    printf("%.6Lf",asr(L,R,EPI,simpson(L,R)));
    return 0;
}