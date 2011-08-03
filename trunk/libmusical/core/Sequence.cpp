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


#include <iostream>
using namespace std;

#include "Sequence.h"

namespace musical {

Sequence::Sequence() : name("noname") {
	// TODO Auto-generated constructor stub

}

Sequence::~Sequence() {
	// TODO Auto-generated destructor stub
	for( unsigned int i=0; i<symbols.size(); i++) {
		delete symbols[i];
	}
}

void Sequence::dump_stdout() {
	for( unsigned int i=0; i<symbols.size(); i++) {
		cout << symbols[i]->toString() << endl;
	}
}

}
