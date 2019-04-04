#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>
#include "getworldcoordinateofnodevisitor.h"
#include "examples/mybillboardtree.h"
#include "examples/mycube.h"
#include <osg/ComputeBoundsVisitor>
#include "mytexture.h"
#include "mytexturecube.h"
#include "examplestexture.h"

#include <osgGA/NodeTrackerManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/AnimationPathManipulator>
#include "mymanipulator.h"
#include <osgEarth/GeoData>
#include <osgEarthUtil/EarthManipulator>
#include "earthwalkmanipulator2.h"
#include "mycubeTexture.h"
#include "perspectiveTrans.h"
#include "polygongeometry.h"
#include "textureUpdate.h"
#include "moviePlay.h"
#include <math.h>
#include "config/geoVideoConfig.h"
#include "config/geoConfigParser.h"

using namespace osgEarth;
using namespace osgEarth::Util;

enum Vertex {
    LEFT_TOP = 0,
    RIGHT_TOP = 1,
    RIGHT_BOTTOM = 2,
    LEFT_BOTTOM = 3
};

#define PI 3.141592653

int myManipulator()
{
    //正常的.earth文件加载
    osgViewer::Viewer viewer;
    MapNode* s_mapNode = 0L;
    osg::Node* earthFile = osgDB::readNodeFile("C:\\osg\\Geo3D\\build\\bin\\data\\project\\Geo3D.earth");
    if (earthFile)
        s_mapNode = MapNode::get(earthFile);
    if (!s_mapNode)
    {
        OE_WARN << "Unable to load earth file." << std::endl;
        return -1;
    }
    osg::Group* root = new osg::Group();
    root->addChild(earthFile);

    osg::Matrix matrixGood1;
    osg::Vec3d geopoint1, geopoint2, geopoint3;
    GeoPoint point1(s_mapNode->getMapSRS(), 0, 0, 1000);
    point1.createLocalToWorld(matrixGood1);
    //matrixGood1.getLookAt(geopoint1, geopoint2, geopoint3);
    //osg::Vec3 _vector = geopoint1 - geopoint2;

    //添加一头牛，查看位置是否正确
    //osg::Node* cow = osgDB::readNodeFile("D:\\temp\\node\\cow.osg");
    //
    //osg::ref_ptr<osg::MatrixTransform> pat = new osg::MatrixTransform;
    //pat->addChild(cow);
    //pat->setMatrix(osg::Matrix::scale(200000, 200000, 200000));

    //osg::Matrix maaat2;
    //osg::ref_ptr<osg::MatrixTransform> pat2 = new osg::MatrixTransform;
    //pat2->setMatrix(osg::Matrix::rotate(matrixGood1.getRotate())*
    //    osg::Matrix::translate(matrixGood1.getTrans()));
    //pat2->addChild(pat);
    //root->addChild(pat2);

    viewer.setSceneData(root);

    //模型漫游器
    osgGA::NodeTrackerManipulator* nodeTrack = new osgGA::NodeTrackerManipulator();
    nodeTrack->setTrackNode(root);

    /*************************************动画漫游器**下*********************************/
    GeoPoint gPoint1(s_mapNode->getMap()->getSRS(), 32, 118, 400);
    osg::Matrix gMatrix1;
    gPoint1.createLocalToWorld(gMatrix1);//获取当前地球上的正确姿态
    //由于相机，自身向下看，所以在当前姿态基础上抬起60度，注意是前乘！
    gMatrix1.preMultRotate(osg::Quat(osg::DegreesToRadians(60.0), osg::X_AXIS));
    osg::Quat q1;    gMatrix1.get(q1);//获取当前矩阵姿态
    osg::Vec3d vPos1 = gMatrix1.getTrans();//获取当前矩阵位置

    GeoPoint gPoint2(s_mapNode->getMap()->getSRS(), 32.01, 118.01, 400);
    osg::Matrix gMatrix2;
    gPoint2.createLocalToWorld(gMatrix2);
    gMatrix2.preMultRotate(osg::Quat(osg::DegreesToRadians(60.0), osg::X_AXIS));
    osg::Quat q2;
    gMatrix2.get(q2);
    osg::Vec3d vPos2 = gMatrix2.getTrans();

    GeoPoint gPoint3(s_mapNode->getMap()->getSRS(), 32.02, 118.02, 400);
    osg::Matrix gMatrix3;
    gPoint3.createLocalToWorld(gMatrix3);
    osg::Quat q3;
    gMatrix3.get(q3);
    osg::Vec3d vPos3 = gMatrix3.getTrans();
    //获取相机之后再顺旋转,其实是错误的姿态
    osg::Quat qbuf(osg::DegreesToRadians(60.0), osg::X_AXIS);
    q3    *= qbuf;

    //使用动画漫游器
    osgGA::AnimationPathManipulator *animationPathMp = new osgGA::AnimationPathManipulator();
    //给动画漫游器添加关键帧
    osg::AnimationPath* _animationPath = new osg::AnimationPath;
    _animationPath->insert(0.0, osg::AnimationPath::ControlPoint(vPos1, q1));//姿态正确
    _animationPath->insert(3.0, osg::AnimationPath::ControlPoint(vPos2, q2));//姿态正确
    _animationPath->insert(6.0, osg::AnimationPath::ControlPoint(vPos3, q3));//姿态错误！
    _animationPath->setLoopMode(osg::AnimationPath::SWING);//设置路径是回摆的
    animationPathMp->setAnimationPath(_animationPath);
    /*************************************动画漫游器**上*********************************/

    //这里添加三个漫游器，使用一个控制漫游器选择，按键盘‘3’就切换到路径动画漫游器了
    osgGA::KeySwitchMatrixManipulator* keyPtr = new osgGA::KeySwitchMatrixManipulator();
    keyPtr->addMatrixManipulator('1', "earthMan", new EarthManipulator());
    keyPtr->addMatrixManipulator('2', "trakerMan", nodeTrack);
    keyPtr->addMatrixManipulator('3', "animationPathMan", animationPathMp);
    keyPtr->addMatrixManipulator('4', "earthWalkMan", new EarthWalkManipulator1());
    viewer.setCameraManipulator(keyPtr);
    //viewer.setUpViewOnSingleScreen(0);


    {
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
        traits->x = 40;
        traits->y = 40;
        traits->width = 600;
        traits->height = 480;
        traits->windowDecoration = true;
        traits->doubleBuffer = true;
        traits->sharedContext = 0;

        osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

        osg::ref_ptr<osg::Camera> camera = new osg::Camera;
        camera->setGraphicsContext(gc.get());
        camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
        GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
        camera->setDrawBuffer(buffer);
        camera->setReadBuffer(buffer);

        // add this slave camera to the viewer, with a shift left of the projection matrix
        viewer.addSlave(camera.get());
    }

    while(!viewer.done())
        viewer.frame();


    return 1;
}

osg::ref_ptr<osg::Vec3dArray> get4VertexArrInClockwise(osg::Vec3 leftTop,
                                                                       osg::Vec3 rightTop,
                                                                       osg::Vec3 rightBottom,
                                                                       osg::Vec3 leftBottom)
{
    osg::ref_ptr<osg::Vec3dArray> pVertexArr = new osg::Vec3dArray;

    pVertexArr->push_back(leftTop);//左上
    pVertexArr->push_back(rightTop);//右上
    pVertexArr->push_back(rightBottom);//右下
    pVertexArr->push_back(leftBottom);//左下

    return pVertexArr;
}

osg::ref_ptr<osg::Vec2dArray> Vec3SurfaceToVec2Surface(osg::ref_ptr<osg::Vec3dArray> vec3dArray)
{
    osg::Vec3 vec3_lefttop((*vec3dArray)[LEFT_TOP].x(),(*vec3dArray)[LEFT_TOP].y(),(*vec3dArray)[LEFT_TOP].z());
    osg::Vec3 vec3_righttop((*vec3dArray)[RIGHT_TOP].x(),(*vec3dArray)[RIGHT_TOP].y(),(*vec3dArray)[RIGHT_TOP].z());
    osg::Vec3 vec3_rightbottom((*vec3dArray)[RIGHT_BOTTOM].x(),(*vec3dArray)[RIGHT_BOTTOM].y(),(*vec3dArray)[RIGHT_BOTTOM].z());
    osg::Vec3 vec3_leftbottom((*vec3dArray)[LEFT_BOTTOM].x(),(*vec3dArray)[LEFT_BOTTOM].y(),(*vec3dArray)[LEFT_BOTTOM].z());

    float upside_line = sqrt(pow((vec3_lefttop.x() - vec3_righttop.x()),2) +
                             pow((vec3_lefttop.y() - vec3_righttop.y()),2) +
                             pow((vec3_lefttop.z() - vec3_righttop.z()),2));
    float downside_line = sqrt(pow((vec3_leftbottom.x() - vec3_rightbottom.x()),2) +
                               pow((vec3_leftbottom.y() - vec3_rightbottom.y()),2) +
                               pow((vec3_leftbottom.z() - vec3_rightbottom.z()),2));
    float leftside_line = sqrt(pow((vec3_lefttop.x() - vec3_leftbottom.x()),2) +
                               pow((vec3_lefttop.y() - vec3_leftbottom.y()),2) +
                               pow((vec3_lefttop.z() - vec3_leftbottom.z()),2));
    float rightside_line = sqrt(pow((vec3_righttop.x() - vec3_rightbottom.x()),2) +
                                pow((vec3_righttop.y() - vec3_rightbottom.y()),2) +
                                pow((vec3_righttop.z() - vec3_rightbottom.z()),2));

    std::cout << "upside : " << upside_line << std::endl;
    std::cout << "downside : " << downside_line << std::endl;
    std::cout << "leftside : " << leftside_line << std::endl;
    std::cout << "rightside : " << rightside_line << std::endl;

    //右上顶点与左下顶点的对角线长
    float leftbottom_diagonal_line = sqrt(pow((vec3_righttop.x() - vec3_leftbottom.x()),2) +
                                          pow((vec3_righttop.y() - vec3_leftbottom.y()),2) +
                                          pow((vec3_righttop.z() - vec3_leftbottom.z()),2));
    //左上顶点与右下顶点的对角线长
    float rightbottom_diagonal_line = sqrt(pow((vec3_lefttop.x() - vec3_rightbottom.x()),2) +
                                           pow((vec3_lefttop.y() - vec3_rightbottom.y()),2) +
                                           pow((vec3_lefttop.z() - vec3_rightbottom.z()),2));

    std::cout << "left_diag : " << leftbottom_diagonal_line << std::endl;
    std::cout << "right_diag : " << rightbottom_diagonal_line << std::endl;

    //cos(A) = (b^2 + c^2 - a^2)/2bc
    float lefttop_angle = acos((pow((upside_line), 2) +
                                pow((leftside_line), 2) -
                                pow((leftbottom_diagonal_line), 2)) /
                               (2 * upside_line * leftside_line));

    std::cout << "cos_lefttop : " << (pow((upside_line), 2) +
                                      pow((leftside_line), 2) -
                                      pow((leftbottom_diagonal_line), 2)) /
                                     (2 * upside_line * leftside_line) << std::endl;
    std::cout << "lefttop_angle : " << lefttop_angle << std::endl;
    ///三角形面积为s = sqrt(p(p-a)(p-b)(p-c))
    ///其中p为三角形的周长，p = (a+b+c)/2
    ///    a,b,c分别为三边长
    //获取左下顶点到上边的距离
    float circumference_lefttop = (leftside_line + upside_line + leftbottom_diagonal_line) / 2;
    float area_s_lefttop = sqrt(circumference_lefttop *
                        (circumference_lefttop - leftside_line) *
                        (circumference_lefttop - upside_line) *
                        (circumference_lefttop - leftbottom_diagonal_line));
    float leftbottom_height = 2 * area_s_lefttop / upside_line;

    std::cout << "left_height : " << leftbottom_height << std::endl;
    //获取右下顶点到上边的距离
    float circumference_righttop = (rightside_line + upside_line + rightbottom_diagonal_line) / 2;
    float area_s_righttop = sqrt(circumference_righttop *
                        (circumference_righttop - rightside_line) *
                        (circumference_righttop - upside_line) *
                        (circumference_righttop - rightbottom_diagonal_line));
    float rightbottom_height = 2 * area_s_righttop / upside_line;

    std::cout << "right_height : " << rightbottom_height << std::endl;

    osg::Vec2 vec2_lefttop;
    osg::Vec2 vec2_righttop;
    osg::Vec2 vec2_rightbottom;
    osg::Vec2 vec2_leftbottom;

    if (lefttop_angle > (PI / 2) && lefttop_angle < PI)
    {
        float lefttop_x = sqrt(pow((leftside_line), 2) -
                               pow((leftbottom_height), 2));
        float rightbottom_x = sqrt(pow((downside_line), 2) -
                                   pow((rightbottom_height - leftbottom_height), 2));

        std::cout << "lefttop_x : " << lefttop_x << std::endl;
        std::cout << "rightbottom_x : " << rightbottom_x << std::endl;

        //左下顶点在二维坐标系的y轴上
        vec2_leftbottom = osg::Vec2(0, leftbottom_height);
        vec2_lefttop = osg::Vec2(lefttop_x, 0);
        vec2_righttop = osg::Vec2(lefttop_x + upside_line, 0);
        vec2_rightbottom = osg::Vec2(rightbottom_x, rightbottom_height);

    } else if (lefttop_angle <= (PI / 2) && lefttop_angle > 0) {
        float leftbottom_x = sqrt(pow((leftside_line), 2) -
                                  pow((leftbottom_height), 2));
        float rightbottom_x = sqrt(pow((rightbottom_diagonal_line), 2) -
                                   pow((rightbottom_height), 2));

        std::cout << "leftbottom_x : " << leftbottom_x << std::endl;
        std::cout << "rightbottom_x : " << rightbottom_x << std::endl;

        //左上顶点在二维坐标系的y轴上，并且为坐标原点
        vec2_leftbottom = osg::Vec2(leftbottom_x, leftbottom_height);
        vec2_lefttop = osg::Vec2(0, 0);
        vec2_righttop = osg::Vec2(upside_line, 0);
        vec2_rightbottom = osg::Vec2(rightbottom_x, rightbottom_height);

    } else {
        std::cout <<"error"<< std::endl;
    }

    osg::ref_ptr<osg::Vec2dArray> pVec2dArray = new osg::Vec2dArray;

    //按照顺序，存入二维顶点数组
    pVec2dArray->push_back(vec2_lefttop);
    pVec2dArray->push_back(vec2_righttop);
    pVec2dArray->push_back(vec2_rightbottom);
    pVec2dArray->push_back(vec2_leftbottom);

    return pVec2dArray;
}

int main(int argc, char*argv[])
{

    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

    osg::ref_ptr<osg::Group> root = new osg::Group;
//#define WANGPENG

#if defined(WANGPENG)
    printf("defined WANGPENG\n");
#endif

#if 1
    char* file = "D:\\ProjectMange\\GeoVideo\\project\\osgStudy\\config\\myCfg.conf";

    GeoVideoConfig* config = new GeoVideoConfig();
//    config->insertModel("model");

    GeoConfigParser* parser = new GeoConfigParser(config->getDefaultXmlPath());
#endif
#if 0
#if 0
    osg::Vec2dArray* dstArr = new osg::Vec2dArray;
    dstArr->push_back(osg::Vec2(0,0));
    dstArr->push_back(osg::Vec2(350,0));
    dstArr->push_back(osg::Vec2(180,250));
    dstArr->push_back(osg::Vec2(100,250));

    Size rsSize(350,250);

    osg::Vec2dArray* srcArr = new osg::Vec2dArray;
    srcArr->push_back(osg::Vec2(0,0));
    srcArr->push_back(osg::Vec2(360,0));
    srcArr->push_back(osg::Vec2(360,360));
    srcArr->push_back(osg::Vec2(0,360));
#else
    osg::Vec2dArray* dstArr = new osg::Vec2dArray;
    dstArr->push_back(osg::Vec2(0,0));
    dstArr->push_back(osg::Vec2(1021.6,0));
    dstArr->push_back(osg::Vec2(766.20001,419.39993));
    dstArr->push_back(osg::Vec2(255.40012,419.3999));

    Size rsSize(1021.6,419.39993);

    osg::Vec2dArray* srcArr = new osg::Vec2dArray;
//    srcArr->push_back(osg::Vec2(0,214));
//    srcArr->push_back(osg::Vec2(1277,94));
//    srcArr->push_back(osg::Vec2(1277,702));
//    srcArr->push_back(osg::Vec2(0,702));

    srcArr->push_back(osg::Vec2(0,0));
    srcArr->push_back(osg::Vec2(360,0));
    srcArr->push_back(osg::Vec2(360,360));
    srcArr->push_back(osg::Vec2(0,360));
#endif

    osg::Vec2d p0;
    osg::Vec2d p1;
    osg::Vec2d p2;
    osg::Vec2d p3;


    vector<Point2f> corners(4);
    p3 = (*srcArr)[3];
    p2 = (*srcArr)[2];
    p1 = (*srcArr)[1];
    p0 = (*srcArr)[0];

    corners[0] = Point2f(p0.x(), p0.y());
    corners[1] = Point2f(p1.x(), p1.y());
    corners[2] = Point2f(p2.x(), p2.y());
    corners[3] = Point2f(p3.x(), p3.y());


    vector<Point2f> corners_trans(4);
    p3 = (*dstArr)[3];
    p2 = (*dstArr)[2];
    p1 = (*dstArr)[1];
    p0 = (*dstArr)[0];

    corners_trans[0] = Point2f(p0.x(), p0.y());
    corners_trans[1] = Point2f(p1.x(), p1.y());
    corners_trans[2] = Point2f(p2.x(), p2.y());
    corners_trans[3] = Point2f(p3.x(), p3.y());

    cv::Mat image = cv::imread("C:\\Users\\wangpeng\\Desktop\\pic\\1.jpg");
    cv::Mat trans = cv::getPerspectiveTransform(corners,corners_trans);

    std::cout << trans << std::endl;

    cv::Mat mat;
    cv::warpPerspective(image, mat, trans, rsSize, INTER_LINEAR);

//    cv::Mat mat = perspectiveTrans::perspectiveTrans4X4("C:\\Users\\wangpeng\\Desktop\\pic\\1.jpg", srcArr,dstArr);
    cv::imwrite("C:\\Users\\wangpeng\\Desktop\\pic\\1-out.jpg", mat);
//    waitKey(0);
#endif
#if 0
//    myManipulator();

    //创建一个节点，读取模型
    //osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("xjsn.OSGB");

    //root->addChild(node);

    //布告板显示
    //将节点添加至场景中
    //root->addChild(mybillboardTree::createBillboardTree(osgDB::readImageFile("Images/tree0.rgba")));

    //遍历获取世界坐标
    //osg::Matrixd* matrix = GetWorldCoordinateOfNodeVisitor::getWorldCoords(node);

    //包围盒渲染
    osg::ref_ptr<osg::Node> node1 = myCubeTexture::createBox4();
    //myTexture::runTexture(node);
    //root->addChild(node1);

    //root->addChild(myTextureCube::runTextureCube());

    root->addChild(node1);
    //渲染
    viewer->setSceneData(root.get());
    viewer->realize();
    viewer->run();
#endif
#if 0
    osg::ref_ptr<osg::Vec2dArray> pVertexArr = new osg::Vec2dArray;
    osg::ref_ptr<osg::Vec2dArray> pTransVertexArr = new osg::Vec2dArray;
//    osg::Vec2d px0(0, 0);
//    osg::Vec2d px1(1, 0);
//    osg::Vec2d px2(1, 1);
//    osg::Vec2d px3(0, 1);
    osg::Vec2d px0(0, 0);
    osg::Vec2d px3(0, 1);
    osg::Vec2d px2(1, 1);
    osg::Vec2d px1(1, 0);

    pVertexArr->push_back(px0);
    pVertexArr->push_back(px1);
    pVertexArr->push_back(px2);
    pVertexArr->push_back(px3);
//    pVertexArr->push_back(px0);
//    pVertexArr->push_back(px3);
//    pVertexArr->push_back(px2);
//    pVertexArr->push_back(px1);

    osg::Vec2d py0(0, 0);
    osg::Vec2d py1(4, 0.5);
    osg::Vec2d py2(2, 2);
    osg::Vec2d py3(1, 2);
    pTransVertexArr->push_back(py0);
    pTransVertexArr->push_back(py1);
    pTransVertexArr->push_back(py2);
    pTransVertexArr->push_back(py3);

    cv::Mat resultImg = perspectiveTrans::perspectiveTrans4X4("C:\\Users\\wangpeng\\Desktop\\pic\\1.jpg",
                                                               pVertexArr,
                                                               pTransVertexArr);

//    imshow("wangpeng", resultImg);
    imwrite("C:\\Users\\wangpeng\\Desktop\\pic\\abc.jpg", resultImg);
    waitKey(0);
#endif
#if 0
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(polygonGeometry::createPolygon());

    root->addChild(geode);
    //渲染
    viewer->setSceneData(root.get());
    viewer->realize();
    viewer->run();
#endif
#if 0
    textureUpdate myTextureUpdate;
    myTextureUpdate.doTextureUpdate();
#endif
#if 0
    MovieEventHandler::play(argc, argv);
#endif
#if 0
    osg::Vec3 leftTop(0, 0, 0);
    osg::Vec3 rightTop(100, 0, 0);
    osg::Vec3 rightBottom(150, 50, 0);
    osg::Vec3 leftBottom(50, 50, 0);

    osg::ref_ptr<osg::Vec3dArray>pVertexArray = get4VertexArrInClockwise(leftTop,
                                                                          rightTop,
                                                                          rightBottom,
                                                                          leftBottom);

    osg::ref_ptr<osg::Vec2dArray> pArray = Vec3SurfaceToVec2Surface(pVertexArray);
    std::cout << "lt : " << (*pArray)[0].x() << " " << (*pArray)[0].y() <<std::endl;
    std::cout << "rt : " << (*pArray)[1].x() << " " << (*pArray)[1].y() <<std::endl;
    std::cout << "rb : " << (*pArray)[2].x() << " " << (*pArray)[2].y() <<std::endl;
    std::cout << "lb : " << (*pArray)[3].x() << " " << (*pArray)[3].y() <<std::endl;
#endif

    return 0;
}
