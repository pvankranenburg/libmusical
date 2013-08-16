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


#include "AlignmentVisualizer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

namespace musical {

AlignmentVisualizer::AlignmentVisualizer() {
	// TODO Auto-generated constructor stub

}

AlignmentVisualizer::~AlignmentVisualizer() {
	// TODO Auto-generated destructor stub
}

void AlignmentVisualizer::basicStdoutReport(const int c) const {

	if ( c >= seqs->getNoOfAlignments() ) {
		cerr << "No alignment available at index " << c << endl;
		return;
	}

	for ( int i = 0; i < seqs->getAlignmentSize(c); i++ ) {
		std::string symbol1 = "";
		std::string symbol2 = "";

		/*
		if ( seqs->getTraceElement(i,c)->getIx1() == -1 )
			symbol1 = "x";
		else symbol1 = seqs->getSeq1()->getSymbolAt(seqs->getTraceElement(i,c)->getIx1())->toString();

		if ( seqs->getTraceElement(i,c)->getIx2() == -1 )
			symbol2 = "x";
		else symbol2 = seqs->getSeq2()->getSymbolAt(seqs->getTraceElement(i,c)->getIx2())->toString();

		cout << "(" << seqs->getTraceElement(i,c)->getIx1() << ")[" << symbol1 << "] - (" << seqs->getTraceElement(i,c)->getIx2() <<  ")[" << symbol2 << "]" << " With score: " << seqs->getTraceElement(i,c)->thisscore << " Accumulated: " << seqs->getTraceElement(i,c)->accumulatedscore << endl;
		*/

		cout << "(" << seqs->getTraceElement(i,c)->getIx1() << ") - (" << seqs->getTraceElement(i,c)->getIx2() <<  ")  With score: " << seqs->getTraceElement(i,c)->thisscore << " Accumulated: " << seqs->getTraceElement(i,c)->accumulatedscore << endl;
	}

}

void AlignmentVisualizer::toGnuPlot(const string filebasename, const int c) const {
	float maxvalue1 = -std::numeric_limits<float>::infinity();
	float minvalue1 = std::numeric_limits<float>::infinity();
	float maxvalue2 = -std::numeric_limits<float>::infinity();
	float minvalue2 = std::numeric_limits<float>::infinity();

	for ( int i = 0; i < seqs->getAlignmentSize(c); i++ ) {
			if ( seqs->getTraceElement(i,c)->getIx1() != -1 ) { //skip gaps
			float value = seqs->getSeq1()->getSymbolAt(seqs->getTraceElement(i,c)->getIx1())->toFloat();
			if (value > maxvalue1) maxvalue1 = value;
			if (value < minvalue1) minvalue1 = value;
		}
		if ( seqs->getTraceElement(i,c)->getIx2() != -1 ) { //skip gaps
			float value = seqs->getSeq2()->getSymbolAt(seqs->getTraceElement(i,c)->getIx2())->toFloat();
			if (value > maxvalue2) maxvalue2 = value;
			if (value < minvalue2) minvalue2 = value;
		}
	}

	//DEFAULT SAME SCALE ALONG AXES FOR COMPARABILITY
	if ( minvalue1 < minvalue2 ) minvalue2 = minvalue1; else minvalue1 = minvalue2;
	if ( maxvalue1 > maxvalue2 ) maxvalue2 = maxvalue1; else maxvalue1 = maxvalue2;

	//provide some margin
	float margin1 = (maxvalue1 - minvalue1) * 0.05;
	float margin2 = (maxvalue2 - minvalue2) * 0.05;

	toGnuPlotLineSegments(filebasename, minvalue1-margin1, maxvalue1+margin1, minvalue2-margin2, maxvalue2+margin2, c);
}

void AlignmentVisualizer::toGnuPlot(const string filebasename, const float minyvalue1, const float maxyvalue1, const float minyvalue2, const float maxyvalue2, const int c) const {

	if ( c >= seqs->getNoOfAlignments() ) {
		cerr << "No alignment available at index " << c << endl;
		return;
	}


	//first build the data file

	vector<int> seq1index;
	vector<float> seq1value;
	vector<int> seq2index;
	vector<float> seq2value;
	vector<int> scoreIndex;
	vector<float> scoreValue;

	for ( int i = 0; i < seqs->getAlignmentSize(c); i++ ) {
			if ( seqs->getTraceElement(i,c)->getIx1() != -1 ) { //skip gaps
			float value = seqs->getSeq1()->getSymbolAt(seqs->getTraceElement(i,c)->getIx1())->toFloat();
			seq1index.push_back(i);
			seq1value.push_back(value);
		}
		if ( seqs->getTraceElement(i,c)->getIx2() != -1 ) { //skip gaps
			float value = seqs->getSeq2()->getSymbolAt(seqs->getTraceElement(i,c)->getIx2())->toFloat();
			seq2index.push_back(i);
			seq2value.push_back(value);
		}
		scoreIndex.push_back(i);
		scoreValue.push_back(seqs->getTraceElement(i,c)->thisscore);
	}
	//write to file
	ofstream datafile;
	datafile.open((filebasename+".data").c_str());
	//unsigned int maxsize = max ( seq1index.size(), seq2index.size() );
	for ( unsigned int i=0; i<scoreIndex.size(); i++) {

		//columns 1,2 : individual scores
		datafile << scoreIndex[i] << "," << scoreValue[i] << ",";

		//columns 3,4 : curve for sequence 1
		if ( i < seq1index.size() )
			datafile << seq1index[i] << "," << seq1value[i] << ",";
		else
			datafile << ",,";

		//columns 5,6 : curve for sequence 2
		if ( i < seq2index.size() )
			datafile << seq2index[i] << "," << seq2value[i];
		else
			datafile << ",";

		datafile << endl;

		/*
		if ( i<seq1index.size() ) datafile << seq1index[i] << "," << seq1value[i];
		else datafile << ",";
		datafile << "," << seqs->getTraceElement(i,c)->thisscore;
		if ( i<seq2index.size() ) datafile << "," << seq2index[i] << "," << seq2value[i];
		datafile << endl;
		*/
	}
	datafile.close();

	ofstream gnuplotfile;
	gnuplotfile.open((filebasename+".gnuplot").c_str());
	//if minvalue == maxvalue : provide some margin

	float ymax1 = maxyvalue1;
	float ymin1 = minyvalue1;
	float ymax2 = maxyvalue2;
	float ymin2 = minyvalue2;

	if ( maxyvalue1 == minyvalue1 ) {
		ymax1 = maxyvalue1 + 1.0;
		ymin1 = minyvalue1 - 1.0;
	}
	if ( maxyvalue2 == minyvalue2 ) {
		ymax2 = maxyvalue2 + 1.0;
		ymin2 = minyvalue2 - 1.0;
	}

	string name1 = seqs->getSeq1()->getName();
	string name2 = seqs->getSeq2()->getName();

	gnuplotfile << "set terminal postscript landscape enhanced mono dashed lw 1 \"Helvetica\" 10;" << endl;
	gnuplotfile << "set output \""+filebasename+".ps\";" << endl;
	gnuplotfile << "set datafile separator \",\"" << endl;
	gnuplotfile << "set grid;" << endl;
	gnuplotfile << "set lmargin 5;" << endl; //hopefully this is enough
	gnuplotfile << "set multiplot;" << endl;
	gnuplotfile << "set size 1,0.4;" << endl;
	gnuplotfile << "set origin 0.0,0.6;" << endl;
	gnuplotfile << "set xrange [0:" << seqs->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [" << ymin1 << ":" << ymax1 <<  "];" << endl;
	gnuplotfile << "set title \"" << name1 << "\" noenhanced;" << endl;
	gnuplotfile << "plot \""+filebasename+".data\" using 3:4 notitle;" << endl;

	gnuplotfile << "set size 1,0.2;" << endl;
	gnuplotfile << "set origin 0.0,0.4" << endl;
	gnuplotfile << "set xrange [0:" << seqs->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [-1.1:1.1];" << endl;
	gnuplotfile << "set title \"Scores\"" << endl;
	gnuplotfile << "plot \""+filebasename+".data\" using 1:2 notitle with lines;" << endl;

	gnuplotfile << "set size 1,0.4;" << endl;
	gnuplotfile << "set origin 0.0,0.0;" << endl;
	gnuplotfile << "set title \"" << name2 << "\" noenhanced;" << endl;
	gnuplotfile << "set xrange [0:" << seqs->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [" << ymin2 << ":" << ymax2 <<  "];" << endl;
	gnuplotfile << "plot \""+filebasename+".data\" using 5:6 notitle;" << endl;
	gnuplotfile << "unset multiplot" << endl;

	gnuplotfile.close();
}

void AlignmentVisualizer::toGnuPlotLineSegments(const string filebasename, const float minyvalue1, const float maxyvalue1, const float minyvalue2, const float maxyvalue2, const int c) const {

	if ( c >= seqs->getNoOfAlignments() ) {
		cerr << "No alignment available at index " << c << endl;
		return;
	}

	//first build the data file

	vector<vector<int> > seq1indices;
	vector<vector<float> > seq1values;

	vector<vector<int > > seq2indices;
	vector<vector<float> > seq2values;

	vector<int> scoreIndex;
	vector<float> scoreValue;

	int current1 = -1;
	int current2 = -1;

	bool gap1 = true;
	bool gap2 = true;

	for ( int i = 0; i < seqs->getAlignmentSize(c); i++ ) {

		//cout << i << endl;

		//sequence1
		if ( seqs->getTraceElement(i,c)->getIx1() == -1) { //gap
			gap1 = true;
			//cout << "gap in 1" << endl;
		} else {
			if ( gap1 ) { //start new segment
				current1++; //next segment
				vector<int> intA;
				vector<float> floatA;
				seq1indices.push_back(intA);
				seq1values.push_back(floatA);
				//cout << "new segment added in 1, segment" << current1 << endl;
			}
			float value = seqs->getSeq1()->getSymbolAt(seqs->getTraceElement(i,c)->getIx1())->toFloat();
			seq1indices[current1].push_back(i);
			seq1values[current1].push_back(value);
			gap1 = false;
			//cout << "value added in 1" << endl;
		}

		//sequence2
		if ( seqs->getTraceElement(i,c)->getIx2() == -1 ) { //gap
			gap2 = true;
			//cout << "gap in 2" << endl;
		} else {
			if ( gap2 ) {
				current2++; //next segment
				vector<int> intA;
				vector<float> floatA;
				seq2indices.push_back(intA);
				seq2values.push_back(floatA);
				//cout << "new segment added in 2, segment" << current2 << endl;
			}
			float value = seqs->getSeq2()->getSymbolAt(seqs->getTraceElement(i,c)->getIx2())->toFloat();
			seq2indices[current2].push_back(i);
			seq2values[current2].push_back(value);
			gap2 = false;
			//cout << "value added in 2" << endl;
		}

		//individual scores
		scoreIndex.push_back(i);
		scoreValue.push_back(seqs->getTraceElement(i,c)->thisscore);
	}

	//clog << current1+1 << " / " << seq1indices.size() << " segments in sequence 1" << endl;
	//clog << current2+1 << " / " << seq2indices.size() << " segments in sequence 2" << endl;

	//dump
	/*
	for (int j=0; j<current1+1; j++) {
		clog << "sequence 1 - " << j << " : ";
		for (int k=0; k<seq1indices[j].size(); k++)
			clog << seq1indices[j][k] << " ";
		clog << endl;
	}
	for (int j=0; j<current2+1; j++) {
		clog << "sequence 2 - " << j << " : ";
		for (int k=0; k<seq2indices[j].size(); k++)
			clog << seq2indices[j][k] << " ";
		clog << endl;
	}
	*/

	//write to file
	ofstream datafile;
	datafile.open((filebasename+".data").c_str());
	//unsigned int maxsize = max ( seq1index.size(), seq2index.size() );
	for ( unsigned int i=0; i<scoreIndex.size(); i++) { //no sequence is longer than scoreIndex.

		//columns 1,2 : individual scores
		datafile << scoreIndex[i] << "," << scoreValue[i];

		//current1+1 curves for sequence 1
		for(int j=0; j<=current1; j++) {
			if ( i < seq1indices[j].size() )
				datafile << "," << seq1indices[j][i] << "," << seq1values[j][i];
			else
				datafile << ",,";
		}

		//current2+1 curves for sequence 2
		for(int j=0; j<=current2; j++) {
			if ( i < seq2indices[j].size() )
				datafile << "," << seq2indices[j][i] << "," << seq2values[j][i];
			else
				datafile << ",,";
		}

		datafile << endl;

	}
	datafile.close();

	ofstream gnuplotfile;
	gnuplotfile.open((filebasename+".gnuplot").c_str());
	//if minvalue == maxvalue : provide some margin

	float ymax1 = maxyvalue1;
	float ymin1 = minyvalue1;
	float ymax2 = maxyvalue2;
	float ymin2 = minyvalue2;

	if ( maxyvalue1 == minyvalue1 ) {
		ymax1 = maxyvalue1 + 1.0;
		ymin1 = minyvalue1 - 1.0;
	}
	if ( maxyvalue2 == minyvalue2 ) {
		ymax2 = maxyvalue2 + 1.0;
		ymin2 = minyvalue2 - 1.0;
	}

	string name1 = seqs->getSeq1()->getName();
	string name2 = seqs->getSeq2()->getName();

	gnuplotfile << "set terminal postscript landscape enhanced mono dashed lw 1 \"Helvetica\" 10;" << endl;
	gnuplotfile << "set output \""+filebasename+".ps\";" << endl;
	gnuplotfile << "set datafile separator \",\"" << endl;
	gnuplotfile << "set grid;" << endl;
	gnuplotfile << "set lmargin 5;" << endl; //hopefully this is enough
	gnuplotfile << "set multiplot;" << endl;
	gnuplotfile << "set size 1,0.4;" << endl;
	gnuplotfile << "set origin 0.0,0.6;" << endl;
	gnuplotfile << "set xrange [0:" << seqs->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [" << ymin1 << ":" << ymax1 <<  "];" << endl;
	gnuplotfile << "set title \"" << name1 << "\" noenhanced;" << endl;
	gnuplotfile << "plot \""+filebasename+".data\" using 3:4 notitle with linespoints lt 1 pt 7 ps .6";
	int iix = 3;
	int ival = 4;
	for (int j=1; j<current1+1; j++) {
		iix = iix+2;
		ival = ival+2;
		gnuplotfile << ", \""+filebasename+".data\" using " << iix << ":" << ival << " notitle with linespoints lt 1 pt 7 ps .6";
	}
	gnuplotfile << ";" << endl;

	gnuplotfile << "set size 1,0.2;" << endl;
	gnuplotfile << "set origin 0.0,0.4" << endl;
	gnuplotfile << "set xrange [0:" << seqs->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [-1.1:1.1];" << endl;
	gnuplotfile << "set title \"Scores\"" << endl;
	gnuplotfile << "plot \""+filebasename+".data\" using 1:2 notitle with linespoints lt 1 pt 7 ps .6;" << endl;

	gnuplotfile << "set size 1,0.4;" << endl;
	gnuplotfile << "set origin 0.0,0.0;" << endl;
	gnuplotfile << "set title \"" << name2 << "\" noenhanced;" << endl;
	gnuplotfile << "set xrange [0:" << seqs->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [" << ymin2 << ":" << ymax2 <<  "];" << endl;
	iix = iix + 2;
	ival = ival + 2;
	gnuplotfile << "plot \""+filebasename+".data\" using " << iix << ":" << ival << " notitle with linespoints lt 1 pt 7 ps .6";
	for (int j=1; j<current2+1; j++) {
		iix = iix+2;
		ival = ival+2;
		gnuplotfile << ", \""+filebasename+".data\" using " << iix << ":" << ival << " notitle with linespoints lt 1 pt 7 ps .6";
	}
	gnuplotfile << ";" << endl;
	gnuplotfile << "unset multiplot" << endl;

	gnuplotfile.close();
}


}
