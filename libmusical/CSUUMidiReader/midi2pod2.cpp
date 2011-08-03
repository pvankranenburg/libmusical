// vim:set shiftwidth=4 softtabstop=4 expandtab cindent:

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


#include "file_holder.h"
#include "pod_rep.h"
#include "csuu_midi.h"

namespace Midi=CsuuMidi;
using std::vector;

CSUU_POD::Melody channel_to_pod(Midi::Channel const &channel, unsigned ppqn)
{
    // Should divide by gcd for faster processing
    CSUU_POD::Melody result;
    CSUU_POD::Note pn;
    result.denom = ppqn;
    for (std::vector<Midi::Event>::const_iterator evp = channel.events.begin();
            evp != channel.events.end(); ++evp) {
        if (evp->type()==Midi::NoteEvent) {
            Midi::Note const &note = evp->get_note();
            pn.pitch = note.pitch;
            pn.onset = evp->onset();
            pn.duration = note.duration;
            result.notes.push_back(pn);
        }
    }
    return result;
}

CSUU_POD::Melody pod_melody_from_midi(FILE *fp)
{
    typedef vector<Midi::Channel>::iterator ChannelIt; 
    Midi::Song song = Midi::read_song(fp);
    double highest_pitch = -1.0;
    ChannelIt highest_channel;
    for (ChannelIt cur_channel=song.channels.begin();
            cur_channel != song.channels.end(); ++cur_channel) {
        if (cur_channel->no == 9) continue; // skip percussion channel
        if (cur_channel->no == Midi::Song::SystemChannelNo) continue; // skip
        double cur_pitch = average_pitch(*cur_channel);
        if (cur_pitch>highest_pitch) {
            highest_pitch = cur_pitch;
            highest_channel = cur_channel;
        }
    }
    if (highest_pitch < 0.0) {
        // throw some exception
    }
    return channel_to_pod(*highest_channel, song.ppqn);
}

CSUU_POD::Melody pod_melody_from_midi(std::string const &filename)
{
    CsuuUtil::FpHolder fph(filename.c_str(), "rb");
    return pod_melody_from_midi(fph.get());
}
