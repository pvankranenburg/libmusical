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


#include<iostream>
#include<utility>
#include <algorithm>
using namespace std;

#include "NLBSequences.h"
#include "miscfunctions.h"

namespace musical {

NLBSequences::NLBSequences() : pitch40HistogramShift(0) {
	// TODO Auto-generated constructor stub

}

NLBSequences::~NLBSequences() {
	// TODO Auto-generated destructor stub
}

bool compIntersections( const pair<int,double> a, const pair<int,double> b ) {
	return a.second < b.second;
}

void NLBSequences::computePitch40HistogramShift() {
	//pitch40HistogramShift = histogramShift( static_cast<NLBSequence*>(getSeq1())->pitchHistogram, 200, static_cast<NLBSequence*>(getSeq2())->pitchHistogram, 200);
	//pitch40HistogramShift = histogramShift_bound(static_cast<NLBSequence*>(getSeq1())->pitchHistogram, 200, static_cast<NLBSequence*>(getSeq2())->pitchHistogram, 200);
	//pitch40HistogramShift = 10;
	//cout << getSeq1()->name << " - " << getSeq2()->name << " : " << pitch40HistogramShiftA << endl;

	double * hist1 = static_cast<NLBSequence*>(getSeq1())->pitchHistogram;
	double * hist2 = static_cast<NLBSequence*>(getSeq2())->pitchHistogram;
	int length1 = 200;
	int length2 = 200;

	//double maxIntersection = 0.0;
	double intersection = 0.0;

	pitch40HistogramShift = 0;

	//cout << "-------------------------" << endl;

	//Negative shift + no shift:
	//ol = overlap
	for( int ol=1; ol<=200; ol++ ) {
		intersection = 0.0;
		int shift = -length2+ol;
		for ( int i=0; i<ol; i++ )
			intersection += min(hist1[i], hist2[i-shift]);
		intersections.push_back(pair<int,double>(shift, intersection));
	}
	//Positive shift
	for( int ol=1; ol<=199; ol++ ) {
		intersection = 0.0;
		int shift = length2-ol;
		for ( int j=0; j<ol; j++)
			intersection += min(hist1[j+shift], hist2[j]);
		intersections.push_back(pair<int,double>(shift, intersection));
	}

	sort(intersections.begin(), intersections.end(), compIntersections);
	if ( intersections.size() > 0) pitch40HistogramShift = intersections.back().first;

	/*
	vector<pair<int,double> >::iterator it;
	for(it=intersections.begin(); it != intersections.end(); ++it) {
		cout << (*it).first << "\t" << (*it).second << endl;
	}
	*/

	//cout << "-------------------------" << endl;

}

int NLBSequences::getPitch12Shift() const {
	//compute octave
	int octave = pitch40HistogramShift / 40;
	int degree = pitch40HistogramShift % 40;
	int pitch12 = 0;
	if ( abs(degree) == 1 ) pitch12 = 1;
	//if ( degree == 2 ) pitch12 = ;
	//if ( degree == 3 ) pitch12 = ;
	if ( abs(degree) == 4 ) pitch12 = 0;
	if ( abs(degree) == 5 ) pitch12 = 1;
	if ( abs(degree) == 6 ) pitch12 = 2;
	if ( abs(degree) == 7) pitch12 = 3;
	//if ( degree == 8 ) pitch12 = ;
	//if ( degree == 9 ) pitch12 = ;
	if ( abs(degree) == 10 ) pitch12 = 2;
	if ( abs(degree) == 11 ) pitch12 = 3;
	if ( abs(degree) == 12 ) pitch12 = 4;
	if ( abs(degree) == 13 ) pitch12 = 5;
	//if ( degree == 14 ) pitch12 = 3;
	//if ( degree == 15 ) pitch12 = 4;
	if ( abs(degree) == 16 ) pitch12 = 4;
	if ( abs(degree) == 17 ) pitch12 = 5;
	if ( abs(degree) == 18 ) pitch12 = 6;
	//if ( degree == 19 ) pitch12 = 4;
	//if ( degree == 20 ) pitch12 = 5;
	//if ( degree == 21 ) pitch12 = 6;
	if ( abs(degree) == 22 ) pitch12 = 6;
	if ( abs(degree) == 23 ) pitch12 = 7;
	if ( abs(degree) == 24 ) pitch12 = 8;
	//if ( degree == 25 ) pitch12 = 6;
	//if ( degree == 26 ) pitch12 = 7;
	if ( abs(degree) == 27 ) pitch12 = 7;
	if ( abs(degree) == 28 ) pitch12 = 8;
	if ( abs(degree) == 29 ) pitch12 = 9;
	if ( abs(degree) == 30 ) pitch12 = 10;
	//if ( degree == 31 ) pitch12 = 8;
	//if ( degree == 32 ) pitch12 = 9;
	if ( abs(degree) == 33 ) pitch12 = 9;
	if ( abs(degree) == 34 ) pitch12 = 10;
	if ( abs(degree) == 35 ) pitch12 = 11;
	if ( abs(degree) == 36 ) pitch12 = 12;
	//if ( degree == 37 ) pitch12 = 10;
	//if ( degree == 38 ) pitch12 = 11;
	if ( abs(degree) == 39 ) pitch12 = 11;
	if ( degree < 0 ) { pitch12 = -pitch12; }

	return 12*octave + pitch12;
}

}
