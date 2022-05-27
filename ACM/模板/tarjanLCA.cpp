#include<bits/stdc++.h>
#define LL long long
#define maxn 500005

using namespace std;

int n, m, s, vis[maxn], ans[maxn], fa[maxn];
vector<int>v[maxn];
vector< pair<int, int> >ask[maxn];

inline int read()
{
    int X = 0, w = 0; char ch = 0;
    while (!isdigit(ch)) {w |= ch == '-'; ch = getchar();}
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

int find(int x)
{
    if (fa[x] != x)fa[x] = find(fa[x]);
    return fa[x];
}

void tarjan(int x)
{
    vis[x] = 1;
    int X = find(x);
    for (register int i = 0; i < v[x].size(); i++)
    {
        int y = v[x][i];
        if (vis[y])continue;
        tarjan(y);
        int Y = find(y);
        if (X != Y)fa[Y] = X;
    }

    for (register int i = 0; i < ask[x].size(); i++)
    {
        int y = ask[x][i].first, id = ask[x][i].second;
        if (vis[y])ans[id] = find(y);
    }
}

int main()
{
    n = read(), m = read(), s = read();

    for (register int i = 1; i < n; i++)
    {
        int x = read(), y = read();
        v[x].push_back(y);
        v[y].push_back(x);
    }

    for (register int i = 1; i <= m; i++)
    {
        int x = read(), y = read();
        ask[x].push_back(make_pair(y, i));
        ask[y].push_back(make_pair(x, i));
    }

    for (register int i = 1; i <= n; i++)
        fa[i] = i;

    tarjan(s);

    for (register int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}

