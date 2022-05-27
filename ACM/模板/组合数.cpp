#include <bits/stdc++.h>
#define P 1000000007
#define mod 1000003
#define INF ((1<<31)-1)
#define INFF ((1<<63)-1)
#define int long long
#define N 1000003
using namespace std;
int jc[N], jc_inv[N];
inline int read()
{
	int X = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch))
	{
		w |= ch == '-';
		ch = getchar();
	}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}
int qpow(int x, int y, int k)
{
	int res = 1;
	x %= k;
	while (y)
	{
		if (y & 1)
			res = res * x % k;
		x = x * x % k;
		y >>= 1;
	}
	return res;
}
void init()
{
	jc[0] = 1;
	for (int i = 1; i < N; i++)
		jc[i] = (jc[i - 1] * i) % mod;
	jc_inv[N - 1] = qpow(jc[N - 1], mod - 2, mod);
	for (int i = N - 1; i >= 1; i--)
		jc_inv[i - 1] = (jc_inv[i] * i) % mod;
}
int C(int x, int y)
{
	if (x < y || y < 0)
		return 0;
	if (y == 0)
		return 1;
	return	(jc[x] * jc_inv[y] % mod) * jc_inv[x - y] % mod;
}
signed main()
{
	int T = read();
	init();
	for (int t = 1; t <= T; t++)
	{
		int n = read(), m = read();
		printf("%lld\n", C(n, m));
	}
	return 0;
}
