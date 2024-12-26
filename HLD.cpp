struct HLD
{
    int n, t = 0;
    std::vector<int> sz, top, dep, pre, dfn, out, seq;
    std::vector<std::vector<int>> adj;
    HLD(int n = 0) { init(n); }
    void init(int _n = 0)
    {
        n = _n; t = 0;
        sz.assign(n+1, 1); seq.assign(n+1, 0);
        dep = pre = top = dfn = out = seq;  
        adj.assign(n+1, std::vector<int>());
    }
    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void work(int rt = 1)
    {
        pre[rt] = 0; dep[rt] = 1; top[rt] = rt;
        dfs1(rt); dfs2(rt);
    }
    void dfs1(int u)
    {
        if(pre[u]) adj[u].erase(find(adj[u].begin(),adj[u].end(),pre[u]));
        sz[u] = 1;
        for(auto &v: adj[u])
        {
            pre[v] = u; dep[v] = dep[u] + 1;
            dfs1(v); sz[u] += sz[v];
            if(sz[v] > sz[adj[u][0]]) std::swap(v,adj[u][0]);
        }
    }
    void dfs2(int u)
    {
        dfn[u] = ++t; seq[t] = u;
        for(auto v: adj[u])
        {
            top[v] = (v == adj[u][0] ? top[u] : v);
            dfs2(v);
        }
        out[u] = t;
    }

    int lca(int u, int v)
    {
        while(top[u] != top[v])
        {
            if(dep[top[u]] < dep[top[v]]) v = pre[top[v]];
            else u = pre[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u,v)]; }
    int jump(int u, int k)
    {
        if(dep[u] < k) return 0;
        while(dep[u] - dep[top[u]] < k) k -= dep[u] - dep[top[u]] + 1, u = pre[top[u]];
        return seq[dfn[u]-k];
    }
    using pii = std::pair<int, int>;
    std::vector<pii> decompose(int u, int v)
    {
        std::vector<pii> res;
        while(top[u] != top[v])
        {
            if(dep[top[u]] < dep[top[v]]) std::swap(u,v);
            res.emplace_back(dfn[top[u]],dfn[u]);
            u = pre[top[u]];
        }
        if(dep[u] > dep[v]) std::swap(u,v);
        res.emplace_back(dfn[u],dfn[v]);
        return res;
    }
    pii subtree(int u) { return {dfn[u],out[u]}; }

    bool isAncestor(int u, int v) { return dfn[u] <= dfn[v] && out[u] >= out[v]; }
    int rootedParent(int u, int v)
    {
        if(u == v) return u;
        std::swap(u,v); 
        if(!isAncestor(u,v)) return pre[u];
        return *upper_bound(adj[u].begin(),adj[u].end(),v,[this](int x, int y) { return dfn[x] < dfn[y]; }) - 1;
    }
    int rootedSize(int u, int v)
    {
        if(u == v) return n;
        if(!isAncestor(v,u)) return sz[v];
        return n - sz[rootedParent(v,u)];
    }
    int rootedLCA(int a, int b, int c) { return lca(a,b)^lca(b,c)^lca(c,a); }
};