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
    osg::ref_ptr<osg::Vec3Array> pVertexArr = new osg::Vec3Array;
    pGeometry->setVertexArray(pVertexArr.get());

    osg::Vec3d p0(0.0f, 0.0f, 0.0f);
    osg::Vec3d p1(1.0f, 0.0f, 0.0f);
    osg::Vec3d p2(1.0f, 1.0f, 0.0f);
    osg::Vec3d p3(0.0f, 1.0f, 0.0f);

    osg::Vec3d p4(0.0f, 0.0f, 1.0f);
    osg::Vec3d p5(1.0f, 0.0f, 1.0f);

    pVertexArr->push_back(p0);
    pVertexArr->push_back(p1);
    pVertexArr->push_back(p2);
    pVertexArr->push_back(p3);

    pVertexArr->push_back(p0);
    pVertexArr->push_back(p1);
    pVertexArr->push_back(p5);
    pVertexArr->push_back(p4);

    for (int i = 0; i < 2; i++)
    {
        //设置纹理坐标
        osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array(i*4);
        pGeometry->setTexCoordArray(i,vt.get());

        vt->push_back(osg::Vec2(0.0f, 0.0f));  //2,c
        vt->push_back(osg::Vec2(0.0f, 1.0f));  //3,d
        vt->push_back(osg::Vec2(1.0f, 1.0f)); //0,a
        vt->push_back(osg::Vec2(1.0f, 0.0f));  //1,b

        pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, i*4, 4));
    }
//    osg::ref_ptr<osg::Vec3dArray> nc1 = new osg::Vec3dArray;
//    nc1->push_back(osg::Vec3(0.0f,0.0f,-1.0f));
//    nc1->push_back(osg::Vec3(0.0f,-1.0f,0.0f));
//    pGeometry->setNormalArray(nc1.get(), osg::Array::BIND_PER_PRIMITIVE_SET);
//    pGeometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
    osg::ref_ptr<osg::Vec3dArray> nc1 = new osg::Vec3dArray;
    nc1->push_back(osg::Vec3(0.0f,0.0f,-1.0f));
    pGeometry->setNormalArray(nc1.get(), osg::Array::BIND_OVERALL);
    pGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("C:\\Users\\wangpeng\\Desktop\\pic\\1.jpg");
    osg::ref_ptr<osg::Image> image1 = osgDB::readImageFile("C:\\Users\\wangpeng\\Desktop\\pic\\3.jpg");

    //状态属性对象
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

    for (int i = 0; i < 2; i++)
    {
        //创建一个Texture2D属性对象
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

        //关联image
        if (i == 0 && image.valid())
        {
            texture->setImage(image.get());
        } else if (i == 1 && image1.valid())
        {
            texture->setImage(image1.get());
        }

        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
        //关联Texture2D纹理对象，第三个参数默认为ON
        std::cout << "texture : " << i << std::endl;
        stateset->setTextureAttributeAndModes(i, texture, osg::StateAttribute::ON);
    }

    //启用混合
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    //关闭光照
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    pGeometry->setStateSet(stateset.get());


    return pGeode.get();
}
