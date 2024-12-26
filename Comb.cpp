template<int P>
struct Comb
{
    int n;
    using Z = MInt<P>;
    std::vector<Z> _fac;
    std::vector<Z> _ifac;
    std::vector<Z> _inv;
    Comb(): n(0), _fac{1}, _ifac{1}, _inv{0} {}
    Comb(int n) : Comb() { extend(n); }
    void extend(int m)
    {
        chkmin(m, Z::getMod() - 1);
        if(m <= n) return;
        _fac.resize(m + 1);
        _ifac.resize(m + 1);
        _inv.resize(m + 1);
        for(int i = n + 1; i <= m; ++i) {
            _fac[i] = i * _fac[i-1];
        }
        _ifac[m] = _fac[m].inv();
        for(int i = m; i >= n + 1; --i) {
            _ifac[i-1] = i * _ifac[i], _inv[i] = _ifac[i] * _fac[i-1];
        }
        n = m;
    }

    Z fac(int m) 
    {
        if(m > n) extend(2 * m);
        return _fac[m];
    }
    Z ifac(int m)
    {
        if(m > n) extend(2 * m);
        return _ifac[m];
    }
    Z inv(int m)
    {
        if(m > n) extend(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) { return n >= m && m >= 0? fac(n) * ifac(n-m) * ifac(m): 0; }
    Z perm(int n, int m) { return n >= m && m >= 0? fac(n) * ifac(n-m): 0; }
    Z perm(int n) { return n >= 0? fac(n): 0; }
};