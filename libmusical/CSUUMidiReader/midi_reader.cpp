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


#include "csuu_midi.h"
#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <sstream>
//#include <boost/lexical_cast.hpp>

namespace Midi = CsuuMidi;
using Midi::StreamReadError;
using Midi::NotSupported;
using std::string;
using std::list;
using std::vector;
using std::find_if;
using std::sort;
//using boost::lexical_cast;

namespace {
    typedef unsigned char uchar_t;

    void report_read_error()
    {
        //abort();
        throw StreamReadError();
    }

    inline uchar_t getc_c(FILE *fp)
    {
        int value = getc(fp);
        if (value==EOF) {
            report_read_error();
        }
        return value;
    }

    unsigned read_u2(FILE *fp)
    {
        assert(sizeof(unsigned)>=2);
        uchar_t buf[2];
        if (fread(buf,2,1,fp) != 1)
            report_read_error();
        unsigned result = buf[0];
        result = result<<8 | buf[1];
        return result;
    }

    void read_c3(FILE *fp, uchar_t (&buf)[3])
    {
        if (fread(buf,3,1,fp) != 1) {
            report_read_error();
        }
    }

    unsigned long read_u3(FILE *fp)
    {
        assert(sizeof(unsigned long)>=3);
        uchar_t buf[3];
        read_c3(fp,buf);
        unsigned long value=buf[0];
        for (int i=1; i<3; ++i) {
            value = value<<8 | buf[i];
        }
        return value;
    }

    void read_c4(FILE *fp, uchar_t (&buf)[4])
    {
        if (fread(buf,4,1,fp) != 1) {
            report_read_error();
        }
    }

    unsigned long read_u4(FILE *fp)
    {
        assert(sizeof(unsigned long)>=4);
        uchar_t buf[4];
        read_c4(fp,buf);
        unsigned long value=buf[0];
        for (int i=1; i<4; ++i) {
            value = value<<8 | buf[i];
        }
        return value;
    }

    unsigned long read_var(FILE *fp, unsigned &count)
    {
        uchar_t c;
        unsigned long value;
        count=1;
        if ((value=getc_c(fp)) & 0x80) {
            value &= 0x7f;
            do {
                c=getc_c(fp);
                ++count;
                value = (value<<7) |(c & 0x7f);
            } while (c&0x80);
        }
        return value;
    }

    class ChunkReader {
        FILE *m_fp;
        uchar_t m_id[4];
        unsigned long m_size;
        unsigned long m_read;
        
      public:
        ChunkReader(FILE *fp):m_fp(fp), m_read(0)
        {
            read_c4(m_fp, m_id);
            m_size = read_u4(m_fp);
        }

        bool same_id(char const *id2) const
        {
            for (int i=0; i<4; ++i)
                if (m_id[i]!=*id2++)
                    return false;
            return true;
        }

        unsigned long size()
        {
            return m_size;
        }

        bool exhausted() const
        {
            return m_read >= m_size;
        }
        
        unsigned long read_var()
        {
            unsigned count;
            unsigned long result = ::read_var(m_fp, count);
            m_read += count;
            return result;
        }

        uchar_t getc_c()
        {
            if (m_read+1 > m_size) {
                report_read_error();
            }
            m_read += 1;
            int value = getc(m_fp);
            if (value==EOF) {
                report_read_error();
            }
            return value;
        }

        unsigned read_u2()
        {
            if (m_read+2 > m_size) {
                report_read_error();
            }
            m_read += 2;
            return ::read_u2(m_fp);
        }

        unsigned long read_u3()
        {
            if (m_read+3 > m_size) {
                report_read_error();
            }
            m_read += 3;
            return ::read_u3(m_fp);
        }

        void skip(unsigned n)
        {
            if (m_read+n > m_size)
                report_read_error();
            if (fseeko(m_fp, n, SEEK_CUR) !=0) {
                report_read_error();
            }
            m_read += n;
        }
    };

    struct SamePitch {
        bool operator()(Midi::Note const &mn1, Midi::Note const &mn2)
        {
            return mn1.pitch == mn2.pitch;
        }
    };

    struct OnsetLess {
        bool operator()(Midi::Event const &mn1, Midi::Event const &mn2)
        {
            return mn1.onset() < mn2.onset();
        }
    };

    struct HasPitch {
        HasPitch(uchar_t pitch) : m_pitch(pitch) {}
        bool operator()(Midi::Event const &ev)
        { return ev.type()==Midi::NoteEvent
            && ev.get_note().pitch == m_pitch;}
      private:
        uchar_t m_pitch;
    };

    struct BuildChan: Midi::Channel {
        BuildChan(unsigned no):Channel(no),patch_no(1) {}
        unsigned patch_no;
        list<Midi::Event> open_notes;
    };

    struct HasNo {
        HasNo(unsigned no) : m_no(no) {}
        bool operator()(Midi::Channel const &ch)
        { return ch.no == m_no;}
        private:
        unsigned m_no;
    };

