/*
 * MidiFileReader.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: pvk
 */

#include "MidiFileReader.h"
#include "MidiSymbol.h"
#include "MidiSequence.h"
#include "MetroWeights_Mazzola.h"


#include <vector>
#include <iomanip>
using namespace std;

namespace musical {

MidiFileReader::MidiFileReader() {
	// TODO Auto-generated constructor stub

}

MidiFileReader::~MidiFileReader() {
	// TODO Auto-generated destructor stub
}

Sequence * MidiFileReader::generateSequence() const {
	MidiSequence * nwseq = new MidiSequence(); //NB MidiSequence contains a pitch histogram

	//check whether file exists


	CSUU_POD::Melody md = getOPDfromMIDI(filename);

	string name = filename.substr(filename.find_last_of("/")+1);
	nwseq->setName(name);

	for(unsigned int i=0; i<md.notes.size(); i++) {

		MidiSymbol * s = new MidiSymbol();

		s->pitch12 = md.notes[i].pitch;
		s->onset = md.notes[i].onset;
		s->duration = md.notes[i].duration;

		nwseq->addSymbol(s);

	}

	//set next and previous
	if ( nwseq->size() >= 1 ) {
		if ( nwseq->size() ==1 ) {
			nwseq->getSymbolAt(0)->setNext(NULL);
			nwseq->getSymbolAt(0)->setPrevious(NULL);
		} else {
			nwseq->getSymbolAt(0)->setNext(nwseq->getSymbolAt(1));
			nwseq->getSymbolAt(0)->setPrevious(NULL);
			for( unsigned int i = 1; i<nwseq->size()-1; i++) {
				nwseq->getSymbolAt(i)->setPrevious(nwseq->getSymbolAt(i-1));
				nwseq->getSymbolAt(i)->setNext(nwseq->getSymbolAt(i+1));
			}
			nwseq->getSymbolAt(nwseq->size()-1)->setPrevious( nwseq->getSymbolAt(nwseq->size()-2) );
			nwseq->getSymbolAt(nwseq->size()-1)->setNext(NULL);
		}
	}

	//compute ima weights
	//first make vector of onsets:
	//clog << "Computing IMA weights" << endl;
	/*
	vector<int> onsets;
	onsets.clear();
	for ( int i=0; i<nwseq->size(); i++) {
		onsets.push_back((static_cast<MidiSymbol *>(nwseq->getSymbolAt(i)))->onset);
	}
	MetroWeights_Mazzola mw(2,2,0,1);
	WeightSet weights = mw.getWeights(onsets);
	*/

	/*
	cout << "maximal local meters: " << endl;
	weights.meterCollection.printAll();
	for (int i=0; i<weights.spectralWeight.size(); i++) {
	    cout << weights.spectralWeight[i] << " ";
	}
	cout << endl;
	for (int i=0; i<weights.weights.size(); i++) {
	    cout << weights.weights[i] << " ";
	}
	cout << endl;
	*/

	/*
	int maxw = 0;
	for(int i=0; i<weights.weights.size(); i++)
		if ( weights.weights[i] > maxw ) maxw = weights.weights[i];
	//if all weights are zero
	if ( maxw == 0 ) maxw = 1;
	for(int i=0; i<onsets.size(); i++) {
		//clog << "(double)weights.weights[i]: " << (double)weights.weights[i] << endl;
		(static_cast<MidiSymbol *>(nwseq->getSymbolAt(i)))->ima = (double)weights.weights[i] / (double)maxw;
	}
	*/

	//build pitch histogram
	//clog << "Building pitch histogram" << endl;
	for (int i=0; i<120; i++) {
		nwseq->pitchHistogram[i] = 0.0;
	}
	int countpitches = 0;
	for ( int i=0; i<nwseq->size(); i++) {
		nwseq->pitchHistogram[(static_cast<MidiSymbol *>(nwseq->getSymbolAt(i)))->pitch12] += 1.0;
		countpitches++;
	}
	//normalize histogram
	for ( int i=0; i<120; i++) {
		nwseq->pitchHistogram[i] = nwseq->pitchHistogram[i] / (double)countpitches;
	}
	//print pitchhistogram
	//clog << "Pitchhistogram: " << endl;
	//for ( int i=0; i<120; i++) {
	//	clog << setw(3) << i << " : " << nwseq->pitchHistogram[i] << endl;
	//}


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
