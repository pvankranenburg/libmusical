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


#include <string>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
using namespace std;

#include "PCTXTReader.h"
#include "PCSymbol.h"
#include "PCSequence.h"


namespace musical {


PCTXTReader::~PCTXTReader() {
	// TODO Auto-generated destructor stub
}

Sequence* PCTXTReader::generateSequence() const {
	//create a new sequence
	PCSequence * nwseq = new PCSequence; //NB PCSequence contains a pitch histogram

	vector<string>::const_iterator source_it = source.begin();
	//Melody length

	int length = stoi(*source_it);

	++source_it;
	//clog << "NEXT: " << *source_it << endl;

	//Add symbols to sequence
	for(int i=0; i<length; i++) {
		PCSymbol* s = new PCSymbol();
		nwseq->addSymbol(s);
	}

	//First read pitch40, weight, and fill histogram
	for(int i=0; i<length; i++) {
		//read weights from string
		vector<double> weights;
		stringstream s(*source_it);
		int p40;
		double wt;
		s >> p40;
		s >> wt;
		static_cast<PCSymbol*>(nwseq->getSymbolAt(i))->pitch40 = p40;
		static_cast<PCSymbol*>(nwseq->getSymbolAt(i))->weight = wt;
		nwseq->pitchHistogram[p40%40] += wt;
		++source_it;
		//clog << "NEXT: " << *source_it << endl;
	}

	//normalize histogram
	double histsum = std::accumulate(nwseq->pitchHistogram.begin(), nwseq->pitchHistogram.end(), 0.0);
	for(unsigned int i = 0; i<nwseq->pitchHistogram.size(); i++){
		nwseq->pitchHistogram[i] = nwseq->pitchHistogram[i] / histsum;
	}

	//Read pre and post contexts into symbols. And Normalize (sum=1)
	for(int i=0; i<length; i++) {
		double weight = 0.0;

		//PRE
		vector<double> weights_pre;
		stringstream s_pre(*source_it);
		while(s_pre >> weight) weights_pre.push_back(weight);
		if(weights_pre.size() != 40) clog << "Warning: incorrect length of pre context vector " << i << " : " << *source_it << endl;
		//normalize pre weights
		double weightsum = std::accumulate(weights_pre.begin(), weights_pre.end(), 0.0);
		for(unsigned int i = 0; i<weights_pre.size(); i++){
			weights_pre[i] = weights_pre[i] / weightsum;
		}
		static_cast<PCSymbol*>(nwseq->getSymbolAt(i))->pc_pre = weights_pre;

		// clog << "READING: ";
		// for(int j=0; j<weights_pre.size(); j++) {
		// 	clog << weights_pre[j] << " ";
		// }
		// clog << " - ";
		// for(int j=0; j<weights_pre.size(); j++) {
		// 	clog << static_cast<PCSymbol*>(nwseq->getSymbolAt(1))->pc_pre[j] << " ";
		// } 
		// clog << endl;
		
		// ++source_it;
		// clog << "NEXT: " << *source_it << endl;
		
		//POST
		vector<double> weights_post;
		stringstream s_post(*source_it);
		while(s_post >> weight) weights_post.push_back(weight);
		if(weights_post.size() != 40) clog << "Warning: incorrect length of post context vector " << i << " : " << *source_it << endl;
		//normalize post weights
		weightsum = std::accumulate(weights_post.begin(), weights_post.end(), 0.0);
		for(unsigned int i = 0; i<weights_post.size(); i++){
			weights_post[i] = weights_post[i] / weightsum;
		}
		static_cast<PCSymbol*>(nwseq->getSymbolAt(i))->pc_post = weights_post;
	
		++source_it;
		//clog << "NEXT: " << *source_it << endl;
	}

	//set next and previous
	if ( nwseq->size() > 1) {
		nwseq->getSymbolAt(0)->setNext(nwseq->getSymbolAt(1));
		nwseq->getSymbolAt(0)->setPrevious(NULL);
		for( unsigned int i = 1; i<nwseq->size()-1; i++) {
			nwseq->getSymbolAt(i)->setPrevious(nwseq->getSymbolAt(i-1));
			nwseq->getSymbolAt(i)->setNext(nwseq->getSymbolAt(i+1));
		}
		nwseq->getSymbolAt(nwseq->size()-1)->setPrevious( nwseq->getSymbolAt(nwseq->size()-2) );
		nwseq->getSymbolAt(nwseq->size()-1)->setNext(NULL);
	} else if (nwseq->size() == 1) {
		nwseq->getSymbolAt(0)->setNext(NULL);
		nwseq->getSymbolAt(0)->setPrevious(NULL);
	}

	// set name
	std::string base_filename = inputfilename.substr(inputfilename.find_last_of("/\\") + 1);
	nwseq->setName(base_filename);

	return nwseq;
}

/**
 * Vector initializer
*/
std::vector<std::string> PCTXTReader::source_init(std::string filename) {
	ifstream infile;
	infile.open(filename);

	vector<string> lines;

	string line;
	while (std::getline(infile, line)) {
		lines.push_back(line);
	}

	infile.close();

	return lines;
}

}
