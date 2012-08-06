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
using namespace std;

#include "miscfunctions.h"
#include "MidiSequences.h"

namespace musical {

MidiSequences::MidiSequences() {
	// TODO Auto-generated constructor stub

}

MidiSequences::~MidiSequences() {
	// TODO Auto-generated destructor stub
}

void MidiSequences::computePitch12HistogramShift() {
	//pitch40HistogramShift = histogramShift( static_cast<MidiSequence*>(getSeq1())->pitchHistogram, 200, static_cast<MidiSequence*>(getSeq2())->pitchHistogram, 200);
	//pitch40HistogramShift = histogramShift_bound(static_cast<MidiSequence*>(getSeq1())->pitchHistogram, 200, static_cast<MidiSequence*>(getSeq2())->pitchHistogram, 200);
	//pitch40HistogramShift = 10;
	//cout << getSeq1()->name << " - " << getSeq2()->name << " : " << pitch40HistogramShiftA << endl;

	double * hist1 = static_cast<MidiSequence*>(getSeq1())->pitchHistogram;
	double * hist2 = static_cast<MidiSequence*>(getSeq2())->pitchHistogram;
	int length1 = 120;
	int length2 = 120;

	double avg1 = 0.0;
	double avg2 = 0.0;

	int highest1 = length1-1;
	int lowest1 = 0;
	int highest2 = length2-1;
	int lowest2 = 0;

	for(int i=0; i<length1; i++) { avg1 = avg1 + hist1[i]*(double)i; }
	for(int i=0; i<length2; i++) { avg2 = avg2 + hist2[i]*(double)i; }

	while ( hist1[lowest1] == 0 ) { lowest1++; }
	while ( hist2[lowest2] == 0 ) { lowest2++; }
	while ( hist1[highest1] == 0 ) { highest1--; }
	while ( hist2[highest2] == 0 ) { highest2--; }

	double maxIntersection = 0.0;
	double intersection = 0.0;

	pitch12HistogramShift = 0;

	//cout << "-------------------------" << endl;

	int minshift = lowest1 - highest2;
	int maxshift = highest1 - lowest2;

	for ( int sh=minshift; sh<=maxshift; sh++ ) { //shift of hist2
		intersection = 0.0;
		for ( int j=lowest2; j<highest2; j++) { //index in s2
			int i = j + sh; //index in s1
			if ( i < 0 || i >= length1 ) continue;
			intersection += min(hist1[i], hist2[j]);
		}
		//cout << sh << "\t" << intersection;
		if ( intersection > maxIntersection ) {
			maxIntersection = intersection;
			//cout << " new max";
			pitch12HistogramShift = sh;
		}
		//cout << endl;
	}
	//cout << "-------------------------" << endl;

}


}
