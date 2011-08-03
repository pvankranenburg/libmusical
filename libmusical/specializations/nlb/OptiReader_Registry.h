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


#ifndef OPTIREADER_REGISTRY_H_
#define OPTIREADER_REGISTRY_H_

#include "Reader.h"

namespace musical {

/**
 * This reads OptiSymbols, but stores the individual attributes of the symbols in a registry of key-value pairs instead of class attributes.
 * This results in considerable slowing down of the computation of the alignment because of all the value lookups.
 */
class OptiReader_Registry: public musical::Reader {
public:
	OptiReader_Registry();
	virtual ~OptiReader_Registry();

	/**
	 * Generates the sequence of SymbolRegistry symbols.
	 */
	Sequence * generateSequence();
};

}

#endif /* OPTIREADER_REGISTRY_H_ */
