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

void AlignmentVisualizer::basicStdoutReport(int c) {

	if ( c >= al->getNoOfAlignments() ) {
		cerr << "No alignment available at index " << c << endl;
		return;
	}

	for ( int i = 0; i < al->getAlignmentSize(c); i++ ) {
		std::string symbol1 = "s1";
		std::string symbol2 = "s2";

		if ( al->getTraceElement(i,c)->getIx1() == -1 )
			symbol1 = "x";
		else symbol1 = al->getSeq1()->getSymbolAt(al->getTraceElement(i,c)->getIx1())->toString();

		if ( al->getTraceElement(i,c)->getIx2() == -1 )
			symbol2 = "x";
		else symbol2 = al->getSeq2()->getSymbolAt(al->getTraceElement(i,c)->getIx2())->toString();

		cout << "(" << al->getTraceElement(i,c)->getIx1() << ")[" << symbol1 << "] - (" << al->getTraceElement(i,c)->getIx2() <<  ")[" << symbol2 << "]" << " With score: " << al->getTraceElement(i,c)->thisscore << endl;
	}

}

void AlignmentVisualizer::toGnuPlot(string filebasename, int c) {
	float maxvalue = -std::numeric_limits<float>::infinity();
	float minvalue = std::numeric_limits<float>::infinity();

	for ( int i = 0; i < al->getAlignmentSize(c); i++ ) {
			if ( al->getTraceElement(i,c)->getIx1() != -1 ) { //skip gaps
			float value = al->getSeq1()->getSymbolAt(al->getTraceElement(i,c)->getIx1())->toFloat();
			if (value > maxvalue) maxvalue = value;
			if (value < minvalue) minvalue = value;
		}
		if ( al->getTraceElement(i,c)->getIx2() != -1 ) { //skip gaps
			float value = al->getSeq2()->getSymbolAt(al->getTraceElement(i,c)->getIx2())->toFloat();
			if (value > maxvalue) maxvalue = value;
			if (value < minvalue) minvalue = value;
		}
	}

	toGnuPlot(filebasename, minvalue, maxvalue, c);
}

void AlignmentVisualizer::toGnuPlot(string filebasename, float minyvalue, float maxyvalue, int c) {

	if ( c >= al->getNoOfAlignments() ) {
		cerr << "No alignment available at index " << c << endl;
		return;
	}


	//first build the data file

	vector<int> seq1index;
	vector<float> seq1value;
	vector<int> seq2index;
	vector<float> seq2value;

	for ( int i = 0; i < al->getAlignmentSize(c); i++ ) {
			if ( al->getTraceElement(i,c)->getIx1() != -1 ) { //skip gaps
			float value = al->getSeq1()->getSymbolAt(al->getTraceElement(i,c)->getIx1())->toFloat();
			seq1index.push_back(i);
			seq1value.push_back(value);
		}
		if ( al->getTraceElement(i,c)->getIx2() != -1 ) { //skip gaps
			float value = al->getSeq2()->getSymbolAt(al->getTraceElement(i,c)->getIx2())->toFloat();
			seq2index.push_back(i);
			seq2value.push_back(value);
		}
	}
	//write to file
	ofstream datafile;
	datafile.open((filebasename+".data").c_str());
	unsigned int maxsize = max ( seq1index.size(), seq2index.size() );
	for ( unsigned int i=0; i<maxsize; i++) {
		if ( i<seq1index.size() ) datafile << seq1index[i] << "," << seq1value[i];
		else datafile << ",";
		datafile << "," << al->getTraceElement(i,c)->thisscore;
		if ( i<seq2index.size() ) datafile << "," << seq2index[i] << "," << seq2value[i];
		datafile << endl;
	}
	datafile.close();

	ofstream gnuplotfile;
	gnuplotfile.open((filebasename+".gnuplot").c_str());
	//if minvalue == maxvalue : provide some margin

	float ymax = maxyvalue;
	float ymin = minyvalue;

	if ( maxyvalue == minyvalue ) {
		ymax = maxyvalue + 1.0;
		ymin = minyvalue - 1.0;
	}

	string name1 = al->getSeq1()->getName();
	string name2 = al->getSeq2()->getName();

	gnuplotfile << "set terminal postscript landscape enhanced mono dashed lw 1 \"Helvetica\" 10;" << endl;
	gnuplotfile << "set output \"alignment.ps\";" << endl;
	gnuplotfile << "set datafile separator \",\"" << endl;
	gnuplotfile << "set grid;" << endl;
	gnuplotfile << "set multiplot;" << endl;
	gnuplotfile << "set size 1,0.4;" << endl;
	gnuplotfile << "set origin 0.0,0.6;" << endl;
	gnuplotfile << "set xrange [0:" << al->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [" << ymin << ":" << ymax <<  "];" << endl;
	gnuplotfile << "set title \"" << name1 << "\" noenhanced;" << endl;
	gnuplotfile << "plot \"alignment.data\" using 1:2 notitle;" << endl;

	gnuplotfile << "set size 1,0.2;" << endl;
	gnuplotfile << "set origin 0.0,0.4" << endl;
	gnuplotfile << "set xrange [0:" << al->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [-1.1:1.1];" << endl;
	gnuplotfile << "set title \"Scores\"" << endl;
	gnuplotfile << "plot \"alignment.data\" using 3 notitle with lines;" << endl;

	gnuplotfile << "set size 1,0.4;" << endl;
	gnuplotfile << "set origin 0.0,0.0;" << endl;
	gnuplotfile << "set title \"" << name2 << "\" noenhanced;" << endl;
	gnuplotfile << "set xrange [0:" << al->getAlignmentSize() << "];" << endl;
	gnuplotfile << "set yrange [" << ymin << ":" << ymax <<  "];" << endl;
	gnuplotfile << "plot \"alignment.data\" using 4:5 notitle;" << endl;
	gnuplotfile << "unset multiplot" << endl;

	gnuplotfile.close();
}

}
