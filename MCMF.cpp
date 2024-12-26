template<typename T>
struct MCF
{
    struct edge { int to; int f; T c; };

    int n;
    std::vector<edge> e;
    std::vector<std::vector<int>> adj;
    std::vector<int> pre;
    std::vector<T> h, dis;
    constexpr static T INF = std::numeric_limits<T>::max() / 2;

    MCF(int _n = 0) { init(_n); }
    void init(int _n = 0)
    {
        n = _n;
        e.clear(); adj.assign(n+1, {});
    }

    void addEdge(int u, int v, int f, T c)
    {
        adj[u].push_back(e.size());
        e.emplace_back(v, f, c);
    }
    void add(int u, int v, int f = 0, T c = 0)
    {
        addEdge(u, v, f, c);
        addEdge(v, u, 0, -c);
    }

    bool dij(int s, int t)
    {
        dis.assign(n + 1, INF); pre.assign(n+1, -1);
        using pli = std::pair<T, int>;
        std::priority_queue<pli, std::vector<pli>, std::greater<>> q;
        q.emplace(dis[s]=0,s);
        while(!q.empty())
        {
            auto [d,u] = q.top(); q.pop();
            if(dis[u] < d) continue;
            for(int i: adj[u])
            {
                auto [v,f,c] = e[i];
                if(f > 0 && dis[v] > d + h[u] - h[v] + c)
                    q.emplace(dis[v]=d+h[u]-h[v]+c, v), pre[v] = i;
            }
        }
        return dis[t] != INF;
    }
    std::pair<int, T> dinic(int s, int t)
    {
        int flow(0); T cost(0); h.assign(n+1, 0);
        while(dij(s,t))
        {
            int mn = std::numeric_limits<int>::max() >> 1;
            for(int i = 1; i <= n; ++i) {
                h[i] += dis[i];
            }
            for(int i = t; i != s; i = e[pre[i]^1].to)
                chkmin(mn,e[pre[i]].f);
            for(int i = t; i != s; i = e[pre[i]^1].to)
                e[pre[i]].f -= mn, e[pre[i]^1].f += mn;
            flow += mn; cost += mn * h[t];
        }
        return {flow, cost};
    }
};