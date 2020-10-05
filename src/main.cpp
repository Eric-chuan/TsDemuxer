/***
** TS Demuxer.
** Author: Hu Jingchuan
***/

#include <TsBitStream.h>
#include <TsDemuxer.h>
#include <ProgramStream.h>
#include <iostream>
#include <cstring>
#include <time.h>



int main(int argc,char *argv[])
{
    clock_t start,end,end1,end2,end3;

    /// CMD LINE OPTIONS
    const char  *filename = NULL;
    bool info = false;
    switch(argc) {
        case 1:
            printf("Usage:[./ts_demuxer -i test.ts]\n");
            break;
        case 2:
            filename = argv[1];
            break;
        case 3:
            if (strncmp(argv[1], "-i", 3) == 0) {
                info = true;
                filename = argv[2];
                break;
            }
            // fall throug
        default:
            return -1;
    }

    TsBitStream bitStream(filename);
    TsDemuxer demuxer(info);
    Packet packet;
    start = clock();

    while (bitStream.good() && bitStream.GetPacket(packet)) {
        if (!demuxer.DecodePacket(packet))
            break;
    }

    end=clock();
    std::cout<<"demux time"<<(double)(end-start)/CLOCKS_PER_SEC<<std::endl;
}