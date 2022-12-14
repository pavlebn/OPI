//E1122876, Pavle Mitrovic

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include "izdelek.h"
#include "temp.h"

using namespace std;
using dataSet = unordered_set<Izdelek, IzdelekHash>;
using dataMap = unordered_map<Izdelek, unsigned int, IzdelekHash>;

int vhod;
int argc;
char** argv;
bool test_mode = false;

void glavniMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

void izpisMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void izpisIzdelkov(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void izpisIzdelkovNula(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void izpisIzdelkovEna(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void izpisKolicine(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

void seznamMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void seznamVpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void seznamVpisNula(string, string, dataSet& izdelki, dataMap& seznam);
void seznamIzpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void seznamBrisanje(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

void tempMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam, Temp& temp);
void helpMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

bool isAlphabetic(const string& s);
void preveriAlpha(string& s);
void refresh(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void inputData(string, dataSet& izdelki);
void inputDataSeznam(string, dataSet& izdelki);
void storeData(dataSet& izdelki, dataMap& data);
void storeDataSeznam(dataSet& izdelki, dataMap& data);


int main(int argc, char** argv) {

	for (int i = 0; i < argc; ++i) {
		if (std::string(argv[i]) == "-t") {
			test_mode = true;
			break;
		}
	}

	dataSet izdelkiRFID;
	dataMap evidenca;
	dataMap seznam;

	glavniMenu(izdelkiRFID, evidenca, seznam);
	return 0;
}


/* GLAVNI MENI */

void glavniMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	refresh(izdelki, evidenca, seznam);
	Temp temp;
	temp.readTemp("temp.txt");

	system("CLS");

	if (test_mode) {
		cout << "Zaslon 1\n";
	}

	cout << "Hladilnik, verzija 2.0 \n"
		"-------------------------------------------------- \n"
		"GLAVNI MENI \n"
		"============ \n"
		"1) izpis informacij o izdelkih v hladilniku na zaslonu \n"
		"2) upravljanje z nakupovalnim seznamom \n"
		"3) nastavitev temperature : \n"
		"4) izpis pomoci na zaslonu : \n"
		"0) Izhod \n";

	cout << "===============================" << endl
		 << "Zamrzovalna glava: " << temp.getTemp(4) << endl
		 << "Predal 1: " << temp.getTemp(1) << endl
		 << "Predal 2: " << temp.getTemp(2) << endl
		 << "Predal 3: " << temp.getTemp(3) << endl
		 << "===============================" << endl;
	while ((std::cout << "Izberi ukaz: ")
		&& !(std::cin >> vhod)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vhod mora biti cifra!\n";
		system("pause");
	}

	switch (vhod) {
	case 0: return;
	case 1: izpisMenu(izdelki, evidenca, seznam); break;
	case 2: seznamMenu(izdelki, evidenca, seznam); break;
	case 3: tempMenu(izdelki, evidenca, seznam, temp); break;
	case 4: helpMenu(izdelki, evidenca, seznam); break;
	default: {
		cout << "Napacen vhod\n";
		system("pause");
		glavniMenu(izdelki, evidenca, seznam); 
	}
	}
}


/* MENI 1 - IZDELKI V HLADILNIKU */

void izpisMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 2\n";
	}
	cout << "============= \n"
		"MENI 1: Izpis informacij o izdelkih v hladilniku na zaslonu\n"
		"=============\n"
		"1)Izpis seznama z izdelki\n"
		"2)Izpis katerih izdelkov je zmanjkalo od zadnjega izpisa informacij o izdelkih\n"
		"3)Izpis kateri izdelek je samo se eden\n"
		"4)Izpis kolicine primerkov izdelka\n"
		"0)Nazaj\n";

	while ((std::cout << "Izberi ukaz: ")
		&& !(std::cin >> vhod)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vhod mora biti cifra!\n";
		system("pause");
		izpisMenu(izdelki, evidenca, seznam);
	}

	switch (vhod) {
	case 0: glavniMenu(izdelki, evidenca, seznam); break;
	case 1: izpisIzdelkov(izdelki, evidenca, seznam); break;
	case 2: izpisIzdelkovNula(izdelki, evidenca, seznam); break;
	case 3: izpisIzdelkovEna(izdelki, evidenca, seznam); break;
	case 4: izpisKolicine(izdelki, evidenca, seznam); break;
	default: {
		cout << "Napacen vhod\n";
		system("pause");
		izpisMenu(izdelki, evidenca, seznam);
	}
	}
}

void izpisIzdelkov(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	refresh(izdelki, evidenca, seznam);
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 3\n";
	}
	cout << "================================ \n"
		 << "Proizvajalec, Izdelek, Kolicina: \n"
		 << "================================ \n";
	for (const auto& it : evidenca) {
		if (it.first.kolicina > 0) {
			cout << it.first.ime_proizvajalca << " "
				<< it.first.ime_izdelka << " "
				<< it.first.kolicina << endl;
		}
	}

	cout << "\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}

void izpisIzdelkovNula(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	refresh(izdelki, evidenca, seznam);
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 4\n";
	}
	cout << "=====================\n"
		<< "Proizvajalec, Izdelek \n"
		<< "======================\n";
	int i = 0;
	for (const auto& it : evidenca) {
		if (!it.first.kolicina) {
			i++;
			cout << i << ". "
				<< it.first.ime_proizvajalca << " "
				<< it.first.ime_izdelka << endl;
		}
	}

	cout << "\n\n";

	while (1) {
		i = 1;
		int kolicina = 0;
		cout << "Ce zelite, vnesite stevilko izdelka ki bi ste dodali na nakupovalni seznam (0 za glavni meni): ";
		cin >> vhod;
		if (vhod ==  0) break;
		for (const auto& it : evidenca) {
			if (!it.first.kolicina) {
				if (i++ == vhod) {
					seznamVpisNula(it.first.ime_izdelka, it.first.ime_proizvajalca, izdelki, seznam);
				}
			}
		}
	}
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}

void izpisIzdelkovEna(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	refresh(izdelki, evidenca, seznam);
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 5\n";
	}
	cout << "=====================\n"
		<< "Proizvajalec, Izdelek \n"
		<< "======================\n";
	int i = 0;
	for (const auto& it : evidenca) {
		if (it.first.kolicina == 1) {
			i++;
			cout << i << ". "
				<< it.first.ime_proizvajalca << " "
				<< it.first.ime_izdelka << endl;
		}
	}

	cout << "\n\n";

	while (1) {
		i = 1;
		int kolicina = 0;
		cout << "Ce zelite, vnesite stevilko izdelka ki bi ste dodali na nakupovalni seznam (0 za glavni meni): ";
		cin >> vhod;
		if (vhod == 0) break;
		for (const auto& it : evidenca) {
			if (it.first.kolicina == 1) {
				if (i++ == vhod) {
					seznamVpisNula(it.first.ime_izdelka, it.first.ime_proizvajalca, izdelki, seznam);
				}
			}
		}
	}
	cout << "\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}

void izpisKolicine(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	refresh(izdelki, evidenca, seznam);
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 6\n";
	}
	Izdelek prebran_izdelek;
	int flag = 0;

	cout << "Vpisite ime izdelka: ";
	cin >> prebran_izdelek.ime_izdelka;
	cout << "Vpisite ime proizvajalca: ";
	cin >> prebran_izdelek.ime_proizvajalca;
	for (const auto& it : evidenca) {
		if (it.first.ime_izdelka == prebran_izdelek.ime_izdelka &&
			it.first.ime_proizvajalca == prebran_izdelek.ime_proizvajalca) {
				cout << "Kolicina zelenega izdelka je " << it.first.kolicina;
				flag = 1;
		}
	}
	if (!flag) cout << "Zelenega izdelka ni.";
	cout << "\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);

}


