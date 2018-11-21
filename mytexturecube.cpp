#include "mytexturecube.h"

myTextureCube::myTextureCube()
{
}

//读取立方图
osg::ref_ptr<osg::TextureCubeMap> myTextureCube::readCubeMap()
{
    //读取纹理图片
    /*读取立方图纹理贴图时，纹理贴图要与立方体的各个面一一对应
        POSITIVE_X=0, //Left  X正方向
        NEGATIVE_X=1, //Right  X负方向
        POSITIVE_Y=2, //Front  Y正方向
        NEGATIVE_Y=3, //Back  Y负方向
        POSITIVE_Z=4, //Up  Z正方向
        NEGATIVE_Z=5 //Down  Z负方向
    */
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("1.JPG");
    osg::ref_ptr<osg::Image> imagePosX = osgDB::readImageFile("Cubemap_snow/posx.jpg");
    osg::ref_ptr<osg::Image> imageNegX = osgDB::readImageFile("Cubemap_snow/negx.jpg");
    osg::ref_ptr<osg::Image> imagePosY = osgDB::readImageFile("Cubemap_snow/posy.jpg");
    osg::ref_ptr<osg::Image> imageNegY = osgDB::readImageFile("Cubemap_snow/negy.jpg");
    osg::ref_ptr<osg::Image> imagePosZ = osgDB::readImageFile("Cubemap_snow/posz.jpg");
    osg::ref_ptr<osg::Image> imageNegZ = osgDB::readImageFile("Cubemap_snow/negz.jpg");

    //创建立方体纹理对象
    osg::ref_ptr<osg::TextureCubeMap> cubemap = new osg::TextureCubeMap();
    //判断纹理图片存在
    if (imagePosX.get() && imageNegX.get() && imagePosY.get() && imageNegY.get() && imagePosZ.get() && imageNegZ.get())
    {
        //设置立方图的6个面的贴图
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, image.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, image.get());
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, image.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, image.get());
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, image.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, image.get());
#if 0
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, imagePosX.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, imageNegX.get());
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, imagePosY.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, imageNegY.get());
        cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, imagePosZ.get());
        cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, imageNegZ.get());
#endif
        //设置纹理环绕模式
        /*设置纹理的坐标/包装模式
        enum WrapParmeter
        {
            WRAP_S, //x轴
            WRAP_T, //y轴
            WRAP_T //z轴
        };
        enum WrapMode
        {
            CLAMP, //截取
            CLAMP_TO_EDGE, //边框始终被忽略
            CLAMP_TO_BORDER, //它使用的纹理取自图像的边框，没有边框就使用常量边框的颜色
            REPEAT, //纹理的重复映射
            MIRROR //纹理镜像的重复映射
        };
        */
        cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
        cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

        //设置滤波：线性和mipmap
        /*设置纹理的过滤方法/过滤处理
        enum FilterParameter
        {
            MIN_FILTER, //缩小
            MAG_FILTER //放大
        };
        enum FilterMode
        {
            LINEAR, //以周围4个像素的平均值作为纹理
            LINEAR_MIPMAP_LINEAR, //使用线性均和计算两个纹理的值
            LINEAR_MIPMAP_NEAREST, //线性地改写临近的纹理单元值
            NEAREST, //取比较接近的像素作为纹理
            NEAREST_MIPMAP_LINEAR, //在两个纹理中选择最临近的纹理，并取它们之间的线性均和值
            NEAREST_MIPMAP_NEAREST //选择最临近的纹理单元值
        };
        */
        cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
        cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    }

    return cubemap.release();
}

/*
*创建天空盒
*球体天空盒：最常用，看起来更真实，更能描述真实的天空效果
*读取立方图纹理贴图
*创建立方图纹理对象
*设置自动生成纹理坐标
*设置纹理矩阵
*设置立方图纹理
*设置渲染顺序
*加入到叶节点中绘制
*关闭光照并关闭背面剔除，
*把叶节点添加到矩阵变换节点中，以实现合适的矩阵变换
*/
osg::ref_ptr<osg::Node> myTextureCube::createSkyBox()
{
    osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
#if 0
    //设置纹理映射方式，指定为替代方式，即纹理中的颜色代替原来的颜色
    osg::ref_ptr<osg::TexEnv> te = new osg::TexEnv();
    te->setMode(osg::TexEnv::REPLACE);
    stateset->setTextureAttributeAndModes(0, te.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
#endif

#if 1
    //自动生成纹理坐标，反射方式（REFLECTION_MAP）
    /*
        NORMAL_MAP, //标准模式-立方图纹理
        REFLECTION_MAP //反射模式-反射纹理
        SPHERE_MAP //球体模型-球体纹理
    };
    */

    osg::ref_ptr<osg::TexGen> tg = new osg::TexGen();
    tg->setMode(osg::TexGen::NORMAL_MAP);
    stateset->setTextureAttributeAndModes(0, tg.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
#endif

#if 1
    //设置纹理矩阵
    osg::ref_ptr<osg::TexMat>tm = new osg::TexMat();
    stateset->setTextureAttribute(0, tm.get());
#endif

    //设置立方图纹理
    osg::ref_ptr<osg::TextureCubeMap> skymap = readCubeMap();
    stateset->setTextureAttributeAndModes(0, skymap.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);

    //将深度设置为远平面
    osg::ref_ptr<osg::Depth> depth = new osg::Depth();
    depth->setFunction(osg::Depth::ALWAYS);
    depth->setRange(1.0, 1.0); //远平面
    stateset->setAttributeAndModes(depth, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
#if 0
    //设置渲染顺序为-1，先渲染
    stateset->setRenderBinDetails(-1, "RenderBin");
#endif
    osg::ref_ptr<osg::Drawable> drawable = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 1));
    //osg::ref_ptr<osg::Drawable> drawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), 1));

    //把球体加入到叶节点
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->setCullingActive(false);
    geode->setStateSet(stateset.get());
    geode->addDrawable(drawable.get());

    //设置变换
    osg::ref_ptr<osg::Transform> transform = new MoveEarthySkyWithEyePointTransform();
    //关闭背面剔除
    transform->setCullingActive(false);
    transform->addChild(geode.get());
    osg::ref_ptr<osg::ClearNode> clearNode = new osg::ClearNode();
    clearNode->setCullCallback(new TexMatCallback(*tm));
    clearNode->addChild(transform.get());

    return clearNode.release();
}

osg::ref_ptr<osg::Node> myTextureCube::runTextureCube()
{
    return createSkyBox();
}
