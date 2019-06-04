#include "mapvector.h"

mapVector::mapVector()
{
}

std::vector<int> mapVector::getList(const char* name)
{
    return map[QString(name)];
}
