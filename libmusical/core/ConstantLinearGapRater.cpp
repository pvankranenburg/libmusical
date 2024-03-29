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

#include "ConstantLinearGapRater.h"

namespace musical {

ConstantLinearGapRater::ConstantLinearGapRater() : gapScore(0.0) {
}

ConstantLinearGapRater::ConstantLinearGapRater(double gs) : gapScore(gs) {
}

ConstantLinearGapRater::~ConstantLinearGapRater() {
	// TODO Auto-generated destructor stub
}

double ConstantLinearGapRater::getInitializationScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const {
	//either x1=x2=-1 (initial gap in x)
	//or y1=y2=-1 (initial gap in y)

	if ( x1 == x2 && x1 == -1 ) {
		return ( gapScore * (double)(y2-y1) );
	}
	if ( y1 == y2 && y1 == -1 ) {
		return ( gapScore * (double)(x2-x1) );
	}

	cerr << "ConstantLinearGapRater::getInitializationScore() invoked for non-initialization";
	return 0.0;
}

double ConstantLinearGapRater::getGapScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2, const bool endgap) const {
	if ( x1 == x2 ) { // gap in x
		if(getZeroEndGapScore() && endgap) return 0.0;
		return gapScore * (double)(y2-y1);
	}
	if ( y1 == y2 ) { //gap in y
		if(getZeroEndGapScore() && endgap) return 0.0;
		return gapScore * (double)(x2-x1);
	}

	cerr << "ConstantLinearGapRater::getGapScore for non-gap" << endl;
	return 0.0;
}


}
