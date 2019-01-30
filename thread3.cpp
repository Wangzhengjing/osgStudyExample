#include <OpenThreads/Thread>
#include <OpenThreads/Barrier>
#include <iostream>
#include <Windows.h>

OpenThreads::Barrier bar;

class ThreadSelf : public OpenThreads::Thread
{
public:
    ThreadSelf(int a)
    {
        threadid = a;
    }
    virtual ~ThreadSelf()
    {
        while (isRunning())
            OpenThreads::Thread::YieldCurrentThread();
    }
    void run()
    {
        int count = 10;
        while (--count)
        {
            Sleep(10);
            std::cout <<"Thread print:"<< threadid << std::endl;
        }
        bar.block();
    }
    int threadid;
};

//int main()
//{
//    ThreadSelf t1(10);
//    ThreadSelf t2(6);
//    t1.start();
//    bar.block(2);
//    t2.start();
//    bar.block(0);
//    std::cout << "Here" << std::endl;
//    Sleep(3000);
//    system("pause");
//    return 1;
//}
