#ifndef GEOVIDEOCONFIG_H
#define GEOVIDEOCONFIG_H

#include "tinyxml2.h"
#include <map>
#include <vector>

using namespace tinyxml2;

class GeoVideoConfig
{
public:
    typedef std::map<int, XMLElement*> SurfaceMap_t;

    enum vertexIndex {
        DLT = 0,
        DRT = 1,
        DLB = 2,
        DRB = 3,
        SLT = 4,
        SRT = 5,
        SLB = 6,
        SRB = 7,
        INDEX_MAX
    };


public:
    GeoVideoConfig(char* xmlPath);
    GeoVideoConfig();

    void insertRoot();
    void insertModel(char *modelName);
    void insertModelSurface(int surfaceCnt);
    void insertPosition(XMLElement* options);
    void insertModelPosition();
    void insertModelMatrix();
    void insertMatrix(XMLElement* modelMatrix);
    void CreateDefaultXml();
    void insertElement();
    void CreateXml(char* xml);
    char* getDefaultXmlPath();
    void insertVertex3(XMLElement* surface);
    void insertVertex2(XMLElement* surface);

private:
    tinyxml2::XMLDocument* m_Document;
    XMLElement* m_RootEle;
    XMLElement* m_Model;
    int m_SurfaceCnt;
    SurfaceMap_t m_SurfaceMap;
    char* m_xmlPath;
    char* m_xmlDefaultPath;
    char** m_buf;
    char** m_surfaceName;


};

#endif // GEOVIDEOCONFIG_H
