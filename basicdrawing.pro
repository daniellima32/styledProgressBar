QT += widgets

HEADERS       = \
                window.h \
    controler.h
SOURCES       = main.cpp \
                window.cpp
RESOURCES     =

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/basicdrawing
INSTALLS += target
