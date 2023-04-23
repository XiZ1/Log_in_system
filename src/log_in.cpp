#include "log_in_system.h"
#include <fstream>
#include <string>
#include <Windows.h>

bool log_in_system::log_in()
{
	enter_login();
	enter_password();
	if (download_login_list())
	{
		if (search_login_on_list(given_login_))
		{
			if (download_password(login_))
			{
				if (check_password(given_password_))
				{
					return true;
				}
			}
			else
			{
				//TODO: DELETED USER FROM LOGIN LIST IF DOWNLOAD_PASSWORD RETURN FALSE.
			}
		}
	}
	else
	{
		//TODO: CHECK DATABASE EXIST (TRUE-> ADD LOGIN_LIST.TXT | FALSE-> ADD DB/ AND LOGIN_LIST.TXT)
	}
	return false;
}

void log_in_system::enter_login()
{
	show_message("LOG IN: ", 0);
	cin >> given_login_;
}

void log_in_system::enter_password()
{
	show_message("SIGN IN: ", 0);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	cin.ignore();
	getline(cin, given_password_);
}

bool log_in_system::download_login_list()
{
	string temp;
	ifstream file;
	file.open("db\\login_list.txt");
	if (!file.is_open())
	{
		file.close();
		add_error_log("Login_list.txt file doesn't exist.\n");
		show_message("DATABASE CONNECTION ERROR!\n", 1500);
		return false;
	}
	while (!file.eof())
	{
		std::getline(file, temp);
		login_list_.push_back(temp);
	}
	file.close();
	return true;
}

bool log_in_system::search_login_on_list(const string& give_login)
{
	for (int i = 0; i < login_list_.size(); i++)
	{
		if (login_list_[i] == give_login)
		{
			login_ = login_list_[i];
			return true;
		}
	}
	show_message("USER DOESN'T EXIST!\n", 1500);
	return false;
}

bool log_in_system::download_password(const string& login)
{
	string temp;
	ifstream file;
	file.open("db\\" + login + ".txt");
	if (!file.is_open())
	{
		file.close();
		add_error_log("User \"" + login + "\" file doesn't exist.\n");
		show_message("USER DOESN'T EXIST!\n", 1500);
		return false;
	}
	std::getline(file, temp);
	password_ = temp;
	file.close();
	return true;
}

bool log_in_system::check_password(const string& given_password) const
{
	if (password_ == given_password)
	{
		show_message("LOG IN SUCCESSFULLY!\n", 1500);
		return true;
	}
	show_message("WRONG PASSWORD!\n", 1500);
	return false;
}
