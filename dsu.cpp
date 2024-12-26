struct Dsu
{
    std::vector<int> pre, sz;
    Dsu(int n = 0) { init(n); }
    void init(int n) { pre.resize(n+1); sz.assign(n+1,1); iota(pre.begin(),pre.end(),0); }
    int find(int x)
    {
        while(x != pre[x]) x = pre[x] = pre[pre[x]];
        return x;
    }
    int same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y)
    {
        x = find(x); y = find(y);
        if(x == y) return false;
        if(sz[x] < sz[y]) std::swap(x, y);
        pre[y] = x; sz[x] += sz[y];
        return true;
    }
    int size(int x) { return sz[find(x)]; }
};
