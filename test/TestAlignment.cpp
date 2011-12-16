/*
 * TestAlignment.cpp
 *
 *  Created on: Dec 14, 2011
 *      Author: pvk
 */

#include "libmusical.h"
#include "TestAlignment.h"

int main(int argc, char * argv[]) {

	//construct sequences
	musical::TestReader t1("881133777872288");
	musical::TestReader t2("228700777711004433");

	musical::Sequence * s1 = t1.generateSequence();
	musical::Sequence * s2 = t2.generateSequence();
	musical::Sequences * seqs = new musical::Sequences(s1,s2);

	// Create a similarity rater
	musical::TestSimilarityRater * sr = new musical::TestSimilarityRater();

	// Create a gap rater
	musical::ConstantLinearGapRater * gr = new musical::ConstantLinearGapRater(-0.3);


	/*
	 * LINEARLOCAL
	 */

	//Construct alignmentalgorithm
	musical::LinearLocalAligner lla(seqs, sr, gr);

	lla.setMaxAlignments(-1);
	lla.setFeedback(false);
	//lla.doAllowOverlappingMatches();
	lla.disallowOverlappingMatches();
	lla.doAlign();

	int no = seqs->getNoOfAlignments();

	cout << "Found: " << no << " linear local alignments."<< endl;

	musical::AlignmentVisualizer av(seqs);
	for (int i=0; i<no; i++) {
		cout << endl << "Linear local alignment " << i << " : " << endl;
		av.basicStdoutReport(i);
	}


	/*
	 * LINEARGLOBAL
	 */

	seqs->clearResults();

	//Construct alignmentalgorithm
	musical::LinearGlobalAligner lga(seqs, sr, gr);
	lga.setFeedback(false);
	lga.doAlign();

	no = seqs->getNoOfAlignments();

	cout << endl << "Found: " << no << " linear global alignments."<< endl;
	musical::AlignmentVisualizer av2(seqs);
	for (int i=0; i<no; i++) {
		cout << endl << "Linear global alignment " << i << " : " << endl;
		av2.basicStdoutReport(i);
	}


	/*
	 * AFFINEGLOBAL
	 */

	seqs->clearResults();

	// Create an affine gap rater
	musical::ConstantAffineGapRater * agr = new musical::ConstantAffineGapRater(-0.5,-0.1);

	musical::AffineGlobalAligner aga(seqs, sr, agr);
	aga.doAlign();

	no = seqs->getNoOfAlignments();

	cout << endl << "Found: " << no << " affine global alignments."<< endl;
	musical::AlignmentVisualizer av3(seqs);
	for (int i=0; i<no; i++) {
		cout << endl << "Affine global alignment " << i << " : " << endl;
		av3.basicStdoutReport(i);
	}

	cout << "END OF TESTS" << endl;

	delete s1;
	delete s2;
	delete seqs;
	delete sr;
	delete gr;

	cout << flush;

	return 0;

}
