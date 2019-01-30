#include <iostream>
#include <process.h>
#include <OpenThreads/Condition>
#include <Windows.h>

int condition = 0;

OpenThreads::Condition cont;
OpenThreads::Mutex mutex;

void setCondition(void *ptr)
{
    condition = 1;
    cont.signal();
}

void ifCondition(void *ptr)
{
    cont.wait(&mutex, INFINITE);
    if (condition)
        std::cout << "Condifion os find" << std::endl;
}

//int main()
//{
//    HANDLE t1 = (HANDLE)_beginthread(&ifCondition, 0, 0);
//    HANDLE t2 = (HANDLE)_beginthread(&setCondition, 0, 0);
//    Sleep(1000); std::cout << "END" << std::endl;
//    system("pause");
//    return 0;
//}
