template<typename T>
std::vector<int> getKmp(const std::vector<T> &a)
{
    std::vector<int> kmp(a.size());
    int n = kmp.size() - 1;
    for(int i = 2, j = 0; i <= n; ++i)
    {
        while(j && a[j + 1] != a[i]) j = kmp[j];
        if(a[j + 1] == a[i]) ++j;
        kmp[i] = j;
    }
    return kmp;
}
std::vector<int> getKmp(const std::string &a) { return getKmp(std::vector<char>(a.begin(), a.end())); }