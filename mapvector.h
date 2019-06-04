#ifndef MAPVECTOR_H
#define MAPVECTOR_H

#include <vector>
#include <map>
#include <QString>


class mapVector
{
public:
    mapVector();

    std::vector<int> getList(const char* name);

private:
    std::map<QString, std::vector<int>> map;
};

#endif // MAPVECTOR_H
