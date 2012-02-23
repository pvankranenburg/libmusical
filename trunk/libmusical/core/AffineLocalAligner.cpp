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

#include "AffineLocalAligner.h"
#include <cmath>
#include <iomanip>
using namespace std;

namespace musical {

AffineLocalAligner::AffineLocalAligner()  : AlignmentAlgorithm(), maxAlignments(1), allowOverlappingMatches(true), threshold(0.0) {
	// TODO Auto-generated constructor stub

}

AffineLocalAligner::~AffineLocalAligner() {
	// TODO Auto-generated destructor stub
}

void AffineLocalAligner::doAlign() const {

	cerr << "Warning: LocalAffineAligner not fully implemented!" << endl;

	if (feedback) cout << "start alignment" << endl;

	//for convenience
	Sequence * seq1 = seqs->getSeq1();
	Sequence * seq2 = seqs->getSeq2();

	if (seq1==NULL || seq2==NULL) {
		std::cerr << "No sequences to align" << std::endl;
		return;
	}

	int n = seq1->size();
	int m = seq2->size();

	int mm = m + 1; //size of matrices
	int mn = n + 1;

	//cout << mn << " x " << mm << endl;

	//s = new NWGTrace[(mm)*(mn)];
	//g1 = new NWGTrace[(mm)*(mn)];
	//g2 = new NWGTrace[(mm)*(mn)];

	NWGTrace * s = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));
	NWGTrace * g1 = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));
	NWGTrace * g2 = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));

	/*
	if ( mm*mn > size_s ) {
		if(feedback) cout << "new allocation needed for s, g1, and g2 (" << mm << "x" << mn << "=" << mm*mn << ")" << flush;
		free(s);
		free(g1);
		free(g2);
		s = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));
		g1 = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));
		g2 = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));
		size_s = mm*mn;
		if(feedback) cout << "new allocation made for s, g1, and g2 (" << mm << "x" << mn << "=" << mm*mn << ")" << flush;
	}
	*/


	//initialize initial gaps

	// For initial gaps, we only use s, not g1 and g2!
	// Then the standard gapr->getInitializationScore(...) can be used, and the gap score can be made context dependent.

	// (0,0) : origin. endpoint alignment
	s[0*mm+0].ix1 = Trace::NOWHERE;
	s[0*mm+0].ix2 = Trace::NOWHERE;
	s[0*mm+0].state = NWGTrace::NONE; //endpoint
	s[0*mm+0].accumulatedscore = 0.0;
	s[0*mm+0].thisscore = 0.0;

	// g1(0,0) -- never to be reached
	g1[0*mm+0].ix1 = Trace::NOWHERE;
	g1[0*mm+0].ix2 = Trace::NOWHERE;
	g1[0*mm+0].state = NWGTrace::NONE;
	g1[0*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
	g1[0*mm+0].thisscore = 0.0;

	// g2(0,0) -- never to be reached
	g2[0*mm+0].ix1 = Trace::NOWHERE;
	g2[0*mm+0].ix2 = Trace::NOWHERE;
	g2[0*mm+0].state = NWGTrace::NONE;
	g2[0*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
	g2[0*mm+0].thisscore = 0.0;


	//initialize begin-gap *with* seq2 -- index in seq2 (l) remains same, namely -1
	// - - - - S S
	// S S S S S S

	for(int k=1; k<mn; k++) {
		s[k*mm+0].ix1 = Trace::NOWHERE;
		s[k*mm+0].ix2 = Trace::NOWHERE;
		s[k*mm+0].state = NWGTrace::NONE;
		s[k*mm+0].accumulatedscore = 0.0;
		s[k*mm+0].thisscore = 0.0;

		g1[k*mm+0].ix1 = Trace::NOWHERE;
		g1[k*mm+0].ix2 = Trace::NOWHERE;
		g1[k*mm+0].state = NWGTrace::NONE;
		g1[k*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
		g1[k*mm+0].thisscore = - 0.0;

		g2[k*mm+0].ix1 = Trace::NOWHERE;
		g2[k*mm+0].ix2 = Trace::NOWHERE;
		g2[k*mm+0].state = NWGTrace::NONE;
		g2[k*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
		g2[k*mm+0].thisscore = 0.0;
	}


	//initialize begin-gap *with* seq1 -- index in seq1 (k) remains same, namely -1
	// S S S S S S
	// - - - - S S
	// For local alignment, initial gaps are endpoints

	for(int l=1; l<mm; l++) {
		s[0*mm+l].ix1 = Trace::NOWHERE;
		s[0*mm+l].ix2 = Trace::NOWHERE;
		s[0*mm+l].state = NWGTrace::NONE;
		s[0*mm+l].accumulatedscore = 0.0;
		s[0*mm+l].thisscore = 0.0;

		g1[0*mm+l].ix1 = Trace::NOWHERE;
		g1[0*mm+l].ix2 = Trace::NOWHERE;
		g1[0*mm+l].state = NWGTrace::NONE;
		g1[0*mm+l].accumulatedscore = -std::numeric_limits<double>::infinity();
		g1[0*mm+l].thisscore = 0.0;

		g2[0*mm+l].ix1 = Trace::NOWHERE;
		g2[0*mm+l].ix2 = Trace::NOWHERE;
		g2[0*mm+l].state = NWGTrace::NONE;
		g2[0*mm+l].accumulatedscore = -std::numeric_limits<double>::infinity();
		g2[0*mm+l].thisscore = 0.0;
	}

	if (feedback) cout << "Initialization done" << endl;

	double substsc = -std::numeric_limits<double>::infinity();
	double g1openingscore = -std::numeric_limits<double>::infinity();
	double g2openingscore = -std::numeric_limits<double>::infinity();
	double g1extensionscore = -std::numeric_limits<double>::infinity();
	double g2extensionscore = -std::numeric_limits<double>::infinity();

	double S_S, G1_S, G2_S, S_G1, G1_G1, G2_G1, S_G2, G1_G2, G2_G2;

	int current_ix = 0;

	//For all local alignments:
	int useMaxAlignments = maxAlignments;
	if (maxAlignments == -1) useMaxAlignments = m*n;	// m*n is more than enough
	while ( seqs->alignments.size() < (unsigned int)useMaxAlignments) {

		//now (re)fill matrix
		for(int k=1; k<mn; k++) {
			for(int l=1; l<mm; l++) {

				current_ix = k*mm+l;


				if (s[current_ix].ix1 == Trace::DONTUSE ) { //potential starting point
					s[current_ix].accumulatedscore = 0.0;
					s[current_ix].thisscore = 0.0;
				}
				else if (g1[current_ix].ix1 == Trace::DONTUSE ) {
					g1[current_ix].accumulatedscore = -numeric_limits<double>::infinity();;
					g1[current_ix].thisscore = 0.0;
				}
				else if (g2[current_ix].ix1 == Trace::DONTUSE ) {
					g2[current_ix].accumulatedscore = -numeric_limits<double>::infinity();;
					g2[current_ix].thisscore = 0.0;
				} else {

					//substitution score
					substsc = simr->getScore(seqs,k-2,l-2,k-1,l-1);

					//scores for gap *with* seq1 -- index in seq1 (k) remains same
					g1openingscore = static_cast<AffineGapRater *>(gapr)->getGapOpeningScore(seqs, k-1 , l-2 , k-1, l-1 );
					g2openingscore = static_cast<AffineGapRater *>(gapr)->getGapOpeningScore(seqs, k-1 , l-2 , k-1, l-1 );

					//scores for gap *with* seq2 -- index in seq2 (l) remains same
					g1extensionscore = static_cast<AffineGapRater *>(gapr)->getGapExtensionScore(seqs, k-2 , l-1 , k-1, l-1 );
					g2extensionscore = static_cast<AffineGapRater *>(gapr)->getGapExtensionScore(seqs, k-2 , l-1 , k-1, l-1 );

					if (feedback) cout << "[" << k << "," << l << "]: " << substsc << " " << g1openingscore << " " << g1extensionscore << " " << g2openingscore << " " << g2extensionscore << endl;

					//substitution
					S_S   =  s[(k-1)*mm+(l-1)].accumulatedscore + substsc;
					G1_S  = g1[(k-1)*mm+(l-1)].accumulatedscore + substsc;
					G2_S  = g2[(k-1)*mm+(l-1)].accumulatedscore + substsc;

					//gap *with* symbol from seq1 -- seq2 (l) keeps index
					S_G1  =  s[(k-1)*mm+l].accumulatedscore + g1openingscore;
					G1_G1 = g1[(k-1)*mm+l].accumulatedscore + g1extensionscore;
					G2_G1 = g2[(k-1)*mm+l].accumulatedscore + g1openingscore; //consider this a gap opening

					//gap *with* symbol from seq2 -- seq1 keeps index
					S_G2  =  s[k*mm+(l-1)].accumulatedscore + g2openingscore;
					G1_G2 = g1[k*mm+(l-1)].accumulatedscore + g2openingscore; //consider this a gap opening
					G2_G2 = g2[k*mm+(l-1)].accumulatedscore + g2extensionscore;


					 s[current_ix].accumulatedscore = fmax ( fmax (  S_S,  G1_S ), fmax ( G2_S, 0.0 ) );
					g1[current_ix].accumulatedscore = fmax ( fmax ( S_G1, G1_G1 ), fmax ( G2_G1, 0.0 ) );
					g2[current_ix].accumulatedscore = fmax ( fmax ( S_G2, G1_G2 ), fmax ( G2_G2, 0.0 ) );

					//fill trace

					//substitution
					if (s[current_ix].accumulatedscore == S_S && S_S > 0.0 ) {
						s[current_ix].ix1 = k-1;
						s[current_ix].ix2 = l-1;
						s[current_ix].state = NWGTrace::S;
						s[current_ix].thisscore = substsc;
					}
					else if (s[current_ix].accumulatedscore == G1_S && G1_S > 0.0 ) {
						s[current_ix].ix1 = k-1;
						s[current_ix].ix2 = l-1;
						s[current_ix].state = NWGTrace::G1;
						s[current_ix].thisscore = substsc;
					}
					else if (s[current_ix].accumulatedscore == G2_S && G2_S > 0.0 ) {
						s[current_ix].ix1 = k-1;
						s[current_ix].ix2 = l-1;
						s[current_ix].state = NWGTrace::G2;
						s[current_ix].thisscore = substsc;
					}
					else { //endpoint
						s[current_ix].ix1 = NWGTrace::NOWHERE;
						s[current_ix].ix2 = NWGTrace::NOWHERE;
						s[current_ix].state = NWGTrace::NONE;
						s[current_ix].thisscore = 0.0;
					}

					//if ( k==1 && l==1 ) cout << s[current_ix].ix1 << endl;
					//if ( k==1 && l==1 ) cout << s[current_ix].ix2 << endl;
					//if ( k==1 && l==1 ) cout << s[current_ix].state << endl;


					//gap with seq1
					if (g1[current_ix].accumulatedscore == G1_G1 && G1_G1 > 0.0 ) {
						g1[current_ix].ix1 = k-1;
						g1[current_ix].ix2 = l;
						g1[current_ix].state = NWGTrace::G1;
						g1[current_ix].thisscore = g1extensionscore;
					}
					else if (g1[current_ix].accumulatedscore == G2_G1 && G1_G1 > 0.0 ) {
						g1[current_ix].ix1 = k-1;
						g1[current_ix].ix2 = l;
						g1[current_ix].state = NWGTrace::G2;
						g1[current_ix].thisscore = g1openingscore;
					}
					else if (g1[current_ix].accumulatedscore == S_G1 && S_G1 > 0.0 ) {
						g1[current_ix].ix1 = k-1;
						g1[current_ix].ix2 = l;
						g1[current_ix].state = NWGTrace::S;
						g1[current_ix].thisscore = g1openingscore;
					}
					else { //endpoint
						g1[current_ix].ix1 = NWGTrace::NOWHERE;
						g1[current_ix].ix2 = NWGTrace::NOWHERE;
						g1[current_ix].state = NWGTrace::NONE;
						g1[current_ix].thisscore = 0.0;
					}

					//gap with seq2
					if (g2[current_ix].accumulatedscore == G1_G2 && G1_G2 > 0.0 ) {
						g2[current_ix].ix1 = k;
						g2[current_ix].ix2 = l-1;
						g2[current_ix].state = NWGTrace::G1;
						g2[current_ix].thisscore = g2openingscore;
					}
					else if (g2[current_ix].accumulatedscore == G2_G2 && G2_G2 > 0.0 ) {
						g2[current_ix].ix1 = k;
						g2[current_ix].ix2 = l-1;
						g2[current_ix].state = NWGTrace::G2;
						g2[current_ix].thisscore = g2extensionscore;
					}
					else if (g2[current_ix].accumulatedscore == S_G2 && S_G2 > 0.0 ) {
						g2[current_ix].ix1 = k;
						g2[current_ix].ix2 = l-1;
						g2[current_ix].state = NWGTrace::S;
						g2[current_ix].thisscore = g2openingscore;
					}
					else {
						g2[current_ix].ix1 = NWGTrace::NOWHERE;
						g2[current_ix].ix2 = NWGTrace::NOWHERE;
						g2[current_ix].state = NWGTrace::NONE;
						g2[current_ix].thisscore = 0.0;
					}

				}
			}
		}

		if (feedback) {
			//print s
			cout << endl;
			for(int k=0; k<mn; k++) {
				for(int l=0; l<mm; l++) {
					//cout << setw(2)<<s[k*mm+l].ix1<<"-"<<setw(2) << s[k*mm+l].ix2 << ":" << setw(5) << setprecision(2) << s[k*mm+l].accumulatedscore << "  ";
					//cout << setw(3)<< s[k*mm+l].state;
					cout << setw(6) << setprecision(2) << s[k*mm+l].accumulatedscore << " ";
				}
				cout << endl;
			}
			//print g1
			cout << endl;
			for(int k=0; k<mn; k++) {
				for(int l=0; l<mm; l++) {
					//cout << setw(2)<<g1[k*mm+l].ix1<<"-"<<setw(2) << g1[k*mm+l].ix2 << ":" << setw(5) << setprecision(2) << g1[k*mm+l].accumulatedscore << "  ";
					//cout << setw(3)<< s[k*mm+l].state;
					cout << setw(6) << setprecision(2) << g1[k*mm+l].accumulatedscore << " ";
				}
				cout << endl;
			}
			//print g2
			cout << endl;
			for(int k=0; k<mn; k++) {
				for(int l=0; l<mm; l++) {
					//cout << setw(2)<<g2[k*mm+l].ix1<<"-"<<setw(2) << g2[k*mm+l].ix2 << ":" << setw(5) << setprecision(2) << g2[k*mm+l].accumulatedscore << "  ";
					//cout << setw(3)<< s[k*mm+l].state;
					cout << setw(6) << setprecision(2) << g2[k*mm+l].accumulatedscore << " ";
				}
				cout << endl;
			}
		}


		//find score and do the trace back:
		//add one alignment to alignments
		seqs->alignments.push_back(std::deque<Trace *>());
		seqs->alignments.back().clear();

		//find maximum score = starting point of local alignment

		int max_k = -1;
		int max_l = -1;
		NWGTrace::State state = NWGTrace::NONE;

		double maxscore = -std::numeric_limits<double>::infinity();
		for(int k=0; k<mn; k++) {
			for(int l=0; l<mm; l++) {
				if ( s[k*mm+l].accumulatedscore > maxscore ) {
					maxscore = s[k*mm+l].accumulatedscore;
					if (maxscore > 0) {
						max_k = k;
						max_l = l;
						state = NWGTrace::S;
					}
				}
				if ( g1[k*mm+l].accumulatedscore > maxscore ) {
					maxscore = g1[k*mm+l].accumulatedscore;
					if (maxscore > 0) {
						max_k = k;
						max_l = l;
						state = NWGTrace::G1;
					}
				}
				if ( g2[k*mm+l].accumulatedscore > maxscore ) {
					maxscore = g2[k*mm+l].accumulatedscore;
					if (maxscore > 0) {
						max_k = k;
						max_l = l;
						state = NWGTrace::G2;
					}
				}
			}
		}
		if ( max_k == -1 || max_l == -1 ) { break; } //apparently there are no local aligments => break out loop

		if (feedback) cout << "maximum found: " << maxscore << " at " << max_k << " , " << max_l << "For state " << state << endl;

		int i = max_k; //mapping
		int j = max_l;

		//NB order of this matters
		//if e.g. max score in s equals max score in g1, last one is chosen
		double score = -std::numeric_limits<double>::infinity();
		//start with s?
		if ( state == NWGTrace::S  ) {
			if (feedback) cout << "in S (" << i << "," << j << "), to : ";
			score = s[(n*mm)+mm-1].accumulatedscore;
			seqs->scores.push_back(score);
			s[(n*mm)+mm-1].this_ix1 = i;
			s[(n*mm)+mm-1].this_ix2 = j;
			seqs->alignments[0].push_front(new NWGTrace(s[(n*mm)+mm-1])); //last alignment
			//point to (i,j) in matrix state.
			i = s[(n*mm)+mm-1].ix1;
			j = s[(n*mm)+mm-1].ix2;
			state = s[(n*mm)+mm-1].state;
		} else  //start with g1?
		if ( state == NWGTrace::G1  ) {
			if (feedback) cout << "in G1 (" << i << "," << j << "), to : ";
			score = g1[(n*mm)+mm-1].accumulatedscore;
			seqs->scores.push_back(score);
			g1[(n*mm)+mm-1].this_ix1 = i;
			g1[(n*mm)+mm-1].this_ix2 = j;
			seqs->alignments[0].push_front(new NWGTrace(g1[(n*mm)+mm-1])); //last alignment
			//point to (i,j) in matrix state.
			i = g1[(n*mm)+mm-1].ix1;
			j = g1[(n*mm)+mm-1].ix2;
			state = g1[(n*mm)+mm-1].state;
		} else
		//start with g2?
		if ( state == NWGTrace::G2  ) {
			if (feedback) cout << "in G2 (" << i << "," << j << "), to : ";
			score = g2[(n*mm)+mm-1].accumulatedscore;
			seqs->scores.push_back(score);
			g2[(n*mm)+mm-1].this_ix1 = i;
			g2[(n*mm)+mm-1].this_ix2 = j;
			seqs->alignments[0].push_front(new NWGTrace(g2[(n*mm)+mm-1])); //last alignment
			//point to (i,j) in matrix state.
			i = g2[(n*mm)+mm-1].ix1;
			j = g2[(n*mm)+mm-1].ix2;
			state = g2[(n*mm)+mm-1].state;
		}

		if (feedback) cout << i << " , " << j << ": " << state << endl;

		//do the rest of the trace back
		int i_new = 0;
		do {
			if (state == NWGTrace::S) {
				if (feedback) cout << "in S (" << i << "," << j << "), to : ";
				s[i*mm+j].this_ix1 = i;
				s[i*mm+j].this_ix2 = j;
				seqs->alignments[0].push_front(new NWGTrace(s[i*mm+j]));
				state = s[i*mm+j].state;
				i_new = s[i*mm+j].ix1;
				j = s[i*mm+j].ix2;
				i = i_new;
			}
			else if (state == NWGTrace::G1 ) {
				if (feedback) cout << "in G1 (" << i << "," << j << "), to : ";
				g1[i*mm+j].this_ix1 = i;
				g1[i*mm+j].this_ix2 = j;
				seqs->alignments[0].push_front(new NWGTrace(g1[i*mm+j]));
				state = g1[i*mm+j].state;
				i_new = g1[i*mm+j].ix1;
				j = g1[i*mm+j].ix2;
				i = i_new;
			}
			else if (state == NWGTrace::G2 ) {
				if (feedback) cout << "in G2 (" << i << "," << j << "), to : ";
				g2[i*mm+j].this_ix1 = i;
				g2[i*mm+j].this_ix2 = j;
				seqs->alignments[0].push_front(new NWGTrace(g2[i*mm+j]));
				state = g2[i*mm+j].state;
				i_new = g2[i*mm+j].ix1;
				j = g2[i*mm+j].ix2;
				i = i_new;
			}
			else if ( state == NWGTrace::NONE ) { //end
				break;
			}
			else {
				cerr << "THIS SHOULD NOT HAPPEN" << endl;
				break;
			}
			if (feedback) cout << i << " , " << j << " , " << state << endl;
		} while ( i != 0 || j != 0 ); //endpoint of trace SHOUD be (0,0), but (0,0) should not be in the alignment

	} //local alignments


	free(s);
	free(g1);
	free(g2);
	//delete [] s;
	//delete [] g1;
	//delete [] g2;

	if (feedback) { //print traces
		for(unsigned int al_ix = 0; al_ix < seqs->alignments.size(); al_ix++ ) {
			cout << "ALIGNMENT " << al_ix << " : " << endl;
			for(unsigned int i = 0; i < seqs->alignments[0].size(); i++) {
				cout << seqs->alignments[0][i]->getMatrixThisIx1() << " , " << seqs->alignments[0][i]->getMatrixThisIx2() << " : "
					 << seqs->alignments[0][i]->getAccumulatedscore() << " : " << seqs->alignments[0][i]->getThisscore() << endl;
			}
		}
	}


}


}
