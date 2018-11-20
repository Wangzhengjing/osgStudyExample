SOURCES += \
    main.cpp \
    getworldcoordinateofnodevisitor.cpp \
    myMatrixTransform.cpp \
    examples/mybillboardtree.cpp \
    examples/mycube.cpp

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
    examples/mycube.h
