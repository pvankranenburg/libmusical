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


#ifndef OPTIJSONREADER_H_
#define OPTIJSONREADER_H_

#include "JSONReader.h"
#include "Sequence.h"

namespace musical {

/**
 * Generates a sequence of OptiSymbol symbols from a JSON string
 */
class OptiJSONReader: public musical::JSONReader {
public:
	/**
	 * Constructor
	 */
	OptiJSONReader();

	/**
	 * Constructor
	 * s : pointer to the source of the json string
	 */
	OptiJSONReader(JSONSource * s) : JSONReader(s) {};

	/**
	 * Destructor
	 */
	virtual ~OptiJSONReader();

	/**
	 * Generate the sequence.
	 */
	virtual Sequence* generateSequence();
};

}

#endif /* OPTIJSONREADER_H_ */
