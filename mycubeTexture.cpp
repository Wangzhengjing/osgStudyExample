#include "myCubeTexture.h"
#include "perspectiveTrans.h"
#include <osgDB/WriteFile>
#include "VideoStream.h"
#include "ffmpeg/FFmpegImageStream.hpp"
#include "ffmpeg/FFmpegParameters.hpp"
#include "myFFmpegImageStream.h"

using namespace osgFFmpeg;

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

    std::string videopath = "C:\\osg\\Geo3D\\TestLibss\\data\\03.mov";
    std::string videopath1 = "C:\\osg\\Geo3D\\TestLibss\\data\\shiwai1.mp4";

    VideoStream* videoStream = new VideoStream(videopath);
    VideoStream* videoStream1 = new VideoStream(videopath1);


    //状态属性对象
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

    int num = 2;
    for (int i = 0; i < num; i++)
    {
        //创建一个Texture2D属性对象
        osg::ref_ptr<osg::Texture2D> texture;

        //关联image
        if (i == 0 && image.valid())
        {
            texture = new osg::Texture2D(videoStream->GetImage());
            videoStream->VideoPlay();

//            texture->setImage(image.get());
//            texture->setImage(videoStream->GetImage());
        } else if (i == 1 && image1.valid())
        {
            texture = new osg::Texture2D(videoStream1->GetImage());
            videoStream1->VideoPlay();

//            texture->setImage(image1.get());
//            texture->setImage(videoStream1->GetImage());
        }

        texture->setDataVariance(osg::Object::DYNAMIC);

        texture->setResizeNonPowerOfTwoHint(false);
        texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);

        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
//        texture->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
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

osg::ref_ptr<osg::Node> myCubeTexture::createBox2(void)
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

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
    pGeometry->setTexCoordArray(0,vt.get());

    vt->push_back(osg::Vec2(0.0f, 0.0f));  //2,c
    vt->push_back(osg::Vec2(0.0f, 1.0f));  //3,d
    vt->push_back(osg::Vec2(1.0f, 1.0f)); //0,a
    vt->push_back(osg::Vec2(1.0f, 0.0f));  //1,b

    pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

    osg::ref_ptr<osg::Vec3dArray> nc1 = new osg::Vec3dArray;
    nc1->push_back(osg::Vec3(0.0f,0.0f,-1.0f));
    pGeometry->setNormalArray(nc1.get(), osg::Array::BIND_OVERALL);
    pGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

//    std::string videopath = "C:\\osg\\Geo3D\\TestLibss\\data\\03.mov";
    std::string videopath = "C:\\osg\\Geo3D\\TestLibss\\data\\shiwai1.mp4";

#if 1
//#define ME_1
#ifdef ME_1
    VideoStream* videoStream = new VideoStream(videopath);
#else
    std::cout <<"start"<<std::endl;
    FFmpegImageStream* videoStream = new FFmpegImageStream;
    videoStream->open(videopath, new FFmpegParameters);
#endif

#ifdef ME_1
    videoStream->VideoPlay();
#else
    videoStream->play();
#endif
#else

    myFFmpegImageStream* videoStream = new myFFmpegImageStream;

    int got_frame = 0;
    videoStream->getFrame(&got_frame, videopath);
#endif
    //创建一个Texture2D属性对象
    osg::ref_ptr<osg::Texture2D> texture;
    //状态属性对象
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

    //关联image
    texture = new osg::Texture2D(/*videoStream->GetImage()*/);

    texture->setDataVariance(osg::Object::DYNAMIC);

    texture->setResizeNonPowerOfTwoHint(false);
    texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);

    texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
    texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
    //        texture->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
    //关联Texture2D纹理对象，第三个参数默认为ON
    stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

    //启用混合
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    //关闭光照
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    pGeometry->setStateSet(stateset.get());

    osg::Image * img = videoStream->asImage();
    osgDB::writeImageFile(*img, "C:\\Users\\wangpeng\\Desktop\\pic\\out\\xxx.jpg");

    return pGeode.get();
}

osg::ref_ptr<osg::Node> myCubeTexture::createBox3(void)
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

    //设置纹理坐标
    osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
    pGeometry->setTexCoordArray(0,vt.get());

    vt->push_back(osg::Vec2(0.0f, 0.0f));  //2,c
    vt->push_back(osg::Vec2(0.0f, 1.0f));  //3,d
    vt->push_back(osg::Vec2(1.0f, 1.0f)); //0,a
    vt->push_back(osg::Vec2(1.0f, 0.0f));  //1,b

    pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

    osg::ref_ptr<osg::Vec3dArray> nc1 = new osg::Vec3dArray;
    nc1->push_back(osg::Vec3(0.0f,0.0f,-1.0f));
    pGeometry->setNormalArray(nc1.get(), osg::Array::BIND_OVERALL);
    pGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

//    std::string videopath = "C:\\osg\\Geo3D\\TestLibss\\data\\03.mov";
    std::string videopath = "C:\\osg\\Geo3D\\TestLibss\\data\\shiwai1.mp4";

    myFFmpegImageStream* videoStream = new myFFmpegImageStream;

    int got_frame = 0;
    videoStream->getFrame(&got_frame, videopath);

    //创建一个Texture2D属性对象
    osg::ref_ptr<osg::Texture2D> texture;
    //状态属性对象
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

    //关联image
    texture = new osg::Texture2D(/*videoStream->GetImage()*/);

    texture->setDataVariance(osg::Object::DYNAMIC);

    texture->setResizeNonPowerOfTwoHint(false);
    texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);

    texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
    texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
    //        texture->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
    //关联Texture2D纹理对象，第三个参数默认为ON
    stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

    //启用混合
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    //关闭光照
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    pGeometry->setStateSet(stateset.get());

    return pGeode.get();
}

int count = 0;

unsigned char* mycb(int width, int height, unsigned char * pc)
{
    std::cout << "this is my Transform callback with width : " << width << "," << "heigth : " << height << std::endl;
//    cv::Mat mat = Mat(height, width, CV_8UC1, (void *)pc);

    std::cout << "this is mycb---0" << std::endl;
//    OpenThreads::Thread::microSleep(5000000);

//    cv::imwrite("C:\\Users\\wangpeng\\Desktop\\pic\\out\\out.jpg", mat);

    return NULL;
}

int count1 = 0;

unsigned char* mycb1(int width, int height, unsigned char * pc)
{
    std::cout << "this is my Transform callback with width : " << width << "," << "heigth : " << height << std::endl;
//    cv::Mat mat = Mat(height, width, CV_8UC1, (void *)pc);
    std::cout << "this is mycb---1" << std::endl;

//    OpenThreads::Thread::microSleep(1000);

//    cv::imwrite("C:\\Users\\wangpeng\\Desktop\\pic\\out\\out.jpg", mat);

    return NULL;
}

osg::ref_ptr<osg::Node> myCubeTexture::createBox4(void)
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

    std::string videopath = "C:\\osg\\Geo3D\\TestLibss\\data\\03.mov";
    std::string videopath1 = "C:\\osg\\Geo3D\\TestLibss\\data\\shiwai1.mp4";

    VideoStream* videoStream = new VideoStream(videopath);
    VideoStream* videoStream1 = new VideoStream(videopath1);

    videoStream1->setTransformcb(mycb1);
    videoStream->setTransformcb(mycb);

    //状态属性对象
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet;

    int num = 2;
    for (int i = 0; i < num; i++)
    {
        //创建一个Texture2D属性对象
        osg::ref_ptr<osg::Texture2D> texture;

        //关联image
        if (i == 0 && image.valid())
        {
            texture = new osg::Texture2D(videoStream->GetImage());
            videoStream->VideoPlay();

//            texture->setImage(image.get());
//            texture->setImage(videoStream->GetImage());
        } else if (i == 1 && image1.valid())
        {
            texture = new osg::Texture2D(videoStream1->GetImage());
            videoStream1->VideoPlay();

//            texture->setImage(image1.get());
//            texture->setImage(videoStream1->GetImage());
        }

        texture->setDataVariance(osg::Object::DYNAMIC);

        texture->setResizeNonPowerOfTwoHint(false);
        texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);

        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
//        texture->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);
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
