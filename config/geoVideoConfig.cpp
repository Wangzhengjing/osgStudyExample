#include "geoVideoConfig.h"

#include "Config_pub.h"

char* m_VertexInfo[8] = {
    "DLT",
    "DRT",
    "DRB",
    "DLB",
    "SLT",
    "SRT",
    "SRB",
    "SLB"
};
char* m_Surface[] = {
    "GoundSurface",
    "BackSurface",
    "LeftSurface",
    "RightSurface",
    "TopSurface",
    "FrontSurface"
};

char* default_model_cfg = ".\\default-model.conf";
//char* default_model_cfg = "D:\\ProjectMange\\GeoVideo\\project\\osgStudy\\config\\default-model.conf";

char* default_video_path = "C:\\osg\\Geo3D\\TestLibss\\OpenglPlay\\data";

GeoVideoConfig::GeoVideoConfig(char* xmlPath)
    :m_SurfaceCnt(0)
{


    m_buf = m_VertexInfo;
    m_surfaceName = m_Surface;

    m_Document = new XMLDocument;
    m_xmlPath = xmlPath;
    m_xmlDefaultPath = default_model_cfg;

    CreateXml(xmlPath);
}

GeoVideoConfig::GeoVideoConfig()
    :m_SurfaceCnt(0)
{


    m_buf = m_VertexInfo;
    m_surfaceName = m_Surface;

    m_Document = new XMLDocument;
    m_xmlDefaultPath = default_model_cfg;

    CreateDefaultXml();
}

char* GeoVideoConfig::getDefaultXmlPath()
{
    return m_xmlDefaultPath;
}

void GeoVideoConfig::insertRoot()
{
    m_RootEle = m_Document->NewElement(CFG_VIDEO);
    m_RootEle->SetAttribute("defaultPath", default_video_path);
    m_Document->InsertEndChild(m_RootEle);
}

void GeoVideoConfig::insertModel(char* modelName)
{
    m_Model=m_Document->NewElement(CFG_MODEL);
    m_Model->SetAttribute("Name", modelName);
    m_Model->SetAttribute("Count", 6);
    m_Model->SetAttribute("Type","mp4");
    m_RootEle->InsertEndChild(m_Model);
}

void GeoVideoConfig::insertVertex3(XMLElement* surface)
{
    XMLElement* vertex = m_Document->NewElement(CFG_VEC3);

    for (int j = 0; j < INDEX_MAX/2; j++)
    {
        XMLElement* vertexNode = m_Document->NewElement(CFG_VERTEX);
        vertexNode->SetAttribute("Name", m_buf[j]);
        vertexNode->SetText("x,y,z");
        vertex->InsertEndChild(vertexNode);
    }

    surface->InsertEndChild(vertex);
}

void GeoVideoConfig::insertVertex2(XMLElement* surface)
{
    XMLElement* vertex = m_Document->NewElement(CFG_VEC2);

    for (int j = 0; j < INDEX_MAX/2; j++)
    {
        XMLElement* vertexNode = m_Document->NewElement(CFG_VERTEX);
        vertexNode->SetAttribute("Name", m_buf[j]);
        vertexNode->SetText("x,y");
        vertex->InsertEndChild(vertexNode);
    }

    surface->InsertEndChild(vertex);
}

void GeoVideoConfig::insertPosition(XMLElement* options)
{
    XMLElement* lon = m_Document->NewElement("lon");
    XMLElement* lat = m_Document->NewElement("lat");
    XMLElement* altitude = m_Document->NewElement("altitude");

    lon->SetText(116.27782);
    lat->SetText(40.04892);
    altitude->SetText(0.0);

    options->InsertEndChild(lon);
    options->InsertEndChild(lat);
    options->InsertEndChild(altitude);

}

void GeoVideoConfig::insertMatrix(XMLElement* modelMatrix)
{
    XMLElement* rotate = m_Document->NewElement("rotate");
    XMLElement* translate = m_Document->NewElement("translate");
    XMLElement* scale = m_Document->NewElement("scale");

    rotate->SetText("180.0,180.0,180.0");
    scale->SetText("0.05,0.05,0.05");
    translate->SetText("-300.0, -920.5,0.1");

    modelMatrix->InsertEndChild(rotate);
    modelMatrix->InsertEndChild(scale);
    modelMatrix->InsertEndChild(translate);
}

void GeoVideoConfig::insertModelPosition()
{
    XMLElement* options = m_Document->NewElement(CFG_POSITION);

    insertPosition(options);

    m_Model->InsertEndChild(options);
}

void GeoVideoConfig::insertModelSurface(int surfaceCnt)
{
    for (int i = 0; i < surfaceCnt; i++)
    {
        XMLElement* surface = m_Document->NewElement(CFG_SURFACE);
        surface->SetAttribute("ID", i);
        surface->SetAttribute("Name", m_surfaceName[i]);
        surface->SetAttribute("Count", INDEX_MAX);

        insertVertex3(surface);
        insertVertex2(surface);

        m_Model->InsertEndChild(surface);
    }

}

void GeoVideoConfig::insertModelMatrix()
{
    XMLElement* modelMatrix = m_Document->NewElement(CFG_MATRIX);

    insertMatrix(modelMatrix);

    m_Model->InsertEndChild(modelMatrix);
}

void GeoVideoConfig::insertElement()
{
    insertRoot();
    insertModel("model-1");
    insertModelPosition();
    insertModelMatrix();
    insertModelSurface(6);
}

void GeoVideoConfig::CreateDefaultXml()
{
    insertElement();

    m_Document->SaveFile(default_model_cfg);
}

void GeoVideoConfig::CreateXml(char* xml)
{
    insertElement();

    m_Document->SaveFile(xml);
}

