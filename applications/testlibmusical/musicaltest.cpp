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
using namespace std;

#include <sys/time.h>
#include <time.h>

#include "libmusical.h"
#include "OptiAlignment.h"

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
     //printf(" %d:%02d:%02d %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
}

int main(int argc, char * argv[]) {

	bool distmat = true; //create distmat file?

	ifstream listfile1, listfile2;

	ofstream outfile;

	ifstream seqfile1, seqfile2;
	string seq1name,seq2name;
	string seq1,seq2;

	listfile1.open(argv[1]);
	listfile2.open(argv[2]);
	vector<musical::OptiSequence *> seqs1;
	vector<musical::OptiSequence *> seqs2;
	while (getline(listfile1, seq1name)) {
		//musical::JSONFileSource * fs1 = new musical::JSONFileSource(seq1name);
		musical::OptiReader mr1(new musical::JSONFileSource(seq1name));
		seqs1.push_back(static_cast<musical::OptiSequence*>(mr1.generateSequence()));
		cout << seq1name << endl;
		//delete fs1; //taken care of by Reader
		//cout << seq1name << ": " << seq1 <<  endl;
	}

	while (getline(listfile2, seq2name)) {
		//musical::JSONFileSource * fs2 = new musical::JSONFileSource(seq2name);
		musical::OptiReader mr2(new musical::JSONFileSource(seq2name));
		seqs2.push_back(static_cast<musical::OptiSequence*>(mr2.generateSequence()));
		cout << seq2name << endl;
		//delete fs2;
		//cout << seq1name << ": " << seq1 <<  endl;
	}
	listfile1.close();
	listfile2.close();

	//dump sequence;
	//cout << "sequence: " << endl;
	//seq->dump_stdout();

	//do this outside the loop:
	//musical::Sequences seqs = musical::Sequences();
	//musical::NeedlemanWunschGotoh nw = musical::NeedlemanWunschGotoh(&seqs);
	//nw.simr = new musical::OptiSimilarityRater();
	//musical::SmithWaterman nw = musical::SmithWaterman(&seqs);
	//musical::NeedlemanWunschGotoh nw = musical::NeedlemanWunschGotoh(&seqs);
	//nw.simr = new musical::OptiSimilarityRater();

	float begin = datemicro();

	if (distmat) {
		outfile.open("distmat.txt");
		outfile << "recnr";

		for ( unsigned int i = 0; i < seqs2.size(); i++ ) {
			outfile << "\t" << seqs2[i]->name;
		}
		outfile << endl;
	}

	for(unsigned int i = 0; i<seqs1.size(); i++) {
		cout << i << ": " << seqs1[i]->name << endl;
		if (distmat) outfile << seqs1[i]->name;
		//#pragma omp parallel for
		for(unsigned int j=0; j<seqs2.size(); j++) {
			//cout << "\t start " << j << ": " << seqs2[j]->name << endl;
			musical::OptiSequences seqs = musical::OptiSequences(seqs1[i],seqs2[j]);
			//cout << "Sequences set"<<endl;
			musical::NeedlemanWunschGotoh nw = musical::NeedlemanWunschGotoh(&seqs);
			//musical::NeedlemanWunsch nw = musical::NeedlemanWunsch(&seqs);
			//musical::SmithWaterman nw = musical::SmithWaterman(&seqs);
			//nw.maxAlignments = -1;
			//cout << "Aligner initialized" << endl;
			nw.simr = new musical::OptiSimilarityRater();
			//nw.simr = new musical::ExactPitch40SimilarityRater();
			//cout << "Similarity Rater set" << endl;
			//nw.gapr = new musical::ConstantLinearGapRater(-0.8);
			nw.gapr = new musical::ConstantAffineGapRater(-0.8, -0.2);
			//cout << "Gap Rater set" << endl;
			nw.doAlign();
			double normalizedscore = nw.score / min(seqs1[i]->symbols.size(),seqs2[j]->symbols.size());
			if (distmat) outfile << "\t" << 1.0 - normalizedscore;
			//cout << seqs1[i]->name << " -> "<< seqs2[j]->name << " " << "Score: " << nw.score << endl;
			//cout << seqs1[i]->name << " -> "<< seqs2[j]->name << " " << "Normalization factor: " << min(seqs1[i]->symbols.size(),seqs2[j]->symbols.size()) << endl;
			//cout << seqs1[i]->name << " -> "<< seqs2[j]->name << " " << "Normalized score: " << normalizedscore << endl;
			//cout << seqs1[i]->name << " -> "<< seqs2[j]->name << " " << "Distance: " << 1.0 - normalizedscore << endl;
			//cout << "Aligned" << endl;
			//delete nw;
			//cout << "Aligner deleted" << endl;
			//nw.clear();
			//if (j%50 == 0) cout << "." << flush;
			//cout << "\t ready " << j << ": " << seqs2[j]->name << endl;
			//delete nw.smir;
		}
		if (distmat) outfile << endl;
		cout << endl;
	}

	float end = datemicro();

	cout << "   total time : " << end - begin << endl;
	cout << "time per query: " << (end - begin)/(float)seqs1.size() << endl;


	return 0;
}
