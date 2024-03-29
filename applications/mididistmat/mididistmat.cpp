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
#include "MidiAlignment.h"

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

	ifstream seqfile1, seqfile2;
	string seq1name,seq2name;
	string seq1,seq2;

	listfile1.open(argv[1]);
	listfile2.open(argv[2]);
	vector<musical::MidiSequence *> seqs1;
	vector<musical::MidiSequence *> seqs2;
	cout << "Reading sequences 1" << endl;
	while (getline(listfile1, seq1name)) {
		cout << seqs1.size() << " " << seq1name << flush;
		musical::MidiFileReader mr1(seq1name);
		seqs1.push_back(static_cast<musical::MidiSequence*>(mr1.generateSequence()));
		//if ( seqs1.size() % 1000 == 0 ) cout << seq1name << endl;
		//if ( seqs1.size() % 1000 == 0 ) cout << "." << flush;
		cout << " done" << endl;
	}
	cout << endl;
	cout << "Finished Reading sequences 1." << endl;


	cout << "Reading seqeunces 2" << endl;
	while (getline(listfile2, seq2name)) {
		cout << seqs2.size() << " " << seq2name << flush;
		musical::MidiFileReader mr2(seq2name);
		seqs2.push_back(static_cast<musical::MidiSequence*>(mr2.generateSequence()));
		//if ( seqs2.size()%1000 == 0 ) cout << seq2name << endl;
		//if ( seqs2.size() % 1000 == 0 ) cout << "." << flush;
		cout << " done" << endl;
	}
	cout << endl;
	cout << "Finished Reading sequences 2." << endl;

	listfile1.close();
	listfile2.close();

	//dump sequence;
	//cout << "sequence: " << endl;
	//seq->dump_stdout();

	if (distmat) {
		outfile.open("distmat.txt");
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
		#pragma omp parallel for
		for(int j=0; j<size2; j++) {
			//if ( j%1000 == 0 ) cout << "." << flush;
			//cout << i << "aligning with: " << seqs2[j]->getName() << flush;
			musical::MidiSequences * seqs = new musical::MidiSequences(seqs1[i],seqs2[j]);
			//musical::MidiExactPitchIntervalSimilarityRater * sr = new musical::MidiExactPitchIntervalSimilarityRater();
			musical::MidiPitchBandSimilarityRater * sr = new musical::MidiPitchBandSimilarityRater();
			sr->use_ima = false;
			musical::ConstantLinearGapRater * gr = new musical::ConstantLinearGapRater(-0.6);
			musical::LinearGlobalAligner nw = musical::LinearGlobalAligner(seqs, sr , gr);
			nw.doAlign();
			double score = seqs->getScore();
			double normalizedscore = score / min(seqs1[i]->size(),seqs2[j]->size());
			//cout << "... " << score << " .... " << 1.0 - normalizedscore << endl;
			if (distmat) thedistmat[i*size2+j] = 1.0 - normalizedscore;
			delete seqs;
			delete gr;
			delete sr;
		}
		cout << endl;
	}

	float end = datemicro();

	cout << "   total time : " << end - begin << endl;
	cout << "time per query: " << (end - begin)/(float)seqs1.size() << endl;

	if (distmat) {
		cout << "Writing distmat.txt" << endl;
		for ( int i = 0; i < size1; i++ ) {
			outfile << seqs1[i]->getName();
			for ( int j = 0; j < size2; j++ ) {
				outfile << "\t" << thedistmat[i*size2+j];
			}
			outfile << endl;
		}
		free(thedistmat);
	}

	//delete te sequences:
	for (int i=0; i<size1; i++) delete seqs1[i];
	for (int j=0; j<size2; j++) delete seqs2[j];

	return 0;
}
