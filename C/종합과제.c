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
				printf("\n입력한 수는 %d 입니다. \n", a);
				break;
			}
		}
	}
}