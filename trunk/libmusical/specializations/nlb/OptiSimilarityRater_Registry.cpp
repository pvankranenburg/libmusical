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

#include "OptiSimilarityRater_Registry.h"
#include "SymbolRegistry.h"

namespace musical {

OptiSimilarityRater_Registry::OptiSimilarityRater_Registry() {
	// TODO Auto-generated constructor stub

}

OptiSimilarityRater_Registry::~OptiSimilarityRater_Registry() {
	// TODO Auto-generated destructor stub
}

double OptiSimilarityRater_Registry::getScore(Sequences * seqs, int x1, int y1, int x2, int y2) {

	//for now ignore x1 and y1. Only return the similarity of the symbols associated with the destination cell

	SymbolRegistry * s1 = static_cast<SymbolRegistry *>(seqs->getSeq1()->getSymbolAt(x2));
	SymbolRegistry * s2 = static_cast<SymbolRegistry *>(seqs->getSeq2()->getSymbolAt(y2));

	int pitch1 = s1->getInt("pitch40");
	int pitch2 = s2->getInt("pitch40");

	float phrasepos1 = s1->getFloat("phrasepos");
	float phrasepos2 = s2->getFloat("phrasepos");

	float IMA1 = s1->getFloat("IMA");
	float IMA2 = s2->getFloat("IMA");

	//cout << x2 << " : " << pitch1 << " - " << y2 << " : " << pitch2 << endl;

	double result = 0.0;

	int diff = abs (pitch1-pitch2);
	if ( diff >= 17 ) result = 0.0; else result = (double)diff / 17.0;

	result = result * (fabs(phrasepos1-phrasepos2));
	result = result * (fabs(IMA1-IMA2));

	return result;
}


}
