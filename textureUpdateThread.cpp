#include "textureUpdateThread.h"

TextureUpdateThread::TextureUpdateThread(osg::ref_ptr<osg::Node> pNode)
{
    m_pNode = pNode;
}
