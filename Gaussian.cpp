std::pair<int, std::vector<f64>> Gauss(std::vector<std::vector<f64>> a)
{
    constexpr f64 eps = 1e-6;
    const int n = a.size() - 1, m = a[1].size() - 1;
    int rows = 1;
    f64 coef = 1;
    For(j, 1, n)
    {
        int mx = rows;
        For(i, rows+1, n)
            if(std::abs(a[i][j]) > std::abs(a[mx][j]))
                mx = i;
        if(std::abs(a[mx][j]) < eps) continue;
        if(mx != rows)
        {
            coef *= -1;
            std::swap(a[rows], a[mx]);
        }
        For(i, 1, n)
        {
            if(i == rows) continue;
            f64 tmp = a[i][j] / a[rows][j];
            For(k, j + 1, m) a[i][k] -= tmp * a[rows][k];
        }
        ++rows;
    }
    if(rows <= n)
    {
        For(i, rows, n)
            if(std::abs(a[i][m]) > eps)
                return {-1, {}};
        return {0, {}};
    }
    std::vector<f64> ans(n+1);
    For(i, 1, n) ans[i] = a[i][m] / a[i][i];
    return {1, ans};
}