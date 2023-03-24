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


#ifndef PCSEQUENCES_H_
#define PCSEQUENCES_H_

#include "PCSequence.h"
#include "Sequences.h"
#include <map>
#include <utility>

namespace musical {

/**
 * Pair of two sequences of PCSymbol.
 */
class PCSequences: public musical::Sequences {

private:
	/**
	 * Constructor
	 */
	PCSequences(); //private to ensure that only PCSequences are assigned

public:
	/**
	 * Constructor
	 * seq1 : pointer to first sequence
	 * seq2 : pointer to second sequence
	 */
	PCSequences(PCSequence * seq1, PCSequence * seq2) : Sequences(seq1,seq2) { computeAndApplyPitchRotation(); };

	/**
	 * Destructor
	 */
	virtual ~PCSequences();

	/**
	 * Computes the rotation of the pitchHistogram such that there is maximum of overlap between seq1 and seq2
	 */
	int getPitchRotation() const { return pitchRotation; };

	/**
	 * Get the n^th pitchrotation
	 * n = 0 : pitch rotation with highest pitch histogram intersection
	 * n = 1 : pitch rotation with second highest pitch histogram intersecion
	 * etc
	 * if n > number of found intersections: return 0
	 */
	int getNthComputedPitchRotation(unsigned int n) const {
		if (n >= intersections.size() ) {
			std::cerr << "Warning: Number of computed pitchrotation intersections is smaller than " << n << "." << std::endl;
			return 0;
		}
		return intersections[intersections.size()-1-n].first;
	}

	/**
	 * Provide a pitch rotation
	 */
	void setPitchRotation(int s) { pitchRotation = s; }

	/**
	 * Get the pitchrotation in base-12 representation
	 */
	int getPitch12Rotation() const;


private:
	/**
	 * The rotation of seq2 to correspond with seq1
	 */
	int pitchRotation;

	/**
	 * All rotations to to be done to the pitch context vectors of seq2 to correspond with seq1, ordered in ascending order of intersection
	 */
	std::vector<std::pair<int,double> > intersections; // (rotation, intersection) pairs in descending order of intersection

	/**
	 * Computes the rotation of seq2 to correspond with seq1
	 */
	void computePitchRotation();

	/**
	 * Rotate seq2 to correspond with seq1
	 */
	void applyPitchRotation();

	void computeAndApplyPitchRotation();

};

}

#endif /* PCSEQUENCES_H_ */
