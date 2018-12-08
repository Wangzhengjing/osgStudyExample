#ifndef myCubeTexture_H
#define myCubeTexture_H

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Array>
#include <osg/Image>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

class myCubeTexture
{
public:
    myCubeTexture();

    static osg::ref_ptr<osg::Node> createBox(void);
};

#endif // MYCUBE_H
