struct Trie
{
    int cnt, len, fail;
    std::array<int, 26> ch;
    Trie() { cnt = len = fail = 0; ch.fill(0); }
};
struct PAM
{
    int cnt, lst, cur;
    std::vector<Trie> a;
    std::vector<int> tot;
    std::string s;
    PAM(int n = 0) { init(n); }
    void init(int n = 0) {
        cnt = 1; lst = cur = 0;
        a.resize(n + 1); s.resize(n + 2);
        a[0].len = 0; a[1].len = -1;
        a[0].fail = 1; a[1].fail = 0;
    }
    int getFail(int x) {
        while(cur - a[x].len - 1 < 1 || s[cur - a[x].len - 1] != s[cur]) {
            x = a[x].fail;
        }
        return x;
    }
    void insert(int ch) {
        ++cur;
        while(cur >= (int)s.size()) {
            s.push_back(ch);
        }
        s[cur] = ch;
        int p = getFail(lst);
        if(!a[p].ch[ch]) {
            ++cnt;
            while(cnt >= (int)a.size()) {
                a.push_back({});
            }
            a[cnt].len = a[p].len + 2;
            a[cnt].fail = a[getFail(a[p].fail)].ch[ch];
            a[p].ch[ch] = cnt;
        }
        lst = a[p].ch[ch];
        ++a[lst].cnt;
    }
};