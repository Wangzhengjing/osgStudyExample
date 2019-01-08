#include "myCubeTexture.h"
#include "perspectiveTrans.h"
#include <osgDB/WriteFile>

myCubeTexture::myCubeTexture()
{
}

osg::ref_ptr<osg::Image> CVMat_2_OSGImage(cv::Mat& cvimg)
{
//    osg::Image osgframe2();
    osg::Image* osgframe = new osg::Image();
    osgframe->setImage(cvimg.cols, cvimg.rows, 3,
        GL_RGB, GL_BGR, GL_UNSIGNED_BYTE, cvimg.data,
        osg::Image::NO_DELETE, 1);
    return osgframe;
}

osg::ref_ptr<osg::Node> myCubeTexture::createBox(void)
{
    ///创建节点保存绘制的包围盒
    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
    pGeode->addDrawable(pGeometry.get());

    //构建顶点
    osg::ref_ptr<osg::Vec3dArray> pVertexArr = new osg::Vec3dArray;
    pGeometry->setVertexArray(pVertexArr.get());

#define TE
//#undef TE

#ifdef TE
    osg::Vec3d p0(0.0f, 0.0f, 0.0f);
    osg::Vec3d p1(4.0f, 0.0f, 0.0f);
    osg::Vec3d p2(3.0f, 2.0f, 0.0f);
    osg::Vec3d p3(2.0f, 2.0f, 0.0f);
#else
    osg::Vec3d p0(0.0f, -1.0f, 1.0f);
    osg::Vec3d p1(0.0f, 0.0f, 1.0f);
    osg::Vec3d p2(1.0f, 0.0f, 1.0f);
    osg::Vec3d p3(1.0f, -1.0f, 1.0f);
#endif
    pVertexArr->push_back(p0);
    pVertexArr->push_back(p1);
    pVertexArr->push_back(p2);
    pVertexArr->push_back(p3);

    //构建索引
    osg::ref_ptr<osg::DrawElementsUInt> pIndexArr =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS);
    pGeometry->addPrimitiveSet(pIndexArr.get());

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;

#ifdef TE
//    vt->push_back(osg::Vec2(0.25f, 0.0f)); //0,a
//    vt->push_back(osg::Vec2(0.5f, 0.0f));  //1,b
//    vt->push_back(osg::Vec2(1.0f, 1.0f));  //2,c
//    vt->push_back(osg::Vec2(0.0f, 1.0f));  //3,d

    vt->push_back(osg::Vec2(1.0f, 1.0f));  //2,c
    vt->push_back(osg::Vec2(0.0f, 1.0f));  //3,d
    vt->push_back(osg::Vec2(0.25f, 0.0f)); //0,a
    vt->push_back(osg::Vec2(0.5f, 0.0f));  //1,b

#else


    vt->push_back(osg::Vec2(1.0f,1.0f));//2,c
    vt->push_back(osg::Vec2(0.0f,1.0f));//3,d
    vt->push_back(osg::Vec2(0.0f,0.0f));//0,a
    vt->push_back(osg::Vec2(1.0f,0.0f));//1,b
#endif

    pGeometry->setTexCoordArray(0,vt.get());

//    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("1.JPG");
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("abc.jpg");

    //顶
    pIndexArr->push_back(0);pIndexArr->push_back(3);pIndexArr->push_back(2);pIndexArr->push_back(1);
    //左
    //pIndexArr->push_back(0);pIndexArr->push_back(4);pIndexArr->push_back(5);pIndexArr->push_back(1);
    //底
    //pIndexArr->push_back(4);pIndexArr->push_back(7);pIndexArr->push_back(6);pIndexArr->push_back(5);
    //后
    //pIndexArr->push_back(2);pIndexArr->push_back(1);pIndexArr->push_back(5);pIndexArr->push_back(6);
    //右
    //pIndexArr->push_back(2);pIndexArr->push_back(3);pIndexArr->push_back(7);pIndexArr->push_back(6);
    //前
    //pIndexArr->push_back(4);pIndexArr->push_back(7);pIndexArr->push_back(3);pIndexArr->push_back(0);


    if (image.get())
    {
        //状态属性对象
        osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

        //创建一个Texture2D属性对象
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
        //关联image
        texture->setImage(image.get());

        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
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
