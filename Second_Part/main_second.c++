#include <iostream>
#include <string>
#include <iomanip>
#include "Bank_second.h"
#include "VariadicTable.h" // for pretty table output

using namespace std;

void outputMenu();
// checks the correctness of the chosen position of
// the bank in banks list:
bool getPosition(Banks& banks, string& code, size_t& position);
int resize(string*& array, Bank& bank, size_t oldLength, size_t newLength);
int resize(Bank*& array, Banks& banks, size_t oldLength, size_t newLength);
// fills the main bank parameters:
Bank inputBank(Bank& bank);
Bank inputBankServices(Bank& bank);
void removeBank(Banks& banks, int chosenIndex);
// checks the existence of required bank parameters:
bool isInList(Bank& bank, string key);
// forms the list of appropriate banks:
void formBanksList(Banks& banks, Banks& chosenBanks);
void outputBanks(Banks& banks);

void outputMenu() {

	cout << "Practical task num. 4 IKBO-03-21 Nasevich V.V.\n"
		"Variant num. 19.\n\nMenu:\n"
		"1)Enter '1' to fill in details of the new bank.\n"
		"2)Enter '2' to fill in the data of the services provided "
		"by the selected bank.\n"
		"3)Enter '3' to delete an information about the selected bank.\n"
		"4)Enter '4' to get a list of state-owned banks "
		"providing mortgage loans.\n"
		"5)Enter '0' to close the programm.\n";
}

bool getPosition(Banks& banks, string& code, size_t& index) {

	for (size_t i = 0; i < banks.listLength; i++) {

		if (banks.list[i].code == code) {

			index = i;
			return true;
		}
	}

	return false;
}

int resize(string*& array, Bank& bank, size_t oldLength, size_t newLength) {

	string* resizedArray = new string[newLength];

	if (oldLength < newLength) {

		for (int i = 0; i < oldLength; i++) {

			resizedArray[i] = array[i];
		}
	}

	else {

		for (int i = 0; i < newLength; i++) {

			resizedArray[i] = array[i];
		}
	}

	bank.servicesListLength = newLength;
	delete[] array;
	array = resizedArray;

	return 1;
}

int resize(Bank*& array, Banks& banks, size_t oldLength, size_t newLength) {

	Bank* resizedArray = new Bank[newLength];

	if (oldLength < newLength) {

		for (int i = 0; i < oldLength; i++) {

			resizedArray[i] = array[i];
		}
	}

	else {

		for (int i = 0; i < newLength; i++) {

			resizedArray[i] = array[i];
		}
	}

	banks.listLength = newLength;
	delete[] array;
	array = resizedArray;

	return 1;
}

Bank inputBank(Bank &bank) {

	cout << "\nEnter the name of the bank:\n";
	getline(cin, bank.name);

	cout << "\nEnter the code of the bank:\n";
	getline(cin, bank.code);

	cout << "\nEnter the address of the bank:\n";
	getline(cin, bank.address);

	cout << "\nEnter the type of the bank:\n";
	getline(cin, bank.type);

	return bank;
}

Bank inputBankServices(Bank &bank) {

	string tempService = "Begin";
	getline(cin, tempService);

	while (tempService.find('0') == string::npos && tempService.length() != 1) {

		// input continues until input zero
		resize(bank.servicesList, bank, bank.servicesListLength, bank.servicesListLength + 1);
		bank.servicesList[bank.servicesListLength - 1] = tempService;

		getline(cin, tempService);
	}

	return bank;
}

void removeBank(Banks& banks, int chosenIndex) {

	for (size_t i = chosenIndex; i < banks.listLength - 1; i++) {

		// shift to the left side by one element is equal to removal:
		banks.list[i] = banks.list[i + 1];
	}

	// reducing the real length of the list:
	resize(banks.list, banks, banks.listLength, banks.listLength - 1);
}

