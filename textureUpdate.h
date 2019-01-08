#ifndef TEXTUREUPDATE_H
#define TEXTUREUPDATE_H

#include <osg/Image>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/ImageSequence>
#include <osg/Texture2D>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

class textureUpdate
{
public:
    textureUpdate();

    int doTextureUpdate();
    void doTextureUpdate1();
    void createTexture2D(osg::StateSet& ss,osg::Image* image);
};

#endif // TEXTUREUPDATE_H
