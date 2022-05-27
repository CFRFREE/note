#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define LL long long
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
string work(int x, int y, int z)
{
	string tep, res;
	tep = to_string(x);
	while (tep.size() < 4)
		tep = "0" + tep;
	res += tep;
	tep = to_string(y);
	while (tep.size() < 2)
		tep = "0" + tep;
	res += tep;
	tep = to_string(z);
	while (tep.size() < 2)
		tep = "0" + tep;
	res += tep;
	return res;
}
signed main()
{
	int a[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int n = read();
	int y = n / 10000;
	int m = n % 10000 / 100;
	int d = n % 100;
	int maxn = a[m];
	maxn += (m == 2 && y % 4 == 0 && y % 100 != 0);
	string ans1 = "", ans2 = "";
	while (y <= 9999 && m <= 12 && d <= maxn)
	{
		d++;
		if (d > maxn)
			d = 1, m++;
		if (m > 12)
			m = 1, y++;
		string tep = work(y, m, d);
		if (ans1 == "")
		{
			string t = tep;
			reverse(t.begin(), t.end());
			if (t == tep)ans1 = tep;
		}
		if (ans2 == "")
		{
			if (tep[0] == tep[2] && tep[0] == tep[5] && tep[0] == tep[7])
				if (tep[1] == tep[3] && tep[1] == tep[4] && tep[1] == tep[6])
					if (tep[0] != tep[1])
					{
						ans2 = tep;
						cout << ans1 << endl << ans2 << endl;
						return 0;
					}
		}
	}
	return 0;
}