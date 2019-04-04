#include "VideoStream.h"

VideoStream::VideoStream(string pVideoPath)
{
    osgDB::Registry::instance()->addFileExtensionAlias("mp4", "ffmpeg");
    osgDB::Registry::instance()->addFileExtensionAlias("mov", "ffmpeg");

    m_pImage = osgDB::readImageFile(pVideoPath);
    m_pImageStream = dynamic_cast<osgFFmpeg::FFmpegImageStream*>(m_pImage);

    if (!m_pImage)
    {
        std::cout << "null" << std::endl;
    }else{
        std::cout << "not null" << std::endl;
    }

    //frame size , s is width and t is height
    m_videoSize = Size(m_pImage->s(), m_pImage->t());

}

/**
 * 添加变换纹理回调函数
 *
 * @brief VideoStream::addDimensionsChangedCallback
 * @param cb
 */
void VideoStream::addDimensionsChangedCallback(Image::DimensionsChangedCallback *cb)
{
    m_pImageStream->addDimensionsChangedCallback(cb);
}

void VideoStream::setTransformcb(osgFFmpeg::FFmpegImageStream::transformcb_p cb)
{
    m_pImageStream->setTransCallback(cb);
}

/**
 * start to play video
 *
 * @author wangpeng
 * @date 20190131
 * @brief VideoStream::VideoPlay
 */
void VideoStream::VideoPlay()
{
    if (m_pImageStream)
    {
        m_pImageStream->play();
    }
}

/**
 * pause video
 *
 * @author wangpeng
 * @date 20190131
 * @brief VideoStream::VideoPause
 */
void VideoStream::VideoPause()
{
    if (m_pImageStream)
    {
        m_pImageStream->pause();
    }
}

/**
 * get image from VideoStream
 *
 * @author wangpeng
 * @date 20190131
 * @brief VideoStream::GetImage
 * @return
 */
osg::Image* VideoStream::GetImage()
{
    return m_pImage;
}
