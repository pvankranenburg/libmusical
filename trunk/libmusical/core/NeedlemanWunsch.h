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


#ifndef NEEDLEMANWUNSCH_H_
#define NEEDLEMANWUNSCH_H_

#include <deque>
using namespace std;

#include "AlignmentAlgorithm.h"
#include "NWTrace.h"
#include "Sequences.h"

namespace musical {

/**
 * Implementation of the Needleman-Wunsch algorithm
 */
class NeedlemanWunsch: public musical::AlignmentAlgorithm {
public:
	NeedlemanWunsch();
	NeedlemanWunsch(Sequences * sqs);
	virtual ~NeedlemanWunsch();

	/**
	 * Do the alignment.
	 */
	void doAlign();

	/**
	 * Do the trace back.
	 */
	virtual void doTraceBack() { };

	/**
	 * Get rid of results.
	 */
	virtual void clear() { alignment.clear(); } ;

	NWTrace * s; //this will be the d.p. matrix
	int size_s;

	/**
	 * This contains the alignment represented by the trace.
	 */
	std::deque<NWTrace> alignment;

};

}

#endif /* NEEDLEMANWUNSCH_H_ */