    struct BuildData {
        unsigned long time;
        unsigned ppqn; // pulses per quarter note
        list<BuildChan> channels;
        BuildChan &get_channel(unsigned no);
    };

    BuildChan &BuildData::get_channel(unsigned no)
    {
        if (no >= 16 && no != Midi::Song::SystemChannelNo) {
            throw StreamReadError();
        }
        list<BuildChan>::iterator it =
            find_if(channels.begin(), channels.end(), HasNo(no));
        if (it == channels.end()) {
            channels.push_back(BuildChan(no));
            return channels.back();
        } else {
            return *it;
        }
    }


    void note_off(BuildChan &chan, unsigned long time, uchar_t pitch, uchar_t v)
    {
        // try to find data1 in open_notes
        list<Midi::Event>::iterator it = find_if(chan.open_notes.begin(),
                chan.open_notes.end(), HasPitch(pitch));
        // record duration if found and move it to notes
        if (it != chan.open_notes.end()) {
            Midi::Note &note = it->get_note();
            note.duration = time-it->onset();
            note.velocity_off = v;
            chan.events.push_back(*it);
            chan.open_notes.erase(it);
        }
    }

    void note_on(BuildChan &chan, unsigned long time, uchar_t pitch, uchar_t v)
    {
        if (v == 0) {
            note_off(chan, time, pitch, v);
        } else {
            Midi::Note mn;
            mn.pitch = pitch;
            mn.velocity_on = v;
            mn.patch = chan.patch_no;
            chan.open_notes.push_back(Midi::Event(mn, time));
        }
    }

    void read_op(ChunkReader &reader, BuildData &bd,
            uchar_t status, uchar_t data1)
    {
        uchar_t data2;
        switch (status&0xf0) {
            case 0x80:
            case 0x90:
            case 0xa0:
            case 0xb0:
            case 0xe0:
                data2 = reader.getc_c();
        }
        BuildChan &channel(bd.get_channel(status & 0x0f));
        switch (status&0xf0) {
            case 0x80:
                note_off(channel, bd.time, data1, data2);
                break;
            case 0x90:
                // add note to open_notes
                note_on(channel, bd.time, data1, data2);
                break;
            case 0xc0:
                channel.patch_no = data1;
                break;
        }
    }

    void skip_sys_exclusive(ChunkReader &reader)
    {
        unsigned long count;
        count = reader.read_var();
        reader.skip(count);
    }

    bool special_event(ChunkReader &reader, BuildData &bd)
    {
        unsigned long count;
        uchar_t status2 = reader.getc_c();
        count = reader.read_var();
        switch (status2) {
            case 0x51:
                {
                    Midi::Tempo tempo;
                    tempo.v = reader.read_u3();
                    BuildChan &channel(bd.get_channel(
                                Midi::Song::SystemChannelNo));
                    channel.events.push_back(Midi::Event(tempo));
                    break;
                }
            case 0x2f:
                return true;
            default:
                reader.skip(count);
        }
        return false; // End of Track
    }

    bool read_system(ChunkReader &reader, BuildData &bd, uchar_t status)
    {
        bool must_stop = false;
        switch (status & 0xff) {
            case 0xf0:
                skip_sys_exclusive(reader);
                break;
            case 0xf2:
                reader.getc_c();
                reader.getc_c();
                break;
            case 0xf3:
                reader.getc_c();
                break;
            case 0xf6:
            case 0xf7:
            case 0xf8:
            case 0xfa:
            case 0xfb:
            case 0xfc:
            case 0xfe:
                break;
            case 0xff:
                must_stop = special_event(reader, bd);
                break;
            default:
            case 0xf1:
            case 0xf4:
            case 0xf5:
            case 0xf9:
            case 0xfd:
                report_read_error();
        }
        return must_stop;
    }

    void read_track(ChunkReader &reader, BuildData &bd)
    {
        if (!reader.same_id("MTrk")) {
            report_read_error();
        }
        bd.time = 0;
        uchar_t status=0xfd, data1;
        bool stop = false;
        while (!(reader.exhausted() || stop)) {
            unsigned delta = reader.read_var();
            bd.time += delta;
            data1 = reader.getc_c();
            if ((data1&0x80) != 0) {
                status = data1;
                if ((status&0xf0) == 0xf0) {
                    stop = read_system(reader, bd,  status);
                } else {
                    data1 = reader.getc_c();
                    read_op(reader, bd, status, data1);
                }
            } else {
                // running status
                read_op(reader, bd, status, data1);
            }
        }
    }