/* MENU 2 - NAKUPOVALNA LISTA */

void seznamMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 7\n";
	}
	cout << "=============\n"
		"MENI 2: upravljanje z nakupovalnim seznamom\n"
		"=============\n"
		"1) vpis zelenega izdelka na seznam\n"
		"2) izpis nakupovalnega seznama na zaslonu\n"
		"3) brisanje vseh izdelkov sa seznama\n"
		"0) Nazaj\n";

	while ((std::cout << "Izberi ukaz: ")
		&& !(std::cin >> vhod)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vhod mora biti cifra!\n";
		system("pause");
		seznamMenu(izdelki, evidenca, seznam);
	}

	switch (vhod) {
	case 0: glavniMenu(izdelki, evidenca, seznam); break;
	case 1: seznamVpis(izdelki, evidenca, seznam); break;
	case 2: seznamIzpis(izdelki, evidenca, seznam); break;
	case 3: seznamBrisanje(izdelki, evidenca, seznam); break;
	default: {
		cout << "Napacen vhod\n";
		system("pause");
		seznamMenu(izdelki, evidenca, seznam);
	}
	}
}

void seznamVpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 8\n";
	}
	Izdelek prebran_izdelek;

	cout << "Vnesi ime izdelka: ";
	getline(cin >> ws, prebran_izdelek.ime_izdelka);
	preveriAlpha(prebran_izdelek.ime_izdelka);	

	cout << "Vnesi ime proizvajalca: ";
	cin >> prebran_izdelek.ime_proizvajalca;
	preveriAlpha(prebran_izdelek.ime_proizvajalca);
	
	while ((std::cout << "Vnesi kolicino: ")
		&& (!(std::cin >> prebran_izdelek.kolicina) || prebran_izdelek.kolicina < 1)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vhod mora biti cifra vecja od 0!\n";
	}

	std::ofstream outfile;
	remove("nakupovalniseznam.txt");
	outfile.open("nakupovalniseznam.txt", fstream::app);
	if (seznam.count(prebran_izdelek)) {
		seznam.erase(prebran_izdelek);
	}
	izdelki.insert(prebran_izdelek);
	storeDataSeznam(izdelki, seznam);
	for (auto& it : seznam) {
			outfile << it.first.ime_izdelka << ","
				<< it.first.ime_proizvajalca << ","
				<< it.first.kolicina << endl;
	}
	outfile.close();

	cout << "\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}

