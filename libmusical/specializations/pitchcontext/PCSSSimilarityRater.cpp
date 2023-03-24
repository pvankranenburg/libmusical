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

#include "PCSSSimilarityRater.h"
#include "PCSymbol.h"
#include "PCSequences.h"

namespace musical {

double PCSSSimilarityRater::computeSSDistance(vector<double> &a, vector<double> &b) const {
	double res = 0.0;
	for(int i=0; i<a.size(); i++){
		res += (b[i]-a[i]) * (b[i]-a[i]);
	}
	return res;
}

double PCSSSimilarityRater::getScore(Sequences * seqs, int x1, int y1, int x2, int y2) const {
	PCSymbol * s1 = static_cast<PCSymbol *>(seqs->getSeq1()->getSymbolAt(x2));
	PCSymbol * s2 = static_cast<PCSymbol *>(seqs->getSeq2()->getSymbolAt(y2));
	
	double pre_ss  = computeSSDistance(s1->pc_pre, s2->pc_pre);
	double post_ss = computeSSDistance(s1->pc_post, s2->pc_post);

	return 1.0 - 2 * (pre_ss + post_ss / 80.0);

}

}
