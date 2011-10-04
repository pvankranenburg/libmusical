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


#ifndef OPTISEQUENCE_H_
#define OPTISEQUENCE_H_

#include "Sequence.h"
#include <map>
#include <iostream>

namespace musical {

/**
 * A sequence of OptiSymbols.
 */
class OptiSequence: public musical::Sequence {
public:
	OptiSequence();
	virtual ~OptiSequence();

public:
	//(normalized) histogram for pitches in base-40 encoding.
	//pitch offset: 40 (pitchHistogram[0] is frequency of pitch 40
	//lowest pitch: BBbb (40)
	//highest pitch: bx''' (239)
	double pitchHistogram[200];

	std::map<int, double> sparsePitchHistogram;

};

}

#endif /* OPTISEQUENCE_H_ */
