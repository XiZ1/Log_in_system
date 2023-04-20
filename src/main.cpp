#include "log_in_system.h"
#include <conio.h>

int main()
{
	system("cls");
	cout << "1. LOG IN\n";
	cout << "1. SIGN IN\n";
	cout << "1. EXIT\n";

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

		}break;

		default:
		{
			
		}
	}

	return 0;
}
