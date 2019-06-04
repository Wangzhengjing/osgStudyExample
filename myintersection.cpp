#include "myintersection.h"

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Geometry>

myIntersection::myIntersection()
{
}

//画正方体
osg::ref_ptr<osg::Geode> CreatBox()
{
    osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
    gnode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0,0,0),10.0,10.0,10.0)));
    //gnode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0,0,0),0.1,0.1,20)));
    return gnode;
}

//画线
osg::ref_ptr<osg::Geode> CreateLine(const osg::Vec3 &start, const osg::Vec3 &end)
{
    osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> gy = new osg::Geometry;

    osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;

    gnode ->addDrawable(gy);
    gy->setVertexArray(coords);
    coords->push_back(start);
    coords->push_back(end);
    gy->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP,0,2));

    return gnode;
}

//画球
osg::ref_ptr<osg::Geode> CreateSphere(osg::Vec3d center)
{
    osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
    gnode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(center,0.5)));
    return gnode;
}
