#include "perspectiveTrans.h"


perspectiveTrans::perspectiveTrans()
{
}

/**
 * @brief bigSort_x 找出x的最大值
 * @param array
 * @param l 最小索引
 * @param r 最大索引
 */
int bigSort_x(osg::Vec2dArray array[], int l, int r)
{
    int x = 0;

    if (l< r)
    {
        x = (*array)[l].x();
        for (int i = l; i < r; i++)
        {
            if (x < (*array)[i].x())
            {
                x = (*array)[i].x();
            }
        }
    }

    return x;
}

/**
 * @brief bigSort_y 找出y的最大值
 * @param array
 * @param l 最小索引
 * @param r 最大索引
 */
int bigSort_y(osg::Vec2dArray array[], int l, int r)
{
    int y = 0;

    if (l< r)
    {
        y = (*array)[l].y();
        for (int i = l; i < r; i++)
        {
            if (y < (*array)[i].y())
            {
                y = (*array)[i].y();
            }
        }
    }

    return y;
}

//Mat perspectiveTrans::getPerspectiveTrans()
//{
//    //计算转换矩阵
//    Mat transform = getPerspectiveTransform(corners,corners_trans);
//}

/**
 * @brief perspectiveTrans::perspectiveTrans4X4
 * @param imgPath           本地图片数据路径
 * @param pVertexArr        源纹理坐标,坐标范围为0-1
 * @param pTransVertexArr   变换后目标图形顶点坐标,基于纹理坐标为长度单元，代表倍数系数
 * @return
 */
Mat perspectiveTrans::perspectiveTrans4X4(String imgPath,
                                           osg::ref_ptr<osg::Vec2dArray> pVertexArr,
                                           osg::ref_ptr<osg::Vec2dArray> pTransVertexArr)
{
    Mat img=imread(imgPath);

    //获取图片大小
    int img_height = img.rows;
    int img_width = img.cols;

    //从传入数组中获取顶点坐标信息
    osg::Vec2d p0;
    osg::Vec2d p1;
    osg::Vec2d p2;
    osg::Vec2d p3;

    //获取四个角的纹理坐标
    vector<Point2f> corners(4);
    p3 = (*pVertexArr)[3];
    p2 = (*pVertexArr)[2];
    p1 = (*pVertexArr)[1];
    p0 = (*pVertexArr)[0];

    //根据比例，获取纹理实际坐标
    corners[0] = Point2f(p0.x() * img_width, p0.y() * img_height);
    corners[1] = Point2f(p1.x() * img_width, p1.y() * img_height);
    corners[2] = Point2f(p2.x() * img_width, p2.y() * img_height);
    corners[3] = Point2f(p3.x() * img_width, p3.y() * img_height);
    std::cout<<"src:"<<std::endl;
    std::cout<<p0.x() * img_width<<","<<p0.y() * img_height<<";"<<std::endl;
    std::cout<<p1.x() * img_width<<","<<p1.y() * img_height<<";"<<std::endl;
    std::cout<<p2.x() * img_width<<","<<p2.y() * img_height<<";"<<std::endl;
    std::cout<<p3.x() * img_width<<","<<p3.y() * img_height<<";"<<std::endl;

    //设置转换后四个角的纹理坐标
    vector<Point2f> corners_trans(4);
    p3 = (*pTransVertexArr)[3];
    p2 = (*pTransVertexArr)[2];
    p1 = (*pTransVertexArr)[1];
    p0 = (*pTransVertexArr)[0];

    //目标尺寸变大
    corners_trans[0] = Point2f(p0.x() * img_width, p0.y() * img_height);
    corners_trans[1] = Point2f(p1.x() * img_width, p1.y() * img_height);
    corners_trans[2] = Point2f(p2.x() * img_width, p2.y() * img_height);
    corners_trans[3] = Point2f(p3.x() * img_width, p3.y() * img_height);
    std::cout<<"dst:"<<std::endl;
    std::cout<<p0.x() * img_width<<","<<p0.y() * img_height<<";"<<std::endl;
    std::cout<<p1.x() * img_width<<","<<p1.y() * img_height<<";"<<std::endl;
    std::cout<<p2.x() * img_width<<","<<p2.y() * img_height<<";"<<std::endl;
    std::cout<<p3.x() * img_width<<","<<p3.y() * img_height<<";"<<std::endl;

    //计算转换矩阵
    Mat transform = getPerspectiveTransform(corners,corners_trans);

    transform = (3.999999999999999, 6.956521739130444, -6.821210263296962e-013,
    5.827044576023344e-016, -8.000000000000002, 2944,
    -8.131516293641283e-020, 0.008152173913043476, 1);
    //设置目标图像大小
    int h_rotate = bigSort_y(pTransVertexArr, 0, 4) * img_height;
    int w_rotate = bigSort_x(pTransVertexArr, 0, 4) * img_width;
    h_rotate = 2560;
    w_rotate = 2944;
    Size resultImageSize(w_rotate, h_rotate);

    std::cout <<"dst : "<<w_rotate<< " * " <<h_rotate<<std::endl;
    //进行透视变换,得到目标图片
    Mat resultImage;
    warpPerspective(img,resultImage,transform, resultImageSize,INTER_LINEAR);

    return resultImage;
}
