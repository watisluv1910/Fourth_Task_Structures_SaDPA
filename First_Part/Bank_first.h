#pragma once
#include <string>
#define maxArrayLength 100

using namespace std;

struct Bank {

	string name, code, address, type;

	string servicesList[maxArrayLength] = {};

	size_t servicesListLength = 0;
};

struct Banks {

	Bank list[maxArrayLength] = {};

	size_t listLength = 0;
};