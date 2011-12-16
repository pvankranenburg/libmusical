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

#include "TestSimilarityRater.h"
#include "TestSymbol.h"

namespace musical {

TestSimilarityRater::TestSimilarityRater() {
	// TODO Auto-generated constructor stub

}

TestSimilarityRater::~TestSimilarityRater() {
	// TODO Auto-generated destructor stub
}

double TestSimilarityRater::getScore(Sequences * seqs, int x1, int y1, int x2, int y2) {
	//for now ignore x1 and y1. Only return the similarity of the symbols associated with the destination cell

	TestSymbol * s1 = static_cast<TestSymbol *>(seqs->getSeq1()->getSymbolAt(x2));
	TestSymbol * s2 = static_cast<TestSymbol *>(seqs->getSeq2()->getSymbolAt(y2));

	if ( s1->attr == s2->attr )
		return 1.0;
	else
		return -1.0;
}

}

