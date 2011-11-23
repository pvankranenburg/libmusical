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


#ifndef CONVERTER_H_
#define CONVERTER_H_

namespace musical {

/**
 * Abstract converter.
 * Intended for conversion between two sequences of symbols in json representation.
 */
class Converter {
public:
	/**
	 * Constructor
	 */
	Converter();

	/**
	 * Destructor
	 */
	virtual ~Converter();
};

}

#endif /* CONVERTER_H_ */
