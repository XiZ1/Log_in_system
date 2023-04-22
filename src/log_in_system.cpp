#include "log_in_system.h"
#include <Windows.h>
#include <fstream>

void log_in_system::show_message(const string& message, const int wait)
{
	system("cls");
	cout << message;
	Sleep(wait);
}

void log_in_system::add_error_log(const string& message)
{
	ofstream file;
	file.open("db\\log.txt", std::fstream::app);
	file << message << "\n";
	file.close();
}