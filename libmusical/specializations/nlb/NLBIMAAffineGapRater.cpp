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

#include "NLBIMAAffineGapRater.h"
#include "NLBSymbol.h"

namespace musical {

NLBIMAAffineGapRater::NLBIMAAffineGapRater() :
		gapExtensionScore(0.0),
		initialGapExtensionScore(0.0) {

	//empty

}

NLBIMAAffineGapRater::NLBIMAAffineGapRater(double es) :
		gapExtensionScore(es),
		initialGapExtensionScore(es) {

	//empty

}

NLBIMAAffineGapRater::NLBIMAAffineGapRater(double es, double ies) :
				gapExtensionScore(es),
				initialGapExtensionScore(ies) {

	//empty

}

NLBIMAAffineGapRater::~NLBIMAAffineGapRater() {
	// TODO Auto-generated destructor stub
}

double NLBIMAAffineGapRater::getInitializationScore(Sequences * const seqs, int x1, int y1, int x2, int y2) const {
	//either x1=x2=0 (initial gap in x)
	//or y1=y2=0 (initial gap in y)

	NLBSymbol * s1 = static_cast<NLBSymbol *>(seqs->getSeq1()->getSymbolAt(0));
	NLBSymbol * s2 = static_cast<NLBSymbol *>(seqs->getSeq2()->getSymbolAt(0));

	double result = 0.0;

	if ( x1 == -1 && x2 == -1 ) {
		if (y1 == -1)
			return( -s1->IMA + (double)(y2-y1-1)*gapExtensionScore );
		else
			return( (double)(y2-y1)*gapExtensionScore );
	}
	if ( y1 == -1 && y2 == -1 ) {
		if (x1 == -1)
			return ( -s2->IMA + (double)(x2-x1-1)*gapExtensionScore );
		else
			return( (double)(x2-x1)*gapExtensionScore );
	}
	cerr << "NLBIMAAffineGapRater::getInitializationScore() invoked for non-initialization";
	return 0.0;
}

double NLBIMAAffineGapRater::getGapScore(Sequences * const seqs, int x1, int y1, int x2, int y2) const {
	cerr << "Do not use NLBIMAAffineGapRater::getGapScore" << endl;
	return 0.0;
}

double NLBIMAAffineGapRater::getGapOpeningScore(Sequences * const seqs, int x1, int y1, int x2, int y2) const {
	//we know y2 = y1 + 1, or x2 = x1 + 1

	NLBSymbol * s1 = static_cast<NLBSymbol *>(seqs->getSeq1()->getSymbolAt(x2));
	NLBSymbol * s2 = static_cast<NLBSymbol *>(seqs->getSeq2()->getSymbolAt(y2));

	if (x1 == x2) //gap opening in x
		return -s2->IMA;
	if (y1 == y2) //gap opening in y
		return -s1->IMA;

	cerr << "NLBIMAAffineGapRater::getGapOpeningScore() invoked for non-gap";
	return 0.0;

}

double NLBIMAAffineGapRater::getGapExtensionScore(Sequences * const seqs, int x1, int y1, int x2, int y2) const {

	return gapExtensionScore;
}

}
