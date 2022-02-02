#include <stdio.h>
#pragma warning(disable:4996)

void main()
{
	int i, j,s, n;
	printf("숫자를 입력해주세요 :");
	scanf("%d", &n);


	for (i = 0; i < n; i++)
	{
		for (s = 0; s < (n-1)-i; s++)
		{
			printf(" ");
		}
		for (j = 0; j < 2 * i + 1; j++)
		{
			if (j == 0 || j == 2 * i || i == n - 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	for (i = n - 2; i >= 0; i--)
	{
		for (s = 0; s < (n - 1) - i; s++)
		{
			printf(" ");
		}
		for (j = 0; j < 2 * i + 1; j++)
		{
			if (j == 0 || j == 2 * i)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}