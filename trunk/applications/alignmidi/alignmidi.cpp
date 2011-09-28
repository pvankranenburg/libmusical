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

	clog << argv[1] << " : " << seq1->symbols.size() << " symbols" << endl;
	clog << argv[2] << " : " << seq2->symbols.size() << " symbols" << endl;

	clog << "Creating aligner" << endl;
	musical::NeedlemanWunsch nw = musical::NeedlemanWunsch(&seqs);

	clog << "Creating similarity rater" << endl;
	nw.simr = new musical::MidiExactPitchIntervalSimilarityRater();

	clog << "Creating gap rater" << endl;
	nw.gapr = new musical::ConstantLinearGapRater(-0.8);

	clog << "Doing the alignment" << endl;
	nw.doAlign();

	double normalizedscore = nw.score / min(seq1->symbols.size(),seq2->symbols.size());
	clog << "Score: " << 1.0 - normalizedscore << endl;

	clog << "Alignment: " << endl;
	for ( unsigned int i = 0; i < nw.alignment.size(); i++ ) {
		clog << setw(3) << nw.alignment[i].this_ix1 << " - " << setw(3) << nw.alignment[i].this_ix2 << setw(7) << nw.alignment[i].thisscore << endl;
	}

	clog << "\nAlignment: " << endl;
	for ( unsigned int i = 0; i < nw.alignment.size(); i++ ) {
		std::string symbol1 = "s1";
		std::string symbol2 = "s2";
		if (nw.alignment[i].this_ix1 == 0 ) symbol1 = "x";
			else if ( i != 0 && nw.alignment[i].this_ix1 == nw.alignment[i-1].this_ix1 ) symbol1 = "x";
				else symbol1 = seq1->symbols[nw.alignment[i].this_ix1-1]->toString();
		if (nw.alignment[i].this_ix2 == 0 ) symbol2 = "x";
			else if ( i != 0 && nw.alignment[i].this_ix2 == nw.alignment[i-1].this_ix2 ) symbol2 = "x";
				else symbol2 = seq2->symbols[nw.alignment[i].this_ix2-1]->toString();
		clog << "[" << symbol1 << "] - [" << symbol2 << "]" << endl;
	}


	return 0;
}
