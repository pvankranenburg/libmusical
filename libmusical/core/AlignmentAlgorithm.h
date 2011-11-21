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
#include <deque>
#include <limits>

namespace musical {

/**
 * Abstract class for an alignment algorithm.
 * All alignment algorithms should derive from this.
 */
class AlignmentAlgorithm {
public:
	AlignmentAlgorithm();
	AlignmentAlgorithm(Sequences * s, SimilarityRater * sr, GapRater * gr) : seqs(s), simr(sr), gapr(gr), feedback(false) {};
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
	 * returns a pointer to the gap rater
	 */
	GapRater * getGapRater() { return gapr; }

	/**
	 * remove all results / score etc.
	 */
	void clearResults();

	/**
	 * Set to true for debugging info to stdout
	 */
	void setFeedback(bool f) { feedback = f; };


protected:
	/**
	 * In this function derived classes (algorithms) should put specific cleaning.
	 * Invoked from clear
	 */
	virtual void specificClear() = 0;

public:
	/**
	 * Get the number of (local) alignments
	 */
	int getNoOfAlignments() { return alignments.size(); }

	/**
	 * Returns the score of alignment c
	 * Default c=0
	 * Do invoke doAlign() first.
	 */
	double getScore(int c=0) const {
		if ( c >= (int)scores.size()) {
			std::cerr << c << "th score not available" << std::endl;
			return -std::numeric_limits<double>::infinity();
		}
		return scores[c];
	};

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

	/**
	 * contains the scores for the alignments
	 */
	vector<double> scores;

	Sequences * seqs;
	SimilarityRater * simr;
	GapRater * gapr;

	/**
	 * For debuging
	 */
	bool feedback;

};

}

#endif /* ALIGNMENTALGORITHM_H_ */
