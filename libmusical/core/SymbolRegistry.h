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


#ifndef SYMBOLREGISTRY_H_
#define SYMBOLREGISTRY_H_

#include <map>
#include <string>

#include "Symbol.h"

namespace musical {

/**
 * Symbol which allows for dynamically addition of attributes.
 * The attributes are in a key-value map.
 */
class SymbolRegistry: public musical::Symbol {
public:
	/**
	 * Constructor
	 */
	SymbolRegistry();

	/**
	 * Destructor
	 */
	virtual ~SymbolRegistry();

	/**
	 * Returns a string representation of the symbol.
	 */
	std::string toString() const;

	/**
	 * Returns the floating point value of a float attribute with key "key".
	 */
	float getFloat(const std::string key) { return floats[key]; } //why can't this be const?

	/**
	 * Add a floating point value with key "key"
	 */
	void addFloat(const std::string key, const float v ) { floats[key] = v; }

	/**
	 * Returns the integer value of an int attribute with key "key"
	 */
	int   getInt  (std::string key) { return ints[key]; }

	/**
	 * Add an int
	 */
	void addInt(const std::string key, const int i) { ints[key] = i; }

	/**
	 * Returns the bool value of a bool attribute with key "key"
	 */
	bool  getBool (const std::string key) { return bools[key]; }

	/**
	 * Adds a bool
	 */
	void addBool(const std::string key, const bool b) { bools[key] = b; }

	/**
	 * Returns the string value of a string attribute with key "key"
	 */
	std::string getString(const std::string key) { return strings[key]; }

	/**
	 * Adds a string
	 */
	void addString(const std::string key, const std::string s) { strings[key] = s; }

public:
	std::map<std::string,float> floats;
	std::map<std::string,int> ints;
	std::map<std::string,std::string> strings;
	std::map<std::string,bool> bools;
};

}

#endif /* SYMBOLREGISTRY_H_ */
