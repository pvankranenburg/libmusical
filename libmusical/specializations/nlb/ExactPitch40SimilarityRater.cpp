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


#include "ExactPitch40SimilarityRater.h"
#include "OptiSymbol.h"
#include "OptiSequences.h"

namespace musical {

ExactPitch40SimilarityRater::ExactPitch40SimilarityRater() {
	// TODO Auto-generated constructor stub

}

ExactPitch40SimilarityRater::~ExactPitch40SimilarityRater() {
	// TODO Auto-generated destructor stub
}

double ExactPitch40SimilarityRater::getScore(Sequences * seqs, int x1, int y1, int x2, int y2) {

	//for now ignore x1 and y1. Only return the similarity of the symbols associated with the destination cell

	OptiSymbol * s1 = static_cast<OptiSymbol *>(seqs->seq1->symbols[x2]);
	OptiSymbol * s2 = static_cast<OptiSymbol *>(seqs->seq2->symbols[y2]);

	//cout << x2 << " : " << pitch1 << " - " << y2 << " : " << pitch2 << endl;

	int pitchShift = static_cast<OptiSequences *>(seqs)->getPitch40Shift();

	if ( s1->pitch40 == s2->pitch40+pitchShift )
		return 1.0;
	else
		return -1.0;

	return -1.0;

}


}
