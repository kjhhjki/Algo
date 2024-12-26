template<class Info>
struct Pers_Seg_Tree
{
    int sz, T = 0, s = 1;
    std::vector<int> rt;
    std::vector<int> ls,rs;
    std::vector<Info> info;
    Pers_Seg_Tree(int n = 0, int _sz = 0) { init(n, _sz); }
    void sets(int _s) { s = _s; }
    void init(int n = 0, int _sz = 0) 
    { 
        sz = _sz; int lg = 33 - __builtin_clz(sz);
        rt.assign(n+1, 0);
        info.assign((sz << 1) + n * lg, Info()); ls.assign((sz << 1) + n * lg, 0); rs.assign((sz << 1) + n * lg, 0);
        std::function<void(int&,int,int)> build = [&](int &i, int l, int r)
        {
            i = ++T;
            if(l==r) return;
            int mid = (l+r) >> 1;
            build(ls[i],l,mid); build(rs[i],mid+1,r);
        };
        build(rt[0],s,sz);
    }

    void pushup(int i) { info[i] = info[ls[i]] + info[rs[i]]; }
    void modify(int i, int &j, int l, int r, int k, const Info &I)
    {
        j = ++T;
        while(int(info.size()) <= T) info.push_back(Info()), ls.push_back(0), rs.push_back(0);
        info[j] = info[i]; ls[j] = ls[i]; rs[j] = rs[i];
        if(l == r) { info[j] = info[j] + I; return; }
        int mid = (l+r)>>1;
        if(k <= mid) modify(ls[i],ls[j],l,mid,k,I);
        else modify(rs[i],rs[j],mid+1,r,k,I);
        pushup(j);
    }
    Info query(int i, int j, int l, int r, int x, int y)
    {
        if(y < l || r < x) return Info();
        if(x <= l && r <= y) return info[j] - info[i];
        int mid = (l+r)>>1;
        return query(ls[i],ls[j],l,mid,x,y) + query(rs[i],rs[j],mid+1,r,x,y);
    }
    template<class F> 
    int findFirst(int i, int j, int l, int r, int x, int y, F k) 
    {
        if(y < l || r < x || !k(info[j]-info[i])) return -1;
        if(l == r) return l;
        int mid = (l+r)>>1;
        int res = findFirst(ls[i],ls[j],l,mid,x,y,k);
        if(!~res) res = findFirst(rs[i],rs[j],mid+1,r,x,y,k-(info[ls[j]]-info[ls[i]]));
        return res;
    }
    template<class F> 
    int findLast(int i, int j, int l, int r, int x, int y, F k) 
    {
        if(y < l || r < x || !k(info[j]-info[i])) return -1;
        if(l == r) return l;
        int mid = (l+r)>>1;
        int res = findLast(rs[i],rs[j],mid+1,r,x,y,k);
        if(!~res) res = findLast(ls[i],ls[j],l,mid,x,y,k-(info[rs[j]]-info[rs[i]]));
        return res;
    }
    void modify(int lst, int cur, int k, const Info &I) { modify(rt[lst],rt[cur],s,sz,k,I); }
    Info query(int l, int r, int x, int y) { return query(rt[l-1],rt[r],s,sz,x,y); }
    template<class F> int findFirst(int l, int r, int x, int y, F k) { return findFirst(rt[l-1],rt[r],s,sz,x,y,k); }
    template<class F> int findLast(int l, int r, int x, int y, F k) { return findLast(rt[l-1],rt[r],s,sz,x,y,k); }
};

struct Info 
{ 
    int cnt;
    Info(int n = 0): cnt(n) {}
    Info operator+(const Info &o) const { return Info(cnt + o.cnt); }
    Info operator-(const Info &o) const { return Info(cnt - o.cnt); }
};
struct Find
{
    int k = 0;
    bool operator()(const Info &o) { return k <= o.cnt; }
    Find operator-(const Info &o) const { return Find{k - o.cnt}; }
};
