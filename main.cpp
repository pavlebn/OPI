//E1122876, Pavle Mitrovic

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "izdelek.h"
#include "temp.h"

using namespace std;
using dataSet = unordered_set<Izdelek, IzdelekHash>;
using dataMap = unordered_map<Izdelek, unsigned int, IzdelekHash>;

char vhod;
void glavniMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

void izpisMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void izpisIzdelkov(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

void seznamMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void seznamVpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void seznamIzpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);
void seznamBrisanje(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

void tempMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam, Temp& temp);
void helpMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam);

void inputData(string, dataSet& izdelki);
void storeData(dataSet& izdelki, dataMap& data);

int main() {
	dataSet izdelkiRFID;
	dataMap evidenca;
	dataMap seznam;
	
	inputData("izdelki.csv", izdelkiRFID);
	storeData(izdelkiRFID, evidenca);
	inputData("nakupovalniseznam.csv", izdelkiRFID);
	storeData(izdelkiRFID, seznam);
	glavniMenu(izdelkiRFID, evidenca, seznam);
}


/* GLAVNI MENI */

void glavniMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	Temp temp;
	temp.readTemp("temp.csv");

	system("CLS");
	cout << "Hladilnik, verzija 0.1 \n"
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
	cin >> vhod;

	switch (vhod) {
	case '0': system("pause"); break;
	case '1': izpisMenu(izdelki, evidenca, seznam); break;
	case '2': seznamMenu(izdelki, evidenca, seznam); break;
	case '3': tempMenu(izdelki, evidenca, seznam, temp); break;
	case '4': helpMenu(izdelki, evidenca, seznam); break;
	default: {
		std::cout << "Error! \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("pause");
		glavniMenu(izdelki, evidenca, seznam);
	}
	}
}


/* MENI 1 - IZDELKI V HLADILNIKU */

void izpisMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	cout << "============= \n"
		"MENI 1: Izpis informacij o izdelkih v hladilniku na zaslonu\n"
		"=============\n"
		"1)Izpis seznama z izdelki\n"
		"2)Izpis katerih izdelkov je zmanjkalo od zadnjega izpisa informacij o izdelkih\n"
		"3)Izpis kateri izdelek je samo se eden\n"
		"4)Izpis kolicine primerkov izdelka\n"
		"0)Nazaj\n";

	cin >> vhod;

	switch (vhod) {
	case '0': glavniMenu(izdelki, evidenca, seznam); break;
	case '1': izpisIzdelkov(izdelki, evidenca, seznam); break;
	case '2': ; break;
	case '3': ; break;
	case '4': ; break;
	default: cout << "Error! \n";
	}
}

void izpisIzdelkov(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	cout << "================================ \n"
		 << "Proizvajalec, Izdelek, Kolicina: \n"
		 << "================================ \n";
	for (const auto& it : evidenca) {
		cout << it.first.ime_proizvajalca << " "
			<< it.first.ime_izdelka << " "
			<< it.first.kolicina << endl;
	}
	cout << "\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}


/* MENU 2 - NAKUPOVALNA LISTA */

void seznamMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	cout << "=============\n"
		"MENI 2: upravljanje z nakupovalnim seznamom\n"
		"=============\n"
		"1) vpis zelenega izdelka na seznam\n"
		"2) izpis nakupovalnega seznama na zaslonu\n"
		"3) brisanje vseh izdelkov sa seznama\n"
		"0) Nazaj\n";

	cin >> vhod;

	switch (vhod) {
	case '0': glavniMenu(izdelki, evidenca, seznam); break;
	case '1': seznamVpis(izdelki, evidenca, seznam); break;
	case '2': seznamIzpis(izdelki, evidenca, seznam); break;
	case '3': seznamBrisanje(izdelki, evidenca, seznam); break;
	default: {
		std::cout << "Error! \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("pause");
		seznamMenu(izdelki, evidenca, seznam);
	}
	}
}

void seznamVpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	Izdelek prebran_izdelek;

	cout << "Vnesi ime izdelka: ";
	cin >> prebran_izdelek.ime_izdelka;
	cout << "Vnesi ime proizvajalca: ";
	cin >> prebran_izdelek.ime_proizvajalca;
	while ((std::cout << "Vnesi kolicino: ")									//FIX INPUT RESTRICTION
		&& !(std::cin >> prebran_izdelek.kolicina)) {
			system("CLS");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Vhod mora biti cifra!\n"
				<< "Vnesi kolicino:";
	}

	std::ofstream outfile;
	outfile.open("nakupovalniseznam.csv", fstream::app);
	outfile << prebran_izdelek.ime_izdelka << ","
			<< prebran_izdelek.ime_proizvajalca << ","
			<< prebran_izdelek.kolicina << endl;
	outfile.close();

	izdelki.insert(prebran_izdelek);
	storeData(izdelki, seznam);

	cout << "\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}

void seznamIzpis(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");

	for (const auto& it : seznam) {
		cout << it.first.ime_izdelka << " "
			<< it.first.ime_proizvajalca << " "
			<< it.first.kolicina << "\n";
	}

	cout << "\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}

void seznamBrisanje(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	seznam.erase(seznam.begin(), seznam.end());
	remove("nakupovalniseznam.csv");
	std::ofstream("nakupovalniseznam.csv");
	cout << "Seznam obrisan\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}


/* DATA MANAGEMENT */

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
			prebran_izdelek.ime_proizvajalca = strData;
			getline(dataInput, strData, ',');
			prebran_izdelek.ime_izdelka = strData;
			getline(dataInput, strData);
			intData = atoi(strData.c_str());
			prebran_izdelek.kolicina = intData;			
			dataInput >> ws;
			izdelki.insert(prebran_izdelek);
		}
		dataInput.close();
	}
}

void storeData(dataSet& izdelki, dataMap& data) {
	while (!izdelki.empty()) {
		data.emplace(*izdelki.begin(), izdelki.count(*izdelki.begin()));
		izdelki.erase(*izdelki.begin());
	}
}

/* TO DO */

void tempMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam, Temp& obj) {
		int predal = 0,
			temp = 0;
		system("CLS");
		cout << "=============\n"
			"MENI 3: nastavitev temperature\n"
			"=============\n";
		while ((std::cout << "Izberi predal (4 - Glava):")									//FIX INPUT RESTRICTION
			&& (!(std::cin >> predal) || predal < 1 || predal > 4)) {
			system("CLS");
			cout << "Napacen vhod\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		if (predal == 4) {
			while ((std::cout << "Vnesi temperaturo (-25 - 0): ")							//FIX INPUT RESTRICTION
				&& (!(std::cin >> temp) || temp < -25 || temp > 0)) {
				system("CLS");
				cout << "Napacen vhod\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			};
		}
		else {
			while ((std::cout << "Vnesi temperaturo (1 - 20): ")							//FIX INPUT RESTRICTION
				&& (!(std::cin >> temp) || temp < 1 || temp > 20)) {
				system("CLS");
				cout << "Napacen vhod\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	obj.setTemp(predal, temp);
	glavniMenu(izdelki, evidenca, seznam);
}

void helpMenu(dataSet& izdelki, dataMap& evidenca, dataMap& seznam) {
	system("CLS");
	cout << "V glavnem meniju lahko izberemo zelene funkcije\n"
		<< "in preberemo temperature predal v hladilniku\n"
		<< "\nCe zelimo prebrati seznam izdelkov v hladilniku, izberemo meni 1\n"
		<< "Ce zelimo upravljati nakupovalni seznam, izberemo meni 2\n"
		<< "Ce zelimo upravljati temperaturo predal, izberemo meni 3\n"
		<< "Meni 4 odpre pomoc\n\n";
	system("PAUSE");
	glavniMenu(izdelki, evidenca, seznam);
}
