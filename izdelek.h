//E1122876, Pavle Mitrovic

#pragma once

struct Izdelek {
	std::string ime_proizvajalca;
	std::string ime_izdelka;
	int kolicina = 0;

	bool operator==(const Izdelek& other) const;
	
};

struct IzdelekHash {
	std::size_t operator()(const Izdelek& k) const;
};
