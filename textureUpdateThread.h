#ifndef TEXTUREUPDATETHREAD_H
#define TEXTUREUPDATETHREAD_H

#include <OpenThreads/Thread>
#include <iostream>
#include <Windows.h>
#include <OpenThreads/ScopedLock>
#include <osg/Node>

class TextureUpdateThread : public OpenThreads::Thread
{
public:
    TextureUpdateThread(osg::ref_ptr<osg::Node> pNode);

    virtual ~TextureUpdateThread()
    {
        while (isRunning())
            OpenThreads::Thread::YieldCurrentThread();
    }

    void run()
    {
        //只有在下边的全部运行之后，才会将下一个进程纳入运行
//        OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);
        int count = 10;
        while (--count)
        {
            Sleep(10);
            std::cout <<"Thread print:"<< threadid << std::endl;
        }
    }

private:
    osg::ref_ptr<osg::Node> m_pNode;
    int threadid;
};

#endif // TEXTUREUPDATETHREAD_H
