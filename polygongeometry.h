#ifndef POLYGONGEOMETRY_H
#define POLYGONGEOMETRY_H

#include <osg/Geode>
#include <osg/Array>
#include <osg/Geometry>

class polygonGeometry
{
public:
    polygonGeometry();

    static osg::ref_ptr<osg::Geometry> createPolygon();
};

#endif // POLYGONGEOMETRY_H
