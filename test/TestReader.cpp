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
#include <sstream>
#include <iostream>
using namespace std;

#include "TestReader.h"
#include "TestSymbol.h"
#include "miscfunctions.h"

namespace musical {

TestReader::TestReader(string inputstring) : input(inputstring) {

}

TestReader::~TestReader() {
	// TODO Auto-generated destructor stub
}

Sequence* TestReader::generateSequence() const {
	//create a new sequence
	Sequence * nwseq = new Sequence;
	//cout << json_string << endl;

	nwseq->setName("A Test Sequence");

	int size = input.size();
	for( int ix=0; ix<size; ix++) {
		TestSymbol* s = new TestSymbol;

		stringstream ss;
		string str;
		char c = input[ix];
		ss << c;
		ss >> str;

		s->attr = convertToInt(str);
		nwseq->addSymbol(s);
	}
	//set next and previous
	nwseq->getSymbolAt(0)->setNext(nwseq->getSymbolAt(1));
	nwseq->getSymbolAt(0)->setPrevious(NULL);
	for( unsigned int i = 1; i<nwseq->size()-1; i++) {
		nwseq->getSymbolAt(i)->setPrevious(nwseq->getSymbolAt(i-1));
		nwseq->getSymbolAt(i)->setNext(nwseq->getSymbolAt(i+1));
	}
	nwseq->getSymbolAt(nwseq->size()-1)->setPrevious( nwseq->getSymbolAt(nwseq->size()-2) );
	nwseq->getSymbolAt(nwseq->size()-1)->setNext(NULL);

	return nwseq;
}

}

