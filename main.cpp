#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>
#include "getworldcoordinateofnodevisitor.h"

int main(void)
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

    osg::ref_ptr<osg::Group> root = new osg::Group;

    //创建一个节点，读取模型
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

    //将节点添加至场景中
    root->addChild(node);

    //遍历获取世界坐标
    osg::Matrixd* matrix = GetWorldCoordinateOfNodeVisitor::getWorldCoords(node);

    //渲染
    viewer->setSceneData(root.get());
    viewer->realize();
    viewer->run();

    return 0;
}
