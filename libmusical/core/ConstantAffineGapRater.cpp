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

#include "ConstantAffineGapRater.h"

namespace musical {

ConstantAffineGapRater::ConstantAffineGapRater() :
		gapOpeningScore(0.0), gapExtensionScore(0.0),
		initialGapOpeningScore(0.0), initialGapExtensionScore(0.0) {

	//empty

}

ConstantAffineGapRater::ConstantAffineGapRater(double gs, double es) :
		gapOpeningScore(gs), gapExtensionScore(es),
		initialGapOpeningScore(gs), initialGapExtensionScore(es) {

	//empty

}

ConstantAffineGapRater::ConstantAffineGapRater(double gs, double es, double igs, double ies) :
				gapOpeningScore(gs), gapExtensionScore(es),
				initialGapOpeningScore(igs), initialGapExtensionScore(ies) {

	//empty

}

ConstantAffineGapRater::~ConstantAffineGapRater() {
	// TODO Auto-generated destructor stub
}

double ConstantAffineGapRater::getInitializationScore(Sequences * const seqs, int x1, int y1, int x2, int y2) const {
	//either x1=x2=0 (initial gap in x)
	//or y1=y2=0 (initial gap in y)

	if ( x1 == x2 && x1 == -1 ) {
		return ( gapOpeningScore + (double)(y2-y1-1)*gapExtensionScore );
	}
	if ( y1 == y2 && y1 == -1 ) {
		return ( gapOpeningScore + (double)(x2-x1-1)*gapExtensionScore );
	}

	cerr << "ConstantAffineGapRater::getInitializationScore() invoked for non-initialization";
	return 0.0;
}

double ConstantAffineGapRater::getGapScore(Sequences * const seqs, int x1, int y1, int x2, int y2, bool endgap) const {
	if ( x1 == x2 ) { // gap in x
		return gapOpeningScore * (double)(y2-y1-1)*gapExtensionScore;
	}
	if ( y1 == y2 ) { //gap in y
		return gapOpeningScore * (double)(x2-x1-1)*gapExtensionScore;
	}

	cerr << "ConstantAffineGapRater::getGapScore for non-gap" << endl;
	return 0.0;
}

double ConstantAffineGapRater::getGapOpeningScore(Sequences * const seqs, int x1, int y1, int x2, int y2, bool endgap) const {

	//just ignore the matrix coefficients
	//For robustness it could be good to check whether (x1==x2 && y1==y2-1) || (x1==x2-1 && y1==y2)

	return gapOpeningScore;
}

double ConstantAffineGapRater::getGapExtensionScore(Sequences * const seqs, int x1, int y1, int x2, int y2, bool endgap) const {

	//just ignore the matrix coefficients
	//For robustness it could be good to check whether (x1==x2 && y1==y2-1) || (x1==x2-1 && y1==y2)

	return gapExtensionScore;
}

}
