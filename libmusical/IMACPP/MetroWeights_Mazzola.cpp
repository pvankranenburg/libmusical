/*
Copyright 2011 Chris Dyer
Ported from java to c++ by Peter van Kranenburg (peter.van.kranenburg@meertens.knaw.nl)

This file is part of IMACPP.

IMACPP is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IMACPP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IMACPP.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MetroWeights_Mazzola.h"
#include "OnsetGroup_Memory.h"
#include "MeterCollection.h"
#include "WeightSet.h"
#include "MetroMath.h"
#include <vector>
#include <iostream>
using namespace std;

WeightSet MetroWeights_Mazzola::getWeights(vector<int> onsets) {
	OnsetGroup_Memory ong(onsets);
	int len = onsets.size();
	int lastOnset = onsets[len-1];
	vector<int> ws(lastOnset+1,0);
	int length = lastOnset+1-onsets[0];
	vector<int> spectWeight(length,0);

	int i;
	for (i = 0; i<lastOnset+1;i++) ws[i] = 0;
	for (i = 0; i<(int)spectWeight.size();i++) spectWeight[i] = 0;
	int minLength = m_l;
	int maxPeriod = m_maxPeriod;
	if (maxPeriod == 0){
	    if(minLength != 0){
		 maxPeriod = lastOnset/minLength+1;}
	    else{
		maxPeriod = lastOnset/2;
	    }
	}
	//const int t = maxPeriod;
	//const int end = lastOnset - minLength;
	int counter = 1;
	int pfactor = 1;
        
	
	MeterCollection meterC(maxPeriod);

	while (counter <= maxPeriod) {  // counter = period length


		vector<int> factors = MetroMath::getAllFactors(counter);//alle Teiler
		
		for (i=onsets[0]; i<=lastOnset; i+=resolution) {
			int l = ong.getLength(i, counter, lastOnset);
			if (l>=minLength) {
			    if (!meterC.contains(counter, i, l, factors)) {//is this local meter already listed in meterCollection?
					if (m_p > 0) pfactor = power(l, m_p);
					meterC.add(counter, i, l,pfactor);
					for (int j=0; j<=l; j++) {
						ws[j*counter+i]+=pfactor;
						//cout << pfactor << " ";
					}
					//spectralweight:
					for(int k=onsets[0]; k<=lastOnset; k++) {
					    if(k%counter == i%counter)//onset mod period = onset_of_meter mod period?
							spectWeight[k-onsets[0]]+=pfactor;
					}
				}
			}
		}
		counter++;
	}
	
	//meterC.printAll();
	counter = 0;
	vector<int> w(len,0);
	for (int aa = 0; aa<len; aa++) {
		 w[aa] = ws[onsets[aa]];
	}
	WeightSet ret;
	ret.weights = w;
	ret.spectralWeight = spectWeight;
	ret.meterCollection = meterC;
	return ret;
}

