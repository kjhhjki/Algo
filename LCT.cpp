template<class Info, class Tag>
struct Node
{
    int pre = 0;
    array<int, 2> ch{};
    Info info = Info();
    Tag tag = Tag();
};
template<class Info, class Tag>
struct LinkCutTree
{
    std::vector<Node<Info,Tag>> tr;

    LinkCutTree(int n = 0, const Info I = Info()) { init(n, I); }
    void init(int n, const Info I = Info())
    {
        tr.assign(n+1, {0,0,0,I});
        tr[0].info = Info();
    }

    bool get(int u) { return u == tr[tr[u].pre].ch[1]; }
    void pushup(int u) { tr[u].info.fresh(); tr[u].info = tr[u].info + tr[tr[u].ch[0]].info + tr[tr[u].ch[1]].info; }
    void apply(int u, const Tag &t) { tr[u].info.apply(t); tr[u].tag.apply(t); }
    void pushdown(int u)
    {
        if(tr[u].ch[0]) apply(tr[u].ch[0], tr[u].tag);
        if(tr[u].ch[1]) apply(tr[u].ch[1], tr[u].tag);
        if(tr[u].tag.rt)
            std::swap(tr[u].ch[0], tr[u].ch[1]);
        tr[u].tag = Tag();
    }
    void rotModify(int x, int y, int chk)
    {
        if(x) tr[x].pre = y;
        if(y) tr[y].ch[chk] = x;
    }
    void rotate(int x)
    {
        int y = tr[x].pre, z = tr[y].pre;
        int chk = get(x);
        if(!isroot(y)) rotModify(x,z,get(y));
        tr[x].pre = z;
        rotModify(tr[x].ch[chk^1],y,chk);
        rotModify(y,x,chk^1);
        pushup(y); pushup(x);
    }
    void splay(int x)
    {
        update(x);
        for(int y = tr[x].pre; y = tr[x].pre, !isroot(x); rotate(x))
            if(!isroot(y))
                rotate(get(y)==get(x)?y:x);
    }

    bool isroot(int x) { return tr[tr[x].pre].ch[0] != x && tr[tr[x].pre].ch[1] != x; }
    void update(int u) 
    { 
        if(!isroot(u)) 
            update(tr[u].pre); 
        pushdown(u); 
    }
    int access(int x) 
    { 
        int y; 
        for(y = 0; x; y = x, x = tr[x].pre) 
            splay(x), tr[x].ch[1] = y, pushup(x); 
        return y; 
    }
    void makeroot(int u) { access(u); splay(u); tr[u].tag.rt ^= 1; }
    void split(int x, int y) { makeroot(x); access(y); splay(y); }
    int find(int x) 
    { 
        access(x); splay(x); 
        pushdown(x); 
        while(tr[x].ch[0]) 
            x = tr[x].ch[0], pushdown(x); 
        splay(x); 
        return x; 
    }
    void link(int x, int y)
    {
        makeroot(x);
        if(find(y) != x) tr[x].pre = y;
    }
    bool cut(int x, int y)
    {
        makeroot(x);
        if(find(y) != x || tr[x].info.size > 2) return false;
        tr[y].pre = tr[x].ch[1] = 0; pushup(x);
        return true;
    }

    void apply(int u, int v, const Tag &t) { split(u,v); apply(v,t); }
    Info query(int u, int v) { split(u,v); return tr[v].info; }
};

struct Tag
{ 
    int p = 0, m = 1;
    bool rt = false; 
    void apply(const Tag &t) 
    { 
        m *= t.m; p *= t.m; p += t.p; 
        rt ^= t.rt;
    } 
};
struct Info
{ 
    int key = 0, sum = 0;
    int size = 0;
    void fresh() { this->sum = key; this->size = 1; } 
    void apply(const Tag &t)
    {
        sum = sum * t.m + t.p * size;
        key = key * t.m + t.p;
    } 
    Info operator+(Info o)
    {
        Info res = *this;
        res.sum += o.sum;
        res.size += o.size;
        return res;
    }
};
