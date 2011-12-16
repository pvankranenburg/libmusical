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


#ifndef NLBSEQUENCES_H_
#define NLBSEQUENCES_H_

#include "NLBSequence.h"
#include "Sequences.h"
#include <map>

namespace musical {

/**
 * Pair of two sequences of NLBSymbol.
 */
class NLBSequences: public musical::Sequences {

private:
	/**
	 * Constructor
	 */
	NLBSequences(); //private to ensure that only NLBSequences are assigned

public:
	/**
	 * Constructor
	 * seq1 : pointer to first sequence
	 * seq2 : pointer to second sequence
	 */
	NLBSequences(NLBSequence * seq1, NLBSequence * seq2) : Sequences(seq1,seq2) { computePitch40HistogramShift(); };

	/**
	 * Destructor
	 */
	virtual ~NLBSequences();

	/**
	 * Computes how much the base40 pitch of seq2 has to be shifted in order to correspond to the pitch of seq1.
	 * This is computed by finding the shift of the normalized pitch histograms of seq1 and seq2 that results
	 * in highest histogram intersection.
	 */
	double getPitch40Shift() const { return pitch40HistogramShift; };

private:
	int pitch40HistogramShift;

	/**
	 * Computes the interval that has to be added to the pitches of seq2 to correspond with seq1
	 */
	void computePitch40HistogramShift();

};

}

#endif /* NLBSEQUENCES_H_ */
