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
using namespace std;

#include "libmusical.h"
#include "MidiAlignment.h"

int main(int argc, char * argv[]) {

	if ( argc != 3 ) {
		cerr << "Usage: alignmidi <file1.mid> <file2.mid>" << endl;
		cout << endl;
		exit(1);
	}

	clog << "Reading from: " << argv[1] << " " << argv[2] << endl;

	musical::MidiFileReader mfr1 = musical::MidiFileReader(argv[1]);
	musical::MidiFileReader mfr2 = musical::MidiFileReader(argv[2]);

	musical::MidiSequence * seq1 = static_cast<musical::MidiSequence*>(mfr1.generateSequence());
	musical::MidiSequence * seq2 = static_cast<musical::MidiSequence*>(mfr2.generateSequence());
	musical::MidiSequences * seqs = new musical::MidiSequences(seq1,seq2);

	//seq1->dump_stdout();
	//seq2->dump_stdout();

	clog << argv[1] << " : " << seq1->size() << " symbols" << endl;
	clog << argv[2] << " : " << seq2->size() << " symbols" << endl;

	clog << "Creating similarity rater" << endl;
	musical::MidiExactPitchIntervalSimilarityRater * sr = new musical::MidiExactPitchIntervalSimilarityRater();
	musical::MidiPitchDurationSimilarityRater * r2 = new musical::MidiPitchDurationSimilarityRater();
	musical::MidiIORSimilarityRater * ior = new musical::MidiIORSimilarityRater();
	//musical::MidiExactPitchSimilarityRater *ep = new musical::MidiExactPitchSimilarityRater();

	clog << "Creating gap rater" << endl;
	musical::ConstantLinearGapRater * gr =  new musical::ConstantLinearGapRater(-0.5);

	clog << "Creating aligner" << endl;
	musical::LinearGlobalAligner nw = musical::LinearGlobalAligner(seqs, ior, gr);
	//nw.setFeedback(true);

	clog << "Doing the alignment" << endl;
	nw.doAlign();

	musical::AlignmentVisualizer av(seqs);
	//av.basicStdoutReport();

	double normalizedscore = seqs->getScore() / min(seq1->size(),seq2->size());
	//cout << "           Score: " << seqs->getScore() << endl;
	//cout << "Normalized score: " << normalizedscore << endl;
	//cout << "        Distance: " << 1.0 - normalizedscore << endl;

	cout << seq1->getName() << "\t" << seq2->getName() << "\t" << normalizedscore << endl;

	delete seq1;
	delete seq2;
	delete seqs;
	delete sr;
	delete gr;

	return 0;
}
