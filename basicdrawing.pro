QT += widgets

HEADERS       = \
                window.h \
    controler.h \
    styledprogressbar.h \
    userclass.h
SOURCES       = main.cpp \
                window.cpp \
    styledprogressbar.cpp \
    userclass.cpp
RESOURCES     =

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/basicdrawing
INSTALLS += target
