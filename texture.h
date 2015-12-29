#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions_3_3_Core>
#include "programmegpu.h"
#include <string>
#include <QImage>
#include <iostream>

#define IMAGE_DIR "/home/thibault/Documents/Cours/2A/LMG/Projet/Systeme_Solaire/image/"

class Texture : protected QOpenGLFunctions_3_3_Core
{
    public:
        //Constructeur
        Texture();

        //Detruire
        void detruire();

        //Creer
        void creer(std::string _nomFichier, QImage::Format _mode, GLint _internalformat = GL_RGB, GLenum _format = GL_RGB);

        //Envoyer uniforme
        void avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nom);

        //Mettre le texture unit
        void mettreTextureUnit(int _idTextureUnit);

        //Envoyer au gpu la texture
        void envoyerUniformVersGPU();

    protected:

        GLuint m_texture;
        GLuint m_uniformTexture;
        GLuint m_idTextureUnit;
};

#endif // TEXTURE_H