bool isInList(Bank& bank, string key) {

	for (size_t i = 0; i < bank.servicesListLength; i++) {

		if (bank.servicesList[i] == key) { return true; }
	}

	return false;
}

void formBanksList(Banks& banks, Banks& chosenBanks) {

	for (size_t i = 0; i < banks.listLength; i++) {

		if (banks.list[i].type == "State") {

			if (isInList(banks.list[i], "Granting a mortgage loan")) {

				resize(chosenBanks.list, chosenBanks, 
					chosenBanks.listLength, chosenBanks.listLength + 1);
				chosenBanks.list[chosenBanks.listLength - 1] = banks.list[i];
			}
		}
	}
}

void outputBanks(Banks& banks) {

	// creating an object of VariabicTable class 
	// with table header parameters:
	VariadicTable<string, string, string, string, string> table({ "Name",
		"Code",
		"Address",
		"Type of ownership",
		"List of provided services"
		});

	for (size_t i = 0; i < banks.listLength; i++) {

		Bank currentBank = banks.list[i];

		if (!currentBank.servicesListLength) {

			// if there is no entered services for current bank:
			table.addRow(currentBank.name,
				currentBank.code,
				currentBank.address,
				currentBank.type, "");
		}

		else {

			for (size_t j = 0; j < currentBank.servicesListLength; j++) {

				if (!j) {

					// on the first entry all prarmeters are displayed:
					table.addRow(currentBank.name,
						currentBank.code,
						currentBank.address,
						currentBank.type,
						currentBank.servicesList[j]);
				}

				else {

					// on the second and futher entries 
					// only services are displayed
					table.addRow("", "", "", "", currentBank.servicesList[j]);
				}
			}
		}
	}

	table.print(std::cout);
}

int main() {

	outputMenu();

	// creating the main object (all banks list):
	Banks banks;
	/*Banks* banks = &bk;*/

	cout << "\nYour choise is:\n";
	int chosenTask;

	cin >> chosenTask;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (chosenTask) {

		switch (chosenTask) {

		case 1: {

			resize(banks.list, banks, banks.listLength, banks.listLength + 1);

			banks.list[banks.listLength - 1] =
				inputBank(banks.list[banks.listLength - 1]);

			break;
		}

		case 2: {

			if (!banks.listLength) {

				cerr << "\nBanks list isn't filled. Try again.\n";
				break;
			}

			string chosenCode;
			cout << "\nChose the code of the bank, which services you "
				"would like to enter:\n";

			getline(cin, chosenCode);

			size_t chosenIndex = -1;

			if (!getPosition(banks, chosenCode, chosenIndex)) {

				cerr << "\nIncorrect code. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}

			cout << "\nEnter services provided by chosen "
				"bank (without separators):\n";
			banks.list[chosenIndex] = 
				inputBankServices(banks.list[chosenIndex]);
			break;
		}

		case 3: {

			if (!banks.listLength) {

				cerr << "\nBanks list isn't filled. Try again.\n";
				break;
			}

			string chosenCode;
			cout << "\nChose the code of the bank, which you "
				"would like to delete:\n";

			getline(cin, chosenCode);

			size_t chosenIndex = -1;

			if (!getPosition(banks, chosenCode, chosenIndex)) {

				cerr << "\nIncorrect code. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}

			removeBank(banks, chosenIndex);
			break;
		}

		case 4: {

			Banks chosenBanks;

			formBanksList(banks, chosenBanks);
			if (!chosenBanks.listLength) {

				cerr << "\nThere are no banks in the "
					"list that meet the condition.\n"
					"Enter the data about other banks and try again.\n";
				break;
			}

			outputBanks(chosenBanks);
			break;
		}

		default:

			cerr << "\nIncorrect task number. Try again.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}

		cout << endl;
		system("pause");
		system("cls");

		outputMenu();

		if (banks.listLength) {

			cout << "\nCurrent list is:\n";
			outputBanks(banks);
		}

		cout << "\nYour next choise is:\n";
		cin >> chosenTask;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return 0;
}