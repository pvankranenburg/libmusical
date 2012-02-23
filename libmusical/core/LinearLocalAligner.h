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


#ifndef SMITHWATERMAN_H_
#define SMITHWATERMAN_H_

#include <deque>

#include "AlignmentAlgorithm.h"
#include "NWTrace.h"

namespace musical {

/**
 * Implementation of the Smith-Watermann local alignment algorithm.
 */
class LinearLocalAligner: public musical::AlignmentAlgorithm {
protected:

	/**
	 * Constructor
	 */
	LinearLocalAligner();

public:
	/**
	 * Constructor
	 * sqs: pointer to sequences to be aligned
	 * sr : pointer to similarity rater
	 * gr : pointer to gap rater
	 */
	LinearLocalAligner(Sequences * sqs, SimilarityRater * sr, GapRater * gr) : AlignmentAlgorithm(sqs,sr,gr), maxAlignments(1), allowOverlappingMatches(false), threshold(0.0) { };

	/**
	 * Destructor
	 */
	virtual ~LinearLocalAligner();

	/**
	 * Do the alignment.
	 */
	void doAlign() const;

	/**
	 * set max number of alignments
	 */
	void setMaxAlignments(const int m) { maxAlignments = m; }

	/**
	 * set local alignment threshold
	 */
	void setThreshold(double th) { threshold = th; }

	/**
	 * Allow for overlapping matches
	 */
	void doAllowOverlappingMatches() { allowOverlappingMatches = true; }

	/**
	 * Do not allow for overlapping matches
	 */
	void disallowOverlappingMatches() { allowOverlappingMatches = false; }

	/**
	 * get max number of alignments
	 */
	int getMaxAlignments() const { return maxAlignments; }

	/**
	 * allow overlapping matches?
	 */
	bool getAllowOverlappingMatches() const { return allowOverlappingMatches; }

	/**
	 * Reset the parameters to default.
	 * I.e., maximal 1 alignment and no overlapping alignments
	 */
	void resetParameters() { maxAlignments = 1; allowOverlappingMatches = false; } ;

private:
	int maxAlignments; //number of local alignments that is returned. -1 is all. default is 1.
	bool allowOverlappingMatches; // if true: symbols can occur in more than one local alignment. Default: false

	double threshold; //alignment ends if accumulated score is below this threshold. default is 0.

};

}

#endif /* SMITHWATERMAN_H_ */
