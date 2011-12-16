/*
 * MidiFileReader.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: pvk
 */

#include "MidiFileReader.h"
#include "MidiSymbol.h"

namespace musical {

MidiFileReader::MidiFileReader() {
	// TODO Auto-generated constructor stub

}

MidiFileReader::~MidiFileReader() {
	// TODO Auto-generated destructor stub
}

Sequence * MidiFileReader::generateSequence() const {
	Sequence * nwseq = new Sequence();

	CSUU_POD::Melody md = getOPDfromMIDI(filename);

	for(unsigned int i=0; i<md.notes.size(); i++) {

		MidiSymbol * s = new MidiSymbol();

		s->pitch12 = md.notes[i].pitch;
		s->onset = md.notes[i].onset;
		s->duration = md.notes[i].duration;

		nwseq->addSymbol(s);

	}

	//set next and previous
	if ( nwseq->size() > 1 ) {
		nwseq->getSymbolAt(0)->setNext(nwseq->getSymbolAt(1));
		nwseq->getSymbolAt(0)->setPrevious(NULL);
		for( unsigned int i = 1; i<nwseq->size()-1; i++) {
			nwseq->getSymbolAt(i)->setPrevious(nwseq->getSymbolAt(i-1));
			nwseq->getSymbolAt(i)->setNext(nwseq->getSymbolAt(i+1));
		}
		nwseq->getSymbolAt(nwseq->size()-1)->setPrevious( nwseq->getSymbolAt(nwseq->size()-2) );
		nwseq->getSymbolAt(nwseq->size()-1)->setNext(NULL);
	}


	return nwseq;
}

} //namespace musical

//declaration
CSUU_POD::Melody pod_melody_from_midi(std::string const &filename);

namespace musical {

CSUU_POD::Melody MidiFileReader::getOPDfromMIDI(const std::string fn) const {
	return pod_melody_from_midi(fn);
}

} //namespace musical
