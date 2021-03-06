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


#include "Sequences.h"
#include "SimilarityRater.h"

namespace musical {

Sequences::Sequences() : seq1(NULL), seq2(NULL) {
	// TODO Auto-generated constructor stub

}

Sequences::~Sequences() {
	// TODO Auto-generated destructor stub
	clearResults();
}

/*
double Sequences::getNormalizedScore(const int c=0, SimilarityRater * sr) const {
	if ( c >= (int)scores.size()) {
		std::cerr << c << "th score not available" << std::endl;
		return -std::numeric_limits<double>::infinity();
	}
	double score = scores[c];

	//compute score of alignment of seq1 with itself
	double score1 = 0.0;
	for ( int i=0; i<seq1->symbols.size(); i++) {
		score1 =
	}

};
*/

void Sequences::clearResults() {
	for (unsigned int i=0; i<alignments.size(); i++) {
		for (unsigned int j=0; j<alignments[i].size(); j++) {
			delete alignments[i][j];
		}
		alignments[i].clear();
	}
	alignments.clear();

	scores.clear();

	//for derived algorithms:
	this->specificClear();
}

std::vector<double> Sequences::getSimilarityScores(SimilarityRater * sr) {
	std::vector<double> res;
	for (unsigned int i=0; i<seq1->size(); i++) {
		for (unsigned int j=0; j<seq2->size(); j++) {
			res.push_back(sr->getScore(this, i, j, i, j));
		}
	}
	return res;
}


}
