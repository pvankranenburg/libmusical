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


#ifndef NEEDLEMANWUNSCHGOTOH_H_
#define NEEDLEMANWUNSCHGOTOH_H_

#include <deque>

#include "AlignmentAlgorithm.h"
#include "NWGTrace.h"

namespace musical {

/**
 * Implementation of the Needleman-Wunsch-Gotoh algorithm.
 */
class NeedlemanWunschGotoh: public musical::AlignmentAlgorithm {
public:
	NeedlemanWunschGotoh();
	NeedlemanWunschGotoh(Sequences * sqs);
	virtual ~NeedlemanWunschGotoh();

	/**
	 * Do the alignment
	 */
	void doAlign();

	/**
	 * Do the traceback
	 */
	virtual void doTraceBack() { };

	/**
	 * Remove the results
	 */
	virtual void clear() { alignment.clear(); } ;

	/**
	 * This algorithm needs three matrices
	 */
	NWGTrace * s; //this will be the d.p. matrix.
	NWGTrace * g1; //this will be the d.p. matrix for state 'gap with seq1'.
	NWGTrace * g2; //this will be the d.p. matrix for state 'gap with seq2'
	int size_s;

	/**
	 * This attribute contains the alignemnt as sequence of trace-elements.
	 */
	std::deque<NWGTrace> alignment;

};

}

#endif /* NEEDLEMANWUNSCHGOTOH_H_ */
