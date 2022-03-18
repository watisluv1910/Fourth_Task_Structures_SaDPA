#pragma once
#include <string>

using namespace std;

struct Bank {

	string name, code, address, type;

	string* servicesList = new string[];

	size_t servicesListLength = 0;
};

struct Banks {

	Bank* list = new Bank[];

	size_t listLength = 0;
};