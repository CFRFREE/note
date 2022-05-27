#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	puts("1");
	puts("8");
	for (int i = 1; i <= 8; i++)
		printf("%d ", rand() % 10);
	puts("");
	return 0;
}
