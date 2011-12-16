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

#ifndef LOCALAFFINEALIGNER_H_
#define LOCALAFFINEALIGNER_H_

#include <AlignmentAlgorithm.h>

namespace musical {

class LocalAffineAligner: public musical::AlignmentAlgorithm {
public:
	/**
	 * Constructor
	 */
	LocalAffineAligner();

	/**
	 * Constructor
	 * sqs : sequences to be aligned
	 * simr : pointer to similarity rater
	 * gapr : pointer to affine gap rater
	 */
	LocalAffineAligner(Sequences * sqs, SimilarityRater * sr, AffineGapRater * afg) : AlignmentAlgorithm(sqs,sr,afg), maxAlignments(1), allowOverlappingMatches(false) { };

	/**
	 * Destructor
	 */
	virtual ~LocalAffineAligner();

	/**
	 * Do the alignment
	 */
	void doAlign() const;

	/**
	 * set max number of alignments
	 */
	void setMaxAlignments(const int m) { maxAlignments = m; }

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
	 * Required function to reset parameters.
	 */
	void resetParameters() { maxAlignments = 1; allowOverlappingMatches = false; };


private:

	int maxAlignments; //number of local alignments that is returned. -1 is all. default is 1.
	bool allowOverlappingMatches; // if true: symbols can occur in more than one local alignment. Default: false

};

}

#endif /* LOCALAFFINEALIGNER_H_ */
