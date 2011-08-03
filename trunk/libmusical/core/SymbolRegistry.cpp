/*
Author: Peter van Kranenburg (peter.van.kranenburg@meertens.knaw.nl)
Copyright 2011 Meertens Institute (KNAW)

This file is part of libmusical.

libmusical is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libmusical is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libmusical.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "SymbolRegistry.h"

namespace musical {

SymbolRegistry::SymbolRegistry() {
	// TODO Auto-generated constructor stub

}

SymbolRegistry::~SymbolRegistry() {
	// TODO Auto-generated destructor stub
}

string SymbolRegistry::toString() {
	//iterate over all name/value pairs
	map<std::string,float>::const_iterator fl_iterator = floats.begin();
	map<std::string,int>::const_iterator int_iterator = ints.begin();
	map<std::string,std::string>::const_iterator str_iterator = strings.begin();
	map<std::string,bool>::const_iterator bool_iterator = bools.begin();

	string result = "";

	while (int_iterator != ints.end()) {
		stringstream ss;
		ss << (*int_iterator).first << " : " << (*int_iterator).second << " | ";
		result += ss.str();
		int_iterator++;
	}
	while (fl_iterator != floats.end()) {
		stringstream ss;
		ss << (*fl_iterator).first << " : " << (*fl_iterator).second << " | ";
		result += ss.str();
		fl_iterator++;
	}
	while (bool_iterator != bools.end()) {
		stringstream ss;
		ss << (*bool_iterator).first << " : " << (*bool_iterator).second << " | ";
		result += ss.str();
		bool_iterator++;
	}
	while (str_iterator != strings.end()) {
		stringstream ss;
		ss << (*str_iterator).first << " : " << (*str_iterator).second << " | ";
		result += ss.str();
		str_iterator++;
	}

	return result;
}

}
