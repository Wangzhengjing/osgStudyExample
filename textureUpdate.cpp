#include "textureUpdate.h"

textureUpdate::textureUpdate()
{
}

void textureUpdate::doTextureUpdate1()
{
    osg::Image* img0 = osgDB::readImageFile("C:\\Users\\wangpeng\\Desktop\\pic\\1.jpg");
    osg::Image* img1 = osgDB::readImageFile("C:\\Users\\wangpeng\\Desktop\\pic\\2_d.jpg");
    //设置纹理数据
    img0->setImage(1024, 768, 1,img1->getInternalTextureFormat(),img1->getPixelFormat(),img1->getDataType(), img1->data(), osg::Image::USE_MALLOC_FREE);
    //刷新
    img0->dirty();
    std::cout << "dfas\n";
    osg::Texture2D* tex = new osg::Texture2D;
    //设置为动态数据
    tex->setDataVariance(osg::Object::DYNAMIC);
    tex->setImage(img0);
}

void textureUpdate::createTexture2D(osg::StateSet& ss,osg::Image* image)
{
    osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D;
    texture->setImage(image);
    texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
    texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
    texture->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_BORDER);
    texture->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_BORDER);

    ss.setTextureAttributeAndModes(0,texture.get());
}

int textureUpdate::doTextureUpdate()
{
    osg::ref_ptr<osg::ImageSequence> imageSquence=new osg::ImageSequence;

    imageSquence->addImageFile("E:\\ProjectDocMng\\otherCode\\DynamicTexture\\images\\ocean_v2.jpg");
    imageSquence->addImageFile("E:\\ProjectDocMng\\otherCode\\DynamicTexture\\images\\ocean_v3.jpg");

    osg::ref_ptr<osg::Geode> geode=new osg::Geode;
    geode->addDrawable(osg::createTexturedQuadGeometry(osg::Vec3(0.0,0.0,0.0),osg::Vec3(1.0,0.0,0.0),osg::Vec3(0.0,0.0,1.0),1.0,1.0));
    createTexture2D(*(geode->getOrCreateStateSet()),imageSquence.get());

    imageSquence->setLength(5.0);
    imageSquence->setTimeMultiplier(20);
    imageSquence->play();

    osgViewer::Viewer viewer;
    viewer.setSceneData(geode.get());
    return viewer.run();
}
