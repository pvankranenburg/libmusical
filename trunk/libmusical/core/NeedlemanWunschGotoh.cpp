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

#include "NeedlemanWunschGotoh.h"
#include "miscfunctions.h"

namespace musical {

NeedlemanWunschGotoh::NeedlemanWunschGotoh() {
	/*
	s = (NWGTrace *)malloc(200*200*sizeof(NWGTrace));
	g1 = (NWGTrace *)malloc(200*200*sizeof(NWGTrace));
	g2 = (NWGTrace *)malloc(200*200*sizeof(NWGTrace));
	size_s = 200*200;
	*/
}

NeedlemanWunschGotoh::NeedlemanWunschGotoh(Sequences * sqs) : AlignmentAlgorithm(sqs) {
	/*
	s = (NWGTrace *)malloc(200*200*sizeof(NWGTrace));
	g1 = (NWGTrace *)malloc(200*200*sizeof(NWGTrace));
	g2 = (NWGTrace *)malloc(200*200*sizeof(NWGTrace));
	size_s = 200*200;
	*/
}


NeedlemanWunschGotoh::~NeedlemanWunschGotoh() {
	/*
	free(s);
	free(g1);
	free(g2);
	*/
	// TODO Auto-generated destructor stub
}

void NeedlemanWunschGotoh::doAlign() {

	bool feedback = false;

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

	s = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));
	g1 = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));
	g2 = (NWGTrace *)malloc(mm*mn*sizeof(NWGTrace));

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

	double gapopeningpenalty = 0.8; //TODO
	double gapextensionpenalty = 0.2; //TODO


	// (0,0) : origin. endpoint of global alignment
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


	//initialize begin-gap *with* seq1
	// S S S S S S
	// - - - - S S

	// (1,0): first symbol of seq1 aligned with gap :
	s[1*mm+0].ix1 = Trace::NOWHERE;
	s[1*mm+0].ix2 = Trace::NOWHERE;
	s[1*mm+0].state = NWGTrace::NONE;
	s[1*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
	s[1*mm+0].thisscore = 0.0;

	g1[1*mm+0].ix1 = 0;
	g1[1*mm+0].ix2 = 0;
	g1[1*mm+0].state = NWGTrace::S; //poits to (0,0) in S
 	g1[1*mm+0].accumulatedscore = - gapopeningpenalty;
	g1[1*mm+0].thisscore = - gapopeningpenalty;

	g2[1*mm+0].ix1 = Trace::NOWHERE;
	g2[1*mm+0].ix2 = Trace::NOWHERE;
	g2[1*mm+0].state = NWGTrace::NONE;
	g2[1*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
	g2[1*mm+0].thisscore = 0.0;

	//rest:
	for(int k=2; k<mn; k++) {
		s[k*mm+0].ix1 = Trace::NOWHERE;
		s[k*mm+0].ix2 = Trace::NOWHERE;
		s[k*mm+0].state = NWGTrace::NONE;
		s[k*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
		s[k*mm+0].thisscore = 0.0;

		g1[k*mm+0].ix1 = k-1;
		g1[k*mm+0].ix2 = 0;
		g1[k*mm+0].state = NWGTrace::G1;
		g1[k*mm+0].accumulatedscore = g1[(k-1)*mm+0].accumulatedscore - gapextensionpenalty;
		g1[k*mm+0].thisscore = - gapextensionpenalty;

		g2[k*mm+0].ix1 = Trace::NOWHERE;
		g2[k*mm+0].ix2 = Trace::NOWHERE;
		g2[k*mm+0].state = NWGTrace::NONE;
		g2[k*mm+0].accumulatedscore = -std::numeric_limits<double>::infinity();
		g2[k*mm+0].thisscore = 0.0;
	}


	//initialize begin-gap *with* seq2
	// - - - - S S
	// S S S S S S

	// (0,1): first symbol of seq1 aligned with gap :
	s[0*mm+1].ix1 = Trace::NOWHERE;
	s[0*mm+1].ix2 = Trace::NOWHERE;
	s[0*mm+1].state = NWGTrace::NONE;
	s[0*mm+1].accumulatedscore = -std::numeric_limits<double>::infinity();
	s[0*mm+1].thisscore = 0.0;

	g1[0*mm+1].ix1 = Trace::NOWHERE;
	g1[0*mm+1].ix2 = Trace::NOWHERE;
	g1[0*mm+1].state = NWGTrace::NONE;
	g1[0*mm+1].accumulatedscore = -std::numeric_limits<double>::infinity();
	g1[0*mm+1].thisscore = - 0.0;

	g2[0*mm+1].ix1 = 0;
	g2[0*mm+1].ix2 = 0;
	g2[0*mm+1].state = NWGTrace::S;
	g2[0*mm+1].accumulatedscore = - gapopeningpenalty;
	g2[0*mm+1].thisscore = - gapopeningpenalty;

	//rest:
	for(int l=2; l<mm; l++) {
		s[0*mm+l].ix1 = Trace::NOWHERE;
		s[0*mm+l].ix2 = Trace::NOWHERE;
		s[0*mm+l].state = NWGTrace::NONE;
		s[0*mm+l].accumulatedscore = -std::numeric_limits<double>::infinity();
		s[0*mm+l].thisscore = 0.0;

		g1[0*mm+l].ix1 = Trace::NOWHERE;
		g1[0*mm+l].ix2 = Trace::NOWHERE;
		g1[0*mm+l].state = NWGTrace::NONE;
		g1[0*mm+l].accumulatedscore = -std::numeric_limits<double>::infinity();
		g1[0*mm+l].thisscore = 0.0;

		g2[0*mm+l].ix1 = 0;
		g2[0*mm+l].ix2 = l-1;
		g2[0*mm+l].state = NWGTrace::G2;
		g2[0*mm+l].accumulatedscore = g2[0*mm+l-1].accumulatedscore - gapextensionpenalty;
		g2[0*mm+l].thisscore = - gapextensionpenalty;
	}

	if (feedback) cout << "Initialization done" << endl;

	double substsc = -std::numeric_limits<double>::infinity();

	double S_S, G1_S, G2_S, S_G1, G1_G1, G2_G1, S_G2, G1_G2, G2_G2;

	int current_ix = 0;

	//now fill matrix
	for(int k=1; k<mn; k++) {
		for(int l=1; l<mm; l++) {

			current_ix = k*mm+l;

			substsc = simr->getScore(seqs,k-2,l-2,k-1,l-1);

			//substitution
			S_S   =  s[(k-1)*mm+(l-1)].accumulatedscore + substsc;
			G1_S  = g1[(k-1)*mm+(l-1)].accumulatedscore + substsc;
			G2_S  = g2[(k-1)*mm+(l-1)].accumulatedscore + substsc;

			//gap with symbol from A
			S_G1  =  s[(k-1)*mm+l].accumulatedscore - gapopeningpenalty;
			G1_G1 = g1[(k-1)*mm+l].accumulatedscore - gapextensionpenalty;
			G2_G1 = g2[(k-1)*mm+l].accumulatedscore - gapopeningpenalty; //consider this a gap opening

			//gap with symbol from B
			S_G2  =  s[k*mm+(l-1)].accumulatedscore - gapopeningpenalty;
			G1_G2 = g1[k*mm+(l-1)].accumulatedscore - gapopeningpenalty; //consider this a gap opening
			G2_G2 = g2[k*mm+(l-1)].accumulatedscore - gapextensionpenalty;


			 s[current_ix].accumulatedscore = fmax ( fmax ( S_S, G1_S ), G2_S );
			g1[current_ix].accumulatedscore = fmax ( fmax ( S_G1, G1_G1 ), G2_G1 );
			g2[current_ix].accumulatedscore = fmax ( fmax ( S_G2, G1_G2 ), G2_G2 );

			//fill trace

			//substitution
			if (s[current_ix].accumulatedscore == S_S) {
				s[current_ix].ix1 = k-1;
				s[current_ix].ix2 = l-1;
				s[current_ix].state = NWGTrace::S;
				s[current_ix].thisscore = substsc;
			}
			else if (s[current_ix].accumulatedscore == G1_S) {
				s[current_ix].ix1 = k-1;
				s[current_ix].ix2 = l-1;
				s[current_ix].state = NWGTrace::G1;
				s[current_ix].thisscore = substsc;
			}
			else if (s[current_ix].accumulatedscore == G2_S) {
				s[current_ix].ix1 = k-1;
				s[current_ix].ix2 = l-1;
				s[current_ix].state = NWGTrace::G2;
				s[current_ix].thisscore = substsc;
			}
			else { cerr << "No max score" << endl; }

			//if ( k==1 && l==1 ) cout << s[current_ix].ix1 << endl;
			//if ( k==1 && l==1 ) cout << s[current_ix].ix2 << endl;
			//if ( k==1 && l==1 ) cout << s[current_ix].state << endl;


			//gap with seq1
			if (g1[current_ix].accumulatedscore == G1_G1 ) {
				g1[current_ix].ix1 = k-1;
				g1[current_ix].ix2 = l;
				g1[current_ix].state = NWGTrace::G1;
				g1[current_ix].thisscore = - gapextensionpenalty;
			}
			else if (g1[current_ix].accumulatedscore == G2_G1 ) {
				g1[current_ix].ix1 = k-1;
				g1[current_ix].ix2 = l;
				g1[current_ix].state = NWGTrace::G2;
				g1[current_ix].thisscore = - gapopeningpenalty;
			}
			else if (g1[current_ix].accumulatedscore == S_G1 ) {
				g1[current_ix].ix1 = k-1;
				g1[current_ix].ix2 = l;
				g1[current_ix].state = NWGTrace::S;
				g1[current_ix].thisscore = - gapopeningpenalty;
			}
			else { cerr << "No max score" << endl; }

			//gap with seq2
			if (g2[current_ix].accumulatedscore == G1_G2 ) {
				g2[current_ix].ix1 = k;
				g2[current_ix].ix2 = l-1;
				g2[current_ix].state = NWGTrace::G1;
				g2[current_ix].thisscore = - gapopeningpenalty;
			}
			else if (g2[current_ix].accumulatedscore == G2_G2 ) {
				g2[current_ix].ix1 = k;
				g2[current_ix].ix2 = l-1;
				g2[current_ix].state = NWGTrace::G2;
				g2[current_ix].thisscore = - gapextensionpenalty;
			}
			else if (g2[current_ix].accumulatedscore == S_G2 ) {
				g2[current_ix].ix1 = k;
				g2[current_ix].ix2 = l-1;
				g2[current_ix].state = NWGTrace::S;
				g2[current_ix].thisscore = - gapopeningpenalty;
			}
			else { cerr << "No max score" << endl; }

		}
	}

	if (feedback) {
		//print s
		cout << endl;
		for(int k=0; k<mn; k++) {
			for(int l=0; l<mm; l++) {
				cout << setw(2)<<s[k*mm+l].ix1<<"-"<<setw(2) << s[k*mm+l].ix2 << ":" << setw(2)<< s[k*mm+l].state << "  ";
				//cout << setw(3)<< s[k*mm+l].state;
			}
			cout << endl;
		}
		//print g1
		cout << endl;
		for(int k=0; k<mn; k++) {
			for(int l=0; l<mm; l++) {
				cout << setw(2)<<g1[k*mm+l].ix1<<"-"<<setw(2) << g1[k*mm+l].ix2 << ":" << setw(2)<< g1[k*mm+l].state << "  ";
				//cout << setw(3)<< s[k*mm+l].state;
			}
			cout << endl;
		}
		//print g2
		cout << endl;
		for(int k=0; k<mn; k++) {
			for(int l=0; l<mm; l++) {
				cout << setw(2)<<g2[k*mm+l].ix1<<"-"<<setw(2) << g2[k*mm+l].ix2 << ":" << setw(2)<< g2[k*mm+l].state << "  ";
				//cout << setw(3)<< s[k*mm+l].state;
			}
			cout << endl;
		}
	}


	//find score and do the trace back:
	//add one alignment to alignments
	alignments.push_back(std::deque<Trace *>());
	alignments.back().clear();

	//find out whether to start with s, g1 or g2
	int i = mn - 1; //point to final cell
	int j = mm - 1;
	NWGTrace::State state = NWGTrace::NONE;

	if (feedback) cout << "S : " << s[(n*mm)+mm-1].accumulatedscore << endl;
	if (feedback) cout << "G1: " << g1[(n*mm)+mm-1].accumulatedscore << endl;
	if (feedback) cout << "G2: " << g2[(n*mm)+mm-1].accumulatedscore << endl;

	//NB order of this matters
	//if e.g. max score in s equals max score in g1, last one is chosen
	double score = -std::numeric_limits<double>::infinity();
	//start with s?
	if ( s[(n*mm)+mm-1].accumulatedscore >= g1[(n*mm)+mm-1].accumulatedscore && s[(n*mm)+mm-1].accumulatedscore >= g2[(n*mm)+mm-1].accumulatedscore  ) {
		if (feedback) cout << "in S (" << i << "," << j << "), to : ";
		score = s[(n*mm)+mm-1].accumulatedscore;
		scores.push_back(score);
		s[(n*mm)+mm-1].this_ix1 = i;
		s[(n*mm)+mm-1].this_ix2 = j;
		alignments[0].push_front(new NWGTrace(s[(n*mm)+mm-1])); //last alignment
		//point to (i,j) in matrix state.
		i = s[(n*mm)+mm-1].ix1;
		j = s[(n*mm)+mm-1].ix2;
		state = s[(n*mm)+mm-1].state;
	} else  //start with g1?
	if ( g1[(n*mm)+mm-1].accumulatedscore >= s[(n*mm)+mm-1].accumulatedscore && g1[(n*mm)+mm-1].accumulatedscore >= g2[(n*mm)+mm-1].accumulatedscore  ) {
		if (feedback) cout << "in G1 (" << i << "," << j << "), to : ";
		score = g1[(n*mm)+mm-1].accumulatedscore;
		scores.push_back(score);
		g1[(n*mm)+mm-1].this_ix1 = i;
		g1[(n*mm)+mm-1].this_ix2 = j;
		alignments[0].push_front(new NWGTrace(g1[(n*mm)+mm-1])); //last alignment
		//point to (i,j) in matrix state.
		i = g1[(n*mm)+mm-1].ix1;
		j = g1[(n*mm)+mm-1].ix2;
		state = g1[(n*mm)+mm-1].state;
	} else
	//start with g2?
	if ( g2[(n*mm)+mm-1].accumulatedscore >= s[(n*mm)+mm-1].accumulatedscore && g2[(n*mm)+mm-1].accumulatedscore >= g1[(n*mm)+mm-1].accumulatedscore  ) {
		if (feedback) cout << "in G2 (" << i << "," << j << "), to : ";
		score = g2[(n*mm)+mm-1].accumulatedscore;
		scores.push_back(score);
		g2[(n*mm)+mm-1].this_ix1 = i;
		g2[(n*mm)+mm-1].this_ix2 = j;
		alignments[0].push_front(new NWGTrace(g2[(n*mm)+mm-1])); //last alignment
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
			alignments[0].push_front(new NWGTrace(s[i*mm+j]));
			state = s[i*mm+j].state;
			i_new = s[i*mm+j].ix1;
			j = s[i*mm+j].ix2;
			i = i_new;
		}
		else if (state == NWGTrace::G1 ) {
			if (feedback) cout << "in G1 (" << i << "," << j << "), to : ";
			g1[i*mm+j].this_ix1 = i;
			g1[i*mm+j].this_ix2 = j;
			alignments[0].push_front(new NWGTrace(g1[i*mm+j]));
			state = g1[i*mm+j].state;
			i_new = g1[i*mm+j].ix1;
			j = g1[i*mm+j].ix2;
			i = i_new;
		}
		else if (state == NWGTrace::G2 ) {
			if (feedback) cout << "in G2 (" << i << "," << j << "), to : ";
			g2[i*mm+j].this_ix1 = i;
			g2[i*mm+j].this_ix2 = j;
			alignments[0].push_front(new NWGTrace(g2[i*mm+j]));
			state = g2[i*mm+j].state;
			i_new = g2[i*mm+j].ix1;
			j = g2[i*mm+j].ix2;
			i = i_new;
		}
		else {
			cerr << "THIS SHOULD NOT HAPPEN" << endl;
			break;
		}
		if (feedback) cout << i << " , " << j << " , " << state << endl;
	} while ( i != 0 || j != 0 ); //endpoint of trace SHOUD be (0,0), but (0,0) should not be in the alignment

	free(s);
	free(g1);
	free(g2);
	//delete [] s;
	//delete [] g1;
	//delete [] g2;

	if (feedback) { //print trace
		for(unsigned int i = 0; i < alignments[0].size(); i++) {
			cout << alignments[0][i]->getMatrixThisIx1() << " , " << alignments[0][i]->getMatrixThisIx2() << " : "
				 << alignments[0][i]->getAccumulatedscore() << " : " << alignments[0][i]->getThisscore() << endl;
		}
	}

}

}
