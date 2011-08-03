/*
Copyright 2011 Chris Dyer
Ported from java to c++ by Peter van Kranenburg (peter.van.kranenburg@meertens.knaw.nl)

This file is part of IMACPP.

IMACPP is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IMACPP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IMACPP.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef METERCOLLECTION_H_
#define METERCOLLECTION_H_

#include "Metrum.h"
#include <vector>

class MeterCollection {
public:
    //ein Array der L�nge onset/2 (f�r l=2) ist  zwar sehr umfangreich, bei Nutzung
    //eines HashMap m�ssen die Eintr�ge aber nachtr�glich f�r die Darstellung sortiert werden
   std::vector< std::vector<Metrum> > m_data;

    /**
     * Creates a new MeterCollection with capacity to store information about
     * periods up to length max.
     */
    MeterCollection(int max=0);

    MeterCollection(std::vector< std::vector<Metrum> > data);

    void printAll();

    int size(){ return 0; };

   std::vector< std::vector<Metrum> > getMeters() { return m_data; };

    /**
     * Add metrum (period, onset, length) to set
     */
    void add(int period, int onset, int length, int metrumWeight);
    
    /**
     * Are the onsets described by metrum (period, onset, length) already
     * present in any of the metra already present.
     */
    bool contains(int period, int onset, int length);

    /**
     * Are the onsets described by metrum (period, onset, length) present
     * in any of metra present who have a period listed in factors?
     */
    bool contains(int period, int onset, int length, std::vector<int> factors);
    /**
     * how many metra are there with a period = p
     */
    int weight(int p);

    /**
     * how many metra are there with period = p and phase = h
     */
    int weight(int p, int h) { return 0; };


};

#endif

