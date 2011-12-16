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


#ifndef READER_H_
#define READER_H_

#include "Sequence.h"
#include "JSONSource.h"

namespace musical {

/**
 * Abstract Reader. Reads the data from somewhere and convert it into internal representation (Sequence object).
 */
class Reader {
public:
	/**
	 * Constructor
	 */
	Reader();

	/**
	 * Destructor
	 */
	virtual ~Reader();

	/**
	 * Returns a pointer to a newly created Sequence, containing a vector of Symbols and possibly Sequence-level attributes.
	 */
	virtual Sequence * generateSequence() const = 0;

};

}

#endif /* READER_H_ */
