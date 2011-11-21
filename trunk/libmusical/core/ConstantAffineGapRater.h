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


#ifndef CONSTANTAFFINEGAPRATER_H_
#define CONSTANTAFFINEGAPRATER_H_

#include "AffineGapRater.h"

namespace musical {

/**
 * A gap rater that has fixed scores for gap-opening and gap-extension.
 * To be used with the Gotoh-variants of the alignment algorithm.
 */
class ConstantAffineGapRater: public AffineGapRater {
public:
	ConstantAffineGapRater();
	ConstantAffineGapRater(double gs, double es);
	ConstantAffineGapRater(double gs, double es, double igs, double ies);
	virtual ~ConstantAffineGapRater();

	/**
	 * Returns initialization score for going from (x1, y1) to (x2, y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0
	 * Condition: x1=x2=-1 or y1=y2=-1
	 */
	virtual double getInitializationScore(Sequences * seqs, int x1, int y1, int x2, int y2);

	/**
	 * Returns gap score for going from (x1,y1) to (x2,y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0.
	 * Condition: x1=x2 or y1=y2.
	 */
	virtual double getGapScore(Sequences * seqs, int x1, int y1, int x2, int y2);

	virtual double getGapOpeningScore(Sequences * seqs, int x1, int y1, int x2, int y2);

	virtual double getGapExtensionScore(Sequences * seqs, int x1, int y1, int x2, int y2);

	/**
	 * Sets the (fixed) gap opening score.
	 */
	void setGapOpeningScore(double gs) { gapOpeningScore = gs; };

	/**
	 * Sets the (fixed) gap extension score.
	 */
	void setGapExtensionScore(double es) { gapExtensionScore = es; };
private:
	double gapOpeningScore;
	double gapExtensionScore;
	double initialGapOpeningScore;
	double initialGapExtensionScore;
};

}

#endif /* CONSTANTAFFINEGAPRATER_H_ */
