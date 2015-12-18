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


#ifndef ALIGNMENTALGORITHM_H_
#define ALIGNMENTALGORITHM_H_

#include "Sequences.h"
#include "GapRater.h"
#include "SimilarityRater.h"
#include "Trace.h"

#include <iostream>
#include <limits>

namespace musical {

/**
 * Abstract class for an alignment algorithm.
 * All alignment algorithms should derive from this.
 */
class AlignmentAlgorithm {
protected:
	/**
	 * Constructor.
	 */
	AlignmentAlgorithm();

public:
	/**
	 * Constructor. Provides the sequences and raters to the algorithm
	 * s : pointer to sequences object containing the sequeces to be aligned
	 * sr : pointer to a similartiy rater
	 * gr : pointer to a gap rater
	 */
	AlignmentAlgorithm(Sequences * s, SimilarityRater * sr, GapRater * gr) : seqs(s), simr(sr), gapr(gr), feedback(false) {};

	/**
	 * Destructor.
	 * Deletes the similarity and gap raters, but not the Sequences.
	 */
	virtual ~AlignmentAlgorithm();

	/**
	 * Do the alignment
	 */
	virtual void doAlign() const = 0;

	/**
	 * Returns pointer to sequence 1
	 */
	Sequence * getSeq1() const {
		return seqs->getSeq1();
	}

	/**
	 * Returns pointer to sequence 2
	 */
	Sequence * getSeq2() const {
		return seqs->getSeq2();
	}

	/**
	 * Returns a pointer to the similarity rater
	 */
	SimilarityRater * getSimilarityRater() const { return simr; }

	/**
	 * Returns a pointer to the gap rater
	 */
	GapRater * getGapRater() const { return gapr; }

	/**
	 * Set to true for debugging info to stdout
	 */
	void setFeedback(const bool f) { feedback = f; };

	/**
	 * Reset the parameters to default.
	 */
	virtual void resetParameters() = 0 ;

	/**
	 * Returns the name of the aligner
	 */
	virtual std::string getName() = 0;

protected:
	/**
	 * The two sequences that have to be aligned
	 */
	Sequences * seqs;

	/**
	 * Similarity Rater for symbols
	 */
	SimilarityRater * simr;

	/**
	 * Gap Rater
	 */
	GapRater * gapr;

	/**
	 * For debuging
	 */
	bool feedback;

};

}

#endif /* ALIGNMENTALGORITHM_H_ */
