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

namespace musical {

/**
 * Max of two doubles
 */
inline double fmax(double a,double b) { return (a>b)?a:b; }

/**
 * Computes how much to shift histogram 2 in order to get maximal intersection with histogram 1
 */
int histogramShift(double hist1[], int length1, double hist2[], int length2);
int histogramShift_bound(double hist1[], int length1, double hist2[], int length2);

}

#endif /* MISCFUNCTIONS_H_ */
