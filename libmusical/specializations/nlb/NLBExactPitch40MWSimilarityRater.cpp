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

#include "NLBExactPitch40MWSimilarityRater.h"
#include "NLBSymbol.h"
#include "NLBSequences.h"

namespace musical {

NLBExactPitch40MWSimilarityRater::NLBExactPitch40MWSimilarityRater() {
	// TODO Auto-generated constructor stub

}

NLBExactPitch40MWSimilarityRater::~NLBExactPitch40MWSimilarityRater() {
	// TODO Auto-generated destructor stub
}

double NLBExactPitch40MWSimilarityRater::getScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const {

	//for now ignore x1 and y1. Only return the similarity of the symbols associated with the destination cell

	NLBSymbol * s1 = static_cast<NLBSymbol *>(seqs->getSeq1()->getSymbolAt(x2));
	NLBSymbol * s2 = static_cast<NLBSymbol *>(seqs->getSeq2()->getSymbolAt(y2));

	//cout << x2 << " : " << pitch1 << " - " << y2 << " : " << pitch2 << endl;

	int pitchShift = static_cast<NLBSequences *>(seqs)->getPitch40Shift();

	// double result = 0.0;
	double epsilon = 0.0001;

	// if ( s1->pitch40 == s2->pitch40+pitchShift )
	// 	result = 1.0;
	// else
	// 	result = -1.0;

	// // scale results into [0,1]
	// result = ( result + 1.0 ) / 2.0;

	// // lower score if beatstrengths differ
	// result = result * (1.0 - fabs(s2->beatstrength - s1->beatstrength));

	// // scale back
	// return -1.0 + 2.0*result;

	if ( s1->pitch40 == s2->pitch40+pitchShift ) {
		return -1.0 + 2.0 * (1.0 - fabs(s2->beatstrength - s1->beatstrength));
	} else {
		return -1.0;
	
		////MW2:
		//return -1.0 * fmax(s2->beatstrength, s1->beatstrength); //give some score to notes with low beatstrength.

		//MW3:
		// if (fmax(s2->beatstrength, s1->beatstrength) <= (0.25+epsilon) )
		// 	return -0.5;
		// else
		// 	return -1.0;
	}

}


}