void seznamVpisNula(string ime_izdelka, string ime_proizvajalca, dataSet& izdelki, dataMap& seznam) {
	Izdelek prebran_izdelek;
	prebran_izdelek.ime_izdelka = ime_izdelka;
	prebran_izdelek.ime_proizvajalca = ime_proizvajalca;
	cout << "Izbrani izdelek: "
		<< ime_izdelka << " "
		<< ime_proizvajalca << endl;
	while ((std::cout << "Vnesi kolicino: ")									//FIX INPUT RESTRICTION
		&& !(std::cin >> prebran_izdelek.kolicina)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Vhod mora biti cifra!\n"
			<< "Vnesi kolicino:";
	}

	std::ofstream outfile;
	remove("nakupovalniseznam.txt");
	outfile.open("nakupovalniseznam.txt", fstream::app);
	izdelki.insert(prebran_izdelek);
	storeDataSeznam(izdelki, seznam);
	for (auto& it : seznam) {
		outfile << it.first.ime_izdelka << ","
			<< it.first.ime_proizvajalca << ","
			<< it.first.kolicina << endl;
	}
	outfile.close();
}

void seznamIzpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	refresh(izdelki, evidenca, seznam);
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 9\n";
	}

	for (const auto& it : seznam) {
		if (it.first.kolicina) {
			cout << it.first.ime_izdelka << " "
				<< it.first.ime_proizvajalca << " "
				<< it.first.kolicina << "\n";
		}

	}

	cout << "\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}

void seznamBrisanje(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 10\n";
	}
	seznam.erase(seznam.begin(), seznam.end());
	remove("nakupovalniseznam.txt");
	std::ofstream("nakupovalniseznam.txt");
	cout << "Seznam obrisan\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}


/* DATA MANAGEMENT */

bool isAlphabetic(const string& s) {
	for (auto c : s) {
		if (!isalpha(c) && !isspace(c)) {
			return false;
		}
	}
	return true;
}

void preveriAlpha(string& s) {
	while (!isAlphabetic(s)) {
		std::cout << "Vhod mora biti tekst! Poskusi se enkrat: \n";
		std::cin >> s;
	}
}

void refresh(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	inputData("RFID.txt", izdelki);
	storeData(izdelki, evidenca);
	inputDataSeznam("nakupovalniseznam.txt", izdelki);
	storeDataSeznam(izdelki, seznam);
}

void inputData(string dataName, dataSet& izdelki) {
	ifstream dataInput(dataName);
	if (!dataInput) {
		cout << "Datoteko nisem mogel odpreti." << endl
			<< "Program se zapira" << endl;
		system("PAUSE");
		exit(0);
	}
	else {
		while (!dataInput.eof()) {
			string strData;
			int intData;
			Izdelek prebran_izdelek;
			getline(dataInput, strData, ',');
			strData.erase(remove_if(strData.begin(), strData.end(), isspace), strData.end());
			prebran_izdelek.ime_proizvajalca = strData;
			getline(dataInput, strData, ',');
			strData.erase(remove_if(strData.begin(), strData.end(), isspace), strData.end());
			prebran_izdelek.ime_izdelka = strData;
			strData.erase(remove_if(strData.begin(), strData.end(), isspace), strData.end());
			getline(dataInput, strData);
			intData = atoi(strData.c_str());
			if (intData < 0 || intData > 9999) {
				cout << "RFID koda je napacna!\n";
			}
			else {
				prebran_izdelek.rfid = intData;

				if (!izdelki.insert(prebran_izdelek).second) {
					auto& key = *izdelki.find(prebran_izdelek);
					key.kolicina++;
				}
				else {
					auto& key = *izdelki.find(prebran_izdelek);
					key.kolicina = 1;
				}
			}
			dataInput >> ws;
		}
		dataInput.close();
	}
}

