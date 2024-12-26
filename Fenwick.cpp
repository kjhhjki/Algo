template <typename T>
struct Fenwick
{
    int sz, lg;
    std::vector<T> t;
    Fenwick(int n = 0, T tt = T()) { init(std::vector<T>(n + 1, tt)); }
    Fenwick(const std::vector<T> &a) { init(a); }
    void init(int n = 0, T tt = T()) { init(std::vector<T>(n + 1, tt)); }
    void init(const std::vector<T> &a)
    {
        sz = a.size(); lg = log2(sz); t.assign(sz + 1, T());
        for(int i = 1; i <= sz; ++i) {
            t[i] += a[i - 1];
            int j = i + lowbit(i);
            if (j <= sz) t[j] += t[i];
        }
    }
    int lowbit(int i) { return i & -i; }
    void add(int i, T k) { ++i; while(i <= sz) t[i] += k, i += lowbit(i); }
    void add(int l, int r, T k) { add(l, k); add(r+1, -k); }
    T query(int i) { ++i; T res = 0; while(i) res += t[i], i -= lowbit(i); return res; }
    T query(int l, int r) { return query(r) - query(l - 1); }
    int lower_bound(T k)
    {
        int res = 0;
        for(int i = lg; i >= 0; --i) {
            if(res + (1 << i) <= sz && t[res + (1 << i)] < k) {
                k -= t[res += (1 << i)];
            }
        }
        return res;
    }
    int upper_bound(T k)
    {
        int res = 0;
        for(int i = lg; i >= 0; --i) {
            if(res + (1 << i) <= sz && t[res + (1 << i)] <= k) {
                k -= t[res += (1 << i)];
            }
        }
        return res;
    }
};

template <typename T>
struct Fenwick2
{
    int sz, lg;
    std::vector<T> t;
    Fenwick2(int n = 0, T tt = T()) { init(std::vector<T>(n + 1, tt)); }
    Fenwick2(const std::vector<T> &a) { init(a); }
    void init(int n = 0, T tt = T()) { init(std::vector<T>(n + 1, tt)); }
    void init(const std::vector<T> &a)
    {
        sz = a.size(); lg = log2(sz); t.assign(sz + 1,T());
        for(int i = 1; i <= sz; ++i) {
            t[i] += a[i - 1];
            int j = i + lowbit(i);
            if (j <= sz) t[j] += t[i];
        }
    }
    int lowbit(int i) { return i & -i; }
    void add(int i, T k) { ++i; while(i) t[i] += k, i -= lowbit(i); }
    void add(int l, int r, T k) { add(r, k); add(l - 1, -k); }
    T query(int i) { ++i; T res = 0; while(i <= sz) res += t[i], i += lowbit(i); return res; }
    T query(int l, int r) { return query(l) - query(r + 1); }
};