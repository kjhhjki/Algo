template<class T, class Cmp = std::less<T>>
struct RMQ
{
    const Cmp cmp = Cmp();
    static constexpr unsigned int B = 64;
    int n;
    std::vector<std::vector<T>> a;
    std::vector<T> pre, suf, ini;
    std::vector<u64> st;
    RMQ() {}
    RMQ(const std::vector<T> &v) { init(v); }
    void init(const std::vector<T> &v)
    {
        n = v.size();
        pre = suf = ini = v;
        st.resize(n);
        if(!n) return;
        const int M = (n-1) / B + 1, lg = std::__lg(M);
        a.assign(lg+1, std::vector<T>(M));
        For(i, 0, M-1) 
        {
            a[0][i] = v[i*B];
            For(j, 1, std::min(B, n - i * B) - 1)
                a[0][i] = std::min(a[0][i], v[i * B + j], cmp);
        }
        For(i, 1, n-1) if(i % B) pre[i] = std::min(pre[i], pre[i-1], cmp); 
        foR(i, n-2, 0) if(i % B != B - 1) suf[i] = std::min(suf[i], suf[i+1], cmp); 
        For(j, 0, lg - 1) For(i, 0, M - (2 << j)) a[j+1][i] = std::min(a[j][i], a[j][i + (1 << j)], cmp);
        For(i, 0, M-1)
        {
            const int l = i * B, r = std::min(1u * n, l + B);
            u64 s = 0;
            For(j, l, r-1)
            {
                while(s && cmp(v[j], v[std::__lg(s) + l])) s ^= 1llu << std::__lg(s);
                s |= 1llu << (j - l);
                st[j] = s;
            }
        }
    }
    T operator()(int l, int r)
    {
        ++r;
        if(l / B == (r - 1) / B)
        {
            int x = B * (l / B);
            return ini[__builtin_ctzll(st[r-1] >> (l-x)) + l];
        }
        T ans = std::min(suf[l], pre[r-1], cmp);
        l /= B; ++l; r /= B;
        if(l < r)
        {
            int k = std::__lg(r - l);
            ans = std::min({ans, a[k][l], a[k][r - (1 << k)]}, cmp);
        }
        return ans;
    }
};