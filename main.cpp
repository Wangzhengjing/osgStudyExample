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

int main(void)
{
    //examplesTexture::test3();
#if 1
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

    osg::ref_ptr<osg::Group> root = new osg::Group;

    //创建一个节点，读取模型
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("xjsn.OSGB");

    //root->addChild(node);

    //布告板显示
    //将节点添加至场景中
    //root->addChild(mybillboardTree::createBillboardTree(osgDB::readImageFile("Images/tree0.rgba")));

    //遍历获取世界坐标
    //osg::Matrixd* matrix = GetWorldCoordinateOfNodeVisitor::getWorldCoords(node);

    //包围盒渲染
    //osg::ref_ptr<osg::Node> node1 = myCube::createBox2();
    //myTexture::runTexture(node);
    //root->addChild(node1);

    root->addChild(myTextureCube::runTextureCube());


    //渲染
    viewer->setSceneData(root.get());
    viewer->realize();
    viewer->run();
#endif
    return 0;
}
