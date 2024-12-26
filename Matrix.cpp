template<typename T>
struct Matrix
{
    int n, m;
    std::vector<std::vector<T>> a;
    Matrix(int _n = 0, int _m = 0) { init(std::vector(_n, std::vector<T>(_m))); }
    Matrix(const std::vector<std::vector<T>> &a) { init(a); }
    void init(const std::vector<std::vector<T>> &a) {
        this->a = a;
        n = a.size();
        if(n == 0) {
            return;
        }
        m = a[0].size();
    }
    constexpr Matrix operator+(const Matrix &o) const {
        if(a.empty() || a.size() != o.a.size() || a[0].size() != o.a[0].size()) {
            return {};
        }
        auto res = o;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                res.a[i][j] += a[i][j];
            }
        }
        return res;
    }
    constexpr Matrix operator-(const Matrix &o) const {
        if(a.empty() || a.size() != o.a.size() || a[0].size() != o.a[0].size()) {
            return {};
        }
        auto res = *this;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                res.a[i][j] -= o.a[i][j];
            }
        }
        return res;
    }
    constexpr Matrix operator*(const Matrix &o) const {
        if(a.empty() || o.a[0].empty() || a[0].empty() || a[0].size() != o.a.size()) {
            return {};
        }
        Matrix res(n, o.a[0].size());
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                for(int k = 0; k < (int)o.a[0].size(); ++k) {
                    res.a[i][k] += a[i][j] * o.a[j][k];
                }
            }
        }
        return res;
    }
    constexpr Matrix operator^(i64 N) const {
        if(a.empty() || a.size() != a[0].size()) {
            return {};
        }
        Matrix res(n, n), mat(*this);
        for(int i = 0; i < n; ++i) {
            res[i][i] = 1;
        }
        while(N) {
            if(N & 1) {
                res *= mat;
            }
            mat *= mat;
            N >>= 1;
        }
        return res;
    }
    constexpr Matrix& operator+=(const Matrix &o) { return *this = *this + o; }
    constexpr Matrix& operator-=(const Matrix &o) { return *this = *this - o; }
    constexpr Matrix& operator*=(const Matrix &o) { return *this = *this * o; }
    constexpr Matrix& operator^=(i64 o) { return *this = *this ^ o; }
    constexpr std::vector<T>& operator[](int id) noexcept {
        assert(id < n);
        return a[id];
    }
};

template<typename T, int N>
struct SquareMatrix
{
    std::array<std::array<T, N>, N> a;
    SquareMatrix() { a.fill(std::array<T, N>{}); }
    SquareMatrix(const std::array<std::array<T, N>, N> &a): a(a) {}
    constexpr SquareMatrix operator+(const SquareMatrix &o) const {
        auto res = o;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                res.a[i][j] += a[i][j];
            }
        }
        return res;
    }
    constexpr SquareMatrix operator-(const SquareMatrix &o) const {
        auto res = *this;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                res.a[i][j] -= o.a[i][j];
            }
        }
        return res;
    }
    constexpr SquareMatrix operator*(const SquareMatrix &o) const {
        SquareMatrix res;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                for(int k = 0; k < (int)o.a[0].size(); ++k) {
                    res.a[i][k] += a[i][j] * o.a[j][k];
                }
            }
        }
        return res;
    }
    constexpr SquareMatrix operator^(i64 n) const {
        SquareMatrix res, mat(*this);
        for(int i = 0; i < n; ++i) {
            res[i][i] = 1;
        }
        while(n) {
            if(n & 1) {
                res *= mat;
            }
            mat *= mat;
            n >>= 1;
        }
        return res;
    }
    constexpr SquareMatrix& operator+=(const SquareMatrix &o) { return *this = *this + o; }
    constexpr SquareMatrix& operator-=(const SquareMatrix &o) { return *this = *this - o; }
    constexpr SquareMatrix& operator*=(const SquareMatrix &o) { return *this = *this * o; }
    constexpr SquareMatrix& operator^=(i64 o) { return *this = *this ^ o; }
    constexpr std::array<T, N>& operator[](int id) noexcept {
        return a[id];
    }
};