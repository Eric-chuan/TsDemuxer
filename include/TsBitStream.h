/// /////////////////////////////////////////////////////////////////////////////
/// Defines Modules for Reading TS Stream of data
/// ////////////////////////////////////////////////////////////////////////////
#ifndef MY_HOST_LINUX_TSBITSTREAM_H
#define MY_HOST_LINUX_TSBITSTREAM_H

#include <TsDataStruct.h>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <iostream>

/// ////////////////////////////////////////////////////////////////////////////
/// MPEG Bit Reader
class TsBitStream
{
public:
    TsBitStream(const char * filename);
    TsBitStream(const TsBitStream&) = delete;
    ~TsBitStream();

    /// Read and fill data packet
    bool GetPacket(Packet& packet);

    bool bad() const { return m_bad; }
    bool eof() const { return m_eof; }
    bool good() const { return !m_eof && !m_bad; }

private:
    FILE* m_file;

    bool m_eof;
    bool m_bad;
};

#endif