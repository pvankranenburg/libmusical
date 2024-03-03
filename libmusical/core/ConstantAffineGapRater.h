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
	/**
	 * Constructor.
	 * Sets all gap scores to 0.0
	 */
	ConstantAffineGapRater();

	/**
	 * Constructor
	 * gs: gap opning score and initial gap opening score
	 * es: gap extension score and initial gap extension score
	 */
	ConstantAffineGapRater(double gs, double es);

	/**
	 * Constructor
	 * gs: gap opening score
	 * igs: initial gap opening score
	 * es: gap extension score
	 * ies: initial gap extension score
	 */
	ConstantAffineGapRater(double gs, double es, double igs, double ies);

	/**
	 * Destructor for ConstantAffineGapRater
	 */
	virtual ~ConstantAffineGapRater();

	/**
	 * Returns initialization score for going from (x1, y1) to (x2, y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0
	 * Condition: x1==x2==-1 || y1==y2==-1
	 */
	virtual double getInitializationScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const;

	/**
	 * Returns gap score for going from (x1,y1) to (x2,y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0.
	 * Condition: x1==x2 || y1==y2.
	 */
	virtual double getGapScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2, const bool endgap) const;

	/**
	 * Returns gap opening score for going from (x1,y1) to (x2,y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0.
	 * Condition: (x1==x2 && y1 = y2-1) || (x1==x2-1 && y1 == y2)
	 */
	virtual double getGapOpeningScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2, const bool endgap) const;

	/**
	 * Returns gap extension score for going from (x1,y1) to (x2,y2).
	 * The parameters are indices in seq1 and seq2. First symbol has index 0.
	 * Condition: (x1==x2 && y1 = y2-1) || (x1==x2-1 && y1 == y2)
	 */
	virtual double getGapExtensionScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2, const bool endgap) const;

	/**
	 * Sets the (fixed) gap opening score.
	 */
	void setGapOpeningScore(const double gs) { gapOpeningScore = gs; };

	/**
	 * Sets the (fixed) gap extension score.
	 */
	void setGapExtensionScore(const double es) { gapExtensionScore = es; };

	/**
	 * Sets the (fixed) initial gap opening score.
	 */
	void setInitialGapOpeningScore(const double igs) { initialGapOpeningScore = igs; };

	/**
	 * Sets the (fixed) initial gap extension score.
	 */
	void setInitialGapExtensionScore(const double ies) { initialGapExtensionScore = ies; };

	virtual std::string getName() { return "ConstantAffineGapRater"; }


private:
	/**
	 * Score for opening a gap
	 */
	double gapOpeningScore;

	/**
	 * Score for extension of a gap
	 */
	double gapExtensionScore;

	/**
	 * Score for opening initial gap
	 */
	double initialGapOpeningScore;

	/**
	 * Score for extending initial gap
	 */
	double initialGapExtensionScore;
};

}

#endif /* CONSTANTAFFINEGAPRATER_H_ */
