#ifndef MOVIEPLAY_H
#define MOVIEPLAY_H


#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgDB/ReadFile>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/TextureRectangle>
#include <osg/TextureCubeMap>
#include <osg/TexMat>
#include <osg/CullFace>
#include <osg/ImageStream>
#include <osg/io_utils>

#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/EventVisitor>

#include <iostream>

class MovieEventHandler : public osgGA::GUIEventHandler
{
public:

    MovieEventHandler():_playToggle(true),_trackMouse(false) {}

    void setMouseTracking(bool track) { _trackMouse = track; }
    bool getMouseTracking() const { return _trackMouse; }

    void set(osg::Node* node);

    virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor* nv);

    virtual void getUsage(osg::ApplicationUsage& usage) const;

    typedef std::vector< osg::observer_ptr<osg::ImageStream> > ImageStreamList;
    static int play(int argc ,char * argv[]);

protected:

    virtual ~MovieEventHandler() {}

    class FindImageStreamsVisitor : public osg::NodeVisitor
    {
    public:
        FindImageStreamsVisitor(ImageStreamList& imageStreamList):
            _imageStreamList(imageStreamList) {}

        virtual void apply(osg::Geode& geode)
        {
            std::cout<<"1"<<std::endl;
            apply(geode.getStateSet());

            for(unsigned int i=0;i<geode.getNumDrawables();++i)
            {
                apply(geode.getDrawable(i)->getStateSet());
            }

            traverse(geode);
        }

        virtual void apply(osg::Node& node)
        {
            std::cout<<"2"<<std::endl;
            apply(node.getStateSet());
            traverse(node);
        }

        inline void apply(osg::StateSet* stateset)
        {
            std::cout<<"3"<<std::endl;
            if (!stateset) return;

            osg::StateAttribute* attr = stateset->getTextureAttribute(0,osg::StateAttribute::TEXTURE);
            if (attr)
            {
                std::cout<<"get texture from attr"<<std::endl;
                osg::Texture2D* texture2D = dynamic_cast<osg::Texture2D*>(attr);
                if (texture2D) apply(dynamic_cast<osg::ImageStream*>(texture2D->getImage()));

                osg::TextureRectangle* textureRec = dynamic_cast<osg::TextureRectangle*>(attr);
                if (textureRec) apply(dynamic_cast<osg::ImageStream*>(textureRec->getImage()));
            } else {
                std::cout<<"attr is null"<<std::endl;
            }

//            std::cout << "textureRec"<<std::endl;

//              osg::TextureRectangle* textureRec = dynamic_cast<osg::TextureRectangle*>(stateset->getTextureAttribute(0,osg::StateAttribute::TEXTURE)->asTexture());
//              if (textureRec)
//              {
//                  std::cout << "textureRec is not null"<<std::endl;

//                  apply(dynamic_cast<osg::ImageStream*>(textureRec->getImage()));
//              } else {
//                  std::cout << "textureRec is null"<<std::endl;
//              }

        }

        inline void apply(osg::ImageStream* imagestream)
        {
            std::cout<<"4"<<std::endl;
            if (imagestream)
            {
                std::cout << "imagestream push back"<<std::endl;
                _imageStreamList.push_back(imagestream);
            }
        }

        ImageStreamList& _imageStreamList;

    protected:

        FindImageStreamsVisitor& operator = (const FindImageStreamsVisitor&) { return *this; }

    };


    bool            _playToggle;
    bool            _trackMouse;
    ImageStreamList _imageStreamList;

};

#endif // MOVIEPLAY_H
