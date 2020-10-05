#include <TsBitStream.h>


TsBitStream::TsBitStream(const char* filename):m_file(NULL),m_eof(false),m_bad(true)
{
    assert(filename != NULL);
    m_file = fopen(filename,"rb");
    if (!m_file)
    {
        std::cerr<<"[ERROR]:open file\'"<<filename<<"\'error"<<std::endl;
    }
    else
    {
        m_bad = false;
    }
}

TsBitStream::~TsBitStream()
{
    if (m_file)
    {
        fclose(m_file);
    }
    else
    {
        std::cout<<"[WARNING]:file is empty now"<<std::endl;
    }
}

bool TsBitStream::GetPacket(Packet& packet)
{
    if (!m_file || !good())
        return false;
    Packet::iterator p = packet.begin();
    size_t count = 1;
    int C = fgetc(m_file);
    if (C == EOF) {
        /// No More packets in stream
        m_eof = true;
        return false;
    }
    uint8_t c = static_cast<uint8_t> (C);
    if (c != MPEGTS_SYNC_BYTE) {
        std::cerr << "[ERROR]: Sync byte not found." << std::endl;
        m_bad = true;
        return false;
    }
    *p++ = c;
    while (p != packet.end()) {  //write 188
        C = fgetc(m_file);
        if (C == EOF) {
            m_eof = true;
            break;
        }
        c = static_cast<uint8_t> (C);
        *p++ = c;
        ++count;
    }
    if (count != PACKET_SIZE) {
        std::cerr << "[ERROR]: Expected " << PACKET_SIZE << " bytes, found " << count << std::endl;
        m_bad = true;
        return false;
    }
    return true;
}