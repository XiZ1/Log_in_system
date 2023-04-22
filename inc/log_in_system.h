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
		string given_login_, given_password_;

		void clear_input();
		void enter_login();
		void enter_password();
		bool download_login_list();
		bool search_login_on_list(const string& give_login);
		bool download_password(const string& login);
		bool check_password(const string& given_password) const;

		static void show_message(const string& message, const int wait);

};
