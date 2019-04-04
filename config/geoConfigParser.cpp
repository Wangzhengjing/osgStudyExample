#include "geoConfigParser.h"
#include <QString>
#include <QStringList>
#include "Config_pub.h"

using namespace std;

GeoConfigParser::ModelInfo* m_ModelInfo = NULL;

GeoConfigParser::GeoConfigParser(char* xml)
{
    m_Document = new XMLDocument;

    m_VideoPathBuf = (char*)malloc(PATHLEN);
    if (m_VideoPathBuf)
        memset((void*)m_VideoPathBuf, 0, PATHLEN);
    memset(m_xmlPath, 0, sizeof(m_xmlPath));
    memcpy(m_xmlPath, xml, strlen(xml));

    xmlParse(xml);
    printXml();
}

void GeoConfigParser::printSurface(GeoConfigParser::SurfaceInfo* surfaceInfo)
{
    if (!surfaceInfo)
        return;

    std::cout << "      Surface     : " << surfaceInfo->surfaceName << std::endl;
    std::cout << "      Surface-ID  : " << surfaceInfo->surfaceID << std::endl;
    std::cout << "      vertexCnt   : " << surfaceInfo->vertexInfoMap.size() << std::endl;

    for (int i = 0; i < surfaceInfo->vertex3InfoMap.size(); i++)
    {
        if (!surfaceInfo->vertex3InfoMap[i])
            break;

        std::cout << "          vec3    : " << surfaceInfo->vertex3InfoMap[i]->desc << " ("
                                            << surfaceInfo->vertex3InfoMap[i]->position3.x() << ", "
                                            << surfaceInfo->vertex3InfoMap[i]->position3.y() << ", "
                                            << surfaceInfo->vertex3InfoMap[i]->position3.z() << ") "
                                            << std::endl;

    }

    for (int i = 0; i < surfaceInfo->vertexInfoMap.size(); i++)
    {
        if (!surfaceInfo->vertexInfoMap[i])
            break;

        std::cout << "          vec2    : " << surfaceInfo->vertexInfoMap[i]->desc << " ("
                                            << surfaceInfo->vertexInfoMap[i]->position.x() << ", "
                                            << surfaceInfo->vertexInfoMap[i]->position.y() << ")"
                                            << std::endl;

    }
}

void GeoConfigParser::printPosition(GeoConfigParser::ModelPositionInfo* modelOption)
{
    if (!modelOption)
        return;

    std::cout << "      Position    : " << std::endl;
    std::cout << "          longitude   : " << modelOption->longitude << std::endl;
    std::cout << "          latitude    : " << modelOption->latitude << std::endl;
    std::cout << "          altitude    : " << modelOption->altitude << std::endl;
}

void GeoConfigParser::printMatrix(GeoConfigParser::ModelMatrixInfo* modelMatrix)
{
    if (!modelMatrix)
        return;

    std::cout << "      Model-Matrix: " << std::endl;
    std::cout << "          rotate      : " << "("
                                        << modelMatrix->rotate.x << ","
                                        << modelMatrix->rotate.y << ","
                                        << modelMatrix->rotate.z << ")" << std::endl;
    std::cout << "          scale       : " << "("
                                        << modelMatrix->scale.x << ","
                                        << modelMatrix->scale.y << ","
                                        << modelMatrix->scale.z << ")" << std::endl;
    std::cout << "          translate   : " << "("
                                        << modelMatrix->translate.x << ","
                                        << modelMatrix->translate.y << ","
                                        << modelMatrix->translate.z << ")" << std::endl;
}

void GeoConfigParser::printModel(GeoConfigParser::ModelInfo* modelInfo)
{
    if (!modelInfo)
        return;

    std::cout << "Model-Name    : " << modelInfo->modelName << std::endl;
    std::cout << "surfaceCnt    : " << modelInfo->surfaceCnt << std::endl;
    std::cout << "videoType     : " << modelInfo->videoType << std::endl;

    printPosition(modelInfo->getModelPosition());
    printMatrix(modelInfo->getModelMatrix());

    for (int i = 0; i < modelInfo->surfaceMap.size(); i++)
    {
        printSurface(modelInfo->surfaceMap[i]);
    }
}

void GeoConfigParser::printXml()
{
    std::cout<< "parse xml       : " << m_xmlPath << std::endl;
    std::cout<< "      videoPath : " << m_VideoPath.toStdString().data() << std::endl;

    for (int i = 0; i < m_ModelMap.size(); i++)
    {
        printModel(m_ModelMap[i]);
    }
}

