
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

template<int P>
constexpr MInt<P> findG() 
{
    MInt<P> i = 2;
    int k = __builtin_ctz(P - 1);
    while(qpow(i, (P-1) >> 1) == 1) i += 1;
    return qpow(i, (P-1) >> k);
}

template<int P>
constexpr MInt<P> G = findG<P>();
template<>
constexpr MInt<998244353> G<998244353> {3};

template<int P>
std::vector<MInt<P>> w{0, 1};

template<int P>
void extendw(MInt<P> l)
{
    int limit = l.val();
    if(int(w<P>.size()) < limit)
    {
        int t = __builtin_ctz(w<P>.size());
        w<P>.resize(limit);
        while((1 << t) < limit)
        {
            MInt<P> wn = qpow(G<P>, (P-1)/(1<<(t+1)));
            w<P>[1 << t] = 1;
            for(int j = (1 << t) + 1; j < (1 << (t+1)); ++j)
                w<P>[j] = w<P>[j-1] * wn;
            ++t;
        }
    }
}
template<int P>
void NTT(std::vector<MInt<P>> &a)
{
    int limit = a.size();
    extendw(MInt<P>(limit));
    for(int mid = limit >> 1; mid >= 1; mid >>= 1)
    {
        for(int j = 0; j < limit; j += mid<<1)
        {
            for(int k = j, s = mid; k < j+mid; ++k, ++s)
            {
                MInt<P> x = a[k], y = a[k+mid];
                a[k] = x + y;
                a[k+mid] = (x - y) * w<P>[s];
            }
        }
    }
}
template<int P>
void INTT(std::vector<MInt<P>> &a)
{
    int limit = a.size();
    extendw(MInt<P>(limit));
    for(int mid = 1; mid < limit; mid <<= 1)
    {
        for(int j = 0; j < limit; j += mid<<1)
        {
            for(int k = j, s = mid; k < j+mid; ++k, ++s)
            {
                MInt<P> x = a[k], y = w<P>[s] * a[k+mid];
                a[k] = x + y;
                a[k+mid] = x - y;
            }
        }
    }
    reverse(a.begin()+1, a.end());
    MInt<P> inv = MInt<P>(limit).inv();
    for(int i = 0; i < limit; ++i) a[i] *= inv;
}

template<int P = 998244353>
struct Poly: std::vector<MInt<P>> 
{
    using Z = MInt<P>;
    explicit constexpr Poly(int n = 0) : std::vector<Z>(n) {}
    explicit constexpr Poly(const std::vector<Z> &a) : std::vector<Z>(a) {}
    constexpr Poly(const std::initializer_list<Z> &a) : std::vector<Z>(a) {}
    template<class F> explicit constexpr Poly(int n, F f) : std::vector<Z>(n) { for(int i = 0; i < n; ++i) (*this)[i] = f(i); }

    template<class InputIt, class = std::_RequireInputIter<InputIt>>
    explicit constexpr Poly(InputIt first, InputIt last) : std::vector<Z>(first, last) {}

    constexpr Poly shift(int k) const 
    {
        if(k >= 0) 
        {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } 
        else if (int(this->size()) <= -k) return Poly();
        else return Poly(this->begin() + (-k), this->end());
    }
    constexpr Poly trunc(int k) const 
    {
        Poly f = *this;
        f.resize(k);
        return f;
    }
    constexpr friend Poly operator+(const Poly &a, const Poly &b) 
    {
        Poly res(std::max(a.size(), b.size()));
        for(int i = 0; i < int(a.size()); ++i) res[i] = a[i];
        for(int i = 0; i < int(b.size()); ++i) res[i] += b[i];
        return res;
    }
    constexpr friend Poly operator-(const Poly &a, const Poly &b) 
    {
        Poly res(std::max(a.size(), b.size()));
        for(int i = 0; i < int(a.size()); ++i) res[i] = a[i];
        for(int i = 0; i < int(b.size()); ++i) res[i] -= b[i];
        return res;
    }
    constexpr friend Poly operator-(const Poly &a) 
    {
        std::vector<Z> res(a.size());
        for(int i = 0; i < int(res.size()); ++i) res[i] = -a[i];
        return Poly(res);
    }
    constexpr friend Poly operator*(Poly a, Poly b) 
    {
        if(a.size() == 0 || b.size() == 0) return Poly();
        if(a.size() < b.size()) std::swap(a, b);
        int limit = 1, tot = a.size() + b.size() - 1;
        while(limit < tot) limit <<= 1;
        if(((P - 1) & (limit - 1)) != 0 || b.size() < 128) 
        {
            Poly c(a.size() + b.size() - 1);
            for(int i = 0; i < int(a.size()); ++i)
                for(int j = 0; j < int(b.size()); ++j)
                    c[i+j] += a[i] * b[j];
            return c;
        }
        a.resize(limit); b.resize(limit);
        NTT(a); NTT(b);
        for(int i = 0; i < limit; ++i) a[i] *= b[i];
        INTT(a);
        a.resize(tot);
        return a;
    }
    constexpr friend Poly operator*(Z a, Poly b) 
    {
        for(int i = 0; i < int(b.size()); ++i) b[i] *= a;
        return b;
    }
    constexpr friend Poly operator*(Poly a, Z b) 
    {
        for(int i = 0; i < int(a.size()); ++i) a[i] *= b;
        return a;
    }
    constexpr friend Poly operator/(Poly a, Z b) 
    {
        for (int i = 0; i < int(a.size()); ++i) a[i] /= b;
        return a;
    }
    constexpr Poly &operator+=(Poly b) { return (*this) = (*this) + b; }
    constexpr Poly &operator-=(Poly b) { return (*this) = (*this) - b; }
    constexpr Poly &operator*=(Poly b) { return (*this) = (*this) * b; }
    constexpr Poly &operator*=(Z b) { return (*this) = (*this) * b; }
    constexpr Poly &operator/=(Z b) { return (*this) = (*this) / b; }

