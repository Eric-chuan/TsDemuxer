/// /////////////////////////////////////////////////////////////////////////////
/// Define Program Stream which is used to write in file
/// /////////////////////////////////////////////////////////////////////////////
#ifndef MY_HOST_LINUX_PROGRAMSTREAM_H
#define MY_HOST_LINUX_PROGRAMSTREAM_H
#include <TsDataStruct.h>
#include <cstdio>
#include <map>
#include <set>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>


class ProgramStream
{
public:
    ProgramStream(const char * filename, PID id, PID pid);
    ProgramStream(const ProgramStream&) = delete;
    ProgramStream& operator=(const ProgramStream&) = delete;
    PID GetId() const { return m_id; }
    PID GetPId() const { return m_pid; }
    void SetPId(PID id) { m_pid = id; }


    /// Write data from packet to sink
    void Write(Packet::const_iterator b, Packet::const_iterator e);
private:
    FILE* m_file;
    PID m_id; /// Packet identifier for this stream
    PID m_pid; /// Program id for this stream
};

#endif