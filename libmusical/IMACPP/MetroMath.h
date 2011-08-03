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

#ifndef METROMATH_H_
#define METROMATH_H_

#include<vector>

class MetroMath {

public:

    static int ggt(int a, int b)
    {
	if (b==0)
	    return a;
	else
	    return ggt(b, a%b);
    }

    static int ggt(std::vector<int> periods){
	//ggt aller Abst�nde wird gerechnet
	int gcd = -1;
	if(periods.size() != 0) gcd = periods[0];//ggt wird initialisiert
	for(unsigned int i=1; gcd!=1 && i < periods.size(); i++){
	    gcd = ggt(gcd,periods[i]);
	}
	return gcd;
    }
 

  
  
  
    /**
     * return the greatest common divisor of all integers from a[i] - a[i+1]
     */
    
   
    static int metro_ggt(std::vector<int> onsets){
	//array f�r alle Abst�nde
	std::vector<int> a(onsets.size()-1,0);
	int dist;
	for (unsigned int i = 0; i < a.size(); i++) {
	    dist = onsets[i+1] - onsets[i];
	    a[i] = dist;
	}
	//ggt aller Abst�nde wird gerechnet
	int gcd = -1;
	if(a.size() != 0) gcd = a[0];//ggt wird initialisiert
	for(unsigned int i=1; gcd!=1 && i < a.size(); i++){
	    gcd = ggt(gcd,a[i]);
	}
	return gcd;
    }



    /**
     * return array containing all integral divisors of x
     */
    
   
  
    static std::vector<int> getAllFactors(int x) {
	std::vector<int> il;
	for (int i = 1; i<x; i++) {
	    if (x%i == 0) il.push_back(i);
	}
	return il;
    }


};
   
#endif

