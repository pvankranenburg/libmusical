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


#ifndef MIDIREADER_H_
#define MIDIREADER_H_

#include "Reader.h"

namespace musical {

/**
 * Reads JSON representation of a midi sequence into internal representation.
 * Sequence attributes:
 * - ticks_per_quarter (int)
 * Attributes:
 * - onset (int)
 * - pitch (int)
 * - duration (int)
 */
class MidiReader: public musical::Reader {
public:
	MidiReader();
	virtual ~MidiReader();

	/**
	 * Generate the Sequence from the JSON representation
	 */
	Sequence * generateSequence();

};

}

#endif /* MIDIREADER_H_ */
