//E1122876, Pavle Mitrovic

#include <string>
#include "izdelek.h"

bool Izdelek::operator==(const Izdelek& other) const
{
	return ((ime_proizvajalca == other.ime_proizvajalca)
		&& (ime_izdelka == other.ime_izdelka));
}

std::size_t IzdelekHash::operator()(const Izdelek& k) const {
	return std::hash<std::string>()(k.ime_proizvajalca) ^
		(std::hash<std::string>()(k.ime_izdelka) << 1);
}
