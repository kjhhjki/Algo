//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define MAXN 501
#define INF 1145141919810ll
typedef long long _ll;
using namespace std;

_ll n,m,x,y,res,d,v[MAXN],mat[MAXN],pre[MAXN],ll[MAXN],lr[MAXN],s[MAXN],e[MAXN][MAXN];

void bfs(_ll u)
{
    _ll y1=0; y=0; memset(pre,0,sizeof(pre));
    for(_ll i = 1; i <= n; ++i) s[i] = INF;
    mat[y] = u;
    while(1)
    {
        x = mat[y]; d = INF; v[y] = 1;
        for(_ll i = 1; i <= n; ++i)
        {
            if(v[i]) continue;
            if(s[i] > ll[x] + lr[i] - e[x][i])
                s[i] = ll[x] + lr[i] - e[x][i], pre[i] = y;
            if(s[i] < d) d = s[i], y1 = i;
        }
        for(_ll i = 0; i <= n; ++i)
        {
            if(v[i]) ll[mat[i]] -= d, lr[i] += d;
            else     s[i] -= d;
        }
        y = y1;
        if(mat[y] == -1) break;
    }
    while(y) mat[y] = mat[pre[y]], y = pre[y];
}
_ll KM()
{
    _ll res = 0ll;
    memset(mat,-1,sizeof(mat)); memset(ll,0,sizeof(ll)); memset(lr,0,sizeof(lr));
    for(_ll i = 1; i <= n; ++i)
    {   memset(v,0,sizeof(v)); bfs(i);    }
    for(_ll i = 1; i <= n; ++i) 
        if(mat[i]!=-1)
            res += e[mat[i]][i];
    return res;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            e[i][j] = -INF;
    for(int i = 1; i <= m; ++i)
    {   cin >> x >> y; cin >> e[x][y];  }
    cout << KM() << endl;
    for(int i = 1; i <= n; ++i)
        printf("%lld ",mat[i]);
    return 0;
}