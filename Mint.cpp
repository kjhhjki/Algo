// constexpr i64 MOD = 100055128505716009ll;

template<typename T>
constexpr T qpow(T x, i64 n)
{
    T res(1);
    while(n)
    {
        if(n&1) res *= x;
        x *= x; n >>= 1;
    }
    return res;
}

template<u32 P>
constexpr u32 mul(u32 a, u32 b) {
    return 1llu * a * b % P;
}

template<u64 P>
constexpr u64 mul(u64 a, u64 b) {
    u64 res = a * b - u64(1.l * a * b / P - 0.5l) * P;
    res %= P;
    return res;
}

template<typename U, U P>
requires std::unsigned_integral<U>
struct MIntBase
{
    U x;

    constexpr MIntBase() : x(0) {}
    template<typename T>
    requires std::integral<T>
    constexpr MIntBase(T x_) : x(norm(x_ % P)) {}

    constexpr U norm(U x)
    { 
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    constexpr int val() const { return x; }
    explicit constexpr operator U() const { return x; }

    constexpr MIntBase operator+=(const MIntBase o) { return x = norm(x+o.x), *this; }
    constexpr MIntBase operator-=(const MIntBase o) { return x = norm(x-o.x), *this; }
    constexpr MIntBase operator*=(const MIntBase o) { return x = mul<P>(x, o.val()), *this; }
    constexpr MIntBase operator/=(const MIntBase o) { return *this *= o.inv(); }
    friend constexpr MIntBase operator+(const MIntBase a, const MIntBase b) { MIntBase res(a); return res += b; }
    friend constexpr MIntBase operator-(const MIntBase a, const MIntBase b) { MIntBase res(a); return res -= b; }
    friend constexpr MIntBase operator*(const MIntBase a, const MIntBase b) { MIntBase res(a); return res *= b; }
    friend constexpr MIntBase operator/(const MIntBase a, const MIntBase b) { MIntBase res(a); return res /= b; }
    friend constexpr MIntBase operator-(const MIntBase a) { MIntBase res(0); return res -= a; }
    
    friend constexpr bool operator==(const MIntBase &a, const MIntBase &b) { return a.x == b.x; }
    friend constexpr bool operator!=(const MIntBase &a, const MIntBase &b) { return a.x != b.x; }
    friend constexpr auto operator<=>(const MIntBase &a, const MIntBase &b) { return a.x <=> b.x; }
    friend std::istream &operator>>(std::istream &is, MIntBase &a) { is >> a.x, a.x = a.norm(a.x); return is; }
    friend std::ostream &operator<<(std::ostream &os, const MIntBase &a) { return os << a.x; }

    constexpr MIntBase inv() const { return qpow(*this, P-2); }
};

template<u32 P>
using MInt= MIntBase<u32, P>;

template<u64 P>
using MLong = MIntBase<u64, P>;

using Z = MInt<P>;
// template<>
// u32 Z::mod = 0;
