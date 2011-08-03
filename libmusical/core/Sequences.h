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


#ifndef SEQUENCES_H_
#define SEQUENCES_H_

#include <vector>
using namespace std;

#include "Sequence.h"

namespace musical {

/**
 * Abstract container of a pair of sequences.
 */
class Sequences {
public:
	Sequences();
	Sequences(Sequence * s1, Sequence * s2) : seq1(s1), seq2(s2) { };
	virtual ~Sequences();

	void setSeq1(Sequence * s) {seq1 = s; };
	void setSeq2(Sequence * s) {seq2 = s; };

	Sequence * getSeq1() {return seq1;};
	Sequence * getSeq2() {return seq2;};

	Sequence * seq1;
	Sequence * seq2;
};

}

#endif /* SEQUENCES_H_ */
