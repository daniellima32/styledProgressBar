QT += widgets

HEADERS       = \
    styledprogressbar.h \
    userclass.h \
    spbstate.h \
    squarecomponent.h
SOURCES       = main.cpp \
    styledprogressbar.cpp \
    userclass.cpp
RESOURCES     =

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/basicdrawing
INSTALLS += target
