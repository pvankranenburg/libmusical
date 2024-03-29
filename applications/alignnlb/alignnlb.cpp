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
using namespace std;

#include "libmusical.h"
#include "NLBAlignment.h"

int main(int argc, char * argv[]) {

	if ( argc != 3 ) {
		cerr << "Usage: alignnlb <file1.json> <file2.json>" << endl;
		exit(1);
	}

	clog << "Reading from " << argv[1] << " and " << argv[2] << endl;


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

	seq1->dump_stdout();
	seq2->dump_stdout();

	// Encapsulate the two sequences in a Sequences object
	musical::NLBSequences * seqs = new musical::NLBSequences(seq1,seq2);
	//seqs->setPitch40Shift(seqs->getNthComputedPitch40Shift(0));

	// Create a similarity rater
	//musical::NLBOptiSimilarityRater * sr = new musical::NLBOptiSimilarityRater();
	//musical::NLBPitchbandIMASimilarityRater * sr = new musical::NLBPitchbandIMASimilarityRater();
	//musical::NLBAlwaysOneSimilarityRater * sr = new musical::NLBAlwaysOneSimilarityRater();
	//musical::NLBExactPitch40SimilarityRater * sr = new musical::NLBExactPitch40SimilarityRater();
	musical::NLBExactPitch40IMASimilarityRater * sr = new musical::NLBExactPitch40IMASimilarityRater();

	// Create a gap rater
	//musical::ConstantAffineGapRater * gr = new musical::ConstantAffineGapRater(-0.6,-0.2);
	//musical::NLBIMAAffineGapRater * gr = new musical::NLBIMAAffineGapRater(-0.2);
	musical::ConstantLinearGapRater * gr = new musical::ConstantLinearGapRater(-0.6);

	//gr->setZeroEndGapScore(); // To give end gaps score zero

	// Create an alignment algorithm
	//musical::AffineGlobalAligner nw = musical::AffineGlobalAligner(seqs, sr, gr);
	musical::LinearGlobalAligner nw = musical::LinearGlobalAligner(seqs, sr, gr);
	//musical::LinearLocalAligner nw = musical::LinearLocalAligner(seqs, sr, gr);

	// Debug
	nw.setFeedback(false);

	// Do the alignment
	nw.doAlign();

	// Print the alignment to stdout
	musical::AlignmentVisualizer av(seqs);
	av.basicStdoutReport();
	av.toGnuPlot("alignment-"+seq1->getName()+"-"+seq2->getName());

	double normalizedscore = seqs->getScore() / min(seq1->size(),seq2->size());
	clog << "      Sequence 1: " << seq1->getName() << endl;
	clog << "      Sequence 2: " << seq2->getName() << endl;
	clog << "         Aligner: " << nw.getName() << endl;
	clog << "Similarity Rater: " << sr->getName() << endl;
	clog << "       Gap Rater: " << gr->getName() << endl;
	clog << "   Pitch40 Shift: " << seqs->getPitch40Shift() << endl;
	clog << "   Pitch12 Shift: " << seqs->getPitch12Shift() << endl;
	clog << "           Score: " << seqs->getScore() << endl;
	clog << "Normalized score: " << normalizedscore << endl;
	clog << "        Distance: " << 1.0 - normalizedscore << endl;

	// free memory
	delete seq1;
	delete seq2;
	delete seqs;
	delete gr;
	delete sr;

	return 0;
}
