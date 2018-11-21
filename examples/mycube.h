#ifndef MYCUBE_H
#define MYCUBE_H

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Billboard>
#include <osg/Image>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/LineWidth>
#include <osgText/Text>
#include <osgDB/ReadFile>
#include <osg/TextureCubeMap>
#include <osg/ShapeDrawable>
#include <osg/TexGen>
#include <osg/TexMat>

class myCube
{
public:
    myCube();

    static void showBoundingBox(osg::Group* pGroup,osg::BoundingBox bb,bool showPoint = true);
    static osg::ref_ptr<osg::Node> createBox(osg::BoundingBox bb,bool showPoint = true);
    static osg::ref_ptr<osg::Node> createBox2(void);
    static osg::ref_ptr<osg::Node> createBox3(void);
};

#endif // MYCUBE_H