    void read_file(FILE *fp, BuildData &bd)
    {
        ChunkReader header(fp);
        if (!header.same_id("MThd")) {
            report_read_error();
        }
        if (header.size() != 6) {
            report_read_error();
        }
        unsigned type, track_count, ppqn;
        type = header.read_u2();
        track_count = header.read_u2();
        ppqn = header.read_u2();
        if (type>2) {
            report_read_error();
        }
        if (type==2)
            throw NotSupported("Midi files with format 2 are not supported");
        if (ppqn >= 0x8000)
            throw NotSupported("Only midi files with timestamps based on ppqn are supported");
        bd.ppqn = ppqn;
        if (type==0 && track_count !=1) {
            report_read_error();
        }
        for (unsigned i=0; i<track_count; ++i) {
            ChunkReader reader(fp);
            read_track(reader, bd);
        }
        for (list<BuildChan>::iterator cur_channel=bd.channels.begin();
                cur_channel != bd.channels.end(); ) {
            if (cur_channel->events.empty())
                cur_channel = bd.channels.erase(cur_channel);
            else
                ++cur_channel;
        }
        for (list<BuildChan>::iterator cur_channel=bd.channels.begin();
                cur_channel != bd.channels.end(); ++cur_channel) {
            stable_sort(cur_channel->events.begin(), cur_channel->events.end(), OnsetLess());
        }
    }

}

namespace CsuuMidi {
Song read_song(FILE *fp)
{
    BuildData bd;
    read_file(fp, bd);
    Song result;
    result.ppqn = bd.ppqn;
    result.channels.reserve(bd.channels.size());
    // copy data from BuildData channels
    for (list<BuildChan>::iterator cur_channel = bd.channels.begin();
            cur_channel!=bd.channels.end(); ++cur_channel) {
        result.channels.push_back(Channel(cur_channel->no));
        cur_channel->events.swap(result.channels.back().events);
    }
     return result;
}


double average_pitch(Channel const &channel)
{
    double sum = 0.0, total_time=0.0;
    for (vector<Event>::const_iterator it = channel.events.begin();
            it != channel.events.end(); ++it) {
        if (it->type()==NoteEvent) {
            Note const &note = it->get_note();
            sum += note.pitch * note.duration;
            total_time += note.duration;
        }
    }
    return total_time <= 0.0 ? -1.0 : sum/total_time;
}
}

#ifdef MIDI_READ

#include "file_holder.h"
#include "csuu_pod.h"

void write_channel(Midi::Channel const &channel, unsigned ppqn, string base_name)
{
    
    
    std::ostringstream o;
    o << int(channel.no);
    CsuuUtil::FpHolder fh((base_name+o.str()+".mid").c_str(),
            "wb");
    CSUU_POD::PodMidiWriter pmw(fh.get(), ppqn, 500000, channel.no);
    CSUU_POD::Note pn;
    unsigned last_patch = -1;
    for (vector<Midi::Event>::const_iterator evp = channel.events.begin();
            evp != channel.events.end(); ++evp) {
        if (evp->type()==Midi::NoteEvent) {
            Midi::Note const &note = evp->get_note();
            if (note.patch != last_patch) {
                CSUU_POD::PatchChoice pc;
                pc.patch = note.patch;
                pc.onset = evp->onset();
                pmw.add_patch(pc);
            }
            pn.pitch = note.pitch;
            pn.onset = evp->onset();
            pn.duration = note.duration;
            pmw.add_note(pn);
        }
    }
    pmw.finish();
}

void write_channels(BuildData const &bd, string base_name)
{
    string::size_type pos = base_name.rfind('.');
    if (pos != string::npos)
        base_name.resize(pos);
    /*
    long tempo = 500000; // 120 BPM = 50.000 microsec per quarter note
    for (list<BuildChan>::const_iterator cur_channel = bd.channels.begin();
            cur_channel != bd.channels.end(); ++cur_channel) {
        if (cur_channel->no == Midi::Song::SystemChannelNo)
            tempo = find_tempo(*cur_channel);
    }
    */
    for (list<BuildChan>::const_iterator cur_channel = bd.channels.begin();
            cur_channel != bd.channels.end(); ++cur_channel) {
        if (cur_channel->no != Midi::Song::SystemChannelNo)
            write_channel(*cur_channel, bd.ppqn, base_name);
    }
}

int main(int argc, char **argv)
{
    using std::cerr;
    if (argc != 2) {
        cerr<<"Expected exactly one argument (filename).\n";
        return 2;
    }
    int result = 0;
    try {
        CsuuUtil::FpHolder fh(argv[1], "rb");
        BuildData bd;
        read_file(fh.get(), bd);
        fh.close();
        std::cout<<"Number of channels: "<<bd.channels.size()<<"\n";
        for (list<BuildChan>::iterator cur_channel=bd.channels.begin();
                cur_channel != bd.channels.end(); ++cur_channel) {
            if (cur_channel->no != Midi::Song::SystemChannelNo)
                std::cout<<"Channel "<<int(cur_channel->no)
                    <<" has average pitch "<<average_pitch(*cur_channel)<<"\n";
        }
        write_channels(bd, argv[1]);
        
    } catch(NotSupported const &ex) {
        cerr<<"NotSupported exception thrown: "<<ex.what()<<"\n";
        result = 1;
    } catch(std::exception const &ex) {
        cerr<<"exception thrown: "<<ex.what()<<"\n";
        result = 3;
    } catch(...) {
        cerr<<"Unknown exception thrown.\n";
        result = 3;
    }
    return result;
}

#endif
