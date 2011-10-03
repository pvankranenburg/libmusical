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


#include "AlignmentVisualizer.h"
#include <iostream>
using namespace std;

namespace musical {

AlignmentVisualizer::AlignmentVisualizer() {
	// TODO Auto-generated constructor stub

}

AlignmentVisualizer::~AlignmentVisualizer() {
	// TODO Auto-generated destructor stub
}

void AlignmentVisualizer::basicStdoutReport(int c) {

	for ( int i = 0; i < al->getAlignmentSize(c); i++ ) {
		std::string symbol1 = "s1";
		std::string symbol2 = "s2";

		if ( al->getTraceElement(i,c)->getIx1() == -1 )
			symbol1 = "x";
		else symbol1 = al->getSeq1()->getSymbolAt(al->getTraceElement(i,c)->getIx1())->toString();

		if ( al->getTraceElement(i,c)->getIx2() == -1 )
			symbol2 = "x";
		else symbol2 = al->getSeq2()->getSymbolAt(al->getTraceElement(i,c)->getIx2())->toString();

		cout << "(" << al->getTraceElement(i,c)->getIx1() << ")[" << symbol1 << "] - (" << al->getTraceElement(i,c)->getIx2() <<  ")[" << symbol2 << "]" << endl;
	}

}

}
