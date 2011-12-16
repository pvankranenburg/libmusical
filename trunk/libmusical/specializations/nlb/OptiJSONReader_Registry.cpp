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
using namespace std;

#include "OptiJSONReader_Registry.h"
#include "SymbolRegistry.h"
#include "libjson.h"

namespace musical {

OptiJSONReader_Registry::OptiJSONReader_Registry() {
	// TODO Auto-generated constructor stub

}

OptiJSONReader_Registry::~OptiJSONReader_Registry() {
	// TODO Auto-generated destructor stub
}

Sequence* OptiJSONReader_Registry::generateSequence() const {
	//create a new sequence
	Sequence * nwseq = new Sequence;
	string json_string = source->getJSONString();
	//cout << json_string << endl;
	JSONNode seq = libjson::parse(json_string);
	//the name should be at 'top-level'
	JSONNode::const_iterator i1 = seq.begin();
	nwseq->setName(i1->name());
	//cout << nwseq->name << endl;
	i1 = seq.begin()->find("symbols");
	int size = i1->size();
	for( int ix=0; ix<size; ix++) {
		int pitch=i1->at(ix).at("pitch40").as_int();
		float phrasepos=i1->at(ix).at("phrasepos").as_float();
		float ima=i1->at(ix).at("IMA").as_float();
		//check whether id is present. If not take index as id
		//string id = i1->at(ix).at("id").as_string();
		SymbolRegistry* s = new SymbolRegistry;
		s->addInt("pitch40", pitch);
		s->addFloat("IMA", ima);
		s->addFloat("phrasepos", phrasepos);
		//s->strings["id"] = id;
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
