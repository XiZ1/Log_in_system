/*
 *	Copyright (C) 2023 Jakub Gorecki - All Rights Reserved.
 */

#include "log_in_system.h"
#include <conio.h>

int main()
{
	bool end_app = true;
	do
	{
		system("cls");
		cout << "1. LOG IN\n";
		cout << "2. SIGN IN\n";
		cout << "3. EXIT\n";

		switch (_getch())
		{
			case '1':
			{
				log_in_system start;
				start.log_in();
			}break;

			case '2':
			{
				log_in_system start;
				start.sign_in();
			}break;

			case '3':
			{
				end_app = false;
			}break;

			default:
			{
				system("cls");
				cout << "THIS OPTION NOT EXIST!\n";
			}
		}
	} while (end_app);

	return 0;
}
