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
	if (!search_login_on_list(given_login_) && login_validation(given_login_))
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
	show_message("Login length from 4 to 16 characters.\nLogin cannot contain spaces.\n", 0);
	cin >> given_login_;
}

void log_in_system::set_password()
{
	const string message = "Password length from 4 to 24 characters.\nPassword must include 1 lowercase, 1 uppercase, 1 number and 1 special character.\nPassword cannot contain spaces.\n";
	show_message(message, 0);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	cin.ignore();
	getline(cin, given_password_);
	show_message(message, 0);
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	getline(cin, given_repeat_password_);
}

void log_in_system::set_user_details()	//TODO: Add user details validation and add message!
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
		if (given_login.length() >= 4 && given_login.length() <= 16)
		{
			login_ = given_login;
			return true;
		}
	}
	show_message("Login format is incorrect.\n Try again!\n", 0);
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
	show_message("Password format is incorrect.\n Try again!\n", 0);
	return false;
}

bool log_in_system::add_user_to_database()
{
	if (create_user_directory(login_))
	{
		if (save_user_details(login_))
		{
			add_to_login_list(login_);
			return true;
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
	add_log("ERROR: Creating user folder.\n");
	return false;
}

bool log_in_system::save_user_details(const string& login) const
{
	ofstream file;

	file.open("db\\" + login + "\\password.txt");
	if (!file.is_open())
	{
		file.close();
		add_log("ERROR: Password saving.\n");
		return false;
	}
	file << password_ << "\n";
	file.close();

	file.open("db\\" + login + "\\user_details.txt");
	if (!file.is_open())
	{
		file.close();
		add_log("ERROR: User details saving.\n");
		return false;
	}
	file << name_ << "\n";
	file << surname_ << "\n";
	file << email_ << "\n";
	file << phone_number_ << "\n";
	file.close();

	return true;
}

void log_in_system::add_to_login_list(const string& login)
{
	login_list_.push_back(login);
	update_login_list();
}
