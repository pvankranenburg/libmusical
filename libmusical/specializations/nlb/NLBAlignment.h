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


#include "libmusical.h"

#ifndef NLBALIGNMENT_H_
#define NLBALIGNMENT_H_

#include "NLBJSONReader.h"

//Sequences
#include "NLBSequence.h"
#include "NLBSequences.h"

//SimilarityRaters
#include "NLBOptiSimilarityRater.h"
#include "NLBExactPitch40SimilarityRater.h"
#include "NLBExactPitch40IMASimilarityRater.h"
#include "NLBExactPitch40MWSimilarityRater.h"
#include "NLBMidiIntervalSimilarityRater.h"
#include "NLBPitchbandIMASimilarityRater.h"
#include "NLBPitchbandSimilarityRater.h"
#include "NLBAlwaysOneSimilarityRater.h"
#include "NLBIMAGapRater.h"
#include "NLBIMAAffineGapRater.h"

#endif /* NLBALIGNMENT_H_ */
