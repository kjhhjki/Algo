#include <bits/stdc++.h>
#define MAXN 1000006
#define For(I,A,B) for(ui I = (A), endi = (B); I <= endi; ++I)
#define foR(I,A,B) for(ui I = (A), endi = (B); I >= endi; --I)
using namespace std;
typedef long long _ll;
typedef unsigned int ui;

_ll qpow(_ll x, _ll n, _ll p)
{
    _ll res = 1;
    while(n)
    {
        if(n&1) res = res * x % p;
        x = x * x % p; n >>= 1;
    }
    return res;
}

int cnt,p[MAXN],phi[MAXN];
bool v[MAXN],b[MAXN<<1];
void get_prime(int n)
{
    v[1] = v[0] = 1; b[2] = b[4] = 1; phi[1] = 1;
    For(i,2,n)
    {
        if(!v[i])
        {
            p[++cnt] = i; phi[i] = i-1;
            if(i > 2) for(_ll j = i; j <= n; j *= i) b[j] = b[j<<1] = 1;
        }
        for(int j = 1; j <= cnt && 1ll*i*p[j] <= n; ++j)
        {
            v[i*p[j]] = 1;
            if(!(i%p[j])) { phi[i*p[j]] = phi[i] * p[j]; break; }
            phi[i*p[j]] = phi[i] * phi[p[j]];
        }
    }
}

int T,n,q,d,m,mm,g;
bool vis[MAXN];
int main()
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    get_prime(MAXN-6);
    cin >> T;
    while(T--)
    {
        cin >> n >> d; g = 0;
        if(!b[n]) { cout << "0\n\n"; continue; }
        vector<int> ans,fac;
        cout << phi[phi[n]] << '\n';
        int r = pow(n,0.25)+1; mm = m = phi[n];
        if(!v[m]) fac.push_back(m), vis[m] = 1;
        else for(int i = 1; i <= cnt && p[i] <= mm; ++i)
        {
            if(!(mm%p[i]))
            {
                fac.push_back(p[i]);
                while(!(mm%p[i])) mm /= p[i];
                for(_ll j = 1; j*p[i] <= m; ++j) vis[j*p[i]] = 1;
            }
        }
        for(int f = 0; ; ++g, f = 0)
        {   
            while(qpow(g,m,n) != 1) ++g;
            for(auto x: fac)
                if(qpow(g,m/x,n) == 1) 
                {   f = 1;  break;  }
            if(!f) break;
        }
        For(i,1,m)
        {
            if(vis[i]) vis[i] = 0;
            else ans.push_back(qpow(g,i,n));
        }
        sort(ans.begin(),ans.end());
        for(int i = d-1; i < ans.size(); i += d)
            cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}