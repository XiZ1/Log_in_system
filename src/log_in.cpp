#include "log_in_system.h"
#include <fstream>

bool log_in_system::log_in()
{
	enter_login();
	enter_password();
	if (check_login(login_))
	{
		if (check_password(login_))
		{
			return true;
		}
	}
	return false;
}

void log_in_system::enter_login()
{
	show_message("LOG IN", 0);
	cin >> login_;
}

void log_in_system::enter_password()
{
	show_message("SIGN IN", 0);
	cin >> password_;
}

bool log_in_system::check_login(const string& login)
{
	ifstream file;
	file.open("db\\login_list.txt");
	if (!file.is_open())
	{
		file.close(); //TODO: ADD ERROR CONTROL!
		return false;
	}

	file.close();

	return true;
}

bool log_in_system::check_password(const string& login)
{
	ifstream file;
	file.open("db\\" + login + ".txt");
	if (!file.is_open())
	{
		file.close(); //TODO: ADD ERROR CONTROL!
		return false;
	}

	file.close();

	return true;
}
