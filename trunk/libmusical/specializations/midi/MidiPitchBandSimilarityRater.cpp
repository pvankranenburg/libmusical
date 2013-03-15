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

#include "MidiPitchBandSimilarityRater.h"
#include "MidiSymbol.h"
#include "MidiSequences.h"

#include <cmath>

namespace musical {

MidiPitchBandSimilarityRater::MidiPitchBandSimilarityRater() : use_ima(false) {
	// TODO Auto-generated constructor stub

}

MidiPitchBandSimilarityRater::~MidiPitchBandSimilarityRater() {
	// TODO Auto-generated destructor stub
}

double MidiPitchBandSimilarityRater::getScore(Sequences * const seqs, const int x1, const int y1, const int x2, const int y2) const {
	//for now ignore x1 and y1. Only return the similarity of the symbols associated with the destination cell

	MidiSymbol * s1 = static_cast<MidiSymbol *>(seqs->getSeq1()->getSymbolAt(x2));
	MidiSymbol * s2 = static_cast<MidiSymbol *>(seqs->getSeq2()->getSymbolAt(y2));

	double res = 0.0;

	int pitch1 = s1->pitch12;
	int pitch2 = s2->pitch12;

	if ( pitch1 != 0 ) pitch2 += (static_cast<MidiSequences *>(seqs))->getPitch12Shift();

	if ( pitch2 == 0 || pitch1 == 0 ) return 0.0;  //rest


	int interval = abs ( pitch1 - pitch2 ) % 12;

	if ( interval > 7) return -1.0;

	res = 1.0 - ( (double)interval * 1.0/7.0 );

	if ( use_ima ) {
		double factor_ima = 1.0 - fabs ( s2->ima - s1->ima );

		if ( res > 0 ) res = res * factor_ima; //less positive
	}

	return res;
}

}
