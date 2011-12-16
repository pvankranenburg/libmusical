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


#ifndef NWTRACE_H_
#define NWTRACE_H_

#include "Trace.h"

namespace musical {

/**
 * Trace element for Needleman-Wunsch (and Smith-Watermann).
 * An element points to (ix1,ix2).
 */
class NWTrace: public musical::Trace {
public:

	/**
	 * Constructor
	 */
	NWTrace() : Trace(), ix1(0), ix2(0) { };

	/**
	 * Constructor
	 * i1 : x-coordinate in the d.p. matrix
	 * i2 : y-coordinate in the d.p. matrix
	 * ac : accumulated score
	 * ts : score for this particular cell
	 */
	NWTrace(int i1, int i2, double ac, double ts ) : Trace(ac, ts), ix1(i1), ix2(i2) { } ;

	/**
	 * Destructor
	 */
	virtual ~NWTrace();

	/**
	 * Returns index of symbol from sequence 1, or -1 for a gap
	 */
	int getIx1() const { if ( this_ix1 == 0 ) return -1; if ( this_ix1 != ix1 ) return this_ix1 - 1; else return -1; }

	/**
	 * Returns index of symbol from sequence 2, or -1 for a gap
	 */
	int getIx2() const { if ( this_ix2 == 0 ) return -1; if ( this_ix2 != ix2 ) return this_ix2 - 1; else return -1; }

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
	int getMatrixThisIx1() const { return this_ix1; };

	/**
	 * Returns for sequence 2 the index of the cell in the dynamic programming matrix in which this Trace object is.
	 */
	int getMatrixThisIx2() const { return this_ix2; };

public:
	int ix1; //the indices of the previous matrix cell in the alignment
	int ix2;

	int this_ix1; //indices of current cell. Important for trace back.
	int this_ix2;

};

}

#endif /* NWTRACE_H_ */
