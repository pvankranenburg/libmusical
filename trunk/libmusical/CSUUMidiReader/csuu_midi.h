#ifndef CSUU_MIDI__RTYVGT8ERNW
#define CSUU_MIDI__RTYVGT8ERNW

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
#include <stdlib.h>
#include <vector>
#include <stdexcept>

namespace CsuuMidi {

    typedef unsigned char uchar_t;

    struct StreamReadError: std::runtime_error {
        StreamReadError(): runtime_error("Could not read from stream") {}
    };

    struct NotSupported: std::runtime_error {
        NotSupported(char const *msg): runtime_error(msg) {}
    };

    struct Note {
        unsigned duration;
        unsigned pitch;
        unsigned patch;
        unsigned velocity_on;
        unsigned velocity_off;
    };

    struct Tempo {
        unsigned long v;
    };


    enum EventType {NoEvent, NoteEvent, PolyKeyPressEvent, ControlChangeEvent,
        ChannelPressEvent, PitchChangeEvent, NonMidiEvent,
        TempoEvent, TrackEndEvent}; 

    class Event {
        unsigned long m_onset;
        EventType tp;
        union {
            Note note; // for NoteEvent
            Tempo tempo; // for TempoEvent
        };
      public:
        ~Event() {}
        Event() :tp(NoEvent){}
        Event(Note const &in_note, unsigned long onset)
            :m_onset(onset),tp(NoteEvent),note(in_note) {}
        Event(Tempo in_tempo, unsigned long onset=0)
            :m_onset(onset),tp(TempoEvent),tempo(in_tempo) {}

        unsigned long onset() const { return m_onset;}
        EventType type() const {return tp;}
        Note const &get_note() const {
            if (tp != NoteEvent) abort();
            return note;
        }
        Note &get_note() {
            if (tp != NoteEvent) abort();
            return note;
        }
        Tempo get_tempo() const {
            if (tp != TempoEvent) abort();
            return tempo;
        }
        Tempo &get_tempo() {
            if (tp != TempoEvent) abort();
            return tempo;
        }
    };


    struct Channel {
        Channel(unsigned no):no(no) {}
        uchar_t no;
        std::vector<Event> events;
    };

    struct Song {
        static const unsigned SystemChannelNo = 253;
        unsigned ppqn; // pulses per quarter note
        std::vector<Channel> channels;
    };

    Song read_song(FILE *fp);
    double average_pitch(Channel const &channel);

}

// vim:set shiftwidth=4 softtabstop=4 expandtab cindent:
#endif // CSUU_MIDI__RTYVGT8ERNW