void inputDataSeznam(string dataName, dataSet& izdelki) {
	ifstream dataInput(dataName);
	if (!dataInput) {
		cout << "Datoteko nisem mogel odpreti." << endl
			<< "Program se zapira" << endl;
		system("PAUSE");
		exit(0);
	}
	else {
		while (!dataInput.eof()) {
			string strData;
			int intData;
			Izdelek prebran_izdelek;
			getline(dataInput, strData, ',');
			strData.erase(remove_if(strData.begin(), strData.end(), isspace), strData.end());
			prebran_izdelek.ime_izdelka = strData;
			getline(dataInput, strData, ',');
			strData.erase(remove_if(strData.begin(), strData.end(), isspace), strData.end());
			prebran_izdelek.ime_proizvajalca = strData;
			getline(dataInput, strData);
			strData.erase(remove_if(strData.begin(), strData.end(), isspace), strData.end());
			intData = atoi(strData.c_str());
			prebran_izdelek.kolicina = intData;
			if (prebran_izdelek.kolicina) {
				izdelki.insert(prebran_izdelek);
			}
			dataInput >> ws;
		}
		dataInput.close();
	}
}

void storeData(dataSet& izdelki, dataMap& data) {
	for (auto& k : data) {
		k.first.kolicina = 0;
	}
	while (!izdelki.empty()) {
		data.emplace(*izdelki.begin(), izdelki.count(*izdelki.begin()));
		auto& keyData = *data.find(*izdelki.begin());
		auto& keyIzdelki = *izdelki.begin();
		keyData.first.kolicina = keyIzdelki.kolicina;
		izdelki.erase(*izdelki.begin());
	}
}

void storeDataSeznam(dataSet& izdelki, dataMap& data) {
	while (!izdelki.empty()) {
		data.emplace(*izdelki.begin(), izdelki.count(*izdelki.begin()));
		auto& keyData = *data.find(*izdelki.begin());
		auto& keyIzdelki = *izdelki.begin();
		keyData.first.kolicina = keyIzdelki.kolicina;
		izdelki.erase(*izdelki.begin());
	}
}

/* TO DO */

void tempMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam, Temp& obj) {
		int predal = 0,
			temp = 0;
		system("CLS");
		if (test_mode) {
			cout << "Zaslon 11\n";
		}
		cout << "=============\n"
			"MENI 3: nastavitev temperature\n"
			"=============\n";
		while ((std::cout << "1 - Prvi predal\n"
						<< "2 - Drugi predal\n"
						<< "3 - Tretji predal\n"
						<< "4 - Glava\n"
						<< "0 - Nazaj na glavni meni\n"
						<< "Izberi predal: ")
			&& (!(std::cin >> predal) || predal < 0 || predal > 4)) {
			system("CLS");
			cout << "Napacen vhod!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (predal == 0) {
			glavniMenu(izdelki, evidenca, seznam);
		}
		else if (predal == 4) {
			while ((std::cout << "Vnesi temperaturo (-25 - 0): ")
				&& (!(std::cin >> temp) || temp < -25 || temp > 0)) {
				system("CLS");
				cout << "Napacen vhod!\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			};
		}
		else {
			while ((std::cout << "Vnesi temperaturo (1 - 20): ")
				&& (!(std::cin >> temp) || temp < 1 || temp > 20)) {
				system("CLS");
				cout << "Napacen vhod!\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	obj.setTemp(predal, temp);
}

void helpMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	if (test_mode) {
		cout << "Zaslon 12\n";
	}
	cout << "V glavnem meniju lahko izberemo zelene funkcije\n"
		<< "in preberemo temperature predal v hladilniku\n"
		<< "\nCe zelimo prebrati seznam izdelkov v hladilniku, izberemo meni 1\n"
		<< "Ce zelimo upravljati nakupovalni seznam, izberemo meni 2\n"
		<< "Ce zelimo upravljati temperaturo predal, izberemo meni 3\n"
		<< "Meni 4 odpre pomoc\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}
