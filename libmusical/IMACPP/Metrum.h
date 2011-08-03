/*
Copyright 2011 Mona Brand
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

#ifndef METRUM_H_
#define METRUM_H_


#include <string>
#include <vector>


class Metrum {

public:

    int period;
    int onset;
    int length;
    int metrumWeight;
    int phase;


    Metrum(int p, int o, int l, int w) : period(p), onset(o), length(l), metrumWeight(w), phase(o%p), selection(true) {};

    /**Konstruktor macht aus einem Namen der Form
     * (o=..., period=..., phase=..., l=...)
     * ein Metrum
     */
    /*
    public Metrum (String name, int weight){
	//der String wird zerlegt und die integers abgelegt
	StringTokenizer tok = new StringTokenizer(name,"=,)");
	int[] arg = new int[4];
	for(int i = 0; tok.hasMoreTokens();){
	    String token = tok.nextToken();
	    try{
		arg[i] = Integer.parseInt(token);
		i++;
	    }catch(NumberFormatException ne){}
	}
	onset = arg[0];
	period = arg[1];
	phase = arg[2];
	length = arg[3];
	metrumWeight = weight;
    }
    */

    std::vector<int> getOnsets();

    bool getSelection() {return selection; };

    void setSelection(bool b) {	selection = b; };


    /**
     * is (p1,o1,l1) already contained in this metrum?
     * precondition: p1 > this.period
     */
    bool contains(int p1, int o1, int l1) ;
    
    std::string toString() ;

    private:
    	bool selection;//f�r die Darstellung im Jtreetable


};

#endif

