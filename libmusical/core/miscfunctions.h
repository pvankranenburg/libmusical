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


#ifndef MISCFUNCTIONS_H_
#define MISCFUNCTIONS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <sstream>

namespace musical {

/**
 * Max of two doubles
 */
inline double fmax(double a,double b) { return (a>b)?a:b; };

class BadConversion : public std::runtime_error {
public:
	BadConversion(const std::string& s)	: std::runtime_error(s) { }
};

inline int convertToInt(const std::string& s) {
	std::istringstream i(s);
	int x;
	if (!(i >> x))
	  throw BadConversion("convertToInt(\"" + s + "\")");
	return x;
}

inline float convertToFloat(const std::string& s) {
	std::istringstream i(s);
	float x;
	if (!(i >> x))
	  throw BadConversion("convertToFloat(\"" + s + "\")");
	return x;
}

inline std::string convertToString(const int i) {
	std::ostringstream o;
	if (!(o << i))
	  throw BadConversion("convertToString(...)");
	return o.str();
}

inline std::string convertToString(const double d) {
	std::ostringstream o;
	if (!(o << d))
	  throw BadConversion("convertToString(...)");
	return o.str();
}

}

#endif /* MISCFUNCTIONS_H_ */
