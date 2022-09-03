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


#include <cstdlib>

#include <iostream>
#include <iomanip>
using namespace std;

#include "LinearGlobalAligner.h"
#include "ConstantLinearGapRater.h"

namespace musical {

LinearGlobalAligner::LinearGlobalAligner() {
	//s = (NWTrace *)malloc(200*200*sizeof(NWTrace));
	//size_s = 200*200;
	// TODO Auto-generated constructor stub
}

LinearGlobalAligner::LinearGlobalAligner(Sequences * sqs, SimilarityRater * sr, GapRater * gr) : AlignmentAlgorithm(sqs,sr,gr) {
	//s = (NWTrace *)malloc(200*200*sizeof(NWTrace));
	//size_s = 200*200;
}


LinearGlobalAligner::~LinearGlobalAligner() {
	//free(s);
}

void LinearGlobalAligner::doAlign() const {

	//make sure n and m are sizes of sequences.


	//for convenience
	Sequence * seq1 = seqs->getSeq1();
	Sequence * seq2 = seqs->getSeq2();

	if (seq1==NULL || seq2==NULL) {
		std::cerr << "No sequences to align" << std::endl;
		return;
	}

	int n = seq1->size();
	int m = seq2->size();

	if (feedback) {
		cout << "Length sequence 1 : " << n << endl;
		cout << "Length sequence 2 : " << m << endl;
	}

	int mn = n + 1;
	int mm = m + 1; //size of matrix

	//cout << mn << " x " << mm << endl;

	//s = new NWTrace[(mm)*(mn)];

	NWTrace * s = (NWTrace *)malloc(mm*mn*sizeof(NWTrace));

	if (feedback) cout << endl << "size: " << (mm)*(mn)*sizeof(NWTrace) << endl;

	/*
	if ( mm*mn > size_s ) {
		free(s);
		s = (NWTrace *)malloc(mm*mn*sizeof(NWTrace));
		size_s = mm*mn;
		if(feedback) cout << "new allocation for s (" << mm << "x" << mn << "=" << mm*mn << ")";
	}
	*/

	//initialize initial gaps
	s[0*mm+0].ix1 = Trace::NOWHERE;
	s[0*mm+0].ix2 = Trace::NOWHERE;
	s[0*mm+0].accumulatedscore = 0.0;
	s[0*mm+0].thisscore = 0.0;
	for(int k=1; k<mn; k++) {
		s[(k*mm)+0].ix1 = k-1;
		s[(k*mm)+0].ix2 = 0;
		s[(k*mm)+0].accumulatedscore = s[(k-1)*mm+0].accumulatedscore + gapr->getInitializationScore(seqs,k-2,-1,k-1,-1);
		s[(k*mm)+0].thisscore = gapr->getInitializationScore(seqs,k-2,-1,k-1,-1);
	}
	for(int l=1; l<mm; l++) {
		s[0*mm+l].ix1 = 0;
		s[0*mm+l].ix2 = l-1;
		s[0*mm+l].accumulatedscore = s[0*mm+l-1].accumulatedscore + gapr->getInitializationScore(seqs,-1,l-2,-1,l-1);
		s[0*mm+l].thisscore = gapr->getInitializationScore(seqs,-1,l-2,-1,l-1);
	}

	if (feedback) cout << "Initialization done" << endl;

	double substsc = -std::numeric_limits<double>::infinity();
	double gapS1Score = 0.0; //gap in S1
	double gapS2Score = 0.0; //gap in S2

	double S, G1, G2;

	int current_ix;

	//now fill matrix

	for(int k=1; k<mn; k++) {
		for(int l=1; l<mm; l++) {

			if (feedback) clog << "Filling " << k << " , " << l << endl;

			substsc    = simr->getScore(seqs, k-2,l-2,k-1,l-1);
			gapS1Score = gapr->getGapScore(seqs, k-1,l-2,k-1,l-1);
			gapS2Score = gapr->getGapScore(seqs, k-2,l-1,k-1,l-1);

			if ( feedback ) clog << "subst score: " << substsc << endl;
			if ( feedback ) clog << "gapS1 score: " << gapS1Score << endl;
			if ( feedback ) clog << "gapS2 score: " << gapS2Score << endl;

			current_ix = k*mm+l;

			S  = s[(k-1)*mm+(l-1)].accumulatedscore + substsc;
			G1 = s[k*mm+(l-1)].accumulatedscore     + gapS1Score;
			G2 = s[(k-1)*mm+l].accumulatedscore     + gapS2Score;

			if ( feedback ) clog << "acc subst score: " << S << endl;
			if ( feedback ) clog << "acc gapS1 score: " << G1 << endl;
			if ( feedback ) clog << "acc gapS2 score: " << G2 << endl;

			if ( S >= G2 && S >= G1 ) { //substitution
				s[current_ix].ix1 = k-1;
				s[current_ix].ix2 = l-1;
				s[current_ix].accumulatedscore = S;
				s[current_ix].thisscore = substsc;
			} else
			if ( G1 >= G2 && G1 >= S ) { //gap in S1
				s[current_ix].ix1 = k;
				s[current_ix].ix2 = l-1;
				s[current_ix].accumulatedscore = G1;
				s[current_ix].thisscore = gapS1Score;
			} else
			if ( G2 >= S && G2 >= G1 ) { //gap in S2
				s[current_ix].ix1 = k-1;
				s[current_ix].ix2 = l;
				s[current_ix].accumulatedscore = G2;
				s[current_ix].thisscore = gapS2Score;
			}

			//gaps1.ix1 = k  ; gaps1.ix2 = l-1; gaps1.accumulatedscore = s[k*mm+(l-1)].accumulatedscore     + gapscore; gaps1.thisscore = gapscore;
			//gaps2.ix1 = k-1; gaps2.ix2 = l  ; gaps2.accumulatedscore = s[(k-1)*mm+l].accumulatedscore     + gapscore; gaps2.thisscore = gapscore;
			//subst.ix1 = k-1; subst.ix2 = l-1; subst.accumulatedscore = s[(k-1)*mm+(l-1)].accumulatedscore + substsc;  subst.thisscore = substsc;

			//if ( subst.accumulatedscore >= gaps1.accumulatedscore && subst.accumulatedscore >= gaps2.accumulatedscore ) s[k*mm+l] = subst;
			//if ( gaps1.accumulatedscore >= subst.accumulatedscore && gaps1.accumulatedscore >= gaps2.accumulatedscore ) s[k*mm+l] = gaps1;
			//if ( gaps2.accumulatedscore >= gaps1.accumulatedscore && gaps2.accumulatedscore >= subst.accumulatedscore ) s[k*mm+l] = gaps2;
		}
	}


	//debug : print s
	if (feedback) {
		cout << endl;
		for(int k=0; k<mn; k++) {
			for(int l=0; l<mm; l++) {
				//cout << setw(2)<<s[k*mm+l].ix1<<"-"<<setw(2) << s[k*mm+l].ix2 << "  ";
				cout << setw(10)<< s[k*mm+l].accumulatedscore << " ";
			}
			cout << endl;
		}
	}

	double score = s[((mn-1)*mm)+(mm-1)].accumulatedscore;
	if (feedback) cout << "score: " << score << endl;
	seqs->scores.push_back(score);


	//do the trace back:
	//only one alignment needed.
	seqs->alignments.push_back(std::deque<Trace *>());
	seqs->alignments.back().clear();
	int i = mn - 1; //point to final cell
	int j = mm - 1;
	int i_new = 0;
	do {
		s[i*mm+j].this_ix1 = i;
		s[i*mm+j].this_ix2 = j;
		seqs->alignments[0].push_front(new NWTrace(s[i*mm+j]));
		i_new = s[i*mm+j].ix1;
		j = s[i*mm+j].ix2;
		i = i_new;
	} while ( i != 0 || j != 0 ); //endpoint of trace SHOUD be (0,0), but (0,0) should not be in the alignment

	//debug : print trace
	if (feedback) {
		for(unsigned int i=0; i<seqs->alignments[0].size(); i++) {
			cout << seqs->alignments[0][i]->getMatrixThisIx1() << " , " << seqs->alignments[0][i]->getMatrixThisIx2() << " : " << seqs->alignments[0][i]->getAccumulatedscore() << " , " << seqs->alignments[0][i]->getThisscore() << endl;
		}
	}


	//delete [] s;
	free(s);
	//if ( j % 50 == 0 ) cout << "." << flush;
}

}
