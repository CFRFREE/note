#include<bits/stdc++.h>
#define LL long long
#define maxn 100005
using namespace std;
int n, m, r, P, id[maxn], fa[maxn], son[maxn], cnt;
int top[maxn], sum, a[maxn], b[maxn], deep[maxn], size[maxn];
vector<int>v[maxn];
struct node {
	int l, r, w, f;
} tree[maxn << 2];
inline int read()
{
	int X = 0, w = 0; char ch = 0;
	while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
	while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
	return w ? -X : X;
}

void PushUp(int k)
{
	tree[k].w = tree[k << 1].w + tree[k << 1 | 1].w;
	tree[k].w %= P;
}

void PushDown(int k)
{
	if (tree[k].f)
	{
		int x = tree[k].f;
		tree[k].f = 0;
		tree[k << 1].f += x;
		tree[k << 1 | 1].f += x;
		tree[k << 1].w += x * (tree[k << 1].r - tree[k << 1].l + 1);
		tree[k << 1 | 1].w += x * (tree[k << 1 | 1].r - tree[k << 1 | 1].l + 1);
		tree[k << 1].w %= P;
		tree[k << 1 | 1].w %= P;
	}
}

void build(int k, int ll, int rr)
{
	tree[k].l = ll;
	tree[k].r = rr;
	if (ll == rr)
	{
		tree[k].w = a[ll];
		return;
	}
	int mid = (ll + rr) >> 1;
	build(k << 1, ll, mid);
	build(k << 1 | 1, mid + 1, rr);
	PushUp(k);
}

void change(int k, int ll, int rr, int d)
{
	if (tree[k].l >= ll && tree[k].r <= rr)
	{
		tree[k].f += d;
		tree[k].w += d * (tree[k].r - tree[k].l + 1);
		return;
	}
	PushDown(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= ll)change(k << 1, ll, rr, d);
	if (rr > mid)change(k << 1 | 1, ll, rr, d);
	PushUp(k);
}

int search(int k, int ll, int rr)
{
	int ans = 0;
	if (tree[k].l >= ll && tree[k].r <= rr)
		return tree[k].w % P;

	PushDown(k);
	int mid = (tree[k].l + tree[k].r) >> 1;
	if (mid >= ll)ans += search(k << 1, ll, rr);
	if (rr > mid)ans += search(k << 1 | 1, ll, rr);
	return ans % P;
}

int dfs1(int x, int f, int dep)
{
	deep[x] = dep;
	fa[x] = f;
	size[x] = 1;
	int maxson = -1;
	for (int i = 0; i < v[x].size(); i++)
	{
		int y = v[x][i];
		if (y == fa[x])continue;
		size[x] += dfs1(y, x, dep + 1);
		if (size[y] > maxson)
		{
			son[x] = y;
			maxson = size[y];
		}
	}
	return size[x];
}

void dfs2(int x, int topf)
{
	top[x] = topf;
	id[x] = ++cnt;
	a[cnt] = b[x];

	if (!son[x])return;

	dfs2(son[x], topf);

	for (int i = 0; i < v[x].size(); i++)
		if (!id[v[x][i]])
			dfs2(v[x][i], v[x][i]);
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
	cout << ans % P << endl;
}

void tree_change(int x, int y)
{
	change(1, id[x], id[x] + size[x] - 1, y);
}

void tree_search(int x)
{
	cout << search(1, id[x], id[x] + size[x] - 1) << endl;
}
int main()
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
		int p = read();
		if (p == 1)
		{
			int x = read(), y = read(), z = read();
			path_change(x, y, z);
		}
		if (p == 2)
		{
			int x = read(), y = read();
			path_search(x, y);
		}
		if (p == 3)
		{
			int x = read(), y = read();
			tree_change(x, y);
		}
		if (p == 4)
		{
			int x = read();
			tree_search(x);
		}
	}
	return 0;
}

