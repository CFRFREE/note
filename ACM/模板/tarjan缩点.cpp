#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
#define N 100005
using namespace std;
int from[N], to[N], Next[N], sum[N], id[N], in[N];
int low[N], dfn[N], w[N], dp[N];
int n, m, cnt, M, ans;
stack<int>s;
struct Node
{
	int from, to;
} e[N << 1];
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
inline void add(int x, int y)
{
	to[++cnt] = y;
	Next[cnt] = from[x];
	from[x] = cnt;
}
void tarjan(int x)
{
	in[x] = 1;
	s.push(x);
	dfn[x] = low[x] = ++cnt;
	for (int i = from[x]; i; i = Next[i])
	{
		int y = to[i];
		if (!dfn[y])
		{
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if (in[y])
			low[x] = min(low[x], dfn[y]);
	}
	if (dfn[x] == low[x])
	{
		M++;
		while (s.top() != x)
		{
			int X = s.top();
			s.pop();
			id[X] = M;
			in[X] = 0;
			sum[M] += w[X];
		}
		int X = s.top();
		s.pop();
		id[X] = M;
		in[X] = 0;
		sum[M] += w[X];
	}
}
void search(int x)
{
	if (dp[x])return;
	dp[x] = sum[x];
	int maxson = 0;
	for (int i = from[x]; i; i = Next[i])
	{
		int y = to[i];
		if (!dp[y])
			search(y);
		maxson = max(maxson, dp[y]);
	}
	dp[x] += maxson;
}
int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		w[i] = read();

	for (int i = 1; i <= m; i++)
	{
		e[i].from = read();
		e[i].to = read();
		add(e[i].from, e[i].to);
	}
	cnt = 0;
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i);
	cnt = 0;
	memset(from, 0, sizeof(from));
	memset(to, 0, sizeof(to));
	memset(Next, 0, sizeof(Next));

	for (int i = 1; i <= m; i++)
		if (id[e[i].from] != id[e[i].to])
			add(id[e[i].from], id[e[i].to]);
	for (int i = 1; i <= M; i++)
		search(i);
	for (int i = 1; i <= M; i++)
		ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}