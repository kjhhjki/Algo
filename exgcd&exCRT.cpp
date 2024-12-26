// i64 exgcd(i64 a, i64 b, i64 &x, i64 &y)
// {
//     x = 1; y = 0;
//     i64 x1 = 0, y1 = 1, a1 = a, b1 = b;
//     while(b1)
//     {
//         i64 q = a1 / b1;
//         std::tie(x, x1) = std::pair(x1, x - q * x1);
//         std::tie(y, y1) = std::pair(y1, y - q * y1);
//         std::tie(a1, b1) = std::pair(b1, a1 - q * b1);
//     }
//     return a1;
// }

i64 exgcd(i64 &x, i64 &y, i64 a, i64 b)
{
    if(!b)
    {
        x = 1; y = 0;
        return a;
    }
    i64 g = exgcd(x,y,b,a%b);
    i64 t = x; x=y;
    y = t - a / b * y;
    return g;
}

i64 excrt()
{
    M = bb[1]; ans = aa[1];
	For(i,2,n)
	{
		x = y = 0; a = aa[i]; b = bb[i];
		c = ((a - ans) % b + b) % b;
		g = exgcd(M,b,x,y);
		// cout << g << ' ' << M << ' ' << b << ' ' << x << ' ' << y << endl;
		p = b / g;
		x = mul(x, c/g, p);
		ans += x * M;
		M *= p;
		ans = (ans % M + M) % M;
	}
}
 
int main()
{
    //freopen("in.txt","r",stdin); freopen("out.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> aa[i] >> bb[i], M *= aa[i];
    for(int i = 1; i <= n; ++i)
    {
        m = M / aa[i];
        exgcd(m,aa[i],x,y);
        if(x < 0) x = x + aa[i];
        ans += bb[i] * m * x;
    }
    cout << ans;
    //fclose(stdin); fclose(stdout);
    return 0;
}