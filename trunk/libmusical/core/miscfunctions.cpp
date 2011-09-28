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


#include "miscfunctions.h"
#include <algorithm>
#include <iostream>
using namespace std;

namespace musical {

int histogramShift(double hist1[], int length1, double hist2[], int length2) {
	double maxIntersection = 0.0;
	double intersection = 0.0;
	int shift = 0;

	//for now. do all shifts
	//cout << "-------------------------" << endl;

	int minshift = -(length2-1);
	int maxshift = length1-1;

	for ( int sh=minshift; sh<=maxshift; sh++ ) { //shift of hist2
		intersection = 0.0;
		for ( int j=0; j<length2; j++) { //index in s2
			int i = j + sh; //index in s1
			if ( i < 0 || i >= length1 ) continue;
			intersection += min(hist1[i], hist2[j]);
		}
		//cout << sh << "\t" << intersection;
		if ( intersection > maxIntersection ) {
			maxIntersection = intersection;
			//cout << " new max";
			shift = sh;
		}
		//cout << endl;
	}
	//cout << "-------------------------" << endl;

	return shift;

}

int histogramShift_diffavg(double hist1[], int length1, double hist2[], int length2) {

	/* Doesn't work!
	 * Tested: full evaluation: mean avg. prec. 0.84 op Annotated dataset
	 *         this function  : mean avg. prec. 0.7  op Annotated dataset
	 */

	int shift = 0;

	double avg1 = 0.0;
	double avg2 = 0.0;

	for(int i=0; i<length1; i++) { avg1 = avg1 + hist1[i]*(double)i; if(hist1[i]>0); }
	for(int i=0; i<length2; i++) { avg2 = avg2 + hist2[i]*(double)i; if(hist2[i]>0); }

	shift = (int)(avg2-avg1);

	//cout << avg1 << " " << avg2 << " " << shift << endl;

	return shift;

}



}
