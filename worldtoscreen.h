#ifndef WORLDTOSCREEN_H
#define WORLDTOSCREEN_H
#include <osg/Vec3d>
#include <osg/Vec3>
#include <osgViewer/View>

class worldToScreen
{
public:
    worldToScreen();

    osg::Vec3d WorldToScreen(osgViewer::View* view,osg::Vec3 worldpoint);
    static void Transform_Point (double out[4], const double m[16], const double in[4]);
};

#endif // WORLDTOSCREEN_H
