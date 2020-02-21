#include "MinecraftServerLauncher.h"

int main()
{
	system("title ºÏ±ØÀÇ ¼­¹ö ±¸µ¿±â ver 2.1");

	read();

	while (1)
	{
		system("cls");

		__print_lobby();

		char input;

		do {
			input = _getch();
		} while (input > '4' || input < '1');

		switch (input)
		{
		case '1':
			start();
			break;
		case '2':
			setting();
			break;
		case '3':
			info();
			break;
		case '4':
			return 0;
		}
	}
}