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
    polygongeometry.cpp

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
    polygongeometry.h
