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

	/**
	 * The states the element could point to
	 */
	enum State {S, G1, G2, NONE};

	/**
	 * Constructor.
	 */
	NWGTrace() : Trace(), ix1(0), ix2(0) { };

	/**
	 * Constructor
	 * i1 : x-coordinate in the d.p. matrix
	 * i2 : y-coordinate in the d.p. matrix
	 * ac : accumulated score
	 * ts : score for this particular cell
	 */
	NWGTrace(int i1, int i2, State st, double ac, double ts ) : Trace(ac, ts), ix1(i1), ix2(i2), state(st) { } ;

	/**
	 * Destructor
	 */
	virtual ~NWGTrace();

	/**
	 * Returns index of symbol from sequence 1, or -1 for a gap
	 */
	int getIx1() const { if (this_ix1 != ix1) return this_ix1 - 1; else return -1; };

	/**
	 * Returns index of symbol from sequence 2, or -1 for a gap
	 */
	int getIx2() const { if (this_ix2 != ix2) return this_ix2 - 1; else return -1; };

	/**
	 * Returns for sequence 1 the index of the cell in the dynamic programming matrix to which current Trace object is pointing.
	 */
	int getMatrixPreviousIx1() const { return ix1; };

	/**
	 * Returns for sequence 2 the index of the cell in the dynamic programming matrix to which current Trace object is pointing.
	 */
	int getMatrixPreviousIx2() const { return ix2; };

	/**
	 * Returns for sequence 1 the index of the cell in the dynamic programming matrix in which this Trace object is.
	 */
	int getMatrixThisIx1() const {  return this_ix1; };

	/**
	 * Returns for sequence 2 the index of the cell in the dynamic programming matrix in which this Trace object is.
	 */
	int getMatrixThisIx2() const { return this_ix2; };


public:
	//the indices of the previous matrix cell in the alignment
	int ix1;
	int ix2;
	State state; //ix1, ix2 points either to S, G1 or G2

	//the indices of the current matrix cell in the alignment
	int this_ix1;
	int this_ix2;

};

}

#endif /* NWGTRACE_H_ */
