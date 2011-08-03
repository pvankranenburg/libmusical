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

#ifndef ONSETGROUP_MEMORY_H_
#define ONSETGROUP_MEMORY_H_

#include <vector>

class OnsetGroup_Memory {
public:
    OnsetGroup_Memory(std::vector<int> onsets);

    int getLength(int time, int period, int lastOnset);
 
    bool isOnset(int time) { return m_data[time]; }

    private:
    std::vector<bool> m_data;
};


#endif
