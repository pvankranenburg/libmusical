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

#include "OnsetGroup_Memory.h"
#include <vector>
using namespace std;

OnsetGroup_Memory::OnsetGroup_Memory(vector<int> onsets) {
	int len = onsets.size();
	int lastOnset = onsets[len-1];
	int i;
	for (i=0; i<=lastOnset; i++)
	    m_data.push_back(false);
	for (i=0; i<len; i++)
	    m_data[onsets[i]] = true;
}


int OnsetGroup_Memory::getLength(int time, int period, int lastOnset) {
	if (!m_data[time]) return -1;//die Einsatzzeit existiert im Stück nicht
	if ((time >= period) && (m_data[time-period])) return 0;//Test nach links!!!!!
	int count = 0;
	//int p = time+period; alte Version: eine Länge zuwenig wurde ausgegeben!
	int p = time+period;
	while ((p <= lastOnset) && (m_data[p])) {
	    count++;
	    p += period;
	}
	return count;
}

