std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 998244352);
template<class Info, class Tag>
struct Node
{
    std::array<Node*, 2> ch{};
    Info info = Info();
    Tag tag = Tag();
    int rk = distrib(gen);
    Node(const Info &I = Info()): info(I) { }
};
template<class Info, class Tag>
struct Treap
{
    using pNode = Node<Info, Tag>*;
    pNode rt = nullptr;

    Treap() { }
    ~Treap()
    {
        auto dfs = [&](auto &&self, pNode u) -> void
        { 
            if(!u) return;
            if(u->ch[0]) self(self, u->ch[0]);
            if(u->ch[1]) self(self, u->ch[1]);
            delete u;
            u = nullptr;
        };
        dfs(dfs, rt);
    }

    void apply(pNode u, const Tag &t) { u->info.apply(t); u->tag.apply(t); }
    void pushup(pNode u)
    {
        u->info.fresh();
        if(u->ch[0]) u->info = u->info + u->ch[0]->info;
        if(u->ch[1]) u->info = u->info + u->ch[1]->info;
    }
    void pushdown(pNode u)
    {
        if(u->ch[0]) apply(u->ch[0], u->tag);
        if(u->ch[1]) apply(u->ch[1], u->tag);
        if(u->tag.rt) std::swap(u->ch[0], u->ch[1]);
        u->tag = Tag();
    }

    void split(pNode u, int k, pNode &x, pNode &y, pNode &z)
    {
        if(u == nullptr) { x = y = z = nullptr; return; }
        pushdown(u);
        int lsz = (u->ch[0]? u->ch[0]->info.size: 0);
        if(k <= lsz) z = u, split(u->ch[0], k, x, y, u->ch[0]);
        else if(k > lsz + u->info.cnt) x = u, split(u->ch[1], k-lsz-u->info.cnt, u->ch[1], y, z);
        else
        {
            x = u->ch[0]; y = u; z = u->ch[1];
            u->ch.fill(nullptr);
        }
        pushup(u);
    }
    pNode merge(pNode x, pNode y)
    {
        if(x == nullptr) return y;
        else if(y == nullptr) return x;
        if(x->rk < y->rk) 
        { 
            pushdown(x);
            x->ch[1] = merge(x->ch[1], y); 
            pushup(x); 
            return x; 
        }
        pushdown(y);
        y->ch[0] = merge(x, y->ch[0]);
        pushup(y);
        return y;
    }

    int rank(Info val)
    {
        pNode u = rt;
        int rk = 0;
        while(u)
        {
            if(val.key < u->info.key) u = u->ch[0];
            else
            {
                if(u->ch[0]) rk += u->ch[0]->info.size;
                if(val.key == u->info.key) break;
                rk += u->info.cnt;
                u = u->ch[1];
            }
        }
        return rk + 1;
    }

    void insert(Info val)
    {
        pNode x(nullptr), y(nullptr), z(nullptr);
        int rk = rank(val);
        split(rt, rk, x, y, z);
        if(y == nullptr) y = new Node<Info, Tag>(Info(val.key, 1, 1));
        else if(y->info.key == val.key)
        {
            ++y->info.cnt;
            pushup(y);
        } 
        else y->ch[y->info.key < val.key] = new Node<Info, Tag>(Info(val.key, 1, 1)), pushup(y);
        rt = merge(merge(x, y), z);
    }
    void erase(Info val)
    {
        int rk = rank(val);
        pNode x(nullptr), y(nullptr), z(nullptr);
        split(rt, rk, x, y, z);
        if(y && y->info.key == val.key) delete y, y = nullptr;
        rt = merge(merge(x, y), z);
    }
    void extract(Info val)
    {
        int rk = rank(val);
        pNode x(nullptr), y(nullptr), z(nullptr);
        split(rt, rk, x, y, z);
        if(y == nullptr || y->info.key != val.key);
        else if(y->info.cnt == 1) delete y, y = nullptr;
        else --y->info.cnt, pushup(y);
        rt = merge(merge(x, y), z);
    }
    Info kth(int k, pNode _rt)
    {
        pNode u = _rt;
        while(u)
        {
            if(u->ch[0] && u->ch[0]->info.size >= k) u = u->ch[0];
            else if(u->info.cnt + (u->ch[0]? u->ch[0]->info.size: 0) >= k) return u->info;
            else k -= u->info.cnt + (u->ch[0]? u->ch[0]->info.size: 0), u = u->ch[1];
        }
        return {-1};
    }
    Info kth(int k) { return kth(k, rt); }
    Info pre(Info val)
    {
        int rk = rank(val);
        pNode x(nullptr), y(nullptr), z(nullptr);
        split(rt,rk-1,x,y,z);
        Info ans = y->info;
        rt = merge(merge(x, y), z);
        return ans;
    }
    Info nxt(Info val)
    {
        ++val.key;
        int rk = rank(val);
        pNode x(nullptr), y(nullptr), z(nullptr);
        split(rt,rk,x,y,z);
        Info ans = y->info;
        rt = merge(merge(x, y), z);
        return ans;
    }
};  
struct Tag
{ 
    bool rt = false; 
    void apply(const Tag &t) 
    { 
        rt ^= t.rt;
    } 
};
struct Info
{ 
    int key = 0;
    int cnt = 0, size = 0;
    Info(int k = 0, int c = 0, int s = 0): key(k), cnt(c), size(s) {}
    void fresh() { this->size = cnt; } 
    void apply(const Tag &t) { } 
    Info operator+(Info o)
    {
        Info res = *this;
        res.size += o.size;
        return res;
    }
};