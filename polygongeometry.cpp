#include "polygongeometry.h"

polygonGeometry::polygonGeometry()
{
}
#if 0
osg::ref_ptr<osg::Geometry> polygonGeometry::createPolygon(osg::ref_ptr<osg::Geometry> geom)
{
//    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    //设置顶点坐标
    osg::ref_ptr<osg::Vec2Array> vc = new osg::Vec2Array();

    vc->push_back(osg::Vec2(0.0f, 0.0f));
    vc->push_back(osg::Vec2(4.0f, 0.0f));
    vc->push_back(osg::Vec2(2.0f, 2.0f));
    vc->push_back(osg::Vec2(1.0f, 2.0f));

    geom->setVertexArray(vc.get());

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

    geom->setTexCoordArray(0, vt.get());

    vt->push_back(osg::Vec2(0.0f, 0.0f));
    vt->push_back(osg::Vec2(4.0f, 0.0f));
    vt->push_back(osg::Vec2(2.0f, 2.0f));
    vt->push_back(osg::Vec2(1.0f, 2.0f));

    //设置法线
    osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
    nc->push_back(osg::Vec3(0.0f,-1.0f,0.0f));

    geom->setNormalArray(nc.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //添加图元
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON,0,4));

    return geom;
}
#endif
