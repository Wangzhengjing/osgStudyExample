#include "mybillboardtree.h"

mybillboardTree::mybillboardTree()
{
}

/**
 * 创建布告板，并进行贴图，后将场景组返回，进行渲染
 *
 * @brief mybillboardTree::createBillboardTree
 * @param image
 * @return
 */
osg::ref_ptr<osg::Node> mybillboardTree::createBillboardTree (osg::ref_ptr<osg::Image> image)
{
    //创建四边形
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;

    //定义顶点，并设置顶点
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    v->push_back(osg::Vec3(-0.5f,0.0f,0.5f));
    v->push_back(osg::Vec3(0.5f,0.0f,-0.5f));
    v->push_back(osg::Vec3(0.5f,0.0f,0.5f));
    v->push_back(osg::Vec3(-0.5f,0.0f,-0.5f));

    geometry->setVertexArray(v.get());

    //设置法线，以及绑定方式(绑定到全部顶点)
    osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array;
    normal->push_back(osg::Vec3(1.0f,0.0f,0.0f) ^ osg::Vec3(0.0f,0.0f,1.0f));

    geometry->setNormalArray(normal.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
    vt->push_back(osg::Vec2(0.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,0.0f));
    vt->push_back(osg::Vec2(1.0f,1.0f));
    vt->push_back(osg::Vec2(0.0f,1.0f));

    geometry->setTexCoordArray(0,vt.get());

    //绘制四边形
    /*
     *指定要利用这些数据生成一个怎么样的形状
     *使用DrawArrays类向Geometry类送入了新几何体的信息，即，该几何体是一个QUADS，它的顶点坐标从索引数组中读入，从第1个索引值开始，共读入4个索引值，组成一个四边形图形。
     *几何体的形状参数除了QUADS之外，还有数种方式，以用于不同的用户需求
     */
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

    if (image.get())
    {
        //状态属性对象
        osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

        //创建一个Texture2D属性对象
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
        //关联image
        texture->setImage(image.get());
        //关联Texture2D纹理对象，第三个参数默认为ON
        stateset->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
        //启用混合
        stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
        //关闭光照
        stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

        geometry->setStateSet(stateset.get());
    }

    //创建billboard对象一
    osg::ref_ptr<osg::Billboard> billboard1 = new osg::Billboard;

    //设置旋转模式为绕视点
    billboard1->setMode(osg::Billboard::POINT_ROT_EYE);
    //添加drawable，并设置其位置，默认位置为osg::Vec3(0.0f,0.0f,0.0f)
    billboard1->addDrawable(geometry.get(),osg::Vec3(5.0f,0.0f,0.0f));

    //创建billboard对象二
    osg::ref_ptr<osg::Billboard> billboard2 = new osg::Billboard;

    //设置旋转模式为绕轴转，因此要设置轴旋转
    billboard2->setMode(osg::Billboard::AXIAL_ROT);
    //设置旋转轴
    billboard2->setAxis(osg::Vec3(0.0f,0.0f,1.0f));
    billboard2->addDrawable(geometry.get(),osg::Vec3(10.0f,0.0f,0.0f));

    osg::ref_ptr<osg::Group> billboard = new osg::Group;
    billboard->addChild(billboard1.get());
    billboard->addChild(billboard2.get());

    return billboard.get();
}
