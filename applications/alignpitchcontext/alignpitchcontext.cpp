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
#include "PCAlignment.h"

int main(int argc, char * argv[]) {

	if ( argc != 3 ) {
		cerr << "Usage: alignpitchcontext <file1.txt> <file2.txt>" << endl;
		exit(1);
	}

	clog << "Reading from: " << argv[1] << " and " << argv[2] << endl;

	musical::PCTXTReader pcr1(argv[1]);
	musical::PCSequence * seq1 = static_cast<musical::PCSequence*>(pcr1.generateSequence());

	musical::PCTXTReader pcr2(argv[2]);
	musical::PCSequence * seq2 = static_cast<musical::PCSequence*>(pcr2.generateSequence());

	// Encapsulate the two sequences in a Sequences object

	musical::PCSequences * seqs = new musical::PCSequences(seq1,seq2);

	seq1->dump_stdout();
	seq2->dump_stdout();

	// Create a similarity rater
	musical::PCSSSimilarityRater * sr = new musical::PCSSSimilarityRater();
	//musical::PCCosSimilarityRater * sr = new musical::PCCosSimilarityRater();
	
	// Create a gap rater
	musical::ConstantAffineGapRater * gr = new musical::ConstantAffineGapRater(-0.8,-0.05);
	
	// Create an alignment algorithm
	musical::AffineGlobalAligner nw = musical::AffineGlobalAligner(seqs, sr, gr);
	
	// Debug
	//nw.setFeedback(true);

	// Do the alignment
	nw.doAlign();

	// Print the alignment to stdout
	musical::AlignmentVisualizer av(seqs);
	av.basicStdoutReport();
	// av.toGnuPlot("alignment-"+seq1->getName()+"-"+seq2->getName());

	double normalizedscore = seqs->getScore() / min(seq1->size(),seq2->size());
	clog << "      Sequence 1: " << seq1->getName() << endl;
	clog << "      Sequence 2: " << seq2->getName() << endl;
	clog << "         Aligner: " << nw.getName() << endl;
	clog << "Similarity Rater: " << sr->getName() << endl;
	clog << "       Gap Rater: " << gr->getName() << endl;
	clog << "  Pitch Rotation: " << seqs->getPitchRotation() << endl;
	clog << "Pitch12 Rotation: " << seqs->getPitch12Rotation() << endl;
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
