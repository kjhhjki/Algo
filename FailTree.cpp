//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define MAXN 1000006
using namespace std;
typedef long long _ll;

int n,m,a,b,d[MAXN],kmp[23][MAXN];
char s[MAXN];
void KMP(char s[])
{
    kmp[0][0] = kmp[0][1] = 0; d[0] = 0; d[1] = 1;
    for(int i = 2, j = 0; i <= n; ++i)
    {
        while(j && s[j+1]!=s[i]) j = kmp[0][j];
        if(s[j+1] == s[i]) ++j;
        kmp[0][i] = j; d[i] = d[j] + 1;
    }
}
void init()
{
    for(int i = 1; (1<<i) <= n; ++i)
        for(int j = 1; j <= n; ++j)
            kmp[i][j] = kmp[i-1][kmp[i-1][j]];
}
int LCA(int x, int y)
{
    if(d[x] < d[y]) swap(x,y);
    for(int i = log2(d[x]-d[y]); i >= 0; --i)
        if(d[kmp[i][x]] >= d[y])
            x = kmp[i][x];
    //if(x==y) return x;
    for(int i = log2(d[x]); i >= 0; --i)
        if(kmp[i][x] != kmp[i][y])
            x = kmp[i][x], y = kmp[i][y];
    return kmp[0][x];
}

int main()
{
    //freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin >> s+1 >> m; n = strlen(s+1);
    KMP(s);     init();
    while(m--)
        cin >> a >> b, cout << LCA(a,b) << endl;
    //fclose(stdin); fclose(stdout);
    return 0;
}