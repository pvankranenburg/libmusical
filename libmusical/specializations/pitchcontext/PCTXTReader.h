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


#ifndef PCTXTREADER_H_
#define PCTXTREADER_H_

#include <vector>
#include "Sequence.h"
#include <string>

namespace musical {

/**
 * Generates a sequence of PCSymbol symbols from a vector of strings
 */
class PCTXTReader {
public:
	/**
	 * Constructor
	 */
	PCTXTReader() : inputfilename(""), source(vector<std::string>()) { };

	/**
	 * Constructor
	 */
	PCTXTReader(std::string inputfilename) : inputfilename(inputfilename), source(source_init(inputfilename)) { }

	/**
	 * Destructor
	 */
	~PCTXTReader();

	/**
	 * Generate the sequence.
	 */
	Sequence* generateSequence() const;

	const std::vector<string> source;
	const std::string inputfilename;

	/**
	 * Vector initializer
	*/
	static std::vector<std::string> source_init(std::string filename);

};

}

#endif /* PCTXTREADER_H_ */
