#ifndef MYTEXTURECUBE_H
#define MYTEXTURECUBE_H

#include <osg/Geometry>
#include <osg/Geode>

#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>

#include <osg/ShapeDrawable> //预定义几何体类，派生自osg::Drawable类。OSG中使用该类来将OSG内嵌的预定义几何体与osg::Drawable关联以渲染这些几何体
#include <osg/Transform> //一个组节点，所有子节点都通过4x4矩阵进行变换，通常用于在场景中定位对象，生成轨迹球功能或用于动画
//#include <osg/NodeCallback > //节点更新回调
#include <osg/Depth> //封装OpenGL glDepthFunc / Mask / Range函数
#include <osg/CullFace>

#include <osg/TexMat>
#include <osg/TexGen> //指定用于自动生成纹理坐标的函数，可以设置纹理的计算方式是以物体坐标空间还是相机坐标空间来进行不同的计算
#include <osg/TexEnv>
#include <osg/TextureCubeMap> //立方体纹理映射

#include <osgViewer/Viewer>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

class myTextureCube
{
public:
    myTextureCube();

    static osg::ref_ptr<osg::TextureCubeMap> readCubeMap();
    static osg::ref_ptr<osg::Node> createSkyBox();
    static osg::ref_ptr<osg::Node> runTextureCube();
};

//更新立方图纹理
struct TexMatCallback:public osg::NodeCallback
{
public:
    TexMatCallback(osg::TexMat &tm) :
        _texMat(tm)
    {
        //
    }
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nv)
    {
        osgUtil::CullVisitor *cv = dynamic_cast<osgUtil::CullVisitor *>(nv);
        if (cv)
        {
            //得到模型视图矩阵并设置旋转角度
            const osg::Matrix &MV = *(cv->getModelViewMatrix());
            const osg::Matrix R = osg::Matrix::rotate(osg::DegreesToRadians(112.0f), 0.0f, 0.0f, 0.0f) * osg::Matrix::rotate(osg::DegreesToRadians(90.0f), 1.0f, 0.0f, 0.0f);
            osg::Quat q = MV.getRotate();
            const osg::Matrix C = osg::Matrix::rotate(q.inverse());

            //设置纹理矩阵
            _texMat.setMatrix(C*R);
        }
        traverse(node, nv);
    }

    //纹理矩阵
    osg::TexMat &_texMat;
};

//一个变换类，使天空盒绕视点旋转
class MoveEarthySkyWithEyePointTransform :public osg::Transform
{
public:
    //局部矩阵计算成世界矩阵
    virtual bool computerLocalToWorldMatrix(osg::Matrix &matrix, osg::NodeVisitor *nv) const
    {
        osgUtil::CullVisitor *cv = dynamic_cast<osgUtil::CullVisitor *>(nv);
        if (cv)
        {
            osg::Vec3 eyePointLocal = cv->getEyeLocal();
            matrix.preMult(osg::Matrix::translate(eyePointLocal));
        }
        return true;
    }

    //世界矩阵计算为局部矩阵
    virtual bool computerWorldToLocalMatrix(osg::Matrix &matrix, osg::NodeVisitor *nv) const
    {
        osgUtil::CullVisitor *cv = dynamic_cast<osgUtil::CullVisitor *>(nv);
        if (cv)
        {
            osg::Vec3 eyePointLocal = cv->getEyeLocal();
            matrix.postMult(osg::Matrix::translate(-eyePointLocal));
        }
        return true;
    }
};

#endif // MYTEXTURECUBE_H
