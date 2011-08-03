#ifndef POD_REP_17475_803
#define POD_REP_17475_803

/*
Author: Geert-Jan Giezeman <geert@cs.uu.nl>
Copyright: Utrecht University, 2009

This file is part of CSUUMidiReader.

CSUUMidiReader is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CSUUMidiReader is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CSUUMidiReader.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vector>

namespace CSUU_POD {

    struct Note {
        int pitch;     // midi pitch
        long onset;    // absolute time in ppqn (0 or positive)
        long duration; // in ppqn, just like onset (positive)
    };

    struct Melody {
        int denom;
        std::vector<Note> notes;
    };

}

// vim:set shiftwidth=4 softtabstop=4 expandtab cindent:
#endif // POD_REP_17475_803
