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


#ifndef NLBSYMBOL_H_
#define NLBSYMBOL_H_

#include "Symbol.h"

namespace musical {

/**
 * Represents an "NLBSymbol"
 * has: pitch40, IMA and phrasepos.
 */
class NLBSymbol: public musical::Symbol {
public:
	/**
	 * Constructor
	 */
	NLBSymbol();

	/**
	 * Destructor
	 */
	virtual ~NLBSymbol();

	/**
	 * Returns a float representation of the symbol
	 */
	virtual float toFloat() const { return (float)pitch40; }

	/**
	 * Returns a string representation of the symbol
	 */
	std::string toString() const ;

	int pitch40;
	float phrasepos;
	float IMA;
	long onset;
	int phrase;
	float songpos;
	float beatstrength;
};

}

#endif /* NLBSYMBOL_H_ */
