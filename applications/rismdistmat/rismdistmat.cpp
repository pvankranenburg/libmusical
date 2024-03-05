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
#include "NLBAlignment.h"

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
	double * thedistmat; //in this case this will contain one 'row'. Only items with dist < threshold will be outputed.
    double threshold = 0.7;
    int seq2minsize = 6;

	ifstream listfile1, listfile2;

	ofstream outfile;

	ifstream seqfile1, seqfile2;
	string seq1filename, seq2filename;
	string seq1name, seq2name;
	string seq1, seq2;

    /**
     * SEQs1 are the QUERIES
     * SEQs2 is the corpus
    */

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


	listfile1.open(seq1filename);
	listfile2.open(seq2filename);
	vector<musical::NLBSequence *> seqs1;
	vector<musical::NLBSequence *> seqs2;
	cout << "Reading sequences 1" << endl;
	int file1count = 0;
	while (getline(listfile1, seq1name)) {
		//cout << "Reading " << seq1name << endl << flush;
		musical::NLBJSONReader mr1(new musical::JSONFileSource(seq1name));
		seqs1.push_back(static_cast<musical::NLBSequence*>(mr1.generateSequence()));
		//if ( seqs1.size() % 1000 == 0 ) cout << seq1name << endl;
		if ( seqs1.size() % 1000 == 0 ) cout << "\r" << file1count << flush;
		file1count += 1;
	}
	cout << endl;

	cout << "Reading seqeunces 2" << endl;
	int file2count = 0;
	while (getline(listfile2, seq2name)) {
		musical::NLBJSONReader mr2(new musical::JSONFileSource(seq2name));
		seqs2.push_back(static_cast<musical::NLBSequence*>(mr2.generateSequence()));
		//if ( seqs2.size()%1000 == 0 ) cout << seq2name << endl;
		if ( seqs2.size() % 1000 == 0 ) cout << "\r" << file2count << flush;
		file2count += 1;
	}
	cout << endl;
	listfile1.close();
	listfile2.close();

	//dump sequence;
	//cout << "sequence: " << endl;
	//seq->dump_stdout();

	string distmatfile = "pairs.txt";
	if (!symmetric && argc == 4) {
		distmatfile = argv[3];
	}
	if (symmetric && argc == 5) {
		distmatfile = argv[4];
	}
	if (distmat) cout << "Writing to: " << distmatfile << endl;

	if (distmat) {
		outfile.open(distmatfile.c_str());
		//prepare memory for the distmat
		thedistmat = (double *)malloc(seqs2.size()*sizeof(double)); //seq2 is the corpus
	}

	int size1 = seqs1.size();
	int size2 = seqs2.size();

	float begin = datemicro();

	for(int i = 0; i<size1; i++) {
		cout << i << ": " << seqs1[i]->getName() << endl;
		#pragma omp parallel for num_threads(12)
		//#pragma omp parallel for
		for(int j=0; j<size2; j++) {
			if ( j%10000 == 0 ) cout << "." << flush;

            if ( seqs1[i]->size() == 0 || seqs2[j]->size() <= seq2minsize ) {
                if (distmat) thedistmat[j] = 100.0;
            } else {
                //sequences
                musical::NLBSequences * seqs = new musical::NLBSequences(seqs1[i],seqs2[j]);
                
                //similarity rater
                //musical::NLBOptiSimilarityRater * sr = new musical::NLBOptiSimilarityRater();
                //musical::NLBExactPitch40SimilarityRater * sr = new musical::NLBExactPitch40SimilarityRater();
                musical::NLBExactPitch40IMASimilarityRater * sr = new musical::NLBExactPitch40IMASimilarityRater();
                //musical::NLBExactPitch40MWSimilarityRater * sr = new musical::NLBExactPitch40MWSimilarityRater();
                
                //gap rater
                //musical::ConstantAffineGapRater * gr = new musical::ConstantAffineGapRater(-0.6, -0.2);
                musical::ConstantLinearGapRater * gr = new musical::ConstantLinearGapRater(-0.6);
                //musical::NLBIMAAffineGapRater * gr = new musical::NLBIMAAffineGapRater(-0.2);
                //musical::NLBIMAGapRater * gr = new musical::NLBIMAGapRater();
                
                gr->setZeroEndGapScore(); // To give endgaps score zero

                //algignment algorithm
                //musical::AffineGlobalAligner nw = musical::AffineGlobalAligner(seqs, sr , gr);
                musical::LinearGlobalAligner nw = musical::LinearGlobalAligner(seqs, sr, gr);

                nw.doAlign();
                double normalization_factor = 1.0;
                //normalization_factor = seqs->getAlignmentSize(0);
                normalization_factor = min(seqs1[i]->size(),seqs2[j]->size());
                double normalizedscore = seqs->getScore() / normalization_factor;
                if (distmat) thedistmat[j] = 1.0 - normalizedscore;
                delete seqs;
                delete gr;
                delete sr;
            }
		}
		cout << endl;
		if (distmat) {
			for ( int j = 0; j < size2; j++ ) {
				double dist = thedistmat[j];
                if(dist < threshold) {
    				outfile << seqs1[i]->getName() << "\t" << seqs2[j]->getName() << "\t" << dist << endl << flush;
                }
			}
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
