#ifndef MYBILLBOARDTREE_H
#define MYBILLBOARDTREE_H

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Billboard>
#include <osg/Image>
#include <osg/Geometry>
#include <osg/Texture2D>

class mybillboardTree
{
public:
    mybillboardTree();

    static osg::ref_ptr<osg::Node> createBillboardTree (osg::ref_ptr<osg::Image> image);
};

#endif // MYBILLBOARDTREE_H
