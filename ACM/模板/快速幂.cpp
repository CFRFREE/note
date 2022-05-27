#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 100005
using namespace std;
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
int qpow(int x, int y)
{
	int res = 1ll;
	for (; y; y >>= 1ll)
	{
		if (y & 1ll)res = (res * x) % P;
		x = x * x % P;
	}
	return res;
}
signed main()
{
	int T = 1; T = read();
	while ( T-- )
		work();
	return 0;
}