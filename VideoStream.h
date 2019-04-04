#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <osgDB/ReadFile>
#include <osgDB/Registry>
#include <osg/ImageStream>
#include <osg/Image>
#include "ffmpeg/FFmpegImageStream.hpp"

using namespace cv;
using namespace std;
using namespace osg;

class VideoStream
{
public:
    VideoStream(string pVideoPath);

    void VideoPlay();
    void VideoPause();
    osg::Image* GetImage();
    void addDimensionsChangedCallback(osg::Image::DimensionsChangedCallback* cb);
    void setTransformcb(osgFFmpeg::FFmpegImageStream::transformcb_p cb);

private:
    //!
    //! \brief m_videoSize 视频帧大小
    //!
    Size m_videoSize;
    //!
    //! \brief m_pImage image from ffmpeg
    //!
    osg::Image* m_pImage;
    //!
    //! \brief m_pImageStream   imageStream from ffmpeg
    //!
    osgFFmpeg::FFmpegImageStream* m_pImageStream;
};

#endif // VIDEOSTREAM_H
