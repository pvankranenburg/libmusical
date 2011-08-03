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

namespace musical {

/**
 * Abstract similarity raters.
 */
class SimilarityRater {
public:
	SimilarityRater();
	virtual ~SimilarityRater();

	/**
	 * This computes the similarity score for {x1+1, x1+2, ... , x2} from seq1 with {y1+1, y1+2, ... , y2 } from seq2
	 */
	virtual double getScore(Sequences * seqs, int x1, int y1, int x2, int y2) = 0;
};

}

#endif /* SIMILARITYRATER_H_ */
