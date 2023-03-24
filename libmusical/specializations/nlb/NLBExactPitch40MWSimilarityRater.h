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


#ifndef NLBEXACTPITCH40MWSIMILARITYRATER_H_
#define NLBEXACTPITCH40MWSIMILARITYRATER_H_

#include "SimilarityRater.h"

namespace musical {

/**
 * Similarity rater that compares pitch in base40 representation and beatstrength
 * Expected symbol: OptiSymbol
 */
class NLBExactPitch40MWSimilarityRater: public musical::SimilarityRater {
public:
	/**
	 * Constructor
	 */
	NLBExactPitch40MWSimilarityRater();

	/**
	 * Destructor
	 */
	virtual ~NLBExactPitch40MWSimilarityRater();

	/**
	 * Returns the score of aligning Symbols x2 with y2, where x2 and y2 are indices in seq1 and seq2.
	 * For now, x1 and y1 are ignored
	 * In future implementations, these can be used to align k symbols from seq1 with l symbols from seq2.
	 *
	 */
	double getScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const;

	virtual std::string getName() { return "NLBExactPitch40MWSimilarityRater"; };

};

}

#endif /* NLBEXACTPITCH40MWSIMILARITYRATER_H_ */
