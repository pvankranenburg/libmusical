/*
 * MidiFileReader.h
 *
 *  Created on: Sep 28, 2011
 *      Author: pvk
 */

#ifndef MIDIFILEREADER_H_
#define MIDIFILEREADER_H_

#include <Reader.h>
#include "pod_rep.h"
#include <string>

namespace musical {

class MidiFileReader: public musical::Reader {
public:
	MidiFileReader();
	MidiFileReader(std::string fn) : filename(fn) { };
	virtual ~MidiFileReader();


	/**
	 * Returns a pointer to a newly created Sequence, containing a vector of MidiSymbols
	 */
	Sequence * generateSequence() ;


private:
	CSUU_POD::Melody getOPDfromMIDI(std::string filename);
	std::string filename;
};

}

#endif /* MIDIFILEREADER_H_ */
