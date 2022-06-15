#include <bits/stdc++.h>
#define P 1000000007
#define INF 2147483647
#define INFF 9223372036854775807
#define int long long
#define N 200005
using namespace std;
int st[N][30];
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
signed main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        st[i][0] = read();
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    int m = read();
    while (m--)
    {
        int x = read(), y = read();
        int k = log(y - x + 1) / log(2);
        printf("%lld\n", max(st[x][k], st[y - (1 << k) + 1][k]));
    }
    return 0;
}