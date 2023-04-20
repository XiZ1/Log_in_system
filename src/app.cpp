#include "log_in_system.h"
#include <Windows.h>

void log_in_system::show_message(const string& message, const int wait)
{
	system("cls");
	cout << message << "\n";
	Sleep(wait);
}
