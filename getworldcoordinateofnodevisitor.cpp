#include "getworldcoordinateofnodevisitor.h"
#include <osg/Transform>

/**
 * 类构造函数
 * 设置节点的遍历模式为NodeVisitor::TRAVERSE_PARENTS，向当前节点及父节点遍历
 *
 * @brief GetWorldCoordinateOfNodeVisitor::GetWorldCoordinateOfNodeVisitor
 */
GetWorldCoordinateOfNodeVisitor::GetWorldCoordinateOfNodeVisitor() : osg::NodeVisitor(NodeVisitor::TRAVERSE_PARENTS),done(false)
{
    wcMatrix = new osg::Matrix();
}

/**
 * 重新定义apply
 *
 * @brief GetWorldCoordinateOfNodeVisitor::apply
 * @param node
 */
void GetWorldCoordinateOfNodeVisitor::apply(osg::Node &node)
{
    //判断是否已经到达根节点
    if (!done)
    {
        //到达根节点，此时节点路径也已记录完整
        if (0 == node.getNumParents())
        {
            wcMatrix->set(osg::computeLocalToWorld(this->getNodePath()));
            done = true;
        }

        //继续遍历
        traverse(node);
    }

    return;
}

/**
 * 返回世界坐标矩阵
 *
 * @brief GetWorldCoordinateOfNodeVisitor::giveUpDaMat
 * @return
 */
osg::Matrixd* GetWorldCoordinateOfNodeVisitor::giveUpDaMat()
{
    return wcMatrix;
}

/**
 * 计算场景中某个节点的世界坐标，返回osg::Matrix格式的世界坐标
 * 创建用于更新世界坐标矩阵的访问器之后，即获取该矩阵
 *
 * @brief getWorldCoords
 * @param node
 * @return
 */
osg::Matrixd* GetWorldCoordinateOfNodeVisitor::getWorldCoords(osg::Node * node)
{
    //创建一个节点访问器GetWorldCoordinateOfNodeVisitor
    GetWorldCoordinateOfNodeVisitor* ncv = new GetWorldCoordinateOfNodeVisitor();

    if (node && ncv)
    {
        //启用节点访问器，开始遍历
        node->accept(*ncv);

        //遍历完成后，返回世界坐标矩阵
        return ncv->giveUpDaMat();
    }
    else
    {
        return NULL;
    }
}
