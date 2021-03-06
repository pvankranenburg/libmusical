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


#include "MidiSymbol.h"

#include <sstream>
#include <iostream>
using namespace std;

namespace musical {

MidiSymbol::MidiSymbol() {
	// TODO Auto-generated constructor stub

}

MidiSymbol::~MidiSymbol() {
	// TODO Auto-generated destructor stub
}

std::string MidiSymbol::toString() const {
	stringstream ss;
	ss << "pitch12: " << pitch12 << flush
	   << " onset: " << onset << flush
	   << " duration: " << duration << flush
	   << " interonset: " << getInterOnset() << flush
	   << " interonset ratio: " << getInterOnsetRatio();
	return ss.str();
}

int MidiSymbol::getInterOnset() const {
	if ( next != NULL ) {
		return ((MidiSymbol*)next)->onset - this->onset;
	}
	else
		return duration;
}

double MidiSymbol::getInterOnsetRatio() const {
	if ( this->getPrevious() == NULL ) {
		return 1.0;
	} else {
		return double(this->getInterOnset()) / double(((MidiSymbol*)previous)->getInterOnset());
	}
}

}
