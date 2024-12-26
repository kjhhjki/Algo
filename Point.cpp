struct Point
{
    i64 x = 0, y = 0;
    Point(i64 x = 0, i64 y = 0): x(x), y(y) {}
    constexpr Point& operator+=(const Point o) { return x += o.x, y += o.y, *this; }
    constexpr Point& operator-=(const Point o) { return x -= o.x, y -= o.y, *this; }
    constexpr Point& operator*=(const int k) { return x *= k, y *= k, *this; }
    constexpr Point& operator/=(const int k) { return x /= k, y /= k, *this; }
    constexpr Point operator+(const Point o) const { Point res(*this); return res += o; }
    constexpr Point operator-(const Point o) const { Point res(*this); return res -= o; }
    constexpr Point operator*(const int k) const { Point res(*this); return res *= k; }
    constexpr friend Point operator*(const int k, const Point &a) { Point res(a); return res *= k; }
    constexpr Point operator/(const int k) const { Point res(*this); return res /= k; }
    constexpr i64 operator%(const Point o) const { return o.y * x - o.x * y; }
    constexpr i64 operator*(const Point o) const { return x * o.x + y * o.y; }
    constexpr bool operator<(const Point &o) const { return x == o.x? y < o.y: x < o.x; }
    constexpr bool operator==(const Point &o) const { return x == o.x && y == o.y; }
    constexpr i64 norm2() const { return x * x + y * y; }
    friend i64 dist(const Point a, const Point b) { return (b-a).norm2(); }
    friend std::istream& operator>>(std::istream& is, Point &o) { return is >> o.x >> o.y; }
    constexpr f64 theta() const { return atan2l(x, y); }
    friend f64 theta(const Point a, const Point b) {
        return std::acos(a * b / (std::sqrt(a.norm2()) * std::sqrt(b.norm2())));
    }
};

std::vector<Point> getHull(std::vector<Point> p) 
{
    std::vector<Point> h, l{{-1, -1}};
    std::sort(p.begin() + 1, p.end());
    p.erase(std::unique(p.begin() + 1, p.end()), p.end());
    if(p.size() <= 2) {
        return p;
    }
    for(int i = 1; i < (int)p.size(); ++i) {
        while(h.size() > 1 && (p[i] - h.back()) % (p[i] - h[h.size() - 2]) <= 0) {
            h.pop_back();
        }
        while(l.size() > 2 && (p[i] - l.back()) % (p[i] - l[l.size() - 2]) >= 0) {
            l.pop_back();
        }
        l.push_back(p[i]); h.push_back(p[i]);
    }
    l.pop_back();
    std::reverse(h.begin(), h.end());
    h.pop_back();
    l.insert(l.end(), h.begin(), h.end());
    return l;
}