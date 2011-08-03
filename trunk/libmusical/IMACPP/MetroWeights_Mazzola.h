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

#ifndef METROWEIGHTS_MAZZOLA_H_
#define METROWEIGHTS_MAZZOLA_H_

#include "WeightSet.h"
#include <vector>

class MetroWeights_Mazzola  {
public:

    MetroWeights_Mazzola(int p, int l, int off, int res, int maxPeriod) : m_p(p), m_l(l), offset(off), resolution(res), m_maxPeriod(maxPeriod) {};
    MetroWeights_Mazzola(int p, int l, int off, int res) : m_p(p), m_l(l), offset(off), resolution(res), m_maxPeriod(0) {};
    MetroWeights_Mazzola() : m_p(0), m_l(2), offset(0), resolution(1), m_maxPeriod(0) {};

    int m_p;
    int m_l;
    int offset;
    int resolution;
    int m_maxPeriod;

    WeightSet getWeights(std::vector<int> onsets);

    int power(int base, int exp) {
    	if (base == 0) return 1; int res = base; for (int i=1; i<exp; i++) res*=base; return res;
    }
    

};


#endif

