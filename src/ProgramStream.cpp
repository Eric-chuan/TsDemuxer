#include <ProgramStream.h>


ProgramStream::ProgramStream(const char * filename, PID id, PID pid)
{
    this->m_id = id;
    this->m_pid = pid;
    this->m_file = fopen(filename, "wb");
    assert(filename != NULL);
    if (!m_file)
    {
        std::cerr << "[ERROR]: STREAM=" << m_id << " PID=" << m_pid << " : can't open file \'" << filename << "\'" << std::endl;
    }
}


void ProgramStream::Write(Packet::const_iterator b, Packet::const_iterator e)
{
    if (!m_file) return; // Failed to create stream. Exit quietly

    while (b != e) {
        int r = fputc(*b++, m_file);
        if (r == EOF) {
            std::cerr << "[ERROR]: STREAM=" << m_id << " PID=" << m_pid << " Write failed." << std::endl;
            fclose(m_file);
            m_file = NULL;
        }
    }
}


