#include <iostream>
#include <string>
#include <iomanip>
#include "Bank_third.h"
#include "VariadicTable.h" // for pretty table output

using namespace std;

void outputMenu();
// checks the correctness of the chosen position of
// the bank in banks list:
bool getPosition(Banks& banks, string& code, size_t& position);
// fills the main bank parameters:
void inputBank(Bank& bank);
void inputBankServices(Bank& bank);
void removeBank(Banks& banks, int chosenIndex);
// checks the existence of required bank parameters:
bool isInList(vector<string> servicesList, string key);
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

	for (size_t i = 0; i < banks.list.size(); i++) {

		if (banks.list.at(i).code == code) {

			index = i;
			return true;
		}
	}

	return false;
}

void inputBank(Bank& bank) {

	cout << "\nEnter the name of the bank:\n";
	getline(cin, bank.name);

	cout << "\nEnter the code of the bank:\n";
	getline(cin, bank.code);

	cout << "\nEnter the address of the bank:\n";
	getline(cin, bank.address);

	cout << "\nEnter the type of the bank:\n";
	getline(cin, bank.type);
}

void inputBankServices(Bank& bank) {

	string tempService = "Begin";
	getline(cin, tempService);

	while (tempService.find('0') == string::npos && tempService.length() != 1) {

		// input continues until input zero
		bank.servicesList.push_back(tempService);

		getline(cin, tempService);
	}
}

bool isInList(vector<string> servicesList, string key) {

	for (auto& service : servicesList) {

		if (service == key) { return true; }
	}

	return false;
}

void formBanksList(Banks& banks, Banks& chosenBanks) {

	for (size_t i = 0; i < banks.list.size(); i++) {

		if (banks.list.at(i).type == "State") {

			if (isInList(banks.list.at(i).servicesList, "Granting a mortgage loan")) {

				chosenBanks.list.resize(chosenBanks.list.size() + 1);
				chosenBanks.list.at(chosenBanks.list.size() - 1) = banks.list.at(i);
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

	for (size_t i = 0; i < banks.list.size(); i++) {

		Bank currentBank = banks.list.at(i);

		if (!currentBank.servicesList.size()) {

			// if there is no entered services for current bank:
			table.addRow(currentBank.name,
				currentBank.code,
				currentBank.address,
				currentBank.type, "");
		}

		else {

			for (size_t j = 0; j < currentBank.servicesList.size(); j++) {

				if (!j) {

					// on the first entry all prarmeters are displayed:
					table.addRow(currentBank.name,
						currentBank.code,
						currentBank.address,
						currentBank.type,
						currentBank.servicesList.at(j));
				}

				else {

					// on the second and futher entries 
					// only services are displayed
					table.addRow("", "", "", "", currentBank.servicesList.at(j));
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

			banks.list.resize(banks.list.size() + 1);
			inputBank(banks.list.at(banks.list.size() - 1));
			break;
		}

		case 2: {

			if (banks.list.empty()) {

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
			inputBankServices(banks.list[chosenIndex]);
			break;
		}

		case 3: {

			if (banks.list.empty()) {

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

			banks.list.erase(banks.list.begin() + chosenIndex);
			break;
		}

		case 4: {

			Banks chosenBanks;

			formBanksList(banks, chosenBanks);
			if (chosenBanks.list.empty()) {

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

		if (!banks.list.empty()) {

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