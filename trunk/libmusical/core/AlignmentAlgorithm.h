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

#include <deque>

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
	 * Assign a sequences object to the alignment algorithm
	 */
	void setSequences(Sequences * sequences) { seqs = sequences; }

	/**
	 * Returns pointer to sequence 1
	 */
	Sequence * getSeq1() {
		return seqs->getSeq1();
	}

	/**
	 * Returns pointer to sequence 2
	 */
	Sequence * getSeq2() {
		return seqs->getSeq2();
	}

	/**
	 * returns a pointer to the similarity rater
	 */
	SimilarityRater * getSimilarityRater() { return simr; }

	/**
	 * Set the similarity rater
	 */
	void setSimilarityRater(SimilarityRater * sr ) { simr = sr; }

	/**
	 * returns a pointer to the gap rater
	 */
	GapRater * getGapRater() { return gapr; }

	/**
	 * set the gap rater
	 */
	void setGapRater(GapRater * gr) { gapr = gr; }

	/**
	 * remove all results / score etc.
	 */
	void clearResults();

protected:
	/**
	 * In this function derived classes (algorithms) should put specific cleaning.
	 * Invoked from clear (make protected?)
	 */
	virtual void specificClear() = 0;

public:
	/**
	 * Returns the score of alignment c
	 * Default c=0
	 * Do invoke doAlign() first.
	 */
	double getScore(int c=0) const { return scores[c]; };

	/**
	 * Get the length of alignment c
	 * Default c=0
	 */
	int getAlignmentSize(int c=0) { return alignments[c].size(); }

	/**
	 * Returns pointer to nth trace element of alignment c
	 * Default c = 0
	 */
	Trace * getTraceElement(int n, int c=0) {
		return alignments[c][n];
	}

protected:
	/**
	 * This will contain one or more alignments
	 */
	std::vector<std::deque<Trace *> > alignments;

	vector<double> scores;

	Sequences * seqs;
	GapRater * gapr;
	SimilarityRater * simr;

};

}

#endif /* ALIGNMENTALGORITHM_H_ */
