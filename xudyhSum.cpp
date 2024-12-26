auto xudyhSmu = [](auto &&self, int n) -> int
{
    static std::unordered_map<int, int> mp;
    if(n <= N) return sm[n];
    if(mp.contains(n)) return mp[n];
    int res = 1;
    for(int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res -= self(self, n / l) * (r - l + 1);
    }
    return mp[n] = res;
};
auto xudyhSphi = [](auto &&self, int n) -> i64
{
    static std::unordered_map<int, i64> mp;
    if(n <= N) return sp[n];
    if(mp.contains(n)) return mp[n];
    i64 res = n * (n + 1ll) / 2;
    for(int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res -= self(self, n / l) * (r - l + 1);
    }
    return mp[n] = res;
};