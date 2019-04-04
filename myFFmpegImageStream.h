#ifndef MYFFMPEGIMAGESTREAM_H
#define MYFFMPEGIMAGESTREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

#ifdef __cplusplus
}
#endif

#include <osg/ImageStream>
#include <OpenThreads/Thread>
#include <iostream>

class myFFmpegImageStream : /*public osg::ImageStream ,*/ public OpenThreads::Thread
{
public:
    myFFmpegImageStream();

    virtual ~myFFmpegImageStream()
    {
        while (isRunning())
            OpenThreads::Thread::YieldCurrentThread();
    }
    void run()
    {
        int count = 10;
        while (--count)
        {
//            Sleep(10);
        }
    }

    int getFrame(int *got_frame, std::string & filename);

};

#endif // MYFFMPEGIMAGESTREAM_H
