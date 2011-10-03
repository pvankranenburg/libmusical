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

Sequence * MidiFileReader::generateSequence() {
	Sequence * nwseq = new Sequence();

	CSUU_POD::Melody md = getOPDfromMIDI(filename);

	for(unsigned int i=0; i<md.notes.size(); i++) {

		MidiSymbol * s = new MidiSymbol();

		s->pitch12 = md.notes[i].pitch;
		s->onset = md.notes[i].onset;
		if ( i < md.notes.size()-1 ) {
			s->duration = md.notes[i+1].onset - md.notes[i].onset;
		} else {
			s->duration = md.notes[i].duration;
		}

		nwseq->addSymbol(s);

		/*
		//add to histogram
		if ( md.notes[i].pitch < 96 )
			mpseq->midiPitchHistogram[md.notes[i].pitch] += duration;
		*/
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


	/*
	//normalize histogram
	double totaldur = 0;
	for(int i=0; i<96; i++) {
		totaldur += mpseq->midiPitchHistogram[i];
	}
	for(int i=0; i<96; i++) {
		mpseq->midiPitchHistogram[i] = mpseq->midiPitchHistogram[i] / totaldur;
		//cout << i << " : " << mpseq->midiPitchHistogram[i] << endl;
	}
	*/

	//Now we can add IMA weights (quantization needed?)
	//

	return nwseq;
}

} //namespace musical

//declaration
CSUU_POD::Melody pod_melody_from_midi(std::string const &filename);

namespace musical {

CSUU_POD::Melody MidiFileReader::getOPDfromMIDI(std::string fn) {
	return pod_melody_from_midi(fn);
}

} //namespace musical
