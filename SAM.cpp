struct SAM
{
    struct Node
    {
        std::array<int, 27> ch;
        int len, pre, cnt;
        Node(int len = 0, int cnt = 0, int pre = 0): len(len), pre(pre), cnt(cnt) { ch.fill(0); }
    };
    std::vector<Node> a;
    int cnt, lst;
    constexpr static int rt = 1;
    SAM(int n = 0) {
        init(n);
    }
    void init(int n = 0) {
        a.assign(2 * n + rt + 1, {});
        cnt = lst = rt;
        a[rt].len = a[rt].pre = 0;
    }
    int newnode() {
        while((int)a.size() < cnt + 2) {
            a.emplace_back();
        }
        return ++cnt;
    }
    void insert(int c) {
        int p = lst, cur = lst = newnode();
        a[cur] = Node(a[p].len + 1, 1);
        while(p && !a[p].ch[c]) {
            a[p].ch[c] = cur;
            p = a[p].pre;
        }
        if(!p) {
            a[cur].pre = rt;
            return;
        }
        int q = a[p].ch[c];
        if(a[q].len == a[p].len + 1) {
            a[cur].pre = q;
            return;
        }
        int cl = newnode();
        a[cl] = {a[p].len + 1, 0, a[q].pre};
        a[cl].ch = a[q].ch;
        while(p && a[p].ch[c] == q) {
            a[p].ch[c] = cl;
            p = a[p].pre;
        }
        a[q].pre = a[cur].pre = cl;
    }
};