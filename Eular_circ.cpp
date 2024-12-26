#include<bits/stdc++.h>
#define MAXN 200005
#define For(i,a,b) for(int i=a;i<=b;i++)
#define foR(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef unsigned long long _ll;

std::vector<int> e[MAXN];
stack<int> st;
int n,m,x,y,s,ss,ts,in[MAXN],out[MAXN],over[MAXN];
void dfs(int u)
{
    for(int i = over[u]; i < e[u].size(); i = over[u])
    {
        over[u] = i+1;
        dfs(e[u][i]);
    }
    st.push(u);
}
int main()
{
    freopen("in.txt","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    For(i,1,m) cin >> x >> y, e[x].push_back(y), ++in[y], ++out[x];
    For(i,1,n)
    {
        sort(e[i].begin(),e[i].end());
        if(in[i]+1 == out[i]) ++ss, s = i;
        else if(in[i] == out[i]+1) ++ts;
        else if(in[i] != out[i]) { cout << "No"; return 0; }
    }
    if(ss != ts) { cout << "No"; return 0; }
    if(!ss && !ts) s = 1;
    dfs(s);
    while(!st.empty()) cout << st.top() << " ", st.pop();
    fclose(stdin);
    return 0;
}