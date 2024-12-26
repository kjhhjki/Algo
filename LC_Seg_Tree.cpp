// #pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAXN 100005
#define For(I,A,B) for(int I = A; I <= B; ++I)
#define foR(I,A,B) for(int I = A; I >= B; --I)
using namespace std;
typedef long long _ll;
const double EPI = 1e-8;

int cmp(double x, double y)
{
	if(fabs(x-y) < EPI) return 0;
	return x < y ? -1 : 1;
}

int cnt,n,op,x1,Y1,x2,y2,last;

struct line
{
	double k,b;
	line(double k = 0, double b = 0):k(k),b(b){}
	double calc(double x) const { return k*x+b; }
}a[MAXN];

int segmax(int u, int v, int x)
{
	int flag = cmp(a[u].calc(x),a[v].calc(x));
	if(flag == 1 || (!flag && u < v)) return u;
	return v;
}

class LC_Seg_Tree
{
	private:
		int pos[MAXN<<2];
		void update(int,int,int,int);
	public:
		void modify(int,int,int,int,int,int);
		int query(int,int,int,int);
}s;
void LC_Seg_Tree::update(int i, int l, int r, int v)
{
	// cout << i << ' ' << l << ' ' << r << '\n';
	int &u = pos[i], mid = (l+r)>>1;
	int flag_mid = cmp(a[v].calc(mid),a[u].calc(mid));
	if(flag_mid == 1 || (flag_mid == 0 && v < u)) swap(u,v);
	int flag_l = cmp(a[v].calc(l),a[u].calc(l)), flag_r = cmp(a[v].calc(r),a[u].calc(r));
	if(flag_l == 1 || (flag_l == 0 && v < u)) update(i<<1,l,mid,v);
	if(flag_r == 1 || (flag_r == 0 && v < u)) update(i<<1^1,mid+1,r,v);
}
void LC_Seg_Tree::modify(int i, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y) { update(i,l,r,v); return; }
	int mid = (l+r)>>1; 
	if(x <= mid) modify(i<<1,l,mid,x,y,v);
	if(y >  mid) modify(i<<1^1,mid+1,r,x,y,v);
}
int LC_Seg_Tree::query(int i, int l, int r, int x)
{
	if(x < l || r < x) return 0;
	if(l == r) return pos[i];
	int mid = (l+r)>>1, res = pos[i];
	int resl = query(i<<1,l,mid,x), resr = query(i<<1^1,mid+1,r,x);
	// cout << res << ' ' << resl << ' ' << resr << '\n';
	return segmax(segmax(res,resl,x),resr,x);
}

line make_line(int x1, int Y1, int x2, int y2)
{
	if(x1 == x2) return line(0,max(Y1,y2));
	double k = 1.0*(Y1-y2)/(x1-x2), b = Y1-k*x1;
	return line(k,b);
}

int main()
{
	freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);
    ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	while(n--)
	{
		cin >> op;
		if(op)
		{
			cin >> x1 >> Y1 >> x2 >> y2;
			x1 = (x1+last-1)%39989+1; Y1 = (Y1+last-1)%1000000000+1;
			x2 = (x2+last-1)%39989+1; y2 = (y2+last-1)%1000000000+1;
			if(x1 > x2) swap(x1,x2), swap(Y1,y2);
			a[++cnt]=make_line(x1,Y1,x2,y2);
			s.modify(1,1,39989,x1,x2,cnt);
		}
		else
		{
			cin >> x1;
			x1 = (x1+last-1)%39989+1;
			cout << (last = s.query(1,1,39989,x1)) << endl;
		}
	}
    return 0;
}