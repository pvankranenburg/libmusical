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


#ifndef OPTISIMILARITYRATER_REGISTRY_H_
#define OPTISIMILARITYRATER_REGISTRY_H_

#include "SimilarityRater.h"

namespace musical {

/**
 * Similarity rater for Opti symbols that uses SymbolRegistry symbols.
 */
class OptiSimilarityRater_Registry: public musical::SimilarityRater {
public:
	/**
	 * Constructor
	 */
	OptiSimilarityRater_Registry();

	/**
	 * Destructor
	 */
	virtual ~OptiSimilarityRater_Registry();

	/**
	 * computes the substitution score for symbolx x2 and y2 in seq1 and seq2 respective.
	 * x1 and y1 are ignored for now.
	 */
	virtual double getScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const ;
};

}

#endif /* OPTISIMILARITYRATER_REGISTRY_H_ */
