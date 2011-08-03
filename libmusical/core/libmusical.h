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

/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */


#ifndef LIBMUSICAL_H_
#define LIBMUSICAL_H_

//functions
#include "miscfunctions.h"

//Data sources
#include "JSONFileSource.h"
#include "JSONMysqlSource.h"

//Readers
#include "Reader.h"

//Sequences
#include "Sequence.h"
#include "Sequences.h"

//SimilarityRaters

//GapRaters
#include "ConstantLinearGapRater.h"
#include "ConstantAffineGapRater.h"

//Algorithms
#include "NeedlemanWunsch.h"
#include "NeedlemanWunschGotoh.h"
#include "SmithWaterman.h"


#endif /* LIBMUSICAL_H_ */
