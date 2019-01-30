#include <OpenThreads/ScopedLock>
#include <OpenThreads/Mutex>
#include <OpenThreads/Thread>
#include <iostream>
#include <Windows.h>
#include <osg/Node>

OpenThreads::Mutex mutex1;
class ThreadSelf : public OpenThreads::Thread
{
public:
    ThreadSelf(osg::ref_ptr<osg::Node> pNode);
    virtual ~ThreadSelf()
    {
        while (isRunning())
            OpenThreads::Thread::YieldCurrentThread();
    }

    void run()
    {
        //只有在下边的全部运行之后，才会将下一个进程纳入运行
        OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex1);
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

//int main()
//{
//    ThreadSelf t1(10);
//    ThreadSelf t2(6);
//    t1.start();
//    t2.start();
//    Sleep(3000);
//    system("pause");

//    return 1;
//}
