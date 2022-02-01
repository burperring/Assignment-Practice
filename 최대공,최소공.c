#include <stdio.h>
#pragma warning(disable:4996)
void main()
{
	int a = 0, b = 0, mul = 1;
	int i;

	printf("정수 두개 입력 : ");
	scanf("%d %d", &a, &b);
	for (i = 2; i <= 100; i++)
	{
		if (a%i == 0 && b%i == 0)
		{
			mul = mul*i;
			printf("%d>>%d %d\n", i, a, b);
			a = a / i;
			b = b / i;
			i = 1;
		}
	}
	printf("  %2d   %2d\n", a, b);
	if (mul == 1)
	{
		printf("서로소다");
	}
	else
		printf("\n\n %2d와 %2d의 최대공약수는 %2d이고\n 최소공배수는 %2d이다", a*mul, b*mul, mul, mul*a*b);
}
