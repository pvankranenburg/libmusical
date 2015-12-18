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


#ifndef SIMILARITYRATER_H_
#define SIMILARITYRATER_H_

#include "Sequences.h"
#include <string>

namespace musical {

/**
 * Abstract similarity raters.
 */
class SimilarityRater {
public:
	/**
	 * Constructor
	 */
	SimilarityRater();

	/**
	 * Destructor
	 */
	virtual ~SimilarityRater();

	/**
	 * Give it a name
	 */
	virtual std::string getName() = 0;

	/**
	 * This computes the similarity score for {x1, x1+1, ... , x2} from seq1 with {y1, y1+1, ... , y2 } from seq2
	 * x1, x2, y1, and y2 are indices in the sequences. First symbol is at position 0.
	 */
	virtual double getScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const = 0;
};

}

#endif /* SIMILARITYRATER_H_ */
