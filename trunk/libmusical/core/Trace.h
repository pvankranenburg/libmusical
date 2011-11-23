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


#ifndef TRACE_H_
#define TRACE_H_

namespace musical {

/**
 * Abstract Trace object. This represents the content of a cell in the DP-matrix of an alignment algorithm.
 */
class Trace {
public:
	/**
	 * Constructor
	 */
	Trace() : accumulatedscore(0.0), thisscore(0.0) { };

	/**
	 * Constructor
	 * as : accumulated score
	 * ts : score for the current cell
	 */
	Trace(double as, double ts) : accumulatedscore(as), thisscore(ts) {} ;

	/**
	 * Destructor
	 */
	virtual ~Trace();

	/**
	 * Returns the index _in_ sequence 1.
	 * Or -1 for a gap
	 */
	virtual int getIx1() = 0;

	/**
	 * Returns the index _in_ sequence 2.
	 * Or -1 for a gap
	 */
	virtual int getIx2() = 0;

	/**
	 * Returns index in matrix of the cell the trace is pointing to.
	 */
	virtual int getMatrixPreviousIx1() = 0;

	/**
	 * Returns index in matrix of the cell the trace is pointing to.
	 */
	virtual int getMatrixPreviousIx2() = 0;

	/**
	 * Returns index in matrix of the cell the trace element is in
	 */
	virtual int getMatrixThisIx1() = 0;

	/**
	 * Returns index in matrix of the cell the trace element is in
	 */
	virtual int getMatrixThisIx2() = 0;

	/**
	 * Returns the accumulatedscore
	 */
	virtual double getAccumulatedscore() { return accumulatedscore; }

	/**
	 * Returns the score for this particular trace element
	 */
	virtual double getThisscore() { return thisscore; }

public:
	double accumulatedscore;
	double thisscore;
	static const int NOWHERE = -1;
	static const int DONTUSE = -2; //for local alignment
};

}

#endif /* TRACE_H_ */
