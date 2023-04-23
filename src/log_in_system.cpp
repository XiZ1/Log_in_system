#include "log_in_system.h"
#include <Windows.h>
#include <fstream>
#include <filesystem>

void log_in_system::is_first_start_up() const
{
	if (!std::filesystem::exists("db\\"))
	{
		std::filesystem::create_directory("db\\");
	}
	ofstream file;
	file.open("db\\login_list.txt", ofstream::app);
	file.close();
	file.open("db\\log.txt", ofstream::app);
	file.close();
}

void log_in_system::show_message(const string& message, const int wait)
{
	system("cls");
	cout << message;
	Sleep(wait);
}

void log_in_system::add_log(const string& message)
{
	ofstream file;
	file.open("db\\log.txt", ofstream::app);
	file << message << "\n";
	file.close();
}