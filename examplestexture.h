//#ifndef EXAMPLESTEXTURE_H
//#define EXAMPLESTEXTURE_H

//#include <osgViewer/Viewer>
//#include <osgDB/ReadFile>
//#include <osg/Image>
//#include <osg/Texture>
//#include <osg/Texture2D>
//#include <osg/TexGen>
//#include <osg/TexEnv>
//#include <osgUtil/Optimizer>
//#include <osgViewer/ViewerEventHandlers>
//#include <osg/Drawable>
//#include <osg/TextureRectangle>
////#include <afxdialogex.h>
//#include <osg/ImageStream>
//#include <osgGA/StateSetManipulator>
//#include <osg/Notify>
//#include <osg/Vec2>
//#include <osg/PositionAttitudeTransform>
////#include <osgDB/
//#include <osg/LineSegment>
//#include <osgUtil/IntersectVisitor>
//#include <osgGA/DriveManipulator>

//#define IMAGERY_URL      "http://readymap.org/readymap/tiles/1.0.0/22/"
//#define ELEVATION_URL    "http://readymap.org/readymap/tiles/1.0.0/9/"
//#define BUILDINGS_URL    "d:\\shp\\data\\boston_buildings_utm19.shp"
//#define RESOURCE_LIB_URL "d:\\shp\\data\\resources/textures_us\\catalog.xml"
//#define STREETS_URL      "d:\\shp\\data\\boston-scl-utm19n-meters.shp"
//#define PARKS_URL        "d:\\shp\\data\\boston-parks.shp"
//#define TREE_MODEL_URL   "d:\\shp\\data\\loopix/tree4.osgb"
//#define DCBUILDING_URL   "d:\\shp\\data\\dcbuildings.shp"

//class examplesTexture
//{
//public:
//    examplesTexture();

//    static osg::Image* createImage( int width, int height,osg::Vec3 color );
//    static osg::Geometry* myCreateTexturedQuadGeometry(const osg::Vec3& pos,float width,float height, osg::Image* image, bool useTextureRectangle, bool xyPlane, bool option_flip);
//    static void DxfandMovie(int argc, char** argv);
//    static osg::Camera* createHUDBg(std::string imagePath);

//    static void test1();
//    static void test2();
//    static void test3();
//    static void test5();
//    static void test7();
//};

//class MovieEventHandler : public osgGA::GUIEventHandler
//{
//public:

//    MovieEventHandler():_trackMouse(false) {}

//    void setMouseTracking(bool track) { _trackMouse = track; }
//    bool getMouseTracking() const { return _trackMouse; }

//    void set(osg::Node* node);

//    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor* nv);

//    virtual void getUsage(osg::ApplicationUsage& usage) const;

//    typedef std::vector< osg::observer_ptr<osg::ImageStream> > ImageStreamList;

//protected:

//    virtual ~MovieEventHandler() {}

//    class FindImageStreamsVisitor : public osg::NodeVisitor
//    {
//    public:
//        FindImageStreamsVisitor(ImageStreamList& imageStreamList):
//          _imageStreamList(imageStreamList) {}

//          virtual void apply(osg::Geode& geode)
//          {
//              apply(geode.getStateSet());

//              for(unsigned int i=0;i<geode.getNumDrawables();++i)
//              {
//                  apply(geode.getDrawable(i)->getStateSet());
//              }

//              traverse(geode);
//          }

//          virtual void apply(osg::Node& node)
//          {
//              apply(node.getStateSet());
//              traverse(node);
//          }

//          inline void apply(osg::StateSet* stateset)
//          {
//              if (!stateset) return;

//              osg::StateAttribute* attr = stateset->getTextureAttribute(0,osg::StateAttribute::TEXTURE);
//              if (attr)
//              {
//                  osg::Texture2D* texture2D = dynamic_cast<osg::Texture2D*>(attr);
//                  if (texture2D) apply(dynamic_cast<osg::ImageStream*>(texture2D->getImage()));

//                  osg::TextureRectangle* textureRec = dynamic_cast<osg::TextureRectangle*>(attr);
//                  if (textureRec) apply(dynamic_cast<osg::ImageStream*>(textureRec->getImage()));
//              }
//          }

//          inline void apply(osg::ImageStream* imagestream)
//          {
//              if (imagestream)
//              {
//                  _imageStreamList.push_back(imagestream);
//              }
//          }

//          ImageStreamList& _imageStreamList;

//    protected:

//        FindImageStreamsVisitor& operator = (const FindImageStreamsVisitor&) { return *this; }

//    };


//    bool            _trackMouse;
//    ImageStreamList _imageStreamList;
//    unsigned int    _seekIncr;

//};
//#endif // EXAMPLESTEXTURE_H
