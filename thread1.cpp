#include <process.h>
#include <Windows.h>
#include <iostream>

int tickets = 10; HANDLE iMutex;//创建一个句柄

void sellTickets1(void *ptr)
{
    while (tickets > 0)
    {
        //等待信号量
        WaitForSingleObject(iMutex, INFINITE);
        Sleep(10);
        std::cout << "Thread1 sell : " << tickets << std::endl;
        tickets--;
        //释放信号量
        ReleaseMutex(iMutex);
    }
}

void sellTickets2(void *ptr)
{
    while (tickets > 0)
    {
        //等待信号量
        WaitForSingleObject(iMutex, INFINITE);
        Sleep(10);
        std::cout << "Thread2 sell : " << tickets << std::endl;
        tickets--;
        //释放信号量
        ReleaseMutex(iMutex);
    }
}

//int main()
//{
//    //创建一个线程，线程调用sellTickets1函数
//    HANDLE t1 = (HANDLE)_beginthread(&sellTickets1, 0, 0);
//    //创建一个线程，线程调用sellTickets2函数
//    HANDLE t2 = (HANDLE)_beginthread(&sellTickets2, 0, 0);
//    //创建一个信号量，用于互斥对象
//    iMutex = (HANDLE)CreateMutex(0, FALSE, 0);
//    Sleep(2000);
//    system("pause");
//    return 0;
//}
