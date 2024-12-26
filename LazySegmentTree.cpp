template<class Info, class Tag>
struct SegmentTree
{
    #define ls(i) i<<1
    #define rs(i) i<<1^1

    int n, s = 1;
    std::vector<Info> info; std::vector<Tag> tag;

    SegmentTree(int _n = 0, Info t = Info()) { init(std::vector<Info>(_n+1,t)); }
    SegmentTree(const std::vector<Info> &v) { init(v); }
    void sets(int _s) { s = _s; }
    void init(int _n = 0, Info t = Info()) { init(std::vector<Info>(_n+1,t)); }
    void init(const std::vector<Info> &v)
    {
        n = v.size()-1;
        info.assign(n<<2^1,Info()); tag.assign(n<<2^1,Tag());
        std::function<void(int,int,int)> build = [&](int i, int l, int r)
        {
            if(l >= r) { info[i] = v[l]; return; }
            int mid = (l+r)>>1;
            build(ls(i),l,mid); build(rs(i),mid+1,r);
            pushup(i);
        };
        build(1,s,n);
    }
    void pushup(int i) { info[i] = info[ls(i)] + info[rs(i)]; }
    void pushdown(int i) { apply(ls(i),tag[i]); apply(rs(i),tag[i]); tag[i] = Tag(); }
    void apply(int i, const Tag &t) { info[i].apply(t); tag[i].apply(t); }
    void modify(int i, int l, int r, int x, const Info &I)
    {
        if(l >= r) { info[i] = I; return; }
        int mid = (l+r)>>1; pushdown(i);
        if(x <= mid) modify(ls(i),l,mid,x,I);
        else modify(rs(i),mid+1,r,x,I);
        pushup(i);
    }
    void apply(int i, int l, int r, int x, int y, const Tag &t)
    {
        if(y < l || r < x) return;
        if(x <= l && r <= y) { apply(i,t); return; }
        int mid = (l+r)>>1; pushdown(i);
        apply(ls(i),l,mid,x,y,t); apply(rs(i),mid+1,r,x,y,t);
        pushup(i);
    }
    Info query(int i, int l, int r, int x, int y)
    {
        if(y < l || r < x) return Info();
        if(x <= l && r <= y) return info[i];
        int mid = (l+r)>>1; pushdown(i);
        return query(ls(i),l,mid,x,y) + query(rs(i),mid+1,r,x,y);
    }
    template<class F> 
    int findFirst(int i, int l, int r, int x, int y, F k) 
    {
        if(y < l || r < x || !k(info[i])) return -1;
        if(l == r) return l;
        int mid = (l+r)>>1; pushdown(i);
        int res = findFirst(ls(i),l,mid,x,y,k);
        if(!~res) res = findFirst(rs(i),mid+1,r,x,y,k);
        return res;
    }
    template<class F> 
    int findLast(int i, int l, int r, int x, int y, F k) 
    {
        if(y < l || r < x || !k(info[i])) return -1;
        if(l == r) return l;
        int mid = (l+r)>>1; pushdown(i);
        int res = findLast(rs(i),mid+1,r,x,y,k);
        if(!~res) res = findLast(ls(i),l,mid,x,y,k);
        return res;
    }
    void modify(int x, const Info &I) { modify(1,s,n,x,I); }
    void apply(int l, int r, const Tag &t) { apply(1,s,n,l,r,t); }
    Info query(int l, int r) { return query(1,s,n,l,r); }
    template<class F> int findFirst(int l, int r, F k) { return findFirst(1,s,n,l,r,k); }
    template<class F> int findLast(int l, int r, F k) { return findLast(1,s,n,l,r,k); }
    
    #undef ls
    #undef rs
};

struct Tag
{
    i64 p,m;
    Tag(i64 _p = 0, i64 _m = 1): p(_p), m(_m) {}
    void apply(const Tag &t)
    {
        if(t.m != 1) p = t.m*p%P, m = t.m*m%P;
        if(t.p) (p += t.p) %= P;
    }
};
struct Info
{
    i64 sum; int len;
    Info(i64 _s = 0, int _l = 0): sum(_s), len(_l) {}
    void apply(const Tag &t) { sum = (sum*t.m + t.p*len)%P; }
    Info operator+(const Info &o) const { return Info((sum+o.sum)%P, len+o.len); }
};
