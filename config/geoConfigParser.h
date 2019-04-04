#ifndef GEOCONFIGPARSER_H
#define GEOCONFIGPARSER_H

#include "tinyxml2.h"
#include <map>
#include <vector>
#include <osg/Vec2>
#include <osg/Vec3>
#include <iostream>
#include <QString>

using namespace tinyxml2;

class GeoConfigParser
{
public:
//    using tinyxml2::XMLDocument;

#define NAMELEN 32
#define DESCLEN NAMELEN
#define PATHLEN 512

    class Vertex {
    public:
        osg::Vec2 position;
        osg::Vec3 position3;
        const char* desc;

        Vertex()
            :desc(0)
        {
            desc = (char*)malloc(DESCLEN);
            if (desc)
            {
                memset((void*)desc, 0, DESCLEN);
            }
        }
        ~Vertex()
        {
            if (desc)
            {
                free((void*)desc);
            }
        }

        osg::Vec2 getPosition()
        {
            return position;
        }

        osg::Vec3 getPosition3()
        {
            return position3;
        }

        const char* getVertexDesc()
        {
            return desc;
        }

    };

    typedef std::map<int, Vertex*> VertexMap_t;

    class SurfaceInfo {
    public:
        const char* surfaceName;
        int surfaceID;
        int vertexCnt;

        VertexMap_t vertexInfoMap;
        VertexMap_t vertex3InfoMap;

        SurfaceInfo()
            :surfaceName(0)
        {
            surfaceName = (char*)malloc(NAMELEN);
            if (surfaceName)
            {
                memset((void*)surfaceName, 0, NAMELEN);
            }
        }
        ~SurfaceInfo()
        {
            if (surfaceName)
            {
                free((void*)surfaceName);
            }
        }

        const char* getSurfaceName()
        {
            return surfaceName;
        }

        int getSurfaceID()
        {
            return surfaceID;
        }

        int getVertexCnt()
        {
            return vertexCnt;
        }

        VertexMap_t getVertexMap()
        {
            return vertexInfoMap;
        }

        VertexMap_t getVertex3Map()
        {
            return vertex3InfoMap;
        }
    };

    typedef std::map<int, SurfaceInfo*> SurfaceMap_t;

    class ModelPositionInfo {
    public:
        float longitude;
        float latitude;
        float altitude;

        ModelPositionInfo()
        {
        }
        ~ModelPositionInfo()
        {
        }
    };

    class ModelMatrixInfo {
        struct matrix_s {
            float x;
            float y;
            float z;
        };
    public:
        matrix_s rotate;
        matrix_s scale;
        matrix_s translate;

        ModelMatrixInfo()
        {
        }
        ~ModelMatrixInfo()
        {
        }
    };

    class ModelInfo {
    public:
        const char* modelName;
        const char* videoType;
        int surfaceCnt;

        SurfaceMap_t surfaceMap;
        ModelPositionInfo* modelPositionInfo;
        ModelMatrixInfo* modelMatrixInfo;

        ModelInfo()
            :modelPositionInfo(0),
              modelMatrixInfo(0),
              modelName(0),
              videoType(0)
        {
            modelName = (const char *)malloc(NAMELEN);
            if (modelName)
            {
                memset((void*)modelName, 0, NAMELEN);
            }
            videoType = (const char *)malloc(NAMELEN);
            if (videoType)
            {
                memset((void*)videoType, 0, NAMELEN);
            }
        }
        ~ModelInfo(){
            if (modelName)
            {
                free((void*)modelName);
            }
            if (videoType)
            {
                free((void*)videoType);
            }
        }

        const char* getModelName()
        {
            return modelName;
        }

        const char* getVideoType()
        {
            return videoType;
        }

        int getSurfaceCnt()
        {
            return surfaceCnt;
        }

        SurfaceMap_t getSurfaceMap()
        {
            return surfaceMap;
        }

        ModelPositionInfo* getModelPosition()
        {
            return modelPositionInfo;
        }

        ModelMatrixInfo* getModelMatrix()
        {
            return modelMatrixInfo;
        }
    };

    typedef std::map<int, ModelInfo*> ModelMap_t;

public:
    GeoConfigParser(char *xml);

    bool xmlParse(char* xml);
    bool modelParser(XMLElement* root);
    bool surfaceParser(XMLElement* model, ModelInfo *modelInfo);
    bool vertexParser(XMLElement* surface, SurfaceInfo* surfaceInfo);
    bool modelPositionParser(XMLElement* model, ModelInfo* modelInfo);
    bool modelPositionChildParse(XMLElement* surface, ModelPositionInfo* modelOptInfo);
    bool modelMatrixChildParse(XMLElement* surface, ModelMatrixInfo* modelMatrixInfo);
    bool modelMatrixParser(XMLElement* model, ModelInfo* modelInfo);
    void printSurface(SurfaceInfo* surfaceInfo);
    void printPosition(ModelPositionInfo* modelOption);
    void printMatrix(ModelMatrixInfo* modelMatrix);
    void printModel(ModelInfo* modelInfo);
    void printXml();
    ModelInfo* getModelByName(char* videoName);
    bool vec2Parser(XMLElement* vec2, SurfaceInfo *surfaceInfo);
    bool vec3Parser(XMLElement* vec3, SurfaceInfo *surfaceInfo);
    osg::Vec2 queryFloatVec2FromText(const char* text);
    osg::Vec3 queryFloatVec3FromText(const char* text);
    int getModelNum();
    ModelMap_t getModelMap();
    QString getVideoPath();

private:
    ModelMap_t m_ModelMap;
    tinyxml2::XMLDocument* m_Document;
    char m_xmlPath[PATHLEN];
    const char* m_VideoPathBuf;
    QString m_VideoPath;
};

#endif // GEOCONFIGPARSER_H
