#include "examplestexture.h"

examplesTexture::examplesTexture()
{
}

void MovieEventHandler::set(osg::Node* node)
{
    _imageStreamList.clear();
    if (node)
    {
        FindImageStreamsVisitor fisv(_imageStreamList);
        node->accept(fisv);
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
                    (nv==0 ? view->computeIntersections(ea, intersections) :
                    view->computeIntersections(ea, nv->getNodePath(), intersections));

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

                                //osg::notify(osg::NOTICE)<<"We hit tex coords "<<tc<<std::endl;

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
            if (ea.getKey()=='p')
            {
                for(ImageStreamList::iterator itr=_imageStreamList.begin();
                    itr!=_imageStreamList.end();
                    ++itr)
                {
                    osg::ImageStream::StreamStatus playToggle = (*itr)->getStatus();
                    if (playToggle != osg::ImageStream::PLAYING)
                    {
                        std::cout<< (*itr).get() << " Play"<<std::endl;
                        (*itr)->play();
                    }
                    else
                    {
                        // playing, so pause
                        std::cout<< (*itr).get() << " Pause"<<std::endl;
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
                    std::cout<< (*itr).get() << " Restart"<<std::endl;
                    (*itr)->rewind();
                    (*itr)->play();
                }
                return true;
            }
            else if (ea.getKey()=='>')
            {
                for(ImageStreamList::iterator itr=_imageStreamList.begin();
                    itr!=_imageStreamList.end();
                    ++itr)
                {
                    std::cout<<"Seeking"<<std::endl;
                    if(_seekIncr > 3) _seekIncr = 0;
                    double length = (*itr)->getLength();
                    double t_pos = (length/4.0f)*_seekIncr;
                    //(*itr)->rewind();
                    (*itr)->seek(t_pos);
                    (*itr)->play();
                    _seekIncr++;
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
                        std::cout<< (*itr).get() << " Toggle Looping Off"<<std::endl;
                        (*itr)->setLoopingMode( osg::ImageStream::NO_LOOPING );
                    }
                    else
                    {
                        std::cout<< (*itr).get() << " Toggle Looping On"<<std::endl;
                        (*itr)->setLoopingMode( osg::ImageStream::LOOPING );
                    }
                }
                return true;
            }
            else if (ea.getKey()=='+')
            {
                for(ImageStreamList::iterator itr=_imageStreamList.begin();
                    itr!=_imageStreamList.end();
                    ++itr)
                {
                    double tm = (*itr)->getTimeMultiplier();
                    tm += 0.1;
                    (*itr)->setTimeMultiplier(tm);
                    std::cout << (*itr).get() << " Increase speed rate "<< (*itr)->getTimeMultiplier() << std::endl;
                }
                return true;
            }
            else if (ea.getKey()=='-')
            {
                for(ImageStreamList::iterator itr=_imageStreamList.begin();
                    itr!=_imageStreamList.end();
                    ++itr)
                {
                    double tm = (*itr)->getTimeMultiplier();
                    tm -= 0.1;
                    (*itr)->setTimeMultiplier(tm);
                    std::cout << (*itr).get() << " Decrease speed rate "<< (*itr)->getTimeMultiplier() << std::endl;
                }
                return true;
            }
            else if (ea.getKey()=='o')
            {
                for(ImageStreamList::iterator itr=_imageStreamList.begin();
                    itr!=_imageStreamList.end();
                    ++itr)
                {
                    std::cout<< (*itr).get() << " Frame rate  "<< (*itr)->getFrameRate() <<std::endl;
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
    usage.addKeyboardMouseBinding("+","Increase speed of movie");
    usage.addKeyboardMouseBinding("-","Decrease speed of movie");
    usage.addKeyboardMouseBinding("o","Display frame rate of movie");
    usage.addKeyboardMouseBinding(">","Advance the movie using seek");
}

osg::Image* examplesTexture::createImage( int width, int height,osg::Vec3 color )
{
    osg::ref_ptr<osg::Image> image = new osg::Image;
    image->allocateImage( width, height, 1, GL_RGB, GL_UNSIGNED_BYTE );
    unsigned char* data = image->data();
    for ( int y=0; y<height; ++y )
    {
        for ( int x=0; x<width; ++x )
        {
            *(data++) = color.x();
            *(data++) = color.y();
            *(data++) = color.z();
        }
    }
    return image.release();
}

void examplesTexture::test1 ()
{
    // TODO: 在此添加控件通知处理程序代码
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group> root = new osg::Group();
    //创建节点,读取SHP文件
    osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile(PARKS_URL);
    osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile(STREETS_URL);
    osg::ref_ptr<osg::Node> node3 = osgDB::readNodeFile(BUILDINGS_URL);
    osg::ref_ptr<osg::Node> node4 = osgDB::readNodeFile(DCBUILDING_URL);

    /////////////////////////////////
    osg::ref_ptr<osg::Image> image= createImage(256,256,osg::Vec3(255.0,1.0,0.0));
    if (image.get())
    {
        osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D();
        texture->setImage(image.get());
        //设置自动生成纹理坐标
        osg::ref_ptr<osg::TexGen> texgen=new osg::TexGen();
        texgen->setMode(osg::TexGen::NORMAL_MAP);
        //设置纹理环境，模式为BLEND
        osg::ref_ptr<osg::TexEnv> texenv=new osg::TexEnv;
        texenv->setMode(osg::TexEnv::Mode::ADD);
        texenv->setColor(osg::Vec4(0.6,0.6,0.6,0.0));
        //启动单元一自动生成纹理坐标，并使用纹理
        osg::ref_ptr<osg::StateSet> state=new osg::StateSet;
        state->setTextureAttributeAndModes(1,texture.get(),osg::StateAttribute::ON);
        state->setTextureAttributeAndModes(1,texgen.get(),osg::StateAttribute::ON);
        // state->setTextureAttribute(1,texenv.get());
        node1->setStateSet(state.get());
    }
    osg::ref_ptr<osg::Image> image1= createImage(256,256,osg::Vec3(1.0,255.0,0.0));
    if (image1.get())
    {
        osg::ref_ptr<osg::Texture2D> texture1=new osg::Texture2D();
        texture1->setImage(image1.get());
        //设置自动生成纹理坐标
        osg::ref_ptr<osg::TexGen> texgen1=new osg::TexGen();
        texgen1->setMode(osg::TexGen::NORMAL_MAP);
        //设置纹理环境，模式为BLEND
        osg::ref_ptr<osg::TexEnv> texenv1=new osg::TexEnv;
        texenv1->setMode(osg::TexEnv::Mode::ADD);
        texenv1->setColor(osg::Vec4(0.6,0.6,0.6,0.0));
        //启动单元一自动生成纹理坐标，并使用纹理
        osg::ref_ptr<osg::StateSet> state1=new osg::StateSet;
        state1->setTextureAttributeAndModes(1,texture1.get(),osg::StateAttribute::ON);
        state1->setTextureAttributeAndModes(1,texgen1.get(),osg::StateAttribute::ON);
        // state->setTextureAttribute(1,texenv.get());
        node2->setStateSet(state1.get());
    }
    /*osg::ref_ptr<osg::Image> image2= createImage(256,256,osg::Vec3(1.0,1.0,255.0));
    if (image2.get())
    {
    osg::ref_ptr<osg::Texture2D> texture2=new osg::Texture2D();
    texture2->setImage(image2.get());
    //设置自动生成纹理坐标
    osg::ref_ptr<osg::TexGen> texgen2=new osg::TexGen();
    texgen2->setMode(osg::TexGen::NORMAL_MAP);
    //设置纹理环境，模式为BLEND
    osg::ref_ptr<osg::TexEnv> texenv2=new osg::TexEnv;
    texenv2->setMode(osg::TexEnv::Mode::ADD);
    texenv2->setColor(osg::Vec4(0.6,0.6,0.6,0.0));
    //启动单元一自动生成纹理坐标，并使用纹理
    osg::ref_ptr<osg::StateSet> state2=new osg::StateSet;
    state2->setTextureAttributeAndModes(1,texture2.get(),osg::StateAttribute::ON);
    state2->setTextureAttributeAndModes(1,texgen2.get(),osg::StateAttribute::ON);
    // state->setTextureAttribute(1,texenv.get());
    node3->setStateSet(state2.get());
    }*/

    //添加到场景

    //	root->addChild(node2.get());
    //	root->addChild(node3.get());
    //	root->addChild(node1.get());
    root->addChild(node4.get());
    //优化场景数据
    osgUtil::Optimizer optimizer ;
    optimizer.optimize(root.get()) ;
    /////////////////////////////////
    //设置场景数据
    //更变背景颜色
    viewer->getCamera()->setClearColor(osg::Vec4f(1.0f,1.0f,1.0f,1.0f));  //white
    viewer->addEventHandler(new osgViewer::WindowSizeHandler);

    viewer->setSceneData(root.get());
    //初始化并创建窗口
    viewer->realize();
    //开始渲染
    viewer->run();
}

void examplesTexture::test2 ()
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

    //创建场景组节点
    osg::ref_ptr<osg::Group> root = new osg::Group();

    //创建一个节点,读取SHP文件
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("C:\\osg\\osgmake\\osgearth_bin\\data\\1.DXF");

    //添加到场景
    root->addChild(node.get());

    //优化场景数据
    osgUtil::Optimizer optimizer ;
    optimizer.optimize(root.get()) ;

    //设置场景数据
    viewer->setSceneData(root.get());

    //初始化并创建窗口
    viewer->realize();

    //开始渲染
    viewer->run();
}

osg::Geometry*   examplesTexture::myCreateTexturedQuadGeometry(const osg::Vec3& pos,float width,float height, osg::Image* image, bool useTextureRectangle, bool xyPlane, bool option_flip)
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

        return pictureQuad;
    }
}

