#include <bits/stdc++.h>
#define INF 2147483647
#define LL long long
#define N 100005
using namespace std;
int n, m, cnt, sum[N], from[N], to[N], next[N], vis[N], d[N], v[N];
queue<int>q;
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
inline void add(int x, int y, int z)
{
	to[++cnt] = y;
	v[cnt] = z;
	next[cnt] = from[x];
	from[x] = cnt;
}
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= m; i++)
	{
		int x = read(), y = read(), z = read();
		add(y, x, z);
	}
	for (int i = 1; i <= n; i++)
		add(0, i, 0);
	memset(d, 0x3f, sizeof(d));
	d[0] = 0;
	vis[0] = 1;
	q.push(0);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for (int i = from[x]; i; i = next[i])
		{
			int y = to[i];
			if (d[y] > d[x] + v[i])
			{
				d[y] = d[x] + v[i];
				if (!vis[y])
				{
					sum[y]++;
					q.push(y);
					if (sum[y] > n)
					{
						printf("NO\n");
						return 0;
					}
					vis[y] = 1;
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", d[i]);
	return 0;
}