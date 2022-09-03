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


#include <iostream>
using namespace std;

#include "NLBIMAGapRater.h"
#include "NLBSymbol.h"

namespace musical {

NLBIMAGapRater::NLBIMAGapRater() {
}

NLBIMAGapRater::NLBIMAGapRater(double gs) {
}

NLBIMAGapRater::~NLBIMAGapRater() {
	// TODO Auto-generated destructor stub
}

double NLBIMAGapRater::getInitializationScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const {

	NLBSymbol * s1 = static_cast<NLBSymbol *>(seqs->getSeq1()->getSymbolAt(0));
	NLBSymbol * s2 = static_cast<NLBSymbol *>(seqs->getSeq2()->getSymbolAt(0));

	if ( x1 == x2 && x1 == -1 ) {
		return ( s1->IMA * (double)(y2-y1) );
	}
	if ( y1 == y2 && y1 == -1 ) {
		return ( s2->IMA * (double)(x2-x1) );
	}

	cerr << "NLBIMAGapRater::getInitializationScore() invoked for non-initialization";
	return 0.0;
}

double NLBIMAGapRater::getGapScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const {
	double result = 0.;

	if ( x1 == x2 ) { // gap in x -> negative sum of IMA values for skipped symbols in y
		for(int i=y1+1; i<=y2; i++) result = result - static_cast<NLBSymbol *>(seqs->getSeq2()->getSymbolAt(i))->IMA;
	}
	else if ( y1 == y2 ) { //gap in y -> negative sum of IMA values for skipped symbols in x
		for(int i=x1+1; i<=x2; i++) result = result - static_cast<NLBSymbol *>(seqs->getSeq1()->getSymbolAt(i))->IMA;
	}
	else {
		cerr << "NLBIMAGapRater::getGapScore for non-gap" << endl;
	}

	return result;
	//return -1.0 + 2.0*(result + 1.0) ; // [-1,0] -> [-1, 1]
}


}
