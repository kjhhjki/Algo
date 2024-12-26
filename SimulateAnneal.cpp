#include <bits/stdc++.h>
#define For(i,a,b) for(int i = (a), endi = (b); i <= endi; ++i)
#define foR(i,a,b) for(int i = (a), endi = (b); i >= endi; --i)
#define ForE(i,u)  for(int i = head[u]; i; i = e[i].nxt)
using namespace std;

using int = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using f64 = long double;

const int MAXN = 1e5+5;
const int P = 998244353;
const i64 INF = 0x7ffffffffffffll;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> distrib(0, 1);

struct item { f64 x,y,w; } a[MAXN];

int n;
f64 calc(item cur)
{
    f64 x = cur.x, y = cur.y, res = 0;
    For(i,1,n)
    {
        auto [dx,dy,w] = item{x-a[i].x, y-a[i].y, a[i].w};
        res += sqrtl(dx*dx+dy*dy)*w;
    }
    return res;
}

void SimulateAnneal(item &ans)
{
    const f64 t0 = 1e5, tn = 1e-3, d = 0.973;
    const int cnt = 1e3;
    f64 t = t0, res = calc(ans), tmp;
    item cur = ans, nxt;
    while(t > tn)
    {
        nxt = { cur.x + t * (distrib(gen)*2-1), 
                cur.y + t * (distrib(gen)*2-1), 0 };
        f64 delta = (tmp = calc(nxt)) - calc(cur);
        if(tmp < res) cur = ans = nxt, res = tmp;
        else if(exp(-delta / t) > distrib(gen)) cur = nxt;
        t *= d;
    }
    For(i,1,cnt) 
    {
        nxt = { ans.x + t * (distrib(gen)*2-1), 
                ans.y + t * (distrib(gen)*2-1), 0 };
        if((tmp=calc(nxt)) < res) ans = nxt, res = tmp;
    }
}
void solve()
{
    cin >> n;
    item ans{0,0,0};
    For(i,1,n) cin >> a[i].x >> a[i].y >> a[i].w, 
               ans.x += a[i].x, ans.y += a[i].y;
    ans.x /= n; ans.y /= n;
    SimulateAnneal(ans);
    printf("%.3Lf %.3Lf", ans.x, ans.y);
}
int main()
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1; 
    // cin >> T;
    
    while(T--) solve();
    return 0;
}