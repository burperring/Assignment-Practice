#include <stdio.h>
#pragma warning(disable:4996)
void main()
{
	int a = 0, b = 0, mul = 1;
	int i;

	printf("���� �ΰ� �Է� : ");
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
		printf("���μҴ�");
	}
	else
		printf("\n\n %2d�� %2d�� �ִ������� %2d�̰�\n �ּҰ������ %2d�̴�", a*mul, b*mul, mul, mul*a*b);
}
