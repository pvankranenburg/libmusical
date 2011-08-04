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

#include "MidiReader.h"
#include "MidiSymbol.h"
#include "libjson.h"

namespace musical {

MidiReader::MidiReader() {
	// TODO Auto-generated constructor stub

}

MidiReader::~MidiReader() {
	// TODO Auto-generated destructor stub
}

Sequence* MidiReader::generateSequence() {
	//create a new sequence
	Sequence * nwseq = new Sequence;
	string json_string = source->getJSONString();
	//cout << json_string << endl;

	JSONNode seq = libjson::parse(json_string);
	//the name should be at 'top-level'
	JSONNode::const_iterator i1 = seq.begin();
	nwseq->name = i1->name();
	//cout << nwseq->name << endl;
	i1 = seq.begin()->find("symbols");

	int size = i1->size();
	for( int ix=0; ix<size; ix++) {
		int onset=i1->at(ix).at("onset").as_int();
		int pitch=i1->at(ix).at("pitch").as_int();
		int duration=i1->at(ix).at("duration").as_int();
		MidiSymbol* s = new MidiSymbol;
		s->onset = onset;
		s->pitch12 = pitch;
		s->duration = duration;
		//string id = i1->at(ix).at("id").as_string();
		//s->strings["id"] = id;
		nwseq->symbols.push_back(s);
	}
	//set next and previous
	nwseq->symbols[0]->next = nwseq->symbols[1];
	nwseq->symbols[0]->previous = NULL;
	for( unsigned int i = 1; i<nwseq->symbols.size()-1; i++) {
		nwseq->symbols[i]->previous = nwseq->symbols[i-1];
		nwseq->symbols[i]->next = nwseq->symbols[i+1];
	}
	nwseq->symbols[nwseq->symbols.size()-1]->previous = nwseq->symbols[nwseq->symbols.size()-2];
	nwseq->symbols[nwseq->symbols.size()-1]->next = NULL;

	return nwseq;
}

}
