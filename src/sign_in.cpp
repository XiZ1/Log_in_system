#include "log_in_system.h"
#include <filesystem>
#include <Windows.h>
#include <fstream>
#include <string>

bool log_in_system::sign_in()
{
	is_first_start_up();
	set_login();
	set_password();
	set_user_details();
	download_login_list();
	if (search_login_on_list(given_login_) && login_validation(given_login_))
	{
		if (password_validation(given_password_, given_repeat_password_))
		{
			if (add_user_to_database())
			{
				show_message("REGISTER SUCCESSFULLY!\n", 2000);
				return true;
			}
		}
	}
	show_message("SIGN IN FAILED!\n", 2000);
	return false;
}

void log_in_system::set_login()
{
	show_message("LOGIN: ", 0);	//TODO: Poprawic opis
	cin >> given_login_;
}

void log_in_system::set_password()
{
	show_message("PASSWORD: ", 0);	//TODO: Poprawic opis
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	cin.ignore();
	getline(cin, given_password_);
	show_message("REPEAT PASSWORD: ", 0);	//TODO: Poprawic opis
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	getline(cin, given_repeat_password_);
}

void log_in_system::set_user_details()	//TODO: Add user details validation!
{
	show_message("SET NAME: ", 0);	//TODO: Poprawic opis
	cin >> name_;
	show_message("SET SURNAME: ", 0);	//TODO: Poprawic opis
	cin >> surname_;
	show_message("SET EMAIL: ", 0);	//TODO: Poprawic opis
	cin >> email_;
	show_message("PHONE NUMBER: ", 0);	//TODO: Poprawic opis
	cin >> phone_number_;
}

bool log_in_system::login_validation(const string& given_login)
{
	char_counter(given_login);
	if (space_counter_ == 0 && special_char_counter_ == 0)
	{
		if (given_login.length() >= 4 && given_login.length() <= 24)
		{
			login_ = given_login;
			return true;
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
				if (lowercase_counter_ >= 1 && uppercase_counter_ >= 1 && number_counter_ >= 1)
				{
					password_ = given_password;
					return true;
				}
			}
		}
	}
	return false;
}

bool log_in_system::add_user_to_database() const
{
	if (create_user_directory(login_))
	{
		if (create_user_files(login_))
		{
			if (save_user_password(login_))
			{
				if (save_user_details(login_))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool log_in_system::create_user_directory(const string& login) const
{
	std::filesystem::create_directory("db\\" + login);
	if (std::filesystem::exists("db\\" + login))
	{
		return true;
	}
	return false;
}

bool log_in_system::create_user_files(const string& login)
{
	ofstream file;
	file.open("db\\" + login + "\\password.txt");
	if (!file.is_open())
	{
		file.close();
		return false;
	}
	file.close();
	file.open("db\\" + login + "\\user_details.txt");
	if (!file.is_open())
	{
		file.close();
		return false;
	}
	file.close();
	return true;
}

bool log_in_system::save_user_password(const string& login) const
{
	ofstream file;
	file.open("db\\" + login + "\\password.txt");
	if (!file.is_open())
	{
		file.close();
		return false;
	}
	file << password_ << "\n";
	file.close();
	return true;
}

bool log_in_system::save_user_details(const string& login) const
{
	ofstream file;
	file.open("db\\" + login + "\\user_details.txt");
	if (!file.is_open())
	{
		file.close();
		return false;
	}
	file << name_ << "\n";
	file << surname_ << "\n";
	file << email_ << "\n";
	file << phone_number_ << "\n";
	file.close();
	return true;
}
