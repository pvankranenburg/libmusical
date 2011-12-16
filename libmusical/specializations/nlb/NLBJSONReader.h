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


#ifndef NLBJSONREADER_H_
#define NLBJSONREADER_H_

#include "JSONReader.h"
#include "Sequence.h"

namespace musical {

/**
 * Generates a sequence of NLBSymbol symbols from a JSON string
 */
class NLBJSONReader: public musical::JSONReader {
public:
	/**
	 * Constructor
	 */
	NLBJSONReader();

	/**
	 * Constructor
	 * s : pointer to the source of the json string
	 */
	NLBJSONReader(JSONSource * s) : JSONReader(s) {};

	/**
	 * Destructor
	 */
	virtual ~NLBJSONReader();

	/**
	 * Generate the sequence.
	 */
	virtual Sequence* generateSequence() const;
};

}

#endif /* NLBJSONREADER_H_ */
