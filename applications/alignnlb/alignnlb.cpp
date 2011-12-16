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
using namespace std;

#include "libmusical.h"
#include "NLBAlignment.h"

int main(int argc, char * argv[]) {

	if ( argc != 3 ) {
		cerr << "Usage: alignnlb <file1.json> <file2.json>" << endl;
		exit(1);
	}

	clog << "Reading from" << argv[1] << " and " << argv[2] << endl;


	// Get a JSON string for sequence 1 from a file
	// Create a Reader object for the JSON string
	musical::NLBJSONReader mr1(new musical::JSONFileSource(argv[1]));

	// Ask the Reader to generate the Sequence
	musical::NLBSequence * seq1 =
		static_cast<musical::NLBSequence*>(mr1.generateSequence());

	// Do the same for sequence 2
	musical::NLBJSONReader mr2(new musical::JSONFileSource(argv[2]));
	musical::NLBSequence * seq2 =
		static_cast<musical::NLBSequence*>(mr2.generateSequence());

	// Encapsulate the two sequences in a Sequences object
	musical::NLBSequences * seqs = new musical::NLBSequences(seq1,seq2);

	// Create a similarity rater
	musical::NLBOptiSimilarityRater * sr = new musical::NLBOptiSimilarityRater();

	// Create a gap rater
	musical::ConstantAffineGapRater * gr = new musical::ConstantAffineGapRater(-0.6,-0.2);

	// Create an alignment algorithm
	musical::AffineGlobalAligner nw = musical::AffineGlobalAligner(seqs, sr, gr);

	// Debug
	nw.setFeedback(true);

	// Do the alignment
	nw.doAlign();

	// Print the score
	cout << "Score:" << seqs->getScore() << endl;

	// Print the alignment to stdout
	musical::AlignmentVisualizer av(seqs);
	av.basicStdoutReport();

	// free memory
	delete seq1;
	delete seq2;
	delete seqs;
	delete gr;
	delete sr;

	return 0;
}
