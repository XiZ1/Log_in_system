#include "log_in_system.h"
#include <Windows.h>
#include <fstream>
#include <string>

bool log_in_system::sign_in()
{
	is_first_start_up();
	enter_login();
	set_password();
	set_user_details();
	download_login_list();
	if (login_validation(given_login_))//search_login_on_list(given_login_) && 
	{
		if (password_validation(given_password_, given_repeat_password_))
		{
			if (add_user_to_database())
			{
				return true;
			}
		}
	}
	return false;
}

void log_in_system::set_password()
{
	show_message("PASSWORD: ", 0);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	cin.ignore();
	getline(cin, given_password_);
	show_message("REPEAT PASSWORD: ", 0);
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	getline(cin, given_repeat_password_);
}

void log_in_system::set_user_details()
{
	show_message("SET NAME: ", 0);
	cin >> name_;
	show_message("SET SURNAME: ", 0);
	cin >> surname_;
	show_message("SET EMAIL: ", 0);
	cin >> email_;
	show_message("PHONE NUMBER: ", 0);
	cin >> phone_number_;
}

bool log_in_system::login_validation(const string& given_login)
{
	char_counter(given_login);
	if (space_counter_ == 0 && special_char_counter_ == 0)
	{
		if (given_login.length() >= 4 && given_login.length() <= 24)
		{
			if (lowercase_counter_ > 1 && uppercase_counter_ > 1 && number_counter_ > 1)
			{
				return true;
			}
		}
	}
	return false;
}

void log_in_system::char_counter(const string& string_data)
{
	for (int i = 0; i < string_data.length(); i++)
	{
		if (std::isspace(string_data[i]))
		{
			space_counter_++;
		}
		if (std::ispunct(string_data[i]))
		{
			special_char_counter_++;
		}
		if (std::islower(string_data[i]))
		{
			lowercase_counter_++;
		}
		if (std::isupper(string_data[i]))
		{
			uppercase_counter_++;
		}
		if (std::isdigit(string_data[i]))
		{
			number_counter_++;
		}
	}
}

bool log_in_system::password_validation(const string& given_password, const string& given_repeat_password)
{
	char_counter(given_password);
	if (space_counter_ == 0 && special_char_counter_ >= 1)
	{
		if (given_password == given_repeat_password)
		{
			if (given_password.length() >= 4 && given_password.length() <= 24)
			{
				if (lowercase_counter_ > 1 && uppercase_counter_ > 1 && number_counter_ > 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool log_in_system::add_user_to_database()
{
	return true;
}
