#pragma once

#include <iostream>

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

		void enter_login();
		void enter_password();
		bool check_login(const string& login);
		bool check_password(const string& login);

};