bool GeoConfigParser::vec3Parser(XMLElement* vec3, GeoConfigParser::SurfaceInfo* surfaceInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = vec3->FirstChildElement();
            child = ele;
        } else {
            child = ele->NextSiblingElement();
        }
        if (!child)
            break;

        GeoConfigParser::Vertex* vertex = new GeoConfigParser::Vertex;

        child->QueryStringAttribute("Name", &vertex->desc);
        const char * buf = child->GetText();
        QString myBuf = QString(QLatin1String(buf));
        QStringList list = myBuf.split(",");
        QString x = list[0];
        QString y = list[1];
        QString z = list[2];

        vertex->position3 = osg::Vec3(x.toFloat(), y.toFloat(), z.toFloat());

        surfaceInfo->vertex3InfoMap[i] = vertex;

        ele = child;
    }

    return true;
}

osg::Vec2 GeoConfigParser::queryFloatVec2FromText(const char* text)
{
    QString myBuf = QString(QLatin1String(text));
    QStringList list = myBuf.split(",");
    QString x = list[0];
    QString y = list[1];

    return osg::Vec2(x.toFloat(), y.toFloat());
}

osg::Vec3 GeoConfigParser::queryFloatVec3FromText(const char* text)
{
    QString myBuf = QString(QLatin1String(text));
    QStringList list = myBuf.split(",");
    QString x = list[0];
    QString y = list[1];
    QString z = list[2];

    return osg::Vec3(x.toFloat(), y.toFloat(), z.toFloat());
}

bool GeoConfigParser::vec2Parser(XMLElement* vec2, GeoConfigParser::SurfaceInfo* surfaceInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = vec2->FirstChildElement();
            child = ele;
        } else {
            child = ele->NextSiblingElement();
        }
        if (!child)
            break;

        GeoConfigParser::Vertex* vertex = new GeoConfigParser::Vertex;

        child->QueryStringAttribute("Name", &vertex->desc);

        vertex->position = queryFloatVec2FromText(child->GetText());

        surfaceInfo->vertexInfoMap[i] = vertex;

        ele = child;
    }

    return true;
}

bool GeoConfigParser::vertexParser(XMLElement* surface, GeoConfigParser::SurfaceInfo* surfaceInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = surface->FirstChildElement();
            child = ele;
        } else {
            child = ele->NextSiblingElement();
        }
        if (!child)
            break;

        if (!strcmp(child->Name(), CFG_VEC2))
        {
            vec2Parser(child, surfaceInfo);
        } else {
            vec3Parser(child, surfaceInfo);
        }

        ele = child;
    }

    return true;
}

bool GeoConfigParser::modelPositionChildParse(XMLElement* surface, GeoConfigParser::ModelPositionInfo* modelOptInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = surface->FirstChildElement();
            child = ele;
        } else {
            child = ele->NextSiblingElement();
        }
        if (!child)
            break;

        QString text = child->GetText();

        if (!strcmp(child->Name(), "lon"))
        {
            modelOptInfo->longitude = text.toFloat();
        } else if (!strcmp(child->Name(), "lat")){
            modelOptInfo->latitude = text.toFloat();
        } else if (!strcmp(child->Name(), "altitude")) {
            modelOptInfo->altitude = text.toFloat();
        }

        ele = child;
    }

    return true;
}

bool GeoConfigParser::modelMatrixChildParse(XMLElement* surface, GeoConfigParser::ModelMatrixInfo* modelMatrixInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = surface->FirstChildElement();
            child = ele;
        } else {
            child = ele->NextSiblingElement();
        }
        if (!child)
            break;

        const char* text = child->GetText();
        osg::Vec3 info;

        if (!strcmp(child->Name(), "rotate"))
        {
            info = queryFloatVec3FromText(text);
            modelMatrixInfo->rotate.x = info.x();
            modelMatrixInfo->rotate.y = info.y();
            modelMatrixInfo->rotate.z = info.z();
        } else if (!strcmp(child->Name(), "scale")){
            info = queryFloatVec3FromText(text);
            modelMatrixInfo->scale.x = info.x();
            modelMatrixInfo->scale.y = info.y();
            modelMatrixInfo->scale.z = info.z();
        } else if (!strcmp(child->Name(), "altitude")) {
            info = queryFloatVec3FromText(text);
            modelMatrixInfo->translate.x = info.x();
            modelMatrixInfo->translate.y = info.y();
            modelMatrixInfo->translate.z = info.z();
        }

        ele = child;
    }

    return true;
}

bool GeoConfigParser::surfaceParser(XMLElement* model, GeoConfigParser::ModelInfo* modelInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = model->FirstChildElement(CFG_SURFACE);
            child = ele;
        } else {
            child = ele->NextSiblingElement(CFG_SURFACE);
        }
        if (!child)
            break;

        GeoConfigParser::SurfaceInfo* surfaceInfo = new GeoConfigParser::SurfaceInfo;

        child->QueryStringAttribute("Name", &surfaceInfo->surfaceName);
        child->QueryIntAttribute("Count", &surfaceInfo->vertexCnt);
        child->QueryIntAttribute("ID", &surfaceInfo->surfaceID);

        vertexParser(child, surfaceInfo);

        modelInfo->surfaceMap[i] = surfaceInfo;

        ele = child;
    }

    return true;
}

bool GeoConfigParser::modelPositionParser(XMLElement* model, GeoConfigParser::ModelInfo* modelInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = model->FirstChildElement(CFG_POSITION);
            child = ele;
        } else {
            child = ele->NextSiblingElement(CFG_POSITION);
        }
        if (!child)
            break;

        GeoConfigParser::ModelPositionInfo* modelOptInfo = new GeoConfigParser::ModelPositionInfo;

        modelPositionChildParse(child, modelOptInfo);
        modelInfo->modelPositionInfo = modelOptInfo;

        ele = child;
    }

    return true;
}

bool GeoConfigParser::modelMatrixParser(XMLElement* model, GeoConfigParser::ModelInfo* modelInfo)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = model->FirstChildElement(CFG_MATRIX);
            child = ele;
        } else {
            child = ele->NextSiblingElement(CFG_MATRIX);
        }
        if (!child)
            break;

        GeoConfigParser::ModelMatrixInfo* modelMatrixInfo = new GeoConfigParser::ModelMatrixInfo;

        modelMatrixChildParse(child, modelMatrixInfo);
        modelInfo->modelMatrixInfo = modelMatrixInfo;

        ele = child;
    }

    return true;
}

bool GeoConfigParser::modelParser(XMLElement* root)
{
    XMLElement* ele;

    for (int i = 0;; i++)
    {
        XMLElement* child;
        if (i == 0)
        {
            ele = root->FirstChildElement();
            child = ele;
        } else {
            child = ele->NextSiblingElement();
        }
        if (!child)
            break;

        GeoConfigParser::ModelInfo* modelInfo = new GeoConfigParser::ModelInfo;

        child->QueryStringAttribute("Name", &modelInfo->modelName);
        child->QueryIntAttribute("Count", &modelInfo->surfaceCnt);
        child->QueryStringAttribute("Type", &modelInfo->videoType);

        surfaceParser(child, modelInfo);
        modelPositionParser(child, modelInfo);
        modelMatrixParser(child,modelInfo);

        m_ModelMap[i] = modelInfo;

        ele = child;
    }

    return true;
}

bool GeoConfigParser::xmlParse(char* xml)
{

    std::cout<< "my xml is : " << xml << std::endl;

    if (m_Document->LoadFile(xml))
    {
        std::cout << "load cfg-file " << xml << " failed!" << std::endl;
        return false;
    }

    XMLElement* root = m_Document->RootElement();
    root->QueryStringAttribute("defaultPath", &m_VideoPathBuf);
    m_VideoPath.append(m_VideoPathBuf);

    modelParser(root);

    return true;
}

QString GeoConfigParser::getVideoPath()
{
    return m_VideoPath;
}

GeoConfigParser::ModelInfo* GeoConfigParser::getModelByName(char* videoName)
{
    ModelInfo* modelInfo;

    for (int i = 0; i < m_ModelMap.size(); i++)
    {
        modelInfo = m_ModelMap[i];
        if (!strcmp(videoName, modelInfo->modelName))
            return modelInfo;
    }

    std::cout << "Can not parser model-info by VideoName : " << videoName << std::endl;

    return NULL;
}

int GeoConfigParser::getModelNum()
{
    return m_ModelMap.size();
}

GeoConfigParser::ModelMap_t GeoConfigParser::getModelMap()
{
    return m_ModelMap;
}
