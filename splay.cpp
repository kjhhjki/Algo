template<typename T>
struct Node
{
    T val = T();
    Node<T> *pre = nullptr;
    int cnt = 0, size = 0;
    std::array<Node<T>*, 2> ch{};
    void pushup()
    {
        size = cnt;
        for(int p = 0; p < 2; ++p) {
            if(ch[p]) size += ch[p]->size;
        }
    }
};
template<typename T>
struct Splay
{
    Node<T> *rt = nullptr;

    struct iterator
    {
        Node<T> *data;
        T operator*(){ return data->val; }
    };

    Splay() { insert(std::numeric_limits<T>::max()); insert(std::numeric_limits<T>::min()); }

    bool get(Node<T> *u) { return u->pre? u == u->pre->ch[1]: 0; }
    void rotModify(Node<T> *x, Node<T> *y, int chk)
    {
        if(x) x->pre = y;
        if(y) y->ch[chk] = x;
        else  rt = x;
    }
    void rotate(Node<T> *x)
    {
        auto *y = x->pre, *z = y->pre;
        int chk = get(x);
        rotModify(x,z,get(y));
        rotModify(x->ch[chk^1],y,chk);
        rotModify(y,x,chk^1);
        y->pushup(); x->pushup();
    }
    void splay(Node<T> *x, Node<T> *tar = nullptr)
    {
        if(!x) return;
        for(auto *y = x->pre; y = x->pre, y != tar; rotate(x))
            if(y->pre != tar)
                rotate(get(y)==get(x)? y: x);
        if(!tar) rt = x;
    }
    void insert(T k)
    {
        Node<T> *cur = rt, *pre = nullptr;
        while(cur && cur->val != k) pre = cur, cur = cur->ch[cur->val < k];
        if(cur) ++cur->cnt;
        else
        {
            cur = new Node<T>{k,pre,1,1};
            if(pre) pre->ch[pre->val < k] = cur;
        }
        splay(cur);
    }
    void erase(T k)
    {
        auto *pre = prev(k).data, *nxt = next(k).data;
        splay(pre); splay(nxt,pre);
        auto *it = nxt->ch[0];
        delete it;
        nxt->ch[0] = nullptr;
    }
    void extract(T k)
    {
        auto *pre = prev(k).data, *nxt = next(k).data;
        splay(pre); splay(nxt,pre);
        auto *it = nxt->ch[0];
        if(it -> cnt > 1) { --it->cnt; splay(it); return; }
        delete it;
        nxt->ch[0] = nullptr;
    }
    void find(T k)
    {
        auto *cur = rt;
        if(!cur) return;
        while(cur->ch[cur->val < k] && k != cur->val)
            cur = cur->ch[cur->val < k];
        splay(cur);
    }
    iterator prev(T k)
    {
        find(k);
        auto *cur = rt;
        if(cur->val < k) return {cur};
        cur = cur->ch[0];
        while(cur->ch[1]) cur = cur->ch[1];
        splay(cur);
        return {cur};
    }
    iterator next(T k)
    {
        find(k);
        auto *cur = rt;
        if(cur->val > k) return {cur};
        cur = cur->ch[1];
        while(cur->ch[0]) cur = cur->ch[0];
        splay(cur);
        return {cur};
    }
    int rank(T k)
    {
        find(k);
        return (rt->ch[0]? rt->ch[0]->size: 0) + (rt->val < k)  *rt->cnt;
    }
    T kth(int k)
    {
        auto *cur = rt;
        while(1)
        {
            if(cur->ch[0] && k <= cur->ch[0]->size) cur = cur->ch[0];
            else
            {
                k -= (cur->ch[0]? cur->ch[0]->size: 0) + cur->cnt;
                if(k <= 0)
                { splay(cur); return cur->val; }
                cur = cur->ch[1];
            }
        }
    }
};