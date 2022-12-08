//E1122876, Pavle Mitrovic

#include <string>
#include <fstream>
#include <iostream>
#include "temp.h"

struct Temp;

const int Temp::getTemp(int x) {
	if (x == 1) {
		return temp1;
	}
	if (x == 2) {
		return temp2;
	}
	if (x == 3) {
		return temp3;
	}
	if (x == 4) {
		return tempGlava;
	}
	return 0;
}

void Temp::readTemp(std::string dataName) {
	std::ifstream dataInput(dataName);
	if (!dataInput) {
		std::cout << "Datoteke RFID nisem mogel odpreti.\n"
			<< "Program se zapira\n";
		system("PAUSE");
	}
	else {
		while (!dataInput.eof()) {
			std::string strData;
			int intData;
			getline(dataInput, strData, ',');
			intData = atoi(strData.c_str());
			temp1 = intData;
			getline(dataInput, strData, ',');
			intData = atoi(strData.c_str());
			temp2 = intData;
			getline(dataInput, strData, ',');
			intData = atoi(strData.c_str());
			temp3 = intData;
			getline(dataInput, strData);
			intData = atoi(strData.c_str());
			tempGlava = intData;
			dataInput >> std::ws;
		}
		dataInput.close();
	}
}

void Temp::setTemp(int predal, int temp) {
	if (predal == 1) temp1 = temp;
	if (predal == 2) temp2 = temp;
	if (predal == 3) temp3 = temp;
	if (predal == 4) tempGlava = temp;
	remove("temp.csv");
	std::ofstream outfile ("temp.csv");
	outfile << temp1 << ","
			<< temp2 << ","
			<< temp3 << ","
			<< tempGlava << std::endl;
}
