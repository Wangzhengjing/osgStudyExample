#include "myMatrixTransform.h"
#include <osgViewer/View>

myMatrixTransform::myMatrixTransform()
{
}

/**
 * 输入点，进行矩阵变换
 *
 * @brief Transform_Point
 * @param out
 * @param m
 * @param in
 */
void myMatrixTransform::Transform_Point (double out[4], const double m[16], const double in[4])
{
#define M(row, col) m[col*4 + row]
    out[0] = M(0,0) * in[0] + M(0,1) * in[1] + M(0,2) * in[2] + M(0,3) * in[3];
    out[1] = M(1,0) * in[0] + M(1,1) * in[1] + M(1,2) * in[2] + M(1,3) * in[3];
    out[2] = M(2,0) * in[0] + M(2,1) * in[1] + M(2,2) * in[2] + M(2,3) * in[3];
    out[3] = M(3,0) * in[0] + M(3,1) * in[1] + M(3,2) * in[2] + M(3,3) * in[3];
#undef M(row, col)
}

/**
 * 返回三维点在二维屏幕上的投影点
 *
 * @brief myMatrixTransform::myMatrixTransform
 * @param view
 * @param worldpoint
 * @return
 */
osg::Vec3d myMatrixTransform::WorldToScreen(osgViewer::View* view,osg::Vec3 worldpoint)
{
    //用于保存进行变换前后点的坐标
    double in[4],out[4];

    in[0] = worldpoint._v[0];
    in[1] = worldpoint._v[1];
    in[2] = worldpoint._v[2];
    in[3] = 1.0;
    //获得当前的投影矩阵和模型视图矩阵
    osg::Matrix projectMatrix = view->getCamera()->getProjectionMatrix();
    osg::Matrix viewprojectMatrix = view->getCamera()->getViewMatrix();
    //进行坐标模型矩阵变换，变换模型视图矩阵
    double modelViewMatrix[16];
    memcpy(modelViewMatrix,viewprojectMatrix.ptr(),sizeof(GLdouble)*16);
    Transform_Point(out,modelViewMatrix,in);

    //进行坐标投影矩阵变换，变换投影矩阵
    double myprojectMatrix[16];
    memcpy(myprojectMatrix,projectMatrix.ptr(),sizeof(GLdouble)*16);
    Transform_Point(out,myprojectMatrix,in);

    //变换视口变换矩阵
    if(in[3] == 0.0)
      return osg::Vec3d(0,0,0);

    in[0]/=in[3];
    in[1]/=in[3];
    in[2]/=in[3];

    //得到视口变换矩阵
    int viewPort[4];
    osg::Viewport* myviewport = view->getCamera()->getViewport();
    viewPort[0] = myviewport->x();
    viewPort[1] = myviewport->y();
    viewPort[2] = myviewport->width();
    viewPort[3] = myviewport->height();

    //计算二维屏幕投影点，保存变换的二维屏幕坐标
    osg::Vec3d screenPoint;
    screenPoint._v[0] = (int)(viewPort[0] + (1+in[0])*viewPort[2]/2+0.5);
    screenPoint._v[0] = (int)(viewPort[1] + (1+in[1])*viewPort[3]/2+0.5);
    screenPoint._v[2] = 0;

    return screenPoint;
}

/**
 * 将屏幕坐标转换到世界坐标
 *
 * @brief myMatrixTransform::screen2World
 * @param viewer
 * @param screenPoint
 * @return
 */
osg::Vec3d myMatrixTransform::screen2World(osgViewer::View* viewer, osg::Vec3 screenPoint)
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

    osg::Matrix mVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    osg::Matrix invertVPW;
    invertVPW.invert(mVPW);
    vec3 = screenPoint * invertVPW;

    return vec3;
}

/**
 * 世界到屏幕
 *
 * @brief myMatrixTransform::world2Screen
 * @param viewer
 * @param worldPoint
 * @return
 */
osg::Vec3d myMatrixTransform::world2Screen(osgViewer::View* viewer, osg::Vec3 worldPoint)
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

    osg::Matrix mVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    vec3 = worldPoint * mVPW;

    return vec3;
}

/**
 * 世界转相机
 *
 * @brief myMatrixTransform::world2Camera
 * @param worldPoint
 * @return
 */
osg::Vec3d myMatrixTransform::world2Camera(osgViewer::View* viewer, osg::Vec3 worldPoint)
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

    osg::Matrix mV = camera->getViewMatrix();
    vec3 = worldPoint * mV;

    return vec3;
}

/**
 * 相机转世界
 *
 * @brief myMatrixTransform::camera2World
 * @param viewer
 * @param cameraPoint
 * @return
 */
osg::Vec3d myMatrixTransform::camera2World(osgViewer::View* viewer, osg::Vec3 cameraPoint)
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

    osg::Matrix mV = camera->getViewMatrix();
    osg::Matrix invertmV;

    invertmV.invert(mV);
    vec3 = cameraPoint * invertmV ;

    return vec3;
}

/**
 * 屏幕转相机
 *
 * @brief myMatrixTransform::screen2Camera
 * @param viewer
 * @param screenPoint
 * @return
 */
osg::Vec3d myMatrixTransform::screen2Camera(osgViewer::View* viewer, osg::Vec3 screenPoint)
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

    osg::Matrix mPW = camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    osg::Matrix invertmPW;
    invertmPW.invert(mPW);
    vec3 = screenPoint * invertmPW;

    return vec3;
}

/**
 * 相机转屏幕
 *
 * @brief myMatrixTransform::camera2Screen
 * @param viewer
 * @param cameraPoint
 * @return
 */
osg::Vec3d myMatrixTransform::camera2Screen(osgViewer::View* viewer, osg::Vec3 cameraPoint)
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

    osg::Matrix mPW = camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    vec3 = cameraPoint * mPW;

    return vec3;
}
