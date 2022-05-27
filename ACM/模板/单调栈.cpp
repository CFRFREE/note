#include <bits/stdc++.h>
#define INF 2147483647
#define LL long long
#define N 3000005
using namespace std;
int n, ans[N], a[N];
stack<int>s;
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
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++)
	{
		while (!s.empty() && a[i] > a[s.top()])
		{
			ans[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	return 0;
}