DEFINES += MULTIBYTE
DEFINES += __STDC_CONSTANT_MACROS
#DEFINES += WANGPENG
#DEFINES += __XMLDocument_FWD_DEFINED__

SOURCES += \
    main.cpp \
    getworldcoordinateofnodevisitor.cpp \
    myMatrixTransform.cpp \
    examples/mybillboardtree.cpp \
    examples/mycube.cpp \
    mytexture.cpp \
    mytexturecube.cpp \
    examplestexture.cpp \
    mymanipulator.cpp \
    earthwalkmanipulator2.cpp \
    mycubeTexture.cpp \
    cameramanipulator.cpp \
    perspectiveTrans.cpp \
    polygongeometry.cpp \
    textureUpdate.cpp \
    textureUpdateThread.cpp \
    thread2.cpp \
    thread3.cpp \
    thread4.cpp \
    thread1.cpp \
    moviePlay.cpp \
    VideoStream.cpp \
    ffmpeg/FFmpegDecoderVideo.cpp \
    ffmpeg/FFmpegClocks.cpp \
    ffmpeg/FFmpegDecoderVideo.cpp \
    ffmpeg/FFmpegClocks.cpp \
    ffmpeg/FFmpegImageStream.cpp \
    ffmpeg/FFmpegDecoder.cpp \
    ffmpeg/FFmpegDecoderAudio.cpp \
    ffmpeg/FFmpegParameters.cpp \
    ffmpeg/FFmpegAudioStream.cpp \
    myFFmpegImageStream.cpp \
    config/tinyxml2.cpp \
    config/geoVideoConfig.cpp \
    config/geoConfigParser.cpp \
    virtualfunc.cpp \
    mapvector.cpp \
    frustumFromCamera.cpp

LIBS += -LC:/osg/osgmake/osgearth_bin/lib \
    -losgd \
    -losgWidgetd \
    -losgUtild \
    -losgSimd \
    -losgTerraind \
    -losgDBd \
    -losgFXd \
    -losgViewerd \
    -losgTextd \
    -losgGAd \
    -losgQtd \
    -losgShadowd \
    -losgVolumed \
    -losgParticled \
    -losgAnimationd \
    -lOpenThreadsd \
    -losgEarthd \
    -losgEarthUtild \
    -losgEarthSymbologyd \
    -losgEarthAnnotationd \
    -losgEarthFeaturesd \
    -losgEarthQtd \
    -losgManipulatord

LIBS += -LC:/osg/ffmpeg-4.1-win64-dev/lib \
    -lavcodec \
    -lavdevice \
    -lavfilter \
    -lavformat \
    -lavutil \
    -lswresample \
    -lswscale

LIBS += -LD:/ProjectMange/GeoVideo/project/OSG/osg3.2.2/build/lib/osgPlugins-3.2.2 \
    -losgdb_ffmpegd

LIBS += -LC:/osg/3rdParty/opencv/x64/vc10/lib/ \
        -lopencv_calib3d330d \
        -lopencv_core330d \
        -lopencv_dnn330d \
        -lopencv_features2d330d \
        -lopencv_flann330d \
        -lopencv_highgui330d \
        -lopencv_imgcodecs330d \
        -lopencv_imgproc330d \
        -lopencv_ml330d \
        -lopencv_objdetect330d \
        -lopencv_photo330d \
        -lopencv_shape330d \
        -lopencv_stitching330d \
        -lopencv_superres330d \
        -lopencv_video330d \
        -lopencv_videoio330d \
        -lopencv_videostab330d

HEADERS += \
    getworldcoordinateofnodevisitor.h \
    myMatrixTransform.h \
    examples/mybillboardtree.h \
    examples/mycube.h \
    mytexture.h \
    mytexturecube.h \
    examplestexture.h \
    mymanipulator.h \
    earthwalkmanipulator2.h \
    mycubeTexture.h \
    cameramanipulator.h \
    perspectiveTrans.h \
    polygongeometry.h \
    textureUpdate.h \
    textureUpdateThread.h \
    moviePlay.h \
    VideoStream.h \
    ffmpeg/FFmpegDecoderVideo.hpp \
    ffmpeg/FFmpegHeaders.hpp \
    ffmpeg/BoundedMessageQueue.hpp \
    ffmpeg/FFmpegClocks.hpp \
    ffmpeg/FFmpegPacket.hpp \
    ffmpeg/FFmpegPacket.hpp \
    ffmpeg/FFmpegHeaders.hpp \
    ffmpeg/FFmpegDecoderVideo.hpp \
    ffmpeg/FFmpegClocks.hpp \
    ffmpeg/BoundedMessageQueue.hpp \
    ffmpeg/version.h \
    ffmpeg/FFmpegImageStream.hpp \
    ffmpeg/FFmpegDecoder.hpp \
    ffmpeg/FFmpegDecoderAudio.hpp \
    ffmpeg/MessageQueue.hpp \
    ffmpeg/FFmpegParameters.hpp \
    ffmpeg/FFmpegAudioStream.hpp \
    myFFmpegImageStream.h \
    config/tinyxml2.h \
    config/geoVideoConfig.h \
    config/geoConfigParser.h \
    myintersection.h \
    virtualfunc.h \
    mapvector.h \
    frustum.h
