#include "texture.h"

Texture::Texture() :
     m_texture(0)
    ,m_uniformTexture(0)
    ,m_idTextureUnit(0)
{
}

//----------------------------------------------------------------------------------------------------------------------------
void Texture::detruire()
{
    glDeleteTextures(1,&m_texture);
}

//----------------------------------------------------------------------------------------------------------------------------
void Texture::creer(std::string _nomFichier, QImage::Format _mode, GLint _internalformat, GLenum _format)
{
    std::string dir = IMAGE_DIR+_nomFichier;
    std::cout << "Chargement de la texture  : " << dir << std::endl;
    QImage img(dir.c_str());
    QImage img0 = img.convertToFormat(_mode,Qt::NoOpaqueDetection);
    unsigned char* data = img0.scanLine(0);

    initializeOpenGLFunctions();
    glEnable(GL_TEXTURE_2D);

    glGenTextures(1,&m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    {
        glTexImage2D(GL_TEXTURE_2D, 0,_internalformat,img0.width(),img0.height(),0,_format,GL_UNSIGNED_BYTE,data);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );*/
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

//----------------------------------------------------------------------------------------------------------------------------
void Texture::avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nom)
{
    m_uniformTexture = _prog.avoirUniformLocation(_nom);
}

//----------------------------------------------------------------------------------------------------------------------------
void Texture::mettreTextureUnit(int _idTextureUnit)
{
    m_idTextureUnit = _idTextureUnit;
    glBindTexture( GL_TEXTURE_2D, m_texture );
    glActiveTexture( GL_TEXTURE0 + m_idTextureUnit );
}

//----------------------------------------------------------------------------------------------------------------------------
void Texture::envoyerUniformVersGPU()
{
    glUniform1i(m_uniformTexture,m_idTextureUnit);
}
