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


#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <string>

namespace musical {

/**
 * Abstract symbol
 */
class Symbol {
public:
	/**
	 * Constructor
	 */
	Symbol();

	/**
	 * Destructor
	 */
	virtual ~Symbol();

	/**
	 * Get the next symbol
	 */
	Symbol * getNext() const { return next; }

	/**
	 * Get the previous symbol
	 */
	Symbol * getPrevious() const { return previous; }

	/**
	 * Set the next symbol
	 */
	void setNext(Symbol * n) { next = n; }

	/**
	 * Set the previous symbol
	 */
	void setPrevious(Symbol * p) { previous = p; }

	/**
	 * Set the id
	 */
	void setId(const std::string i) { id = i; }

	/**
	 * Get the id
	 */
	std::string getId() const { return id; }

	/**
	 * Returns a string representation of the symbol.
	 */
	virtual std::string toString() const = 0;

	/**
	 * Returns a float representation of the symbol.
	 * Default: return 1.0. Can be overridden by derived classes
	 * Used by AlignmentVisualizer.
	 */
	virtual float toFloat() const { return 1.0; }

protected:
	std::string id;
	Symbol * next;
	Symbol * previous;

};

}

#endif /* SYMBOL_H_ */
