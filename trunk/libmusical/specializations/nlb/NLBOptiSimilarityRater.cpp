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


#include <cmath>

#include "NLBOptiSimilarityRater.h"
#include "NLBSymbol.h"
#include "NLBSequences.h"

namespace musical {

NLBOptiSimilarityRater::NLBOptiSimilarityRater() {
	// TODO Auto-generated constructor stub

}

NLBOptiSimilarityRater::~NLBOptiSimilarityRater() {
	// TODO Auto-generated destructor stub
}

double NLBOptiSimilarityRater::getScore(Sequences * seqs, int x1, int y1, int x2, int y2) const {

	NLBSymbol * s1;
	NLBSymbol * s2;
	double result;
	int diff;

	//for now ignore x1 and y1. Only return the similarity of the symbols associated with the destination cell

	//dynamic_cast would be better, but much, much slower
	s1 = static_cast<NLBSymbol *>(seqs->getSeq1()->getSymbolAt(x2));
	s2 = static_cast<NLBSymbol *>(seqs->getSeq2()->getSymbolAt(y2));
	//s1 = static_cast<NLBSymbol *>(seqs->seq1->symbols[x2]);
	//s2 = static_cast<NLBSymbol *>(seqs->seq2->symbols[y2]);

	int pitchshift = static_cast<NLBSequences *>(seqs)->getPitch40Shift();

	//cout << x2 << " : " << pitch1 << " - " << y2 << " : " << pitch2 << endl;

	result = 0.0;

	int im1 = abs (s1->pitch40 - (s2->pitch40+pitchshift));
	diff = im1 % 40;
	if ( diff > 23 ) result = -1.0; else result = 1.0 - ( (double)diff * 1.0/23.0 );

	result = ( result + 1.0 ) / 2.0;

	result = result * (1.0 - fabs(s2->phrasepos-s1->phrasepos)) * (1.0 - fabs(s2->IMA-s1->IMA));

	return -1.0 + 2.0*result;

}

}
