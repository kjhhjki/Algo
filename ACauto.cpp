class ACauto
{
    private:
        int fail[MAXN] = {0}, trie[MAXN][26] = {0}, t = 0;
        int head[MAXN] = {0}, cnt = 0;
        struct Edge { int to,nxt; } e[MAXN];
        inline void addEdge(int,int);
    public:
        int ans[MAXN] = {0}, pos[MAXN] = {0};
        void ins(string&,int);
        void query(string&);
        void fresh();
        void getFail();
        void init();
        void dfs(int);
}a;
void ACauto::ins(string &s, int i)
{
    int p = 0;
    for(int i = 0; s[i]; ++i)
    {
        if(!trie[p][s[i]-'a']) trie[p][s[i]-'a'] = ++t;
        p = trie[p][s[i]-'a'];
    }
    pos[i] = p;
}
void ACauto::query(string &s)
{
    int p = 0;
    for(int i = 0; s[i]; ++i)
        p = trie[p][s[i]-'a'], ++ans[p];
}
void ACauto::getFail()
{
    int v,p;
    queue<int> q;
    for(int i = 0; i < 26; ++i) 
        if(trie[0][i])
            q.push(trie[0][i]), fail[trie[0][i]] = 0;
    while(!q.empty())
    {
        p = q.front(); q.pop();
        for(int i = 0; i < 26; ++i)
        {
            v = trie[p][i];
            if(v) fail[v] = trie[fail[p]][i], q.push(v);
            else  trie[p][i] = trie[fail[p]][i];
        }
    }
}
inline void ACauto::addEdge(int u, int v)
{
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
void ACauto::init()
{
    for(int i = 1;i <= t; ++i) 
        addEdge(fail[i], i);
}
void ACauto::dfs(int u)
{
    for(int i = head[u]; i; i = e[i].nxt)
    {
        dfs(e[i].to);
        ans[u] += ans[e[i].to];
    }
}