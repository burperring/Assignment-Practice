#include <stdio.h>
#pragma warning(disable:4996)

void main()
{
	int n;
	int i, j;

	printf("정수입력");
	scanf("%d", &n);

	for (i = n - 1; i >= 0; i--)
	{
		for (j = 0; j <= i; j++)
		{
			printf("*");
		}
		for (j = 0; j < (n - 1) - i; j++)
		{
			printf(" ");
		}
		for (j = 0; j < (n - 1) - i; j++)
		{
			printf(" ");
		}
		for (j = 0; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	for (i = 1; i < n; i++)
	{
		for (j = 0; j <= i; j++)
		{
			printf("*");
		}
		for (j = 0; j < (n - 1) - i; j++)
		{
			printf(" ");
		}
		for (j = 0; j < (n - 1) - i; j++)
		{
			printf(" ");
		}
		for (j = 0; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}