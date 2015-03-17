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
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include "libmusical.h"
#include "MidiAlignment.h"

int main(int argc, char * argv[]) {

	int pitchshift = 0;
	std::string file1, file2;
	bool pitchshiftprovided = false;

	if ( argc != 3 && argc != 4 ) {
		cerr << "Usage: alignmidi [-p=<pitchshift>] <file1.mid> <file2.mid>" << endl;
		cout << endl;
		exit(1);
	}
	if ( argc == 3 ) {
		file1 = string(argv[1]);
		file2 = string(argv[2]);
	}
	if ( argc == 4 ) {
		pitchshiftprovided = true;
		string sp(argv[1]);
		if ( sp[0] == '-' && sp[1] == 'p') {
			sp = sp.substr(3);
			pitchshift = musical::convertToInt(sp);
		} else {
			cerr << "Usage: alignmidi [-p=<pitchshift>] <file1.mid> <file2.mid>" << endl;
			cout << endl;
			exit(1);
		}
		file1 = string(argv[2]);
		file2 = string(argv[3]);
	}

	if( pitchshiftprovided )
		clog << "Reading from: " << file1 << " " << file2 << ", provided pitchshift is " << pitchshift << endl;
	else
		clog << "Reading from: " << file1 << " " << file2 << endl;


	musical::MidiFileReader mfr1 = musical::MidiFileReader(file1);
	musical::MidiFileReader mfr2 = musical::MidiFileReader(file2);

	musical::MidiSequence * seq1 = static_cast<musical::MidiSequence*>(mfr1.generateSequence());
	musical::MidiSequence * seq2 = static_cast<musical::MidiSequence*>(mfr2.generateSequence());
	musical::MidiSequences * seqs = new musical::MidiSequences(seq1,seq2);

	cout << "===========================================" << endl;
	cout << "Alignment of " << seq1->getName() << " and " << seq2->getName() << endl;

	cout << endl << "SEQUENCE 1 : " << seq1->getName() << endl;
	seq1->dump_stdout();
	cout << endl << "SEQUENCE 2 : " << seq2->getName() << endl;
	seq2->dump_stdout();

	//clog << argv[1] << " : " << seq1->size() << " symbols" << endl;
	//clog << argv[2] << " : " << seq2->size() << " symbols" << endl;

	clog << "Creating similarity rater" << endl;
	musical::MidiExactPitchSimilarityRater * ep = new musical::MidiExactPitchSimilarityRater();
	musical::MidiExactPitchIntervalSimilarityRater * sr = new musical::MidiExactPitchIntervalSimilarityRater();
	musical::MidiIOISimilarityRater * ioi = new musical::MidiIOISimilarityRater();
	musical::MidiIORSimilarityRater * ior = new musical::MidiIORSimilarityRater();
	musical::MidiPitchDurationSimilarityRater * r2 = new musical::MidiPitchDurationSimilarityRater();

	clog << "Creating gap rater" << endl;
	musical::ConstantLinearGapRater * gr =  new musical::ConstantLinearGapRater(-0.5);

	clog << "Creating aligner" << endl;
	musical::LinearGlobalAligner nw = musical::LinearGlobalAligner(seqs, ep, gr);
	//nw.setFeedback(true);

	//pitchshift
	if ( pitchshiftprovided ) {
		seqs->setPitch12Shift(pitchshift);
	}

	cout << endl;
	cout << "Aligner: Needleman-Wunsch" << endl;
	cout << "Similarity Rater: " << "MidiExactPitchSimilarityRater" << endl;
	cout << "Gap score: -0.5" << endl;
	cout << "Pitch shift of second sequence: " << seqs->getPitch12Shift() << endl;

	clog << "Doing the alignment" << endl;
	nw.doAlign();

	musical::AlignmentVisualizer av(seqs);
	cout << endl;
	av.basicStdoutReport();

	double normalizedscore = seqs->getScore() / min(seq1->size(),seq2->size());
	cout << "           Score: " << seqs->getScore() << endl;
	cout << "Normalized score: " << normalizedscore << endl;
	cout << "        Distance: " << 1.0 - normalizedscore << endl;
	cout << endl;

	//cout << seq1->getName() << "\t" << seq2->getName() << "\t" << normalizedscore << endl;

	delete seq1;
	delete seq2;
	delete seqs;
	delete sr;
	delete gr;

	return 0;
}
