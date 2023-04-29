#pragma once

#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;

class log_in_system
{
	public:

		bool log_in();
		bool sign_in();

	private:

		string login_, password_;
		std::vector<string> login_list_;
		string given_login_, given_password_, given_repeat_password_;
		string name_, surname_, email_, phone_number_;
		int lowercase_counter_ = 0, uppercase_counter_ = 0, space_counter_ = 0, special_char_counter_ = 0, number_counter_ = 0;

		void enter_login();
		void enter_password();
		void download_login_list();
		bool search_login_on_list(const string& give_login);
		bool download_password(const string& login);
		void delete_user_from_login_list(const string& login);
		void update_login_list() const;
		bool check_password(const string& given_password) const;

		void set_login();
		void set_password();
		void set_user_details();
		bool login_validation(const string& given_login);
		void char_counter(const string& string_data);
		bool password_validation(const string& given_password, const string& given_repeat_password);
		bool add_user_to_database() const;
		bool create_user_directory(const string& login) const;
		bool save_user_details(const string& login) const;
		
		void is_first_start_up() const;
		static void show_message(const string& message, const int wait);
		static void add_log(const string& message);

};
