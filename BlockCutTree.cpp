struct BlockCutTree
{
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn, low, st;
    int n, t = 0, R;

    BlockCutTree(const std::vector<std::vector<int>> &g) { init(g); }
    void init(const std::vector<std::vector<int>> &g)
    {
        R = n = g.size()-1; t = 0;
        adj.assign(n+1, std::vector<int>());
        dfn.assign(n+1,0); low.assign(n+1,0); st.clear();
        For(i,1,n) if(!dfn[i]) tarjan(i,g);
    }
    const std::vector<std::vector<int>>& getBCT() { return adj; }

    void tarjan(int u, const std::vector<std::vector<int>> &g)
    {
        dfn[u] = low[u] = ++t; st.push_back(u);
        for(auto v: g[u]) {
            if(!dfn[v]) {
                tarjan(v,g); 
                chkmin(low[u],low[v]);
                if(low[v] == dfn[u])
                {
                    ++R; adj.push_back(std::vector<int>{u}); 
                    adj[u].push_back(R);
                    while(!st.empty())
                    {
                        int x = st.back(); st.pop_back();
                        adj[x].push_back(R); adj[R].push_back(x);
                        if(x == v) break;
                    }
                }
            } else chkmin(low[u],dfn[v]);
        }
    };
    void sort() { For(i, 1, R) std::sort(adj[i].begin(),adj[i].end()); }
};           