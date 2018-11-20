#include "mycube.h"
#include <iostream>

using namespace std;

myCube::myCube()
{
}

osg::ref_ptr<osg::Node> myCube::createBox2(osg::BoundingBox bb,bool showPoint)
{
    ///创建节点保存绘制的包围盒
    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
    pGeode->addDrawable(pGeometry.get());

    //构建顶点
    osg::ref_ptr<osg::Vec3dArray> pVertexArr = new osg::Vec3dArray;
    pGeometry->setVertexArray(pVertexArr.get());

    osg::Vec3d p0(0.0f, -1.0f, 1.0f);
    osg::Vec3d p1(0.0f, 0.0f, 1.0f);
    osg::Vec3d p2(1.0f, 0.0f, 1.0f);
    osg::Vec3d p3(1.0f, -1.0f, 1.0f);
    osg::Vec3d p4(0.0f, -1.0f, 0.0f);
    osg::Vec3d p5(0.0f, 0.0f, 0.0f);
    osg::Vec3d p6(1.0f, 0.0f, 0.0f);
    osg::Vec3d p7(1.0f, -1.0f, 0.0f);

    pVertexArr->push_back(p0);
    pVertexArr->push_back(p1);
    pVertexArr->push_back(p2);
    pVertexArr->push_back(p3);
    pVertexArr->push_back(p4);
    pVertexArr->push_back(p5);
    pVertexArr->push_back(p6);
    pVertexArr->push_back(p7);

    //构建索引
    osg::ref_ptr<osg::DrawElementsUInt> pIndexArr =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS);
    pGeometry->addPrimitiveSet(pIndexArr.get());

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;

    vt->push_back(osg::Vec2(0.0f,0.0f));//0,a
    vt->push_back(osg::Vec2(1.0f,0.0f));//1,b
    vt->push_back(osg::Vec2(1.0f,1.0f));//2,c
    vt->push_back(osg::Vec2(0.0f,1.0f));//3,d
    vt->push_back(osg::Vec2(1.0f,1.0f));//4,c
    vt->push_back(osg::Vec2(0.0f,1.0f));//5,d
    vt->push_back(osg::Vec2(0.0f,0.0f));//6,a
    vt->push_back(osg::Vec2(1.0f,0.0f));//7,b

    pGeometry->setTexCoordArray(0,vt.get());

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("1.JPG");

    //顶
    pIndexArr->push_back(0);pIndexArr->push_back(3);pIndexArr->push_back(2);pIndexArr->push_back(1);
    //左
    pIndexArr->push_back(0);pIndexArr->push_back(4);pIndexArr->push_back(5);pIndexArr->push_back(1);
    //底
    pIndexArr->push_back(4);pIndexArr->push_back(7);pIndexArr->push_back(6);pIndexArr->push_back(5);
    //后
    pIndexArr->push_back(2);pIndexArr->push_back(1);pIndexArr->push_back(5);pIndexArr->push_back(6);
    //右
    pIndexArr->push_back(2);pIndexArr->push_back(3);pIndexArr->push_back(7);pIndexArr->push_back(6);
    //前
    pIndexArr->push_back(4);pIndexArr->push_back(7);pIndexArr->push_back(3);pIndexArr->push_back(0);


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

        pGeometry->setStateSet(stateset.get());
    }

    return pGeode.get();
}

osg::ref_ptr<osg::Node> myCube::createBox(osg::BoundingBox bb,bool showPoint)
{
    ///创建节点保存绘制的包围盒
    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
    pGeode->addDrawable(pGeometry.get());

    //构建顶点
    osg::ref_ptr<osg::Vec3dArray> pVertexArr = new osg::Vec3dArray;
    pGeometry->setVertexArray(pVertexArr.get());

    osg::Vec3d p0(0.0f, -1.0f, 1.0f);
    osg::Vec3d p1(0.0f, 0.0f, 1.0f);
    osg::Vec3d p2(1.0f, 0.0f, 1.0f);
    osg::Vec3d p3(1.0f, -1.0f, 1.0f);
    osg::Vec3d p4(0.0f, -1.0f, 0.0f);
    osg::Vec3d p5(0.0f, 0.0f, 0.0f);
    osg::Vec3d p6(1.0f, 0.0f, 0.0f);
    osg::Vec3d p7(1.0f, -1.0f, 0.0f);

    pVertexArr->push_back(p0);
    pVertexArr->push_back(p1);
    pVertexArr->push_back(p2);
    pVertexArr->push_back(p3);
    pVertexArr->push_back(p4);
    pVertexArr->push_back(p5);
    pVertexArr->push_back(p6);
    pVertexArr->push_back(p7);

    //构建索引
    osg::ref_ptr<osg::DrawElementsUInt> pIndexArr =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS);
    pGeometry->addPrimitiveSet(pIndexArr.get());

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;

    vt->push_back(osg::Vec2(0.0f,0.0f));//0,a
    vt->push_back(osg::Vec2(1.0f,0.0f));//1,b
    vt->push_back(osg::Vec2(1.0f,1.0f));//2,c
    vt->push_back(osg::Vec2(0.0f,1.0f));//3,d
    vt->push_back(osg::Vec2(1.0f,1.0f));//4,c
    vt->push_back(osg::Vec2(0.0f,1.0f));//5,d
    vt->push_back(osg::Vec2(0.0f,0.0f));//6,a
    vt->push_back(osg::Vec2(1.0f,0.0f));//7,b

    pGeometry->setTexCoordArray(0,vt.get());

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("1.JPG");

    //顶
    //pIndexArr->push_back(0);pIndexArr->push_back(3);pIndexArr->push_back(2);pIndexArr->push_back(1);
    //左
    pIndexArr->push_back(0);pIndexArr->push_back(4);pIndexArr->push_back(5);pIndexArr->push_back(1);
    //底
    pIndexArr->push_back(4);pIndexArr->push_back(7);pIndexArr->push_back(6);pIndexArr->push_back(5);
    //后
    pIndexArr->push_back(2);pIndexArr->push_back(1);pIndexArr->push_back(5);pIndexArr->push_back(6);
    //右
    pIndexArr->push_back(2);pIndexArr->push_back(3);pIndexArr->push_back(7);pIndexArr->push_back(6);
    //前
    pIndexArr->push_back(4);pIndexArr->push_back(7);pIndexArr->push_back(3);pIndexArr->push_back(0);


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

        pGeometry->setStateSet(stateset.get());
    }

    return pGeode.get();
}

void myCube::showBoundingBox(osg::Group* pGroup,osg::BoundingBox bb,bool showPoint)
{
    ///创建节点保存绘制的包围盒
    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
    pGroup->addChild(pGeode);
    osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
    pGeode->addDrawable(pGeometry.get());


    osg::ref_ptr<osg::LineWidth> mpWidth = new osg::LineWidth(2);
    //设置包围盒线宽为2
    osg::StateSet* pStateSet = pGeode->getOrCreateStateSet();
    pStateSet->setAttributeAndModes(mpWidth.get(),osg::StateAttribute::ON);
    //设置光照关闭
    pStateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    //构建顶点
    osg::ref_ptr<osg::Vec3dArray> pVertexArr = new osg::Vec3dArray;
    pGeometry->setVertexArray(pVertexArr.get());
    //获取包围盒参数，构建顶点
    double xmax = bb.xMax();
    double ymax = bb.yMax();
    double zmax = bb.zMax();
    double xmin = bb.xMin();
    double ymin = bb.yMin();
    double zmin = bb.zMin();
    osg::Vec3d p0(xmin,ymin,zmax);
    osg::Vec3d p1(xmax,ymin,zmax);
    osg::Vec3d p2(xmax,ymax,zmax);
    osg::Vec3d p3(xmin,ymax,zmax);
    osg::Vec3d p4(xmin,ymin,zmin);
    osg::Vec3d p5(xmax,ymin,zmin);
    osg::Vec3d p6(xmax,ymax,zmin);
    osg::Vec3d p7(xmin,ymax,zmin);
    pVertexArr->push_back(p0);
    pVertexArr->push_back(p1);
    pVertexArr->push_back(p2);
    pVertexArr->push_back(p3);
    pVertexArr->push_back(p4);
    pVertexArr->push_back(p5);
    pVertexArr->push_back(p6);
    pVertexArr->push_back(p7);


    //构建索引
    osg::ref_ptr<osg::DrawElementsUInt> pIndexArr =
        new osg::DrawElementsUInt(osg::PrimitiveSet::LINES);
    pGeometry->addPrimitiveSet(pIndexArr.get());

    pIndexArr->push_back(0);pIndexArr->push_back(1);
    pIndexArr->push_back(0);pIndexArr->push_back(3);
    pIndexArr->push_back(2);pIndexArr->push_back(1);
    pIndexArr->push_back(2);pIndexArr->push_back(3);

    pIndexArr->push_back(4);pIndexArr->push_back(5);
    pIndexArr->push_back(4);pIndexArr->push_back(7);
    pIndexArr->push_back(6);pIndexArr->push_back(5);
    pIndexArr->push_back(6);pIndexArr->push_back(7);

    pIndexArr->push_back(0);pIndexArr->push_back(4);
    pIndexArr->push_back(1);pIndexArr->push_back(5);
    pIndexArr->push_back(2);pIndexArr->push_back(6);
    pIndexArr->push_back(3);pIndexArr->push_back(7);

    //设置颜色
    osg::ref_ptr<osg::Vec4Array> pColorArr = new osg::Vec4Array;
    pGeometry->setColorArray(pColorArr.get(), osg::Array::BIND_PER_VERTEX);
    for (int i = 0; i < 8; ++i)
    {
        pColorArr->push_back(osg::Vec4d(1,1,1,1));
    }

    //这一段代码是为了解释上面的顶点，如果不需要，将参数设置为false
    if (showPoint)
    {
        osg::Vec4d textColor(0,1,0,1);

        osg::ref_ptr<osgText::Text> pText0 = new osgText::Text;
        pText0->setText("p0");
        pText0->setPosition(p0);
        pText0->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText0->setColor(textColor);
        pText0->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText0);

        osg::ref_ptr<osgText::Text> pText1 = new osgText::Text;
        pText1->setText("p1");
        pText1->setPosition(p1);
        pText1->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText1->setColor(textColor);
        pText1->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText1);

        osg::ref_ptr<osgText::Text> pText2 = new osgText::Text;
        pText2->setText("p2");
        pText2->setPosition(p2);
        pText2->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText2->setColor(textColor);
        pText2->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText2);

        osg::ref_ptr<osgText::Text> pText3 = new osgText::Text;
        pText3->setText("p3");
        pText3->setPosition(p3);
        pText3->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText3->setColor(textColor);
        pText3->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText3);

        osg::ref_ptr<osgText::Text> pText4 = new osgText::Text;
        pText4->setText("p4");
        pText4->setPosition(p4);
        pText4->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText4->setColor(textColor);
        pText4->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText4);

        osg::ref_ptr<osgText::Text> pText5 = new osgText::Text;
        pText5->setText("p5");
        pText5->setPosition(p5);
        pText5->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText5->setColor(textColor);
        pText5->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText5);

        osg::ref_ptr<osgText::Text> pText6 = new osgText::Text;
        pText6->setText("p6");
        pText6->setPosition(p6);
        pText6->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText6->setColor(textColor);
        pText6->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText6);

        osg::ref_ptr<osgText::Text> pText7 = new osgText::Text;
        pText7->setText("poppo");
        pText7->setPosition(p7);
        pText7->setCharacterSizeMode( osgText::TextBase::SCREEN_COORDS );
        pText7->setColor(textColor);
        pText7->setAxisAlignment(osgText::TextBase::SCREEN);
        pGeode->addDrawable(pText7);

    }
}
