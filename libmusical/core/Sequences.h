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


#ifndef SEQUENCES_H_
#define SEQUENCES_H_

#include <vector>
#include <deque>
#include <iostream>
#include <limits>

#include "Sequence.h"
#include "Trace.h"


namespace musical {

//forward declaration
class SimilarityRater;

/**
 * Abstract container of a pair of sequences.
 */
class Sequences {
public:
	/**
	 * Constructor
	 */
	Sequences();

	/**
	 * Constructor.
	 * s1 : pointer to sequence 1
	 * s2 : pointer to sequence 2
	 */
	Sequences(Sequence * s1, Sequence * s2) : seq1(s1), seq2(s2) { };

	/**
	 * Destructor
	 */
	virtual ~Sequences();

	/**
	 * Assign a sequence to seq1.
	 */
	void setSeq1(Sequence * s) {seq1 = s; };

	/**
	 * Assign a sequence to seq2.
	 */
	void setSeq2(Sequence * s) {seq2 = s; };

	/**
	 * Get sequence 1
	 */
	Sequence * getSeq1() const {return seq1;};

	/**
	 * Get sequence 2
	 */
	Sequence * getSeq2() const {return seq2;};

	/**
	 * Get the number of (local) alignments
	 */
	int getNoOfAlignments() const { return alignments.size(); }

	/**
	 * Returns the score of alignment c
	 * Default c=0
	 * Do invoke doAlign() first.
	 */
	double getScore(const int c=0) const {
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
	int getAlignmentSize(const int c=0) const { return alignments[c].size(); }

	/**
	 * Returns pointer to nth trace element of alignment c
	 * Default c = 0
	 */
	Trace * getTraceElement(const int n, const int c=0) const {
		return alignments[c][n];
	}

	/**
	 * Remove all alignment results / scores etc.
	 */
	void clearResults();


public: //for Alignment algorithm to reach directly
	/**
	 * This will contain one or more alignments
	 */
	std::vector<std::deque<Trace *> > alignments;

	/**
	 * Contains the scores for the alignments
	 */
	std::vector<double> scores;

	/**
	 * Returns the similarity scores for all pairs of symbols
	 * ( order not important; self-similarities excluded)
	 */
	std::vector<double> getSimilarityScores(SimilarityRater * sr);


protected:
	Sequence * seq1;
	Sequence * seq2;

	/**
	 * For derived classes to clear specific results
	 */
	virtual void specificClear() { }; //default empty

};

}

#endif /* SEQUENCES_H_ */