void examplesTexture::DxfandMovie(int argc, char** argv)
{

    osgViewer::Viewer viewer;
    osg::Vec3 pos(0.0f,0.0f,0.0f);
    osg::Vec3 topleft = pos;
    osg::Vec3 bottomright = pos;
    bool mouseTracking = false;
    bool xyPlane = false;
    bool useTextureRectangle = true;
    bool flip = false;
    bool useAudioSink = false;
    osg::ref_ptr<osg::Group> root=new osg::Group();
    osg::ref_ptr<osg::Node>  node_dxf=osgDB::readNodeFile("C:\\osg\\osgmake\\osgearth_bin\\data\\1.DXF");  //d:\\stl\\Spec_House_1st_Floor.stl   D:\\GZWork\\resource\\1.DXF

    osg::ref_ptr<osg::Image> image=osgDB::readImageFile("C:\\osg\\osgmake\\osgearth_bin\\data\\01.mp4");//d:\\shp\\3.bmp  d:\\shp\\m.mp4
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;

    osg::StateSet* stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);


    if (image)
    {
        osg::notify(osg::NOTICE)<<"image->s()"<<image->s()<<" image-t()="<<image->t()<<" aspectRatio="<<image->getPixelAspectRatio()<<std::endl;

        float width = image->s() * image->getPixelAspectRatio();
        float height = image->t();

        osg::ref_ptr<osg::Drawable> drawable = myCreateTexturedQuadGeometry(pos, width, height, image.get(), useTextureRectangle, xyPlane, flip);

        if (image->isImageTranslucent())
        {
            osg::notify(osg::NOTICE)<<"Transparent movie, enabling blending."<<std::endl;

            drawable->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
            drawable->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        }

        geode->addDrawable(drawable.get());

        bottomright = pos + osg::Vec3(width,height,0.0f);

        if (xyPlane) pos.y() += height*1.05f;
        else pos.z() += height*1.05f;
    }
    else
    {
        //CString cs = "Unable to read file ";
        //std::cout<<"Unable to read file "<<arguments[i]<<std::endl;
    }

    if (image.get())
    {
        osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D();
        texture->setImage(image.get());

        //设置自动生成纹理坐标
        osg::ref_ptr<osg::TexGen> texgen=new osg::TexGen();
        texgen->setMode(osg::TexGen::SPHERE_MAP);

        //设置纹理环境，模式为BLEND
        osg::ref_ptr<osg::TexEnv> texenv=new osg::TexEnv;
        texenv->setMode(osg::TexEnv::Mode::ADD);
        texenv->setColor(osg::Vec4(0.6,0.6,0.6,0.0));

        //启动单元一自动生成纹理坐标，并使用纹理
        osg::ref_ptr<osg::StateSet> state=new osg::StateSet;
        state->setTextureAttributeAndModes(1,texture.get(),osg::StateAttribute::ON);
        state->setTextureAttributeAndModes(1,texgen.get(),osg::StateAttribute::ON);
        state->setTextureAttribute(1,texenv.get());

        node_dxf->setStateSet(state.get());

    }
    //
    //看书里的办法
    /*osg::Group* tg = dynamic_cast<osg::Group*>(node.get());
    tg->addChild(geode.get());
    root->addChild(tg);*/
    ////////////////////////////
    //初始办法
    root->addChild(geode.get());
    root->addChild(node_dxf.get());
    viewer.setSceneData(root.get());

    ////////////////////////////////

    MovieEventHandler* meh = new MovieEventHandler();
    meh->setMouseTracking( mouseTracking );
    meh->set( viewer.getSceneData() );
    viewer.addEventHandler( meh );

    viewer.addEventHandler( new osgViewer::StatsHandler );
    viewer.addEventHandler( new osgGA::StateSetManipulator( viewer.getCamera()->getOrCreateStateSet() ) );
    viewer.addEventHandler( new osgViewer::WindowSizeHandler );

    // add the record camera path handler
    viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
    viewer.realize();
    viewer.run();
}

