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

SOURCES += main.cpp\
        fenetre.cpp \
    openglwindow.cpp \
    programmegpu.cpp \
    mesh.cpp \
    camera.cpp \
    astre.cpp \
    sourcelumiere.cpp \
    texture.cpp \
    scenegraph.cpp \
    cercle.cpp \
    billboard.cpp

HEADERS  += fenetre.h \
    openglwindow.h \
    programmegpu.h \
    mesh.h \
    camera.h \
    astre.h \
    sourcelumiere.h \
    texture.h \
    scenegraph.h \
    cercle.h \
    billboard.h

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
