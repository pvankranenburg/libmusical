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
		exit(1);
	}

	clog << "Reading from" << argv[1] << " and " << argv[2] << endl;

	musical::MidiFileReader mfr1 = musical::MidiFileReader(argv[1]);
	musical::MidiFileReader mfr2 = musical::MidiFileReader(argv[2]);

	musical::Sequence * seq1 = mfr1.generateSequence();
	musical::Sequence * seq2 = mfr2.generateSequence();
	musical::Sequences seqs = musical::Sequences(seq1,seq2);

	//seq1->dump_stdout();
	//seq2->dump_stdout();

	clog << argv[1] << " : " << seq1->size() << " symbols" << endl;
	clog << argv[2] << " : " << seq2->size() << " symbols" << endl;

	clog << "Creating similarity rater" << endl;
	musical::MidiExactPitchIntervalSimilarityRater * sr = new musical::MidiExactPitchIntervalSimilarityRater();

	clog << "Creating gap rater" << endl;
	musical::ConstantLinearGapRater * gr =  new musical::ConstantLinearGapRater(-0.8);

	clog << "Creating aligner" << endl;
	musical::LinearGlobalAligner nw = musical::LinearGlobalAligner(&seqs, sr, gr);

	clog << "Doing the alignment" << endl;
	nw.doAlign();

	double normalizedscore = seqs.getScore() / min(seq1->size(),seq2->size());
	clog << "Score: " << 1.0 - normalizedscore << endl;

	musical::AlignmentVisualizer av(&seqs);
	av.basicStdoutReport();

	return 0;
}