void examplesTexture::test3 ()
{
    int argc = 4;
    char* argv[] = {"riririr", "-e","ffmpeg","d:\\shp\\m.mp4"};
    DxfandMovie(argc, argv);
}

#if 0
osg::Node*   createNewShaderCompositionScene(osg::ArgumentParser& arguments)
{
    osg::ref_ptr<osg::Node> node = osgDB::readRefNodeFiles(arguments);
    if (!node) return 0;

    osg::ref_ptr<osg::Group> group = new osg::Group;

    osg::ref_ptr<osg::StateSet> stateset = group->getOrCreateStateSet();
    osg::ref_ptr<osg::Program> program = new osg::Program;
    stateset->setAttribute(program.get());

    osg::ref_ptr<osg::Shader> lighting_shader = osgDB::readRefShaderFile("shaders/lighting.vert");
    if (lighting_shader.valid())
    {
        program->addShader(lighting_shader.get());
        OSG_NOTICE<<"Adding lighting shader"<<std::endl;
    }

    osg::ref_ptr<osg::Shader> vertex_shader = osgDB::readRefShaderFile("shaders/osgshadercomposition.vert");
    if (vertex_shader.valid())
    {
        program->addShader(vertex_shader.get());
        OSG_NOTICE<<"Adding vertex shader"<<std::endl;
    }

    osg::ref_ptr<osg::Shader> fragment_shader = osgDB::readRefShaderFile("shaders/osgshadercomposition.frag");
    if (fragment_shader.valid())
    {
        program->addShader(fragment_shader.get());
        OSG_NOTICE<<"Adding fragment shader"<<std::endl;
    }

    stateset->addUniform(new osg::Uniform("texture0", 0));


    double spacing = node->getBound().radius() * 2.0;

    osg::Vec3d position(0.0,0.0,0.0);

    {
        // first subgraph, one the left, just inherit all the defaults
        osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform;
        pat->setPosition(position);
        pat->addChild(node.get());

        position.x() += spacing;

        group->addChild(pat);
    }

    {
        // second subgraph, enable lighting by passing a GL_LIGHTING defines to the shaders
        // As the lighting.vert shader has a #pragma requires(GL_LIGHTING) in the shader it
        // instructs the osg::Prorgam to link in this shader only when the GL_LIGHTING define
        // is provided.  The osgshadercomposition.vert also has a #pragma import_defines(GL_LIGHTING ..) so
        // when the GL_LIGHTING is provided it'll enable the lighting paths in the osgshadercomposition.vert
        // shader calling the lighting function per vertex
        osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform;
        pat->setPosition(position);
        pat->getOrCreateStateSet()->setDefine("LIGHTING");

        pat->addChild(node.get());

        position.x() += spacing;

        group->addChild(pat);
    }

    {
        // third subgraph, enable texturing by passing the GL_TEXTURE_2D define to the shaders.
        // Both the osgshadercomposition.vert and osgshadercomposition.frag shaders have a
        // #pragma import_defines(GL_TEXTURE_2D) so that can use this define to enable the
        // passing of texture coordinates between the vertex and framgment shaders and for
        // the fragment shader to read the texture of unit 0 (provided by the "texture0" uniform above.
        osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform;
        pat->setPosition(position);
        pat->getOrCreateStateSet()->setDefine("TEXTURE_2D");

        pat->addChild(node.get());

        position.x() += spacing;

        group->addChild(pat);
    }


    {
        // fourth subgraph, enable texturing and lighting
        osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform;
        pat->setPosition(position);
        pat->getOrCreateStateSet()->setDefine("LIGHTING");
        pat->getOrCreateStateSet()->setDefine("TEXTURE_2D");

        pat->addChild(node.get());

        position.x() += spacing;

        group->addChild(pat);
    }

    {
        // fourth subgraph, enable texturing and lighting
        osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform;
        pat->setPosition(position);
        pat->getOrCreateStateSet()->setDefine("LIGHTING");
        pat->getOrCreateStateSet()->setDefine("TEXTURE_2D");
        pat->getOrCreateStateSet()->setDefine("VERTEX_FUNC(v)", "vec4(v.x, v.y, v.z * sin(osg_SimulationTime), v.w)");

        pat->addChild(node.get());

        position.x() += spacing;

        group->addChild(pat);
    }

    group->addChild(node.get());

    return group.release();
}

void Shade(int argc, char **argv)
{
    osg::ArgumentParser arguments(&argc,argv);

    osgViewer::Viewer viewer(arguments);

    viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);

    if (arguments.read("--old"))
    {

    }
    else
    {
        // use new #pragma(tic) shader composition.
        osg::ref_ptr<osg::Node> scenegraph = createNewShaderCompositionScene(arguments);
        if (!scenegraph) return ;

        viewer.setSceneData(scenegraph.get());
    }

    viewer.run();
}

void test4()
{
    // TODO: 在此添加控件通知处理程序代码

    int argc = 2;

    char* argv[] = {"riririr","D:\\GZWork\\resource\\1.DXF"};
    Shade(argc, argv);
}
#endif

void examplesTexture::test5()
{
    // TODO: 在此添加控件通知处理程序代码
    //如何在地形上放置模型
    osgViewer::Viewer viewer;
    osg::ref_ptr<osg::Group>root = new osg::Group;


    osg::ref_ptr<osg::Node> terrian = osgDB::readNodeFile("C:\\osg\\osgmake\\osgearth_bin\\data\\1.DXF");


    // createTank
    osg::ref_ptr<osg::Node> tank = osgDB::readNodeFile("cow.osg");
    osg::ref_ptr<osg::PositionAttitudeTransform> tankPosition = new osg::PositionAttitudeTransform;
    tankPosition->addChild(tank);
    //x,y 点  假设是 -10  -10
    double tankXPosition = -5;
    double tankYPosition = -5;


    osg::LineSegment* tankLocationSegment = new osg::LineSegment;
    //一条足够长的线  <br>
    tankLocationSegment->set(osg::Vec3(tankXPosition,tankYPosition,999),osg::Vec3(tankXPosition,tankYPosition,-999));
    //将这条线添加到visitor中
    osgUtil::IntersectVisitor tankElevationVisitor ;
    tankElevationVisitor.addLineSegment(tankLocationSegment);//检测出在terrian上的点
    terrian->accept(tankElevationVisitor);
    //得到  交点列表
    osgUtil::IntersectVisitor::HitList tankElevationHitLists = tankElevationVisitor.getHitList(tankLocationSegment);

    osgUtil::Hit heightTestResult;
    if(tankElevationHitLists.empty())
    {
        std::cout<<"could not place a tank on this terrian!"<<std::endl;
        return;
    }
    //第一个交点 ，转换成世界坐标<br>
    heightTestResult = tankElevationHitLists.front();
    osg::Vec3 terrianHeight = heightTestResult.getWorldIntersectPoint();
    tankPosition->setPosition(terrianHeight);
    //osg::ref_ptr<osgUtil::LineSegmentIntersector> //
    viewer.setCameraManipulator(new osgGA::DriveManipulator);
    //root->addChild(tank);
    root->addChild(tankPosition);
    root->addChild(terrian);
    viewer.setSceneData(root);
    viewer.realize();
    viewer.run();
}

osg::Camera* examplesTexture::createHUDBg(std::string imagePath)
{
    osg::ref_ptr<osg::Camera>camera=new osg::Camera;
    camera->setProjectionMatrixAsOrtho2D(0, 800, 0, 600);
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->setViewport(0,0,1300,800);
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setAllowEventFocus(false);
    camera->setViewMatrix(osg::Matrix::identity());

    osg::ref_ptr<osg::Geode>geode=new osg::Geode;
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON);

    osg::ref_ptr<osg::Geometry>gm=new osg::Geometry;

    //亚入顶点
    osg::ref_ptr<osg::Vec3Array>vertex=new osg::Vec3Array;
    vertex->push_back(osg::Vec3(0,0,0));
    vertex->push_back(osg::Vec3(800,0,0));
    vertex->push_back(osg::Vec3(800,600,0));
    vertex->push_back(osg::Vec3(0,600,0));
    gm->setVertexArray(vertex);

    //压入法线

    //纹理坐标
    osg::ref_ptr<osg::Vec2Array>coord=new osg::Vec2Array;
    coord->push_back(osg::Vec2(0,0));
    coord->push_back(osg::Vec2(1,0));
    coord->push_back(osg::Vec2(1,1));
    coord->push_back(osg::Vec2(0,1));
    gm->setTexCoordArray(0, coord);
    gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

    osg::ref_ptr<osg::Image>image=osgDB::readImageFile(imagePath);
    if(!image.valid()){
        //    std::cout<"read image faild "<<std::endl;
        return camera.release();
    }
    //  osg::ref_ptr<osg::Texture2D>t2d=new osg::Texture2D;
    osg::Texture2D* t2d=new osg::Texture2D;
    t2d->setImage(0,image);


    gm->getOrCreateStateSet()->setTextureAttributeAndModes(0, t2d,osg::StateAttribute::ON);
    geode->addDrawable(gm);
    camera->addChild(geode);
    return camera.release();
}

void examplesTexture::test7 ()
{
    // TODO: 在此添加控件通知处理程序代码
    osg::ref_ptr<osgViewer::Viewer>viewer=new osgViewer::Viewer;
    //  viewer->getCamera()->setClearMask(GL_DEPTH_BUFFER_BIT);
    osg::ref_ptr<osg::Group>root=new osg::Group;
    root->addChild(osgDB::readNodeFile("C:\\osg\\osgmake\\osgearth_bin\\data\\1.DXF"));
    root->addChild(createHUDBg("d:\\shp\\3.bmp"));
    viewer->setSceneData(root.get());
    viewer->run();
}
