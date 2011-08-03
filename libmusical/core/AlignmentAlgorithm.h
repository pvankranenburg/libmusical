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

namespace musical {

/**
 * Abstract class for an alignment algorithm.
 * All alignment algorithms should derive from this.
 */
class AlignmentAlgorithm {
public:
	AlignmentAlgorithm();
	AlignmentAlgorithm(Sequences * s) : seqs(s) {};
	virtual ~AlignmentAlgorithm();

	/**
	 * Do the alignment
	 */
	virtual void doAlign() = 0;

	/**
	 * Do the trace-back
	 */
	virtual void doTraceBack() = 0;

	/**
	 * Assign a sequences object to the alignment algorithm
	 */
	void setSequences(Sequences * sequences) { seqs = sequences; }

	/**
	 * Assign a gap rater to the alignment algorithm
	 */
	void setGapRater(GapRater * gr ) { gapr = gr; }

	/**
	 * Assign a similarity rater for symbols to the alignment algorithm.
	 */
	void setSRater(SimilarityRater * sr ) { simr = sr; }

	/**
	 * remove all results / score etc.
	 */
	virtual void clear() = 0;

	/**
	 * Returns the score of the alignment
	 * Do invoke doAlign() first.
	 */
	double getScore() const { return score; };


	double score;
	Sequences * seqs;
	GapRater * gapr;
	SimilarityRater * simr;

};

}

#endif /* ALIGNMENTALGORITHM_H_ */