    constexpr Poly deriv() const 
    {
        if(this->empty()) return Poly();
        Poly res(this->size() - 1);
        for(int i = 0; i < int(res.size()); ++i) res[i] = (i + 1) * (*this)[i + 1];
        return res;
    }
    inline static std::vector<Z> invi{0};
    constexpr Poly integ() const 
    {
        Poly res(this->size()+1);
        if(invi.size() < this->size()+1)
        {
            int lst = invi.size();
            invi.resize(this->size()+1);
            for(int i = lst; i <= int(this->size()); ++i) invi[i] = Z(i).inv();
        }
        for(int i = 0; i < int(this->size()); ++i) res[i+1] = (*this)[i] * invi[i+1];
        return res;
    }
    constexpr Poly inv(int n) const 
    {
        Poly res{(*this)[0].inv()};
        int m = 1;
        while(m < n) m <<= 1, res = (res * (Poly{2}-trunc(m)*res)).trunc(m);
        return res.trunc(n);
    }
    constexpr Poly ln(int n) const { return (deriv() * inv(n)).integ().trunc(n); }
    constexpr Poly exp(int n) const
    {
        Poly res{1}; int m = 1;
        while(m < n) m <<= 1, res = (res * (Poly{1}-res.ln(m)+trunc(m))).trunc(m);
        return res.trunc(n);
    }
    constexpr Poly pow(int n, int k, int k2 = -1, bool flag = false) const
    {
        int pos = 0;
        if(k2 < 0) k2 = k;
        while(pos < int(this->size()) && (*this)[pos] == 0) ++pos;
        if(pos == int(this->size()) || (pos && flag) || 1ll*pos*k >= n) return Poly(n);
        Z a0 = (*this)[pos];
        auto f = shift(-pos) * a0.inv();
        return (f.ln(n-pos*k)*k).exp(n-pos*k).shift(pos*k) * qpow(a0, k2);
    }
    constexpr Poly sqrt(int n) const 
    {
        Poly res{1};
        int m = 1;
        while(m < n) m <<= 1, res = (res + (trunc(m) * res.inv(m)).trunc(m)) * CInv<2, P>;
        return res.trunc(n);
    }
    constexpr std::pair<Poly, Poly> div(Poly b) const
    {
        if(this->size() < b.size()) return {Poly(0), *this};
        Poly a = *this; 
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());
        Poly q = (a * b.inv(this->size() - b.size() + 1)).trunc(this->size() - b.size() + 1);
        std::reverse(q.begin(), q.end());
        std::reverse(b.begin(), b.end());
        return {q, (*this - q * b).trunc(b.size() - 1)};
    }
    constexpr Poly mulT(Poly b) const
    {
        int n = b.size(); 
        if(n == 0) return Poly();
        std::reverse(b.begin(), b.end());
        return ((*this) * b).shift(1 - n);
    }
    constexpr std::vector<Z> eval(std::vector<Z> x) const 
    {
        if(this->empty()) return std::vector<Z>(x.size(), 0);
        const int n = std::max(x.size(), this->size());
        std::vector<Poly> a(n * 4 + 1);
        std::vector<Z> ans(x.size());
        x.resize(n);
        #define ls(i) i * 2
        #define rs(i) i * 2 + 1
        auto build = [&](auto &&self, int i, int l, int r) -> void
        {
            if(l == r) 
            {
                a[i] = {1, -x[l]};
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls(i), l, mid); self(self, rs(i), mid + 1, r);
            a[i] = a[ls(i)] * a[rs(i)];
        };
        auto query = [&](auto &&self, int i, int l, int r, const Poly &t) -> void
        {
            if(l == r) 
            {
                if(l < (int)ans.size()) ans[l] = t[0];
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls(i), l, mid, t.mulT(a[rs(i)]).trunc(mid - l + 1)); 
            self(self, rs(i), mid + 1, r, t.mulT(a[ls(i)]).trunc(r - mid));
        };
        #undef ls
        #undef rs
        build(build, 1, 0, n - 1); query(query, 1, 0, n - 1, mulT(a[1].inv(n)));
        return ans;
    }
};