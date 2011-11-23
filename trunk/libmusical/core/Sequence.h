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


#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <vector>
#include <string>

#include "Symbol.h"

namespace musical {

/**
 * Sequence of Symbols
 */
class Sequence {
public:
	/**
	 * Constructor
	 */
	Sequence();

	/**
	 * Destructor
	 */
	virtual ~Sequence();

	/**
	 * Get symbol at index ix
	 */
	Symbol* getSymbolAt(int ix) { return symbols[ix]; }

	/**
	 * Add a symbol
	 */
	void addSymbol(Symbol * s) { symbols.push_back(s); }

	/**
	 * Get number of symbols
	 */
	unsigned int size() const { return symbols.size(); }

	/**
	 * Write the contents of the sequence to stdout.
	 */
	void dump_stdout();

	/**
	 * Returns the name of the sequence.
	 */
	std::string getName() { return name; }

	/**
	 * set the name
	 */
	void setName(std::string n) { name = n; }



protected:
	std::vector<Symbol*> symbols;

	std::string name;

	std::string json_string;
};

}

#endif /* SEQUENCE_H_ */
