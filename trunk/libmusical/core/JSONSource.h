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


#ifndef JSONSOURCE_H_
#define JSONSOURCE_H_

#include <string>

namespace musical {

/**
 * Gets a JSON string from a source. Abstract class.
 */
class JSONSource {
public:
	JSONSource();
	virtual ~JSONSource();

	/**
	 * Returns the JSON string.
	 */
	virtual std::string getJSONString() = 0;
};

}

#endif /* JSONSOURCE_H_ */
