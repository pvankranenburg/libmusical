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

#include "MeterCollection.h"
#include "Metrum.h"
#include "MetroMath.h"
#include <vector>
#include <iostream>
using namespace std;

MeterCollection::MeterCollection(int max) {
	vector<Metrum> leeg;
	for (int i=0; i < max+1; i++ ) m_data.push_back(leeg);
}

MeterCollection::MeterCollection(vector< vector<Metrum> > data){
	m_data.clear();
	vector<Metrum> leeg;
	for (int i = 0; i < data.size(); i++ ) m_data.push_back(leeg);
	for (int i = 0; i < data.size(); i++) {
	    if(data[i].size() != 0)
	        m_data[i] = data[i];
	}
}

void MeterCollection::printAll() {
	for (int i = 0; i<m_data.size(); i++) {
	    if (m_data[i].size() != 0) {
			cout << "meters (period len=" << i << "): ";
			int l = m_data[i].size();
			for (int j=0; j<l; j++) {
			    cout << m_data[i][j].toString() << " ";
			}
			cout << endl;
	    }
	}
}

    /**
     * Add metrum (period, onset, length) to set
     */
void MeterCollection::add(int period, int onset, int length, int metrumWeight) {
	Metrum m(period, onset, length, metrumWeight);
	m_data[period].push_back(m);
}

    /**
     * Are the onsets described by metrum (period, onset, length) already
     * present in any of the metra already present.
     */
bool MeterCollection::contains(int period, int onset, int length) {
	vector<int> factors = MetroMath::getAllFactors(period);
	return contains(period, onset, length, factors);
}

    /**
     * Are the onsets described by metrum (period, onset, length) present
     * in any of metra present who have a period listed in factors?
     */
bool MeterCollection::contains(int period, int onset, int length, vector<int> factors) {

	if (factors.size() == 0) return false;
	for (int i =0; i<factors.size(); i++) {
		int l = m_data[factors[i]].size();
		for (int j=0; j<l; j++) {
		    Metrum m = m_data[factors[i]][j];
		    if (m.contains(period, onset, length)) return true;
		}
	}
	return false;
}

    /**
     * how many metra are there with a period = p
     */
int MeterCollection::weight(int p) {
	return m_data[p].size();
}



