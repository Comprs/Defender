TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14

LIBS = -L/usr/lib/ -lSDL2 -lSDL2_image

SOURCES += \
    window.cpp \
    vector.cpp

HEADERS += \
    window.h \
    vector.h
