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


#ifndef JSONFILESOURCE_H_
#define JSONFILESOURCE_H_

#include "JSONSource.h"

namespace musical {

/**
 * Class for getting a JSON string from a file.
 */
class JSONFileSource: public musical::JSONSource {
public:
	/**
	 * Constructor
	 */
	JSONFileSource() : filename("") {};

	/**
	 * Constructor
	 * fn: filename of the JSON file that has to be read
	 */
	JSONFileSource(std::string fn) : filename(fn) {};

	/**
	 * Destructor
	 */
	virtual ~JSONFileSource();

	/**
	 * Returns the JSON string from the file with name ::filename as a single string without newlines.
	 */
	std::string getJSONString();

private:
	const std::string filename;
};

}

#endif /* JSONFILESOURCE_H_ */
