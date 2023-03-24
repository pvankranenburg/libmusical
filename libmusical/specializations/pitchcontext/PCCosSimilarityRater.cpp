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


#include <cmath>

#include "PCCosSimilarityRater.h"
#include "PCSymbol.h"
#include "PCSequences.h"

namespace musical {

double PCCosSimilarityRater::computeCosSimilarity(vector<double> &a, vector<double> &b) const {
	double res = 0.0;

    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
     for(unsigned int i = 0u; i < 40; ++i) {
        dot += a[i] * b[i] ;
        denom_a += a[i] * a[i] ;
        denom_b += b[i] * b[i] ;
    }
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;	

	return res;
}

double PCCosSimilarityRater::getScore(Sequences * seqs, int x1, int y1, int x2, int y2) const {
	PCSymbol * s1 = static_cast<PCSymbol *>(seqs->getSeq1()->getSymbolAt(x2));
	PCSymbol * s2 = static_cast<PCSymbol *>(seqs->getSeq2()->getSymbolAt(y2));
	
	double pre_cs  = computeCosSimilarity(s1->pc_pre, s2->pc_pre);
	double post_cs = computeCosSimilarity(s1->pc_post, s2->pc_post);

	return -1.0 + 2 * (pre_cs + post_cs) / 2.0;

}

}
