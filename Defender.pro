TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14

LIBS = -L/usr/lib/ -lSDL2 -lSDL2_image

SOURCES += \
    window.cpp \
    vector.cpp \
    texture.cpp \
    renderer.cpp \
    main.cpp \
    keyboardmanager.cpp \
    clock.cpp \
    entity.cpp \
    room.cpp \
    textureregistry.cpp \
    game.cpp \
    maingameroom.cpp \
    player.cpp

HEADERS += \
    window.h \
    vector.h \
    texture.h \
    renderer.h \
    keyboardmanager.h \
    clock.h \
    entity.h \
    room.h \
    textureregistry.h \
    game.h \
    maingameroom.h \
    player.h \
    globals.h
