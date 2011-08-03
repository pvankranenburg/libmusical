#ifndef FILE_HOLDER__MSK82OTPB2
#define FILE_HOLDER__MSK82OTPB2

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

#include <stdio.h>
#include <stdexcept>

namespace CsuuUtil {

    struct OpenError: public std::runtime_error {
        OpenError(char const*what): std::runtime_error(what) {}
    };

    struct FpHolder {
        FpHolder() :fp(0) {}
        FpHolder(char const*fname, char const *mode);
        FpHolder(FILE *fp_in): fp(fp_in) {} 
        ~FpHolder() {close();}
        FILE *get() const {return fp;}
        bool open(char const*fname, char const *mode);
        int close() 
        {
            int result = 0;
            if (is_open()) {
                result = fclose(fp);
                fp = 0;
            }
            return result;
        }
        bool is_open() const
        {
            return fp != 0;
        }
        private:
        FILE *fp;
    };

    inline FpHolder::FpHolder(char const*fname, char const *mode): fp(0)
    {
        fp = fopen(fname,mode);
        if (fp==0) {
            throw OpenError((std::string("Could not open file ")+fname).c_str());
        }
    } 

    inline bool FpHolder::open(char const*fname, char const *mode)
    {
        close();
        fp = fopen(fname,mode);
        return is_open();
    } 

}

// vim:set shiftwidth=4 softtabstop=4 expandtab cindent:
#endif // FILE_HOLDER__MSK82OTPB2
