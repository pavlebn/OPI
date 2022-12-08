//E1122876, Pavle Mitrovic

#pragma once

struct Temp {
	int temp1,
		temp2,
		temp3,
		tempGlava;

	void readTemp(std::string);

	const int getTemp (int);
	void setTemp(int, int);

};