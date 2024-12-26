template<typename T>
struct Max_Flow
{
    struct edge { int to; T f; };

    int n;
    std::vector<edge> e;
    std::vector<std::vector<int>> adj;
    std::vector<int> cur,dis;

    Max_Flow(int _n = 0) { init(_n); }
    void init(int _n = 0) 
    {
        n = _n;
        e.clear(); adj.assign(n+1, {});
        cur.resize(n+1); dis.resize(n+1);
    }

    void addEdge(int u, int v, T f)
    {   
        adj[u].push_back(e.size());
        e.emplace_back(v, f);
    }
    void add(int u, int v, T f = 0)
    {
        addEdge(u,v,f);
        addEdge(v,u,0);
    }

    int cntu;
    bool bfs(int s, int t)
    {
        dis.assign(n+1,-1);
        std::queue<int> q;
        while(!q.empty()) q.pop();
        q.push(s); dis[s] = 0;
        while(!q.empty())
        {
            int u = q.front(); q.pop();
            for(auto i: adj[u])
            {
                auto [v, f] = e[i];
                if(f > 0 && dis[v] == -1)
                {
                    q.push(v); dis[v] = dis[u] + 1;
                    if(v == t) return true;
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T sum)
    {
        if(u == t) return sum;
        T rem = sum;
        for(int &i = cur[u]; i < int(adj[u].size()); ++i)
        {
            const int j = adj[u][i]; auto [v,f] = e[j];
            if(f > 0 && dis[v] == dis[u]+1)
            {
                T k = dfs(v,t,std::min(rem, f));
                e[j].f -= k; e[j^1].f += k;
                if((rem-=k) == 0) return sum; 
            }
        }
        return sum-rem;
    }
    T dinic(int s, int t)
    { 
        T flow = 0;
        while(bfs(s,t)) 
            cur.assign(n+1, 0), flow += dfs(s, t, std::numeric_limits<T>::max()>>1); 
        return flow;
    }
    std::vector<bool> min_cut() 
    {
        std::vector<bool> c(n+1);
        for(int i = 1; i <= n; ++i) {
            c[i] = (dis[i] != -1);
        }
        return c;
    }
};
