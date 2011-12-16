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


#ifndef MIDISYMBOL_H_
#define MIDISYMBOL_H_

#include "Symbol.h"

namespace musical {

/**
 * Symbol representing a MIDI note event.
 */
class MidiSymbol: public musical::Symbol {
public:
	/**
	 * Constructor
	 */
	MidiSymbol();

	/**
	 * Destructor
	 */
	virtual ~MidiSymbol();

	int pitch12;
	int onset;
	int duration;

	//resolution? ticks per quarter / ms?

	std::string toString() const;

};

}

#endif /* MIDISYMBOL_H_ */
