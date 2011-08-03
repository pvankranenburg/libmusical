/*
Copyright 2003 Mona Brand
Ported from java to c++ by Peter van Kranenburg (peter.van.kranenburg@meertens.knaw.nl)

This file is part of IMACPP.

IMACPP is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IMACPP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IMACPP.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Metrum.h"
#include <sstream>
using namespace std;

vector<int> Metrum::getOnsets(){
	vector<int> onsets(length+1,0);
	for (int i = 0; i <= length; i++) {
	    onsets[i] = onset + i*period;
	}
	return onsets;
}

/**
 * is (p1,o1,l1) already contained in this metrum?
 * precondition: p1 > this.period
 */
bool Metrum::contains(int p1, int o1, int l1) {
	return(!((o1<onset) ||  (o1%period != onset%period) ||  // must be in phase with each other
		   ((o1+l1*p1)>(onset+length*period))));
}

string Metrum::toString() {
	ostringstream sb;
	sb << "(o=" << onset << ", period=" << period << ", phase=" << phase << ", l=" << length << ")";
	return sb.str();
}
