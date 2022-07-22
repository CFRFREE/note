#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int n, m, r, P, id[N], fa[N], son[N], cnt;
int top[N], sum, a[N], b[N], deep[N], sz[N];
vector<int>v[N];
struct node {
	int l, r, w, f;
} tree[N << 2];
inline int read()
{
	int X = 0, w = 0; char ch = 0;
	while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

void PushUp(int k)
{
	tree[k].w = (tree[k << 1].w + tree[k << 1 | 1].w) % P;
}

void PushDown(int k)
{
	if (!tree[k].f)return;
	int x = tree[k].f;
	tree[k].f = 0;
	tree[k << 1].f += x;
	tree[k << 1 | 1].f += x;
	tree[k << 1].w += x * (tree[k << 1].r - tree[k << 1].l + 1);
	tree[k << 1 | 1].w += x * (tree[k << 1 | 1].r - tree[k << 1 | 1].l + 1);
	tree[k << 1].w %= P;
	tree[k << 1 | 1].w %= P;
}

void build(int k, int L, int R)
{
	tree[k].l = L;
	tree[k].r = R;
	if (L == R)
	{
		tree[k].w = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(k << 1, L, mid);
	build(k << 1 | 1, mid + 1, R);
	PushUp(k);
}

void change(int k, int L, int R, int d)
{
	if (tree[k].l >= L && tree[k].r <= R)
	{
		tree[k].f += d;
		tree[k].w += d * (tree[k].r - tree[k].l + 1);
		tree[k].w %= P;
		return;
	}
	PushDown(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= L)change(k << 1, L, R, d);
	if (R > mid)change(k << 1 | 1, L, R, d);
	PushUp(k);
}

int search(int k, int L, int R)
{
	int ans = 0;
	if (tree[k].l >= L && tree[k].r <= R)
		return tree[k].w % P;
	PushDown(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= L)ans += search(k << 1, L, R);
	if (R > mid)ans += search(k << 1 | 1, L, R);
	return ans % P;
}

int dfs1(int x, int f, int dep)
{
	deep[x] = dep;
	fa[x] = f;
	sz[x] = 1;
	int maxson = -1;
	for (auto y : v[x])
	{
		if (y == fa[x])continue;
		sz[x] += dfs1(y, x, dep + 1);
		if (sz[y] > maxson)
		{
			son[x] = y;
			maxson = sz[y];
		}
	}
	return sz[x];
}

void dfs2(int x, int topf)
{
	top[x] = topf;
	id[x] = ++cnt;
	a[cnt] = b[x];
	if (!son[x])return;
	dfs2(son[x], topf);
	for (auto y : v[x])
		if (!id[y])
			dfs2(y, y);
}

void path_change(int x, int y, int z)
{
	while (top[x] != top[y])
	{
		if (deep[top[x]] < deep[top[y]])swap(x, y);
		change(1, id[top[x]], id[x], z);
		x = fa[top[x]];
	}
	if (deep[x] > deep[y])swap(x, y);
	change(1, id[x], id[y], z);
}

void path_search(int x, int y)
{
	int ans = 0;
	while (top[x] != top[y])
	{
		if (deep[top[x]] < deep[top[y]])swap(x, y);
		ans += search(1, id[top[x]], id[x]);
		ans %= P;
		x = fa[top[x]];
	}
	if (deep[x] > deep[y])swap(x, y);
	ans += search(1, id[x], id[y]);
	printf("%Ld\n", ans % P);
}

void tree_change(int x, int y)
{
	change(1, id[x], id[x] + sz[x] - 1, y);
}

void tree_search(int x)
{
	printf("%Ld\n", search(1, id[x], id[x] + sz[x] - 1));
}

signed main()
{
	n = read(), m = read(), r = read(), P = read();
	for (int i = 1; i <= n; i++)
		b[i] = read();
	for (int i = 1; i < n; i++)
	{
		int x = read(), y = read();
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs1(r, 0, 1);
	dfs2(r, r);
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		int opt = read();
		if (opt == 1)
		{
			int x = read(), y = read(), z = read();
			path_change(x, y, z);
		}
		else if (opt == 2)
		{
			int x = read(), y = read();
			path_search(x, y);
		}
		else if (opt == 3)
		{
			int x = read(), y = read();
			tree_change(x, y);
		}
		else
		{
			int x = read();
			tree_search(x);
		}
	}
	return 0;
}