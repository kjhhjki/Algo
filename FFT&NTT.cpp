const double PI = acos(-1.0);

class Complex
{
    public:
        double x, y;
        Complex(double x, double y) : x(x), y(y){};
        Complex(double c = 0) : x(c), y(c){};
        Complex operator+(const Complex &o) { return Complex(x + o.x, y + o.y); }
        Complex operator-(const Complex &o) { return Complex(x - o.x, y - o.y); }
        Complex operator*(const Complex &o) { return Complex(x * o.x - y * o.y, x * o.y + y * o.x); }
        void print() { printf("(%.2lf,%.2lf)", x, y); }
} a[MAXN<<2], b[MAXN<<2];

int n, m, limit, l;

Complex wn,w[MAXN<<2];
void init(int n, int m)
{
    for(limit = 2, l = 1; limit < n + m; limit <<= 1, ++l);
    for(int i = 1; i < limit; i <<= 1)
    {
        wn = Complex(cos(PI/(i)), sin(PI/(i)));
        w[i] = Complex(1,0);
        for(int j = i+1; j < (i<<1); ++j)
            w[j] = w[j-1] * wn;
    }
}
void FFT(Complex a[])
{
    for(int mid = limit>>1; mid >= 1; mid >>= 1)
    {
        for(int j = 0; j < limit; j += mid<<1)
        {
            for(int k = j, s = mid; k < j+mid; ++k, ++s)
            {
                Complex x = a[k], y = a[k+mid];
                a[k] = x + y; a[k+mid] = (x-y)*w[s];
            }
        }
    }
}
void IFFT(Complex a[])
{
    for(int mid = 1; mid < limit; mid <<= 1)
    {
        for(int j = 0; j < limit; j += mid<<1)
        {
            for(int k = j, s = mid; k < j+mid; ++k, ++s)
            {
                Complex x = a[k], y = a[k+mid]*w[s];
                a[k] = x + y; a[k+mid] = x - y;
            }
        }
    }
    reverse(a+1, a+limit);
    for(int i = 0; i < limit; ++i) a[i].x /= limit;
}

constexpr u32 P = 998244353, G = 3, Gi = 332748118, inv2 = 499122177;

u32 limit, inv, w[MAXN];
u32 qpow(u32 x, u64 n)
{
    u32 res = 1, base = x;
    while(n)
    {
        if(n&1)  res=1ll*res*base%P;
        n >>= 1; base=1ll*base*base%P;
    }
    return res;
}
void init(u32 n)
{
    limit = 2;
    while(limit < n) limit <<= 1;
    for(int i = 1; i < limit; i <<= 1)
    {
        u32 wn = qpow(G, (P-1)/(i<<1));
        w[i] = 1;
        for(int j = i+1; j < (i<<1); ++j)
            w[j] = 1ll*w[j-1]*wn%P;
    }
    inv = qpow(limit, P-2);
}
void NTT(u32 a[])
{   
    for(int mid = limit>>1; mid >= 1; mid >>= 1)
    {
        for(int j = 0; j < limit; j += mid<<1)
        {
            for(int k = j, s = mid; k < j+mid; ++k, ++s)
            {
                u32 x = a[k], y = a[k+mid];
                a[k] = x+y>=P?x+y-P:x+y;
                a[k+mid] = 1ll*(x<y?P+x-y:x-y)*w[s]%P;
            }
        }
    }
}
void INTT(u32 a[])
{
    for(int mid = 1; mid < limit; mid <<= 1)
    {
        for(int j = 0; j < limit; j += mid<<1)
        {
            for(int k = j, s = mid; k < j+mid; ++k, ++s)
            {
                u32 x = a[k], y = (1ll * w[s] * a[k+mid])%P;
                a[k] = x+y>=P?x+y-P:x+y;
                a[k+mid] = x<y?P+x-y:x-y;
            }
        }
    }
    reverse(a+1, a+limit);
    for(int i = 0; i < limit; ++i)
        a[i] = 1ll*a[i]*inv%P;
}
