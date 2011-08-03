#ifndef CSUUMIDI_17475_803
#define CSUUMIDI_17475_803

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

#include <stdexcept>
#include <string>
#include <vector>
#include "pod_rep.h"

namespace CSUU_POD
{

    struct MidiError: public std::runtime_error {
        MidiError(char const*what): std::runtime_error(what) {}
    };

    struct StreamReadError: std::runtime_error {
        StreamReadError(): runtime_error("Could not read from stream") {}
    };

    struct NotSupported: std::runtime_error {
        NotSupported(char const *msg): runtime_error(msg) {}
    };

    struct StreamWriteError: std::runtime_error {
        StreamWriteError(): runtime_error("Could not write to stream") {}
    };

    struct PatchChoice {
            unsigned patch;
            long onset;
    };

    class PodMidiWriter
    {
        struct Impl;
        Impl *pimpl;
        PodMidiWriter(PodMidiWriter const &);
        PodMidiWriter operator=(PodMidiWriter const &);
      public:
        ~PodMidiWriter();
        PodMidiWriter();
        PodMidiWriter(
            char const*filename, 
            int ppqn, // pulses per quarter note
            long mpqn, // microseconds per quarter note
            int channel=0
            );
        PodMidiWriter(
            FILE *fp, // writable file. Will not be closed.
            int ppqn, // pulses per quarter note
            long mpqn, // microseconds per quarter note
            int channel=0
            );
        void open(
            char const*filename, 
            int ppqn, // pulses per quarter note
            long mpqn, // microseconds per quarter note
            int channel=0
            );
        void open(
            FILE *fp, // writable file. Will not be closed.
            int ppqn, // pulses per quarter note
            long mpqn, // microseconds per quarter note
            int channel=0
            );
        void set_maximum_silent_time(long duration);
        void add_patch(PatchChoice const &pc);
        void add_note(CSUU_POD::Note const &note);
        void finish(); // Should be called after adding the last note.
        void hard_close(); // Should only be called if you want to reopen this
        // Writer with another file, but finish raised an exception.
        // hard_close will not throw, but the resulting file will not be valid.
    };

    template <class PodIter>
    void write(
            char const*filename, 
            int ppqn, // pulses per quarter note
            long mpqn,  // microseconds per quarter note
            PodIter begin, PodIter end)
    {
        PodMidiWriter mw;
        mw.open(filename, ppqn, mpqn);
        for ( ; begin != end; ++begin) {
            mw.add_note(*begin);
        }
        mw.finish();
    }

    template <class PodIter>
    void write(
            FILE *fp, 
            int ppqn, // pulses per quarter note
            long mpqn,  // microseconds per quarter note
            PodIter begin, PodIter end)
    {
        PodMidiWriter mw;
        mw.open(fp, ppqn, mpqn);
        for ( ; begin != end; ++begin) {
            mw.add_note(*begin);
        }
        mw.finish();
    }

    Melody read_midi_melody(FILE *mf);

}

// vim:set shiftwidth=4 softtabstop=4 expandtab cindent:
#endif // CSUUMIDI_17475_803
