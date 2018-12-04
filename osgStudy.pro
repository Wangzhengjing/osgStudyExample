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
    earthwalkmanipulator2.cpp

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

HEADERS += \
    getworldcoordinateofnodevisitor.h \
    myMatrixTransform.h \
    examples/mybillboardtree.h \
    examples/mycube.h \
    mytexture.h \
    mytexturecube.h \
    examplestexture.h \
    mymanipulator.h \
    earthwalkmanipulator2.h
