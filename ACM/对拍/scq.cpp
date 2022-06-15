#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	puts("1");
	puts("8");
	string st;
	int a[9];
	for (int i = 1; i <= 8; i++)
		a[i] = i;
	random_shuffle(a + 1, a + 9);
	for (int i = 1; i <= 8; i++)
		st += char(rand() % 26 + int('a'));
	cout << st << endl;
	for (int i = 1; i <= 8; i++)
		printf("%d ", a[i]);
	puts("");
	return 0;
}
