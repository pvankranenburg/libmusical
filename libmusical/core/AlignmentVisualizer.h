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

#include "AlignmentAlgorithm.h"

#ifndef ALIGNMENTVISUALIZER_H_
#define ALIGNMENTVISUALIZER_H_

namespace musical {

/**
 * Provides various methods to visualize an alignment.
 * Derived classes could provide methods for specific kinds of symbols
 */
class AlignmentVisualizer {
protected:
	/**
	 * Constructor
	 */
	AlignmentVisualizer();

public:

	/**
	 * Constructor.
	 * Assigns an alignment algorithm to the AlignmentVisualizer.
	 * The alignment should have been carried out.
	 */
	AlignmentVisualizer(Sequences * sqs): seqs(sqs) { };

	/**
	 * Destructor
	 */
	virtual ~AlignmentVisualizer();

	/**
	 * Print a textual representation of alignment c to stdout
	 * Default c=0
	 */
	void basicStdoutReport(const int c=0) const;

	/**
	 * Produces a gnuplot inputfile that shows the aligned sequences below each other.
	 * Values for the symbols are obtained from Symbol::toFloat() (or derived).
	 * This function creates two files:
	 * <filebasename>.gnuplot - contains the gnuplot commands
	 * <filebasename>.data - contains the alignment data
	 * Gnuplot will produce <filebasename>.ps
	 */
	void toGnuPlot(const std::string filebasename, const int c=0) const;

	/**
	 * Same as toGnuPlot, but allows to set the extent of the y-axis of the resulting
	 * Plot.
	 */
	void toGnuPlot(const std::string filebasename, const float minyvalue1, const float maxyvalue1, const float minyvalue2, const float maxyvalue2, const int c=0) const;


	/**
	 * Same as toGnuPlot, draws lines between symbols not divided by gaps.
	 */
	void toGnuPlotLineSegments(const std::string filebasename, const float minyvalue1, const float maxyvalue1, const float minyvalue2, const float maxyvalue2, const int c=0) const;

protected:

	/**
	 * Pointer to the (aligned) sequences.
	 */
	Sequences * seqs;

};

}

#endif /* ALIGNMENTVISUALIZER_H_ */
