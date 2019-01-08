#ifndef PERSPECTIVETRANS_H
#define PERSPECTIVETRANS_H

#include <stdio.h>
#include <opencv/highgui.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <iostream>
#include <osg/Array>

using namespace std;
using namespace cv;

class perspectiveTrans
{
public:
    perspectiveTrans();

    /**
     * @brief perspectiveTrans::perspectiveTrans4X4
     * @param imgPath           本地图片数据路径
     * @param pVertexArr        源纹理坐标,坐标范围为0-1
     * @param pTransVertexArr   变换后目标图形顶点坐标,基于纹理坐标为长度单元，代表倍数系数
     * @return
     */
    static cv::Mat perspectiveTrans4X4(String imgPath,
                                        osg::ref_ptr<osg::Vec2dArray> pVertexArr,
                                        osg::ref_ptr<osg::Vec2dArray> pTransVertexArr);
};

#endif // PERSPECTIVETRANS_H
