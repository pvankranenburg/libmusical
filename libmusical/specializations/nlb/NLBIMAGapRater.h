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


#ifndef NLBIMAGAPRATER_H_
#define NLBIMAGAPRATER_H_

#include "GapRater.h"

namespace musical {

/**
 * A gap rater that assigns fixed, linear scores.
 */
class NLBIMAGapRater: public musical::GapRater {
public:
	/**
	 * Constructor. Sets score to 0.0
	 */
	NLBIMAGapRater();

	/**
	 * Constructor
	 * gs : gap score
	 */
	NLBIMAGapRater(double gs);

	/**
	 * Destructor
	 */
	virtual ~NLBIMAGapRater();

	/**
	 * Returns initialization score for going from cell (x1, y1) to (x2, y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0
	 * Condition: x1=x2=-1 or y1=y2=-1
	 */
	virtual double getInitializationScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const;

	/**
	 * Returns gapscore for going from (x1,y1) to (y2,y2)
	 * The parameters are indices in seq1 and seq2. First symbol has index 0
	 * Condition: x1=x2 or y1=y2
	 */
	virtual double getGapScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2, const bool endgap) const;

	virtual std::string getName() { return "NLBIMAGapRater"; }


private:

};

}

#endif /* NLBIMAGAPRATER_H_ */
