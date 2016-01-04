#include "billboard.h"

Billboard::Billboard() :
    Texture(),
    m_astre(NULL),
    m_position(glm::vec3(0.f,0.f,0.f)),
    m_matriceMonde(glm::mat4(1.f)),
    m_uniformMatriceMonde(0),
    m_attributPosition(0),
    m_VBOPosition(0),
    m_VAO(0)
{
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::creer(std::string _nomFichier, Astre *_astre, glm::vec3 _position)
{
    Texture::creer(_nomFichier,QImage::Format_RGBA8888_Premultiplied,GL_RGBA8,GL_RGBA);
    associer(_astre);

    //On prend la matrice monde de l'astre associée
    m_matriceMonde = _astre->avoirMatriceMonde();
    m_position = _position;

    //VBO position
    glGenBuffers(1,&m_VBOPosition);
    glBindBuffer(GL_ARRAY_BUFFER,m_VBOPosition);
    {
        glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3),&m_position,GL_STATIC_DRAW);
    }
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBOPosition);
        glEnableVertexAttribArray(m_attributPosition);
        glVertexAttribPointer(m_attributPosition,3,GL_FLOAT,GL_FALSE,0,0);
    }
    glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::detruire()
{
    Texture::detruire();

    glDeleteBuffers(1,&m_VBOPosition);
    glDeleteVertexArrays(1,&m_VAO);
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::associer(Astre* _astre)
{
    m_astre = _astre;
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::dessiner()
{
    //On envoie le vextice au gpu programme
    glBindVertexArray(m_VAO);
    {
        glDrawArrays(GL_POINTS,0,1);
    }
    glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nom, std::string _nomMatriceMonde)
{
    Texture::avoirUniformLocalisation(_prog,_nom);
    m_uniformMatriceMonde = _prog.avoirUniformLocation(_nomMatriceMonde);
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::avoirAttributLocalisation(ProgrammeGPU& _prog, std::string _position)
{
    m_attributPosition = _prog.avoirAttributeLocation(_position);
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::mettreTextureUnit(int _idTextureUnit)
{
    Texture::mettreTextureUnit(_idTextureUnit);
}

//----------------------------------------------------------------------------------------------------------------------------
void Billboard::envoyerUniformVersGPU()
{
    m_matriceMonde = m_astre->avoirMatriceMonde();
    //On envoie la matrice
    glUniformMatrix4fv(m_uniformMatriceMonde,1,GL_FALSE,glm::value_ptr(m_matriceMonde));
    Texture::envoyerUniformVersGPU();
}

