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

#ifndef AFFINEGAPRATER_H_
#define AFFINEGAPRATER_H_

#include <GapRater.h>

namespace musical {

class AffineGapRater: public musical::GapRater {
public:
	/**
	 * Constructor
	 */
	AffineGapRater();

	/**
	 * Destructor
	 */
	virtual ~AffineGapRater();

	/**
	 * Returns gap opening score for going from (x1,y1) to (x2,y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0.
	 * Condition: (x1==x2 && y1 = y2-1) || (x1==x2-1 && y1 == y2)
	 * This function is unique for Affine gap cost raters.
	 */
	virtual double getGapOpeningScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const = 0;

	/**
	 * Returns gap extension score for going from (x1,y1) to (x2,y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0.
	 * Condition: (x1==x2 && y1 = y2-1) || (x1==x2-1 && y1 == y2)
	 * This function is unique for Affine gap cost raters.
	 */
	virtual double getGapExtensionScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const = 0;

	virtual std::string getName() { return "AffineGapRater"; }
};

}

#endif /* AFFINEGAPRATER_H_ */
