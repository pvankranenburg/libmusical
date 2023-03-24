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


#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "PCSymbol.h"

namespace musical {

PCSymbol::PCSymbol() : pc_pre(40), pc_post(40) {
	// TODO Auto-generated constructor stub

}

PCSymbol::~PCSymbol() {
	// TODO Auto-generated destructor stub
}

string PCSymbol::toString() const {
	stringstream ss;

	ss << pitch40 << " " << weight;

	ss << " PRE: ";
	for(int i=0; i<pc_pre.size(); i++) {
		ss << pc_pre[i] << ",";
	}
	ss << " POST: ";
	for(int i=0; i<pc_post.size(); i++) {
		ss << pc_post[i] << ",";
	}
	
	return ss.str();
}

}
