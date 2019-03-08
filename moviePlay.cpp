﻿#include "moviePlay.h"
#include <Windows.h>

void MovieEventHandler::set(osg::Node* node)
{
    _imageStreamList.clear();
    if (node)
    {
        FindImageStreamsVisitor fisv(_imageStreamList);
        node->accept(fisv);
        std::cout<<"accept FindImageStreamsVisitor"<<std::endl;
    }
}


bool MovieEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor* nv)
{
    switch(ea.getEventType())
    {
    case(osgGA::GUIEventAdapter::MOVE):
    case(osgGA::GUIEventAdapter::PUSH):
    case(osgGA::GUIEventAdapter::RELEASE):
    {
        if (_trackMouse)
        {
            osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
            osgUtil::LineSegmentIntersector::Intersections intersections;
            bool foundIntersection = view==0 ? false :
                                               (nv==0 ? view->computeIntersections(ea.getX(), ea.getY(), intersections) :
                                                        view->computeIntersections(ea.getX(), ea.getY(), nv->getNodePath(), intersections));

            if (foundIntersection)
            {

                // use the nearest intersection
                const osgUtil::LineSegmentIntersector::Intersection& intersection = *(intersections.begin());
                osg::Drawable* drawable = intersection.drawable.get();
                osg::Geometry* geometry = drawable ? drawable->asGeometry() : 0;
                osg::Vec3Array* vertices = geometry ? dynamic_cast<osg::Vec3Array*>(geometry->getVertexArray()) : 0;
                if (vertices)
                {
                    // get the vertex indices.
                    const osgUtil::LineSegmentIntersector::Intersection::IndexList& indices = intersection.indexList;
                    const osgUtil::LineSegmentIntersector::Intersection::RatioList& ratios = intersection.ratioList;

                    if (indices.size()==3 && ratios.size()==3)
                    {
                        unsigned int i1 = indices[0];
                        unsigned int i2 = indices[1];
                        unsigned int i3 = indices[2];

                        float r1 = ratios[0];
                        float r2 = ratios[1];
                        float r3 = ratios[2];

                        osg::Array* texcoords = (geometry->getNumTexCoordArrays()>0) ? geometry->getTexCoordArray(0) : 0;
                        osg::Vec2Array* texcoords_Vec2Array = dynamic_cast<osg::Vec2Array*>(texcoords);
                        if (texcoords_Vec2Array)
                        {
                            // we have tex coord array so now we can compute the final tex coord at the point of intersection.
                            osg::Vec2 tc1 = (*texcoords_Vec2Array)[i1];
                            osg::Vec2 tc2 = (*texcoords_Vec2Array)[i2];
                            osg::Vec2 tc3 = (*texcoords_Vec2Array)[i3];
                            osg::Vec2 tc = tc1*r1 + tc2*r2 + tc3*r3;

                            osg::notify(osg::NOTICE)<<"We hit tex coords "<<tc<<std::endl;

                        }
                    }
                    else
                    {
                        osg::notify(osg::NOTICE)<<"Intersection has insufficient indices to work with";
                    }

                }
            }
            else
            {
                osg::notify(osg::NOTICE)<<"No intersection"<<std::endl;
            }
        }
        break;
    }
    case(osgGA::GUIEventAdapter::KEYDOWN):
    {
        std::cout <<"key down "<<ea.getKey()<<std::endl;
        if (ea.getKey()=='p')
        {
            std::cout<<"key down ppppppp"<<std::endl;
            for(ImageStreamList::iterator itr=_imageStreamList.begin();
                itr!=_imageStreamList.end();
                ++itr)
            {
                _playToggle = !_playToggle;
                if ( _playToggle )
                {
                    // playing, so pause
                    std::cout<<"Play"<<std::endl;
                    (*itr)->play();
                }
                else
                {
                    // playing, so pause
                    std::cout<<"Pause"<<std::endl;
                    (*itr)->pause();
                }
            }
            return true;
        }
        else if (ea.getKey()=='r')
        {
            for(ImageStreamList::iterator itr=_imageStreamList.begin();
                itr!=_imageStreamList.end();
                ++itr)
            {
                std::cout<<"Restart"<<std::endl;
                (*itr)->rewind();
                (*itr)->play();
            }
            return true;
        }
        else if (ea.getKey()=='L')
        {
            for(ImageStreamList::iterator itr=_imageStreamList.begin();
                itr!=_imageStreamList.end();
                ++itr)
            {
                if ( (*itr)->getLoopingMode() == osg::ImageStream::LOOPING)
                {
                    std::cout<<"Toggle Looping Off"<<std::endl;
                    (*itr)->setLoopingMode( osg::ImageStream::NO_LOOPING );
                }
                else
                {
                    std::cout<<"Toggle Looping On"<<std::endl;
                    (*itr)->setLoopingMode( osg::ImageStream::LOOPING );
                }
            }
            return true;
        }
        return false;
    }

    default:
        return false;
    }
    return false;
}

void MovieEventHandler::getUsage(osg::ApplicationUsage& usage) const
{
    usage.addKeyboardMouseBinding("p","Play/Pause movie");
    usage.addKeyboardMouseBinding("r","Restart movie");
    usage.addKeyboardMouseBinding("l","Toggle looping of movie");
}

osg::Geometry* myCreateTexturedQuadGeometry(const osg::Vec3& pos,float width,float height, osg::Image* image, bool useTextureRectangle, bool xyPlane, bool option_flip)
{
    bool flip = image->getOrigin()==osg::Image::TOP_LEFT;
    if (option_flip) flip = !flip;

    if (useTextureRectangle)
    {
        osg::Geometry* pictureQuad = osg::createTexturedQuadGeometry(pos,
                                                                     osg::Vec3(width,0.0f,0.0f),
                                                                     xyPlane ? osg::Vec3(0.0f,height,0.0f) : osg::Vec3(0.0f,0.0f,height),
                                                                     0.0f, flip ? image->t() : 0.0, image->s(), flip ? 0.0 : image->t());

        osg::TextureRectangle* texture = new osg::TextureRectangle(image);
        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);


        pictureQuad->getOrCreateStateSet()->setTextureAttributeAndModes(0,
                                                                        texture,
                                                                        osg::StateAttribute::ON);

        osg::StateAttribute* attr = pictureQuad->getOrCreateStateSet()->getTextureAttribute(0,osg::StateAttribute::TEXTURE);
        if (attr)
        {
            std::cout<<"aaa not NULL"<<std::endl;
        } else {
            std::cout<<"aaa is NULL"<<std::endl;
        }
        return pictureQuad;
    }
    else
    {
        osg::Geometry* pictureQuad = osg::createTexturedQuadGeometry(pos,
                                                                     osg::Vec3(width,0.0f,0.0f),
                                                                     xyPlane ? osg::Vec3(0.0f,height,0.0f) : osg::Vec3(0.0f,0.0f,height),
                                                                     0.0f, flip ? 1.0f : 0.0f , 1.0f, flip ? 0.0f : 1.0f);

        osg::Texture2D* texture = new osg::Texture2D(image);
        texture->setResizeNonPowerOfTwoHint(false);
        texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
        texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
        texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);


        pictureQuad->getOrCreateStateSet()->setTextureAttributeAndModes(0,
                                                                        texture,
                                                                        osg::StateAttribute::ON);
        osg::StateAttribute* attr = pictureQuad->getOrCreateStateSet()->getTextureAttribute(0,osg::StateAttribute::TEXTURE);
        if (attr)
        {
            std::cout<<"bbb not NULL"<<std::endl;
        } else {
            std::cout<<"bbb is NULL"<<std::endl;
        }

        return pictureQuad;
    }
}

int MovieEventHandler::play(int argc ,char * argv[])
{
    bool useTextureRectangle = false;

    osgViewer::Viewer viewer;

    bool fullscreen = false;
    bool flip = false;

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;

    osg::StateSet* stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    osg::Vec3 pos(0.0f,0.0f,0.0f);
    osg::Vec3 topleft = pos;
    osg::Vec3 bottomright = pos;

    bool xyPlane = fullscreen;

#if 0
    osgDB::Registry::instance()->addFileExtensionAlias("avi", "ffmpeg");
    osg::Image* image = osgDB::readImageFile("out.avi");
#else
    osgDB::Registry::instance()->addFileExtensionAlias("mp4", "ffmpeg");
    osgDB::Registry::instance()->addFileExtensionAlias("avi", "ffmpeg");
    osg::Image* image = osgDB::readImageFile("01.mp4");
//    osg::Image* image = osgDB::readImageFile("out.avi");
#endif

    osg::ImageStream* imagestream = dynamic_cast<osg::ImageStream*>(image);
    if (imagestream) imagestream->play();

    std::cout << "sleep 5 start" <<std::endl;
//    Sleep(5000);
    if (image)
    {
        osg::notify(osg::NOTICE)<<"image->s()"<<image->s()<<" image-t()="<<image->t()<<std::endl;

        geode->addDrawable(myCreateTexturedQuadGeometry(pos,image->s(),image->t(),image, useTextureRectangle, xyPlane, flip));

//        bottomright = pos + osg::Vec3(static_cast<float>(image->s()),static_cast<float>(image->t()),0.0f);

//        if (xyPlane) pos.y() += image->t()*1.05f;
//        else pos.z() += image->t()*1.05f;
    }
    else
    {
        std::cout<<"image is null "<<std::endl;
    }

    // set the scene to render
    viewer.setSceneData(geode.get());

    if (viewer.getSceneData()==0)
    {
        std::cout<<"getSceneData is null"<<std::endl;
        return 1;
    }
#if 0
    // pass the model to the MovieEventHandler so it can pick out ImageStream's to manipulate.
    MovieEventHandler* meh = new MovieEventHandler();
    meh->setMouseTracking( mouseTracking );
    meh->set( viewer.getSceneData() );
    viewer.addEventHandler( meh );


    viewer.addEventHandler( new osgViewer::StatsHandler );
    viewer.addEventHandler( new osgGA::StateSetManipulator( viewer.getCamera()->getOrCreateStateSet() ) );
    viewer.addEventHandler( new osgViewer::WindowSizeHandler );
#endif

    // add the record camera path handler
    //viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);

    if (fullscreen)
    {
        std::cout <<"Use frame" <<std::endl;
        viewer.realize();

        viewer.getCamera()->setViewMatrix(osg::Matrix::identity());
        viewer.getCamera()->setProjectionMatrixAsOrtho2D(topleft.x(),bottomright.x(),topleft.y(),bottomright.y());

        while(!viewer.done())
        {
            viewer.frame();
        }

        return 0;
    }
    else
    {
        std::cout <<"Use run" <<std::endl;
        // create the windows and run the threads.
        return viewer.run();
    }
}
