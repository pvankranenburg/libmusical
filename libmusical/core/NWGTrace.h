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


#ifndef NWGTRACE_H_
#define NWGTRACE_H_

#include "Trace.h"

namespace musical {

/**
 * Trace element for Needleman-Wunsch-Gotoh algorithm.
 * With respect to NWTrace, this adds state information: the cell points to (ix1,ix2) in matrix state.
 */
class NWGTrace: public musical::Trace {

public:

	enum State {S, G1, G2, NONE};

	NWGTrace() : Trace(), ix1(0), ix2(0) { };
	NWGTrace(int i1, int i2, State st, double ac, double ts ) : Trace(ac, ts), ix1(i1), ix2(i2), state(st) { } ;
	virtual ~NWGTrace();

	int ix1;
	int ix2;
	State state; //ix1, ix2 points either to S, G1 or G2

	int this_ix1;
	int this_ix2;

};

}

#endif /* NWGTRACE_H_ */
