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

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#include "PCSequence.h"
#include "PCSymbol.h"

namespace musical {

PCSequence::PCSequence() : pitchHistogram(40), current_rotation(0) {
	for(int i=0; i<40; i++) {
		pitchHistogram[i] = 0.0;
	}
}

PCSequence::~PCSequence() {
	// TODO Auto-generated destructor stub
}

void PCSequence::printPitchHistogram() const {
	for(int i=0; i<pitchHistogram.size(); i++) {
		clog << pitchHistogram[i] << ",";
	}
	clog << endl;
}

void PCSequence::do_rotate(int r) {

	// clog << "Rotating sequence " << getName() << " by " << r << endl;

	if(current_rotation != 0) {
		cerr << "Warning: Rotating sequence " << getName() << " while already rotated. Resetting." << endl;
		resetRotation();
	}

	// go over symbols and rotate the contexts by r.
	// And set current rotation
	for( unsigned int i = 0; i<size(); i++) {
		vector<double> * pc_pre  = & (static_cast<PCSymbol*>(getSymbolAt(i))->pc_pre);
		vector<double> * pc_post = & (static_cast<PCSymbol*>(getSymbolAt(i))->pc_post);
		rotate((*pc_pre).begin(), (*pc_pre).begin()+r, (*pc_pre).end());
		rotate((*pc_post).begin(), (*pc_post).begin()+r, (*pc_post).end());
	}
	current_rotation = r;

}

void PCSequence::resetRotation() {
	//reverse current rotation
	if(current_rotation==0) return;
	//find out at what index the original start of the seqence is now.
	int inverse_rotation = 40 - current_rotation;
	for( unsigned int i = 0; i<size(); i++) {
		vector<double> * pc_pre  = & (static_cast<PCSymbol*>(getSymbolAt(i))->pc_pre);
		vector<double> * pc_post = & (static_cast<PCSymbol*>(getSymbolAt(i))->pc_post);
		rotate((*pc_pre).begin(), (*pc_pre).begin()+inverse_rotation, (*pc_pre).end());
		rotate((*pc_post).begin(), (*pc_post).begin()+inverse_rotation, (*pc_post).end());
	}
	current_rotation = 0;
}

}
