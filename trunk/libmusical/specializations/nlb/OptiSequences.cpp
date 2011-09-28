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

#include "OptiSequences.h"
#include "miscfunctions.h"

namespace musical {

OptiSequences::OptiSequences() {
	// TODO Auto-generated constructor stub

}

OptiSequences::~OptiSequences() {
	// TODO Auto-generated destructor stub
}

void OptiSequences::computePitch40HistogramShift() {
	pitch40HistogramShift = histogramShift( static_cast<OptiSequence*>(getSeq1())->pitchHistogram, 200, static_cast<OptiSequence*>(getSeq2())->pitchHistogram, 200);
	//pitch40HistogramShift = histogramShift_diffavg(static_cast<OptiSequence*>(getSeq1())->pitchHistogram, 200, static_cast<OptiSequence*>(getSeq2())->pitchHistogram, 200);
	//pitch40HistogramShift = 10;
	//cout << getSeq1()->name << " - " << getSeq2()->name << " : " << pitch40HistogramShiftA << endl;
}

}
