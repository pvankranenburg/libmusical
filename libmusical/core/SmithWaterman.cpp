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
#include <cstdlib>
using namespace std;

#include "SmithWaterman.h"
#include "miscfunctions.h"

namespace musical {

SmithWaterman::SmithWaterman() : AlignmentAlgorithm(), maxAlignments(1), allowOverlappingMatches(true) {
	// TODO Auto-generated constructor stub
}

SmithWaterman::~SmithWaterman() {
	// cout << "SOMETHING WRONG HERE?"<< endl;
	// TODO Auto-generated destructor stub
}

void SmithWaterman::doAlign() {

	bool feedback = false;
	bool printmatrix = false;

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

	int mm = m + 1; //size of matrix
	int mn = n + 1;

	//create matrix
	//s = new NWTrace[(mm)*(mn)];
	s = (NWTrace *)malloc(mm*mn*sizeof(NWTrace));

	if (feedback) cout << "s allocated : (" << s << ")" << mm << " x " << mn << " = " << mm*mn << endl;

	//initialize initial gaps

	double gapscore = -0.5; //TODO

	//initialize initial gaps
	s[0*mm+0].ix1 = Trace::NOWHERE;
	s[0*mm+0].ix2 = Trace::NOWHERE;
	s[0*mm+0].accumulatedscore = 0.0;
	s[0*mm+0].thisscore = 0.0;
	if (feedback) cout << "s(0,0) initialized" << endl;
	for(int k=1; k<mn; k++) {
		s[(k*mm)+0].ix1 = Trace::NOWHERE;
		s[(k*mm)+0].ix2 = Trace::NOWHERE;
		s[(k*mm)+0].accumulatedscore = 0.0;
		s[(k*mm)+0].thisscore = 0.0;
	}
	if (feedback) cout << "s(k,0) initialized" << endl;
	for(int l=1; l<mm; l++) {
		s[0*mm+l].ix1 = Trace::NOWHERE;
		s[0*mm+l].ix2 = Trace::NOWHERE;
		s[0*mm+l].accumulatedscore = 0.0;
		s[0*mm+l].thisscore = 0.0;
	}
	if (feedback) cout << "s(0,l) initialized" << endl;
	//initialize ix1 and ix2
	for (int k=1; k<mn; k++) {
		for(int l=1; l<mm; l++) {
			s[k*mm+l].ix1 = Trace::NOWHERE;
			s[k*mm+l].ix2 = Trace::NOWHERE;
		}
	}
	if (feedback) cout << "s initialized" << endl;

	//NWTrace gaps1(Trace::NOWHERE,Trace::NOWHERE,-std::numeric_limits<double>::infinity(),-std::numeric_limits<double>::infinity());
	//NWTrace gaps2(Trace::NOWHERE,Trace::NOWHERE,-std::numeric_limits<double>::infinity(),-std::numeric_limits<double>::infinity());
	//NWTrace subst(Trace::NOWHERE,Trace::NOWHERE,-std::numeric_limits<double>::infinity(),-std::numeric_limits<double>::infinity());
	//NWTrace endpoint(Trace::NOWHERE,Trace::NOWHERE,0.0,-std::numeric_limits<double>::infinity());

	double substsc = 0.0;

	int current_ix = -1;

	double S, G1, G2;

	//For all local alignments:
	if (maxAlignments == -1) maxAlignments = m*n;	// m*n is enough
	while ( alignments.size() < (unsigned int)maxAlignments) {

		// (re)fill matrix
		for(int k=1; k<mn; k++) {
			for(int l=1; l<mm; l++) {

				current_ix = k*mm+l;

				if (s[current_ix].ix1 == Trace::DONTUSE ) { //potential starting point
					s[current_ix].accumulatedscore = 0.0;
					s[current_ix].thisscore = 0.0;
				} else {
					substsc = simr->getScore(seqs,k-2,l-2,k-1,l-1);

					S  = s[(k-1)*mm+(l-1)].accumulatedscore + substsc;
					G1 = s[(k-1)*mm+l].accumulatedscore     + gapscore;
					G2 = s[k*mm+(l-1)].accumulatedscore     + gapscore;

					if ( S >= G1 && S >= G2 && S > 0.0) { //substitution
						s[current_ix].ix1 = k-1;
						s[current_ix].ix2 = l-1;
						s[current_ix].accumulatedscore = S;
						s[current_ix].thisscore = substsc;
					} else
					if ( G1 >= S && G1 >= G2 && G1 > 0.0) { //gap
						s[current_ix].ix1 = k-1;
						s[current_ix].ix2 = l;
						s[current_ix].accumulatedscore = G1;
						s[current_ix].thisscore = gapscore;
					} else
					if ( G2 >= G1 && G2 >= S && G2 > 0.0) { //gap
						s[current_ix].ix1 = k;
						s[current_ix].ix2 = l-1;
						s[current_ix].accumulatedscore = G2;
						s[current_ix].thisscore = gapscore;
					} else { //endpoint
						s[current_ix].ix1 = Trace::NOWHERE;
						s[current_ix].ix2 = Trace::NOWHERE;
						s[current_ix].accumulatedscore = -std::numeric_limits<double>::infinity();
						s[current_ix].thisscore = -std::numeric_limits<double>::infinity();
					}
				}


				//gaps1.ix1 = k  ; gaps1.ix2 = l-1; gaps1.accumulatedscore = s[k*mm+(l-1)].accumulatedscore     + gapscore;
				//gaps2.ix1 = k-1; gaps2.ix2 = l  ; gaps2.accumulatedscore = s[(k-1)*mm+l].accumulatedscore     + gapscore;
				//subst.ix1 = k-1; subst.ix2 = l-1; subst.accumulatedscore = s[(k-1)*mm+(l-1)].accumulatedscore + substsc;

				//if ( subst.accumulatedscore >= gaps1.accumulatedscore && subst.accumulatedscore >= gaps2.accumulatedscore && subst.accumulatedscore > 0.0 ) s[k*mm+l] = subst;
				//if ( gaps1.accumulatedscore >= subst.accumulatedscore && gaps1.accumulatedscore >= gaps2.accumulatedscore && gaps1.accumulatedscore > 0.0 ) s[k*mm+l] = gaps1;
				//if ( gaps2.accumulatedscore >= gaps1.accumulatedscore && gaps2.accumulatedscore >= subst.accumulatedscore && gaps2.accumulatedscore > 0.0 ) s[k*mm+l] = gaps2;
				//if ( fmax( fmax(subst.accumulatedscore, gaps1.accumulatedscore), gaps2.accumulatedscore ) <= 0.0 ) s[k*mm+l] = endpoint;

			}
		}
		if (feedback) cout << "matrix filled" << endl;


		//print s
		if (printmatrix) {
			cout << endl;
			for(int k=0; k<mn; k++) {
				for(int l=0; l<mm; l++) {
					//cout << setw(2)<<s[k*m+l].ix1<<"-"<<setw(2) << s[k*m+l].ix2 << "  ";
					cout << setw(6)<< s[k*mm+l].accumulatedscore;
				}
				cout << endl;
			}
		}


		//find maximum score = starting point of local alignment
		int max_k = -1;
		int max_l = -1;
		double maxscore = -std::numeric_limits<double>::infinity();
		for(int k=0; k<mn; k++) {
			for(int l=0; l<mm; l++) {
				if ( s[k*mm+l].accumulatedscore > maxscore ) {
					maxscore = s[k*mm+l].accumulatedscore;
					if (maxscore > 0) {
						max_k = k;
						max_l = l;
					}
				}
			}
		}
		if ( max_k == -1 || max_l == -1 ) { break; } //apparently there are no local aligments => break out loop

		if (feedback) cout << "maximum found: " << max_k << " , " << max_l << endl;

		//trace back
		//add new alignment to alignments
		alignments.push_back(std::deque<Trace *>());
		alignments.back().clear();

		int i = max_k; //point to final cell
		int j = max_l;
		int i_new = 0;
		do {
			s[i*mm+j].this_ix1 = i;
			s[i*mm+j].this_ix2 = j;
			alignments.back().push_front(new NWTrace(s[i*mm+j]));
			i_new = s[i*mm+j].ix1;
			j = s[i*mm+j].ix2;
			i = i_new;
			if (feedback) cout << "to: " << i << " , " << j << endl;
		} while ( s[i*mm+j].accumulatedscore > 0.0 ); //endpoint of trace should not be in the alignment

		if (feedback) cout << "trace back completed" << endl;

		if (feedback) { //print trace
			for(unsigned int i = 0; i < alignments.back().size(); i++) {
				cout << alignments.back()[i]->getIx1() << " , " << alignments.back()[i]->getIx2() << " : "
					 << alignments.back()[i]->getAccumulatedscore() << " : " << alignments.back()[i]->getThisscore() << endl;
			}
		}

		//clear trace
		for(unsigned int i = 0; i < alignments.back().size(); i++) {
			int ix1 = alignments.back()[i]->getMatrixThisIx1();
			int ix2 = alignments.back()[i]->getMatrixThisIx2();
			s[ix1*mm+ix2].ix1 = Trace::DONTUSE;
			s[ix1*mm+ix2].ix2 = Trace::DONTUSE;
		}

		if (feedback) cout << "trace cleared" << endl;


		//disable symbols belonging to the local alignment (if desired).
		if ( !allowOverlappingMatches ) {
			int ix1_start = alignments.back().front()->getMatrixThisIx1();
			int ix2_start = alignments.back().front()->getMatrixThisIx2();
			int ix1_end   = alignments.back().back()->getMatrixThisIx1();
			int ix2_end   = alignments.back().back()->getMatrixThisIx1();

			for(int k=ix1_start; k<=ix1_end; k++)
				for(int l=ix2_start; l<=ix2_end; l++) {
					s[k*mm+l].ix1 = Trace::DONTUSE;
					s[k*mm+l].ix2 = Trace::DONTUSE;
				}
		}

		if (feedback) cout << "block cleared" << endl;

	}

	if (feedback) cout << "ready with " << alignments.size() <<  " alignment(s)" << endl;

	//get rid of matrix
	free(s);
	if (feedback) cout << "s freed" << endl;

}

}