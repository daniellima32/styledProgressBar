QT += widgets

CONFIG += c++11

HEADERS       = \
    styledprogressbar.h \
    spbstate.h \
    squarecomponent.h
SOURCES       = main.cpp \
    styledprogressbar.cpp
RESOURCES     =

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/basicdrawing
INSTALLS += target
