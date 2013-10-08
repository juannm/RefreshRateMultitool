#====================================================================
#          PROJECT CONFIGURATION
#====================================================================

message("Processing $${_FILE_}")

CONFIG(debug, debug|release):BUILD_TARGET = debug
CONFIG(release, debug|release):BUILD_TARGET = release
message("Building [$${BUILD_TARGET}] Makefile for [$${TARGET}] on [$${QMAKE_HOST.os}] [$${QMAKE_HOST.arch}]")

# Project configuration and compiler options
TARGET = RefreshRateMultitool.run
TEMPLATE = app
CONFIG -= qt

# Build locations
DESTDIR = bin
MOC_DIR = tmp
OBJECTS_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp
unix:QMAKE_DISTCLEAN += -r tmp

# Additional configuration
#DEFINES += J=1
*g++* {
    # Disable common but not so useful compilation warnings
    QMAKE_CXXFLAGS += -Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable

    # Enable support for C++11 language features
    QMAKE_CXXFLAGS += -std=c++0x
}

win32-msvc* {
    # Disable deprecation of *printf functions
    DEFINES += _CRT_SECURE_NO_WARNINGS

    # Disable standard-C assertions
    QMAKE_CFLAGS_RELEASE += /DNDEBUG
    QMAKE_CXXFLAGS_RELEASE += /DNDEBUG
}



#====================================================================
#          PROJECT FILES
#====================================================================

INCLUDEPATH += \
    dep/include/

#DEPENDPATH += \

LIBS += -Ldep/lib/ -lglfw3 -lX11 -lXrandr -lXi -lXxf86vm -lGL -lrt -lm

#HEADERS += MyClass.h

SOURCES += src/main.cpp
