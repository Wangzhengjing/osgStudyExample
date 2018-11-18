#ifndef GETWORLDCOORDINATEOFNODEVISITOR_H
#define GETWORLDCOORDINATEOFNODEVISITOR_H

#include <osg/NodeVisitor>

/**
 * 访问器用于返回某个节点的世界坐标
 * 从其实节点开始，向根节点遍历，并将遍历的节点记录到nodePath中
 * 第一次到达根节点后，记录起始点到根节点的节点路径
 * 获取所有世界坐标矩阵后，即获得节点的世界坐标
 *
 * @brief The GetWorldCoordinateOfNodeVisitor class
 */
class GetWorldCoordinateOfNodeVisitor : public osg::NodeVisitor
{
public:
    GetWorldCoordinateOfNodeVisitor();

    virtual void apply(osg::Node &node);

    osg::Matrixd* giveUpDaMat();

    static osg::Matrixd* getWorldCoords(osg::Node * node);

private:
    bool done;

    //保存节点的世界坐标矩阵
    osg::Matrix* wcMatrix;
};

#endif // GETWORLDCOORDINATEOFNODEVISITOR_H
