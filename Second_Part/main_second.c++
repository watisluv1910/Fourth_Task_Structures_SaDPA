#include <iostream>
#include <string>
#include <iomanip>
#include "Bank_second.h"
#include "VariadicTable.h" // for pretty table output

using namespace std;

void outputMenu();
// checks the correctness of the chosen position of
// the bank in banks list:
bool isCorrectPosition(int position, int maxPosition);
int resize(string*& array, size_t oldLength, size_t newLength);
int resize(Banks*& array, size_t oldLength, size_t newLength);
// fills the main bank parameters:
Bank inputBank(Bank bank);
Bank inputBankServices(Bank bank);
void removeBank(Banks& banks, int chosenIndex);
// checks the existence of required bank parameters:
bool isInArray(Bank& bank, string key);
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

bool isCorrectPosition(int position, int maxPosition) {

	return (0 < position && position <= maxPosition) ? true : false;
}

int resize(string*& array, size_t oldLength, size_t newLength) {

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

	delete[] array;
	array = resizedArray;

	return 1;
}

int resize(Banks*& array, size_t oldLength, size_t newLength) {

	Banks* resizedArray = new Banks[newLength];

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

	delete[] array;
	array = resizedArray;

	return 1;
}

Bank inputBank(Banks& banks) {

	resize(banks, banks.listLength, banks.listLength + 1);

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

Bank inputBankServices(Bank bank) {

	string tempService = "Begin";
	getline(cin, tempService);

	while (tempService.find('0') == string::npos && tempService.length() != 1) {

		// input continues until input zero
		bank.servicesList[bank.servicesListLength] = tempService;
		bank.servicesListLength++;

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
	resize(banks.list, banks.listLength, banks.listLength - 1);
	banks.listLength--;
}

bool isInArray(Bank& bank, string key) {

	for (size_t i = 0; i < bank.servicesListLength; i++) {

		if (bank.servicesList[i] == key) { return true; }
	}

	return false;
}

void formBanksList(Banks& banks, Banks& chosenBanks) {

	for (size_t i = 0; i < banks.listLength; i++) {

		if (banks.list[i].type == "State") {

			if (isInArray(banks.list[i], "Granting a mortgage loan")) {

				chosenBanks.list[chosenBanks.listLength] = banks.list[i];
				chosenBanks.listLength++;
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

	cout << "\nYour choise is:\n";
	int chosenTask;

	cin >> chosenTask;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (chosenTask) {

		switch (chosenTask) {

		case 1: {

			banks.list[banks.listLength] =
				inputBank(banks.list[banks.listLength]);
			banks.listLength++;
			break;
		}

		case 2: {

			if (!banks.listLength) {

				cerr << "\nBanks list isn't filled. Try again.\n";
				break;
			}

			int chosenPosition = 0;
			cout << "\nChose the position of the bank, which services you "
				"would like to enter (from 1 to " << banks.listLength << "):\n";

			cin >> chosenPosition;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (!isCorrectPosition(chosenPosition, banks.listLength)) {

				cerr << "\nIncorrect position. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}

			chosenPosition--; // position turns into index

			cout << "\nEnter services provided by chosen "
				"bank (without separators):\n";
			banks.list[chosenPosition] =
				inputBankServices(banks.list[chosenPosition]);
			break;
		}

		case 3: {

			if (!banks.listLength) {

				cerr << "\nBanks list isn't filled. Try again.\n";
				break;
			}

			int chosenPosition = 0;
			cout << "\nChose the position of the bank, which you "
				"would like to delete (from 1 to " << banks.listLength << "):\n";

			cin >> chosenPosition;

			if (!isCorrectPosition(chosenPosition, banks.listLength)) {

				cerr << "\nIncorrect position. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}

			chosenPosition--; // position turns into index

			removeBank(banks, chosenPosition);
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