#include<bits/stdc++.h>
#define MAXN 50005

using namespace std;

int n, m, d[6][MAXN], vis[MAXN], last[200005], next[200005], to[200005], value[200005],
    home[6], sum, ans = 1e18, cnt;
queue<int>q;
map<int, int>M;

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

inline void add(int u, int v, int w)
{
	to[++cnt] = v;
	next[cnt] = last[u];
	last[u] = cnt;
	value[cnt] = w;
}

void spfa(int from, int id)
{
	memset(d[id], 0x7f, sizeof(d[id]));
	memset(vis, 0, sizeof(vis));
	d[id][from] = 0;
	vis[from] = 1;
	q.push(from);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for (register int i = last[x]; i; i = next[i])
		{
			int y = to[i];
			if (d[id][x] + value[i] < d[id][y])
			{
				d[id][y] = d[id][x] + value[i];
				if (!vis[y])
				{
					vis[y] = 1;
					q.push(y);
				}
			}
		}
	}
}

int main()
{
	n = read(), m = read();
	for (register int i = 1; i <= 5; i++)
		home[i] = read();

	while (m--)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z);
		add(y, x, z);
	}

	sort(home + 1, home + 6);
	for (register int i = 1; i <= 5; i++)
	{
		spfa(home[i], i);
		M[home[i]] = i;
	}

	do
	{
		int sum = d[M[home[1]]][1];
		for (register int i = 1; i <= 4; i++)
			sum += d[M[home[i]]][home[i + 1]];
		if (sum < ans)ans = sum;
	}
	while (next_permutation(home + 1, home + 6));

	printf("%d", ans);
	return 0;
}
