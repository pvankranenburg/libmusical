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
#include <iomanip>
#include <stdexcept>
using namespace std;

#include "NLBJSONReader.h"
#include "NLBSymbol.h"
#include "NLBSequence.h"
#include "libjson.h"


namespace musical {

NLBJSONReader::NLBJSONReader() {
	// TODO Auto-generated constructor stub

}

NLBJSONReader::~NLBJSONReader() {
	// TODO Auto-generated destructor stub
}

Sequence* NLBJSONReader::generateSequence() const {
	//create a new sequence
	NLBSequence * nwseq = new NLBSequence; //NB NLBSequence contains a pitch histogram
	string json_string = source->getJSONString();
	//nwseq->json_string = json_string;
	//clog << json_string << endl;
	JSONNode seq;
	try {
		seq = libjson::parse(json_string);
	} catch (invalid_argument&) {
		std::string errormessage = "Error: Not proper json";
		clog << errormessage << endl;
		throw std::runtime_error(errormessage);
	}
	if ( seq.empty() ) {
		std::string errormessage = "Error: Top node has no children";
		clog << errormessage << endl;
		throw std::runtime_error(errormessage);
	}
	//the name should be at 'top-level'
	JSONNode::const_iterator i1 = seq.begin();
	//cout << i1->size() << endl;
	nwseq->setName(i1->name());
	//cout << nwseq->name << endl;
	i1 = seq.begin()->find("symbols");
	if ( i1 == (seq.begin())->end() ) {
		std::string errormessage = "Error: No symbols in json " + nwseq->getName();
		clog << errormessage << endl;
		throw std::runtime_error(errormessage);
	}
	int size = i1->size();
	//cout << "Size: " << size << endl;
	bool missingbeathstrengthmessageprinted = false;
	for( int ix=0; ix<size; ix++) {
		NLBSymbol* s = new NLBSymbol();
		try
		{
			s->pitch40 = i1->at(ix).at("pitch40").as_int();
			s->onset = i1->at(ix).at("onset").as_int();
			//s->phrase = i1->at(ix).at("phrase").as_int();
			s->IMA = i1->at(ix).at("ima").as_float();
			s->phrasepos = i1->at(ix).at("phrasepos").as_float();
		}
		catch (out_of_range&)
		{
			std::string errormessage = "Error: symbols in " + nwseq->getName() + " should contain: pitch40, onset, phrase, ima, and phrasepos";
			clog << errormessage << endl;
			throw std::runtime_error(errormessage);
		}
		JSONNode::const_iterator bsnode = i1->find("beatstrength");
		if(bsnode != i1->end())
			s->beatstrength = i1->at(ix).at("beatstrength").as_float();
		else {
			s->beatstrength = 1.0;
			if( !missingbeathstrengthmessageprinted ) {
				//clog << nwseq->getName() + " - Warning: beatstrength feature not present." << endl;
				missingbeathstrengthmessageprinted = true;
			}
		}
		nwseq->addSymbol(s);
		//check whether id is present. If not take index as id
		//string id = i1->at(ix).at("id").as_string();
		//s->strings["id"] = id;
		//cout << "symbol: " << s->pitch40 << " - " << s->phrasepos << " - " << s->IMA << endl;
	}

	//cout << "size: " << size << endl;

	if ( size > 1) {
		//set next and previous
		nwseq->getSymbolAt(0)->setNext(nwseq->getSymbolAt(1));
		nwseq->getSymbolAt(0)->setPrevious(NULL);
		for( unsigned int i = 1; i<nwseq->size()-1; i++) {
			nwseq->getSymbolAt(i)->setPrevious(nwseq->getSymbolAt(i-1));
			nwseq->getSymbolAt(i)->setNext(nwseq->getSymbolAt(i+1));
		}
		nwseq->getSymbolAt(nwseq->size()-1)->setPrevious( nwseq->getSymbolAt(nwseq->size()-2) );
		nwseq->getSymbolAt(nwseq->size()-1)->setNext(NULL);
	} else if (size == 1) {
		nwseq->getSymbolAt(0)->setNext(NULL);
		nwseq->getSymbolAt(0)->setPrevious(NULL);
	}

	if ( size > 0 ) {
		//set songposition as fraction of onset of last note
		int minonset = static_cast<NLBSymbol*>(nwseq->getSymbolAt(0))->onset;
		int maxonset = static_cast<NLBSymbol*>(nwseq->getSymbolAt(nwseq->size()-1))->onset;
		int length = maxonset - minonset;
		for (unsigned int ix=0; ix<nwseq->size(); ix++) {
			NLBSymbol * sym = static_cast<NLBSymbol*>(nwseq->getSymbolAt(ix));
			sym->songpos = float((sym->onset)-minonset) / float(length);
		}
	}

	if ( size > 0) {

		//read the normalized pitch40 histogram
		//or create it if it is not present in JSON

		for(int i=0; i<200; i++) {
			nwseq->pitchHistogram[i] = 0.0;
		}
		i1 = seq.begin()->find("pitch40histogram");
		if ( i1 == (seq.begin())->end() ) { //not present
			//cout << "Creating pitch histogram for " << nwseq->getName() << endl;
			// count pitches
			int count = 0;
			for (unsigned int ix=0; ix<nwseq->size(); ix++) {
				int indx = static_cast<NLBSymbol*>(nwseq->getSymbolAt(ix))->pitch40;
				//cout << "index: " << indx << endl;
				if ( indx >= 40 && indx < 240) { nwseq->pitchHistogram[indx - 40] += 1.0; count++; }
			}
			// normalize
			for(int i=0; i<200; i++) {
				nwseq->pitchHistogram[i] = nwseq->pitchHistogram[i] / (double)count;
			}
		} else { //present
			//cout << "Reading pitch histogram for " << nwseq->getName() << endl;
			size = i1->size();
			int pitch = 0;
			for ( int ix=0; ix<size; ix++) {
				pitch = i1->at(ix).at("pitch40").as_int() - 40;
				if (pitch >=0 && pitch < 200 )
					nwseq->pitchHistogram[pitch] = i1->at(ix).at("value").as_float();
			}
		}

		/*
		for(int i=0; i<200; i++) {
			cout << setw(4) << i+40 << " : " << nwseq->pitchHistogram[i] << endl;
		}
		*/

	} // if size > 0

	return nwseq;
}

}
