#include <stdio.h>
#pragma warning(disable:4996)
void main(void)

{

	int n;
	int i, j, k = 1;

	printf("정수입력");
	scanf("%d", &n);

	n = n % 2 ? n : n - 1;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (j <= k || j >= (n + 1 - k))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
		i < (n / 2) + 1 ? k++ : k--;
	}
}