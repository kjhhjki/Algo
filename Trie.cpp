struct Trie
{
    std::vector<int> cnt;
    std::vector<std::array<int, 2>> nxt;
    static constexpr int rt = 0;
    int tot = rt, hb;

    Trie(int n = 1, int b = 30) { init(n, b); };
    void init(int n = 1, int b = 30)
    {
        hb = b - 1;
        cnt.assign(b * n + 2, 0); nxt.assign(b * n + 2, {});
    }

    void insert(int x, int d = 1)
    {
        int u = rt; ++cnt[rt];
        for(int i = hb; i >= 0; --i) {
            bool p = x >> i & 1;
            if(!nxt[u][p]) nxt[u][p] = ++tot;
            u = nxt[u][p];
            cnt[u] += d;
        }
    }
    int query(int x)
    {
        if(!cnt[rt]) return 0;
        int u = rt, res(0);
        for(int i = hb; i >= 0; --i) {
            bool p = x >> i & 1;
            if(nxt[u][!p] && cnt[nxt[u][!p]]) u = nxt[u][!p], res ^= (1 << i);
            else u = nxt[u][p];
        }
        return res;
    }
};