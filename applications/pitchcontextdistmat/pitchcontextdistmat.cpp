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
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

#include <sys/time.h>
#include <time.h>

#include "libmusical.h"
#include "PCAlignment.h"

/**
 * returns the current time in microsecs.
 * Doesn't work in linux for some reason.
 */
inline float datemicro() {
     struct timeval tv;
     struct timezone tz;
     struct tm *tm;
     gettimeofday(&tv, &tz);
     tm=localtime(&tv.tv_sec);
     return tm->tm_sec + 60*tm->tm_min + 60*60*tm->tm_hour + (float)tv.tv_usec/1000000.0;
}

int main(int argc, char * argv[]) {

	bool distmat = true; //create distmat file?
	double * thedistmat;

	ifstream listfile1, listfile2;

	ofstream outfile;

	string seq1filename, seq2filename;
	string seq1name, seq2name;

	bool symmetric = false;
	if( string(argv[1]) == "-sym" ) {
		symmetric = true;
		cout << "Distmat is symmetric. Only computing upper triangle." << endl;
		seq1filename = string(argv[2]);
		seq2filename = string(argv[3]);
	} else {
		seq1filename = string(argv[1]);
		seq2filename = string(argv[2]);
	}

	clog << "Reading from: " << seq1filename << " and " << seq2filename << endl;

	listfile1.open(seq1filename);
	listfile2.open(seq2filename);
	vector<musical::PCSequence *> seqs1;
	vector<musical::PCSequence *> seqs2;
	clog << "Reading sequences 1" << flush;
	while (getline(listfile1, seq1name)) {
		musical::PCTXTReader pcr1(seq1name);
		musical::PCSequence * seq1 = static_cast<musical::PCSequence*>(pcr1.generateSequence());
		seqs1.push_back(static_cast<musical::PCSequence*>(seq1));
		if ( seqs1.size() % 1000 == 0 ) clog << "." << flush;
	}
	clog << endl;

	clog << "Reading seqeunces 2" << flush;
	while (getline(listfile2, seq2name)) {
		musical::PCTXTReader pcr2(seq2name);
		musical::PCSequence * seq2 = static_cast<musical::PCSequence*>(pcr2.generateSequence());
		seqs2.push_back(static_cast<musical::PCSequence*>(seq2));
		if ( seqs2.size() % 1000 == 0 ) clog << "." << flush;
	}
	clog << endl;
	listfile1.close();
	listfile2.close();

	//dump sequence;
	//cout << "sequence: " << endl;
	//seq->dump_stdout();

	string distmatfile = "distmat.txt";
	if (!symmetric && argc == 4) {
		distmatfile = argv[3];
	}
	if (symmetric && argc == 5) {
		distmatfile = argv[4];
	}
	if (distmat) cout << "Writing to: " << distmatfile << endl;

	if (distmat) {
		outfile.open(distmatfile.c_str());
		outfile << "recnr";

		for ( unsigned int i = 0; i < seqs2.size(); i++ ) {
			outfile << "\t" << seqs2[i]->getName();
		}
		outfile << endl;

		//prepare memory for the distmat
		thedistmat = (double *)malloc(seqs1.size()*seqs2.size()*sizeof(double));

	}

	int size1 = seqs1.size();
	int size2 = seqs2.size();

	float begin = datemicro();

	for(int i = 0; i<size1; i++) {
		cout << i << ": " << seqs1[i]->getName() << endl;
		#pragma omp parallel for num_threads(4)
		//#pragma omp parallel for
		for(int j=0; j<size2; j++) {
			if ( j%1000 == 0 ) cout << "." << flush;

			if (symmetric && (j<i)) {
				//cout << "reusing " << i << ", " << j << endl;
				if (distmat) thedistmat[i*size2+j] = thedistmat[j*size2+i];
			} else {
				if ( seqs1[i]->size() == 0 || seqs2[j]->size() == 0 ) {
					if (distmat) thedistmat[i*size2+j] = 100.0;
				} else {
					// Create pair of sequences
					musical::PCSequences * seqs = new musical::PCSequences(seqs1[i],seqs2[j]);
					// Create a similarity rater
					//musical::PCSSSimilarityRater * sr = new musical::PCSSSimilarityRater();
					musical::PCCosSimilarityRater * sr = new musical::PCCosSimilarityRater();
					// Create a gap rater
					musical::ConstantAffineGapRater * gr = new musical::ConstantAffineGapRater(-0.6,-0.2);
					// Create an alignment algorithm
					musical::AffineGlobalAligner nw = musical::AffineGlobalAligner(seqs, sr, gr);
					// Do the alignment
					nw.doAlign();
					double normalization_factor = 1.0;
					//normalization_factor = seqs->getAlignmentSize(0);
					normalization_factor = min(seqs1[i]->size(),seqs2[j]->size());
					double normalizedscore = seqs->getScore() / normalization_factor;
					if (distmat) thedistmat[i*size2+j] = 1.0 - normalizedscore;
					delete seqs;
					delete gr;
					delete sr;
				}
			}
		}
		cout << endl;
		if (distmat) {
			outfile << seqs1[i]->getName();
			for ( int j = 0; j < size2; j++ ) {
				double dist = thedistmat[i*size2+j];
				outfile << "\t" << dist;
			}
			outfile << endl << flush;
		}
	}

	if (distmat) free(thedistmat);

	float end = datemicro();

	cout << "   total time : " << end - begin << endl;
	cout << "time per query: " << (end - begin)/(float)seqs1.size() << endl;

	//delete te sequences:
	for (int i=0; i<size1; i++) delete seqs1[i];
	for (int j=0; j<size2; j++) delete seqs2[j];

	return 0;
}
