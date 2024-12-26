template<typename T>
std::vector<int> getZ(const std::vector<T> &a)
{
    int n = a.size() - 1;
    std::vector<int> z(n + 1); z[1] = n;
    for(int i = 2, l = 0, r = 0; i <= n; ++i)
    {
        if(i <= r) z[i] = std::min(z[i-l+1], r-i+1);
        while(i + z[i] <= n && a[i+z[i]] == a[z[i]+1]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = z[i] + i - 1;
    }
    return z;
}
std::vector<int> getZ(const std::string &a) { return getZ(std::vector<char>(a.begin(), a.end())); }