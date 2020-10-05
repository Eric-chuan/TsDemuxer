/// /////////////////////////////////////////////////////////////////////////////
/// Demuxer Interface.
/// Demuxer assumes all packets are related, it will keep list of streams as they appear in TS.
#ifndef MY_HOST_LINUX_TSDEMUXER_H
#define MY_HOST_LINUX_TSDEMUXER_H
#include <TsDataStruct.h>
#include <ProgramStream.h>
#include <cstdio>
#include <map>
#include <set>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>

#define MAX_FRAME_LENGTH 18800000

class TsDemuxer
{
public:
    using Programs = std::map<PID, Program>;
    using Streams = std::map<PID, ProgramStream*>;
    using Filters = std::map<PID, DemuxerEvents>;

    TsDemuxer(bool info);
    ~TsDemuxer();

    bool DecodePacket(const Packet& packet);

protected:
    /// Fills a header with data
    bool ReadHeader(Packet::const_iterator &p, Packet::const_iterator e, PacketHeader& header);

    /// Reads PAT packet
    bool ReadPAT(Packet::const_iterator &p, Packet::const_iterator e);
    /// Reads PMT packet
    bool ReadPMT(Packet::const_iterator &p, Packet::const_iterator e);
    /// Reads PES packet
    bool ReadPES(Packet::const_iterator &p, Packet::const_iterator e, PacketHeader& header, PID id);
    bool CheckPES(Packet::const_iterator &p, Packet::const_iterator e, PacketHeader& header);

    /// Fills a section header info
    bool ReadSection(Packet::const_iterator &p, Packet::const_iterator e, PacketSection& section);

    /// Read PAT tables
    bool ReadPrograms(Packet::const_iterator &p, Packet::const_iterator e);
    /// Read Elementary stream data
    bool ReadESD(Packet::const_iterator &p, Packet::const_iterator e, const Program& prog);

    /// Add program if new
    void RegisterProgram(PID id, PID pid);
    bool RegisterStream(PID id, const Program& prog, bool video);


private:
    Programs m_programs; /// List of programs
    Streams m_streams; /// List of streams
    Filters m_filters;

    uint64_t m_pnum; /// Packet number
    bool m_info; /// Read PAT/PMT info
};


#endif
