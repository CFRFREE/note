#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define pii pair<int,int>
#define LL long long
#define endl '\n'
#define N 100005
#define IOS ios::sync_with_stdio(false), cin.tie(0)
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
void work()
{
	int n;
	cin >> n;
	vector<int>a(n + 1);
	string st, ori;
	cin >> st;
	ori = st;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int cnt = 0;
	while (++cnt)
	{
		string str;
		str.resize(n);
		for (int i = 1; i <= n; i++)
			str[i - 1] = st[a[i] - 1];
		st = str;
		if (str == ori)
			break;
	}
	cout << cnt << endl;
}
signed main()
{
	int T = 1; cin >> T;
	while ( T-- )
		work();
	return 0;
}