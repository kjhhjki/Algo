struct Pers_Trie
{
    std::vector<int> cnt, rt;
    std::vector<std::array<int, 2>> nxt;
    int tot = 0, hb;

    Pers_Trie(int n = 1, int b = 30) { init(n, b); };
    void init(int n = 1, int b = 30)
    {
        hb = b - 1;
        rt.assign(n + 1, 0);
        cnt.assign(b * n + 2, 0); nxt.assign(b * n + 2, {});
    }

    void insert(int lst, int cur, int x, int d = 1)
    {
        if(!rt[cur]) rt[cur] = ++tot;
        int u = rt[lst], v = rt[cur];
        cnt[v] = cnt[u] + d;
        for(int i = hb; i >= 0; --i) {
            bool p = x >> i & 1;
            nxt[v][p] = ++tot;
            cnt[nxt[v][p]] = cnt[nxt[u][p]];
            nxt[nxt[v][p]] = nxt[nxt[u][p]];
            u = nxt[u][p]; v = nxt[v][p];
            cnt[v] += d;
        }
    }
    int query(int l, int r, int x)
    {
        int u = rt[l - 1], v = rt[r];
        if(cnt[v] <= cnt[u]) return 0;
        int res = 0;
        for(int i = hb; i >= 0; --i) {
            bool p = x >> i & 1;
            int cu = cnt[nxt[u][!p]], cv = cnt[nxt[v][!p]];
            if(nxt[v][!p] && cv > cu) u = nxt[u][!p], v = nxt[v][!p], res ^= (1 << i);
            else u = nxt[u][p], v = nxt[v][p];
        }
        return res;
    }
};