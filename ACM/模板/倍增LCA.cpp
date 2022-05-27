#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn = 200001;
int n, m, s, lg[maxn], deep[maxn], fa[maxn][22], col[maxn];
vector<int>v[maxn];

inline int read()
{
	int X = 0, w = 0; char ch = 0;
	while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

inline void dfs(int x, int father)
{
	deep[x] = deep[father] + 1;
	fa[x][0] = father;
	col[x] = col[father];
	for (int i = 1; (1 << i) <= deep[x]; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < v[x].size(); i++)
		if (v[x][i] != father)dfs(v[x][i], x);
}

inline int LCA(int x, int y)
{
	if (deep[x] < deep[y])swap(x, y);
	while (deep[x] != deep[y])x = fa[x][lg[deep[x] - deep[y]] - 1];
	if (x == y)return x;
	for (register int i = lg[deep[x]]; i >= 0; i--)
		if (fa[x][i] != fa[y][i])x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
int getdis(int x, int y)
{
	return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
}
void work()
{
	n = read(), k = read();
	for (register int i = 1; i <= n; i++)
	{
		col[i] = 0;
		v[i].clear();
	}
	for (int i = 1; i <= k; i++)
		col[k] = 1;

	for (register int i = 1; i <= n - 1; i++)
	{
		int x = read(), y = read();
		v[x].push_back(y);
		v[y].push_back(x);
		d[x]++;
		d[y]++;
	}

	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		if (!col[i])
			ans.push_back(i);
	for (int i = 1; i <= n; i++)
		if (d[i] == 1 && !col[i])
		{
			int p = 0;
			int dis = getdis(1, i);
			for (auto x : ans)
				if (getdis(x, i) < dis)
				{
					p = 1;
					break;
				}
			if (p == 0)
			{
				puts("YES");
				return;
			}
		}
	puts("NO");
}
int main()
{
	int T = read();
	for (int i = 1; i < N; i++)
	{
		lg[i] = lg[i - 1];
		if (i == (1 << lg[i - 1]))lg[i]++;
	}
	while (T--)
		work();
	return 0;
}

