#include <stdio.h>
#include <conio.h>
#pragma warning(disable:4996)

void main()
{
	while (1)
	{
		char ch;
		int a = 0, b;

		while (1)
		{
			ch = _getch();
			putchar(ch);

			if (ch >= '0' && ch <= '9')
			{
				b = ch;
				a = a * 10 + b - '0';
			}
			else
			{
				printf("\n�Է��� ���� %d �Դϴ�. \n", a);
				break;
			}
		}
	}
}