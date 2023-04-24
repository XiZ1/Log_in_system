#include "log_in_system.h"
#include <Windows.h>
#include <fstream>
#include <string>

bool log_in_system::log_in()
{
	is_first_start_up();
	enter_login();
	enter_password();
	download_login_list();
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
			delete_user_from_login_list(login_);
		}
	}
	else
	{
		show_message("USER DOESN'T EXIST!\n", 1500);
	}
	return false;
}

void log_in_system::enter_login()
{
	show_message("LOGIN: ", 0);
	cin >> given_login_;
}

void log_in_system::enter_password()
{
	show_message("PASSWORD: ", 0);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	cin.ignore();
	getline(cin, given_password_);
}

void log_in_system::download_login_list()
{
	string temp;
	ifstream file;
	file.open("db\\login_list.txt");
	while (!file.eof())
	{
		std::getline(file, temp);
		login_list_.push_back(temp);
	}
	file.close();
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
	return false;
}

bool log_in_system::download_password(const string& login)
{
	string temp;
	ifstream file;
	file.open("db\\" + login + "\\password.txt");
	if (!file.is_open())
	{
		file.close();
		add_log("ERROR: Not found \"" + login + "\" user in database.\n");
		return false;
	}
	std::getline(file, temp);
	password_ = temp;
	file.close();
	return true;
}

void log_in_system::delete_user_from_login_list(const string& login)
{
	for (int i = 0; i < login_list_.size(); i++)
	{
		if (login_list_[i] == login)
		{
			const auto it = login_list_.begin() + i;
			login_list_.erase(it);
		}
	}
	update_login_list();
}

void log_in_system::update_login_list() const
{
	ofstream file;
	file.open("db\\login_list.txt");
	for (int i = 0; i < login_list_.size(); i++)
	{
		file << login_list_[i] << "\n";
	}
	file.close();
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
