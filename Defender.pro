TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14

LIBS = -L/usr/lib/ -lSDL2 -lSDL2_image -lSDL2_ttf

SOURCES += \
    window.cpp \
    texture.cpp \
    renderer.cpp \
    main.cpp \
    keyboardmanager.cpp \
    clock.cpp \
    entity.cpp \
    room.cpp \
    game.cpp \
    maingameroom.cpp \
    player.cpp \
    playerprojectile.cpp \
    alien.cpp \
    man.cpp \
    mainmenu.cpp \
    ttffont.cpp \
    textureregistry.cpp \
    fontregistry.cpp \
    abductor.cpp \
    alienprojectile.cpp \
    mutant.cpp

HEADERS += \
    window.h \
    vector.h \
    texture.h \
    renderer.h \
    keyboardmanager.h \
    clock.h \
    entity.h \
    room.h \
    game.h \
    maingameroom.h \
    player.h \
    globals.h \
    playerprojectile.h \
    alien.h \
    man.h \
    mainmenu.h \
    ttffont.h \
    textureregistry.h \
    fontregistry.h \
    abductor.h \
    alienprojectile.h \
    mutant.h
