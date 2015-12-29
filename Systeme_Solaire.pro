#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T14:16:49
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Systeme_Solaire
TEMPLATE = app

app_data.files   = $$PWD/shader

INCLUDEPATH += include/

SOURCES += src/main.cpp\
        src/fenetre.cpp \
    src/openglwindow.cpp \
    src/programmegpu.cpp \
    src/mesh.cpp \
    src/camera.cpp \
    src/astre.cpp \
    src/sourcelumiere.cpp \
    src/texture.cpp \
    src/scenegraph.cpp \
    src/cercle.cpp \
    src/billboard.cpp

HEADERS  += src/fenetre.h \
    src/openglwindow.h \
    src/programmegpu.h \
    src/mesh.h \
    src/camera.h \
    src/astre.h \
    src/sourcelumiere.h \
    src/texture.h \
    src/scenegraph.h \
    src/cercle.h \
    src/billboard.h

DISTFILES += \
    shader/FS.glsl \
    shader/VS.glsl

OTHER_FILES += \
    shader/FS_planete.glsl \
    shader/VS_planete.glsl \
    shader/VS_cercle.glsl \
    shader/FS_cercle.glsl \
    shader/VS_soleil.glsl \
    shader/FS_soleil.glsl \
    image/0.png \
    image/1.png \
    image/2.png \
    image/3.png \
    image/4.png \
    image/5.png \
    image/6.png \
    image/7.png \
    image/billboard_0.png \
    image/billboard_0r.png \
    image/billboard_1.png \
    image/billboard_1r.png \
    image/billboard_2.png \
    image/billboard_2r.png \
    image/billboard_3.png \
    image/billboard_3r.png \
    image/billboard_4.png \
    image/billboard_4r.png \
    image/billboard_5.png \
    image/billboard_5r.png \
    image/billboard_6.png \
    image/billboard_6r.png \
    image/billboard_7.png \
    image/billboard_7r.png \
    image/billboard_lune.png \
    image/billboard_luner.png \
    image/billboard_soleil.png \
    image/billboard_soleilr.png \
    image/lune.png \
    image/soleil.png \
    shader/GS_billboard.glsl \
    shader/VS_billboard.glsl \
    shader/FS_billboard.glsl
