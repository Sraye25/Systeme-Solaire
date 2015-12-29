#include "mesh.h"

Mesh::Mesh() :
    m_nbVertice(0),
    m_nbElement(0),
    m_VAO(0),
    m_VBOPosition(0),
    m_VBOCouleur(0),
    m_VBONormal(0),
    m_VBOTextureCoord(0),
    m_EBO(0),
    m_attribPosition(0),
    m_attribCouleur(0),
    m_attribNormal(0),
    m_attribTextureCoord(0),
    m_positionPresent(true),
    m_couleurPresent(true),
    m_normalPresent(true),
    m_textureCoordPresent(true),
    m_eboPresent(true),
    m_matriceMonde(glm::mat4(1.0f)),
    m_matriceNormal(glm::mat4(1.0f)),
    m_uniformMatrice(0),
    m_uniformNormal(0),
    m_mode(GL_TRIANGLES)
{
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::detruire()
{
    if(m_positionPresent) glDeleteBuffers(1,&m_VBOPosition);
    if(m_couleurPresent) glDeleteBuffers(1,&m_VBOCouleur);
    if(m_normalPresent) glDeleteBuffers(1,&m_VBONormal);
    if(m_textureCoordPresent) glDeleteBuffers(1,&m_VBOTextureCoord);
    if(m_eboPresent) glDeleteBuffers(1,&m_EBO);

    glDeleteVertexArrays(1,&m_VAO);
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::activerAttribut(bool position, bool couleur, bool normal, bool coordTex, bool ebo)
{
    m_positionPresent = position;
    m_couleurPresent = couleur;
    m_normalPresent = normal;
    m_textureCoordPresent = coordTex;
    m_eboPresent = ebo;
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::avoirAttributLocalisation(ProgrammeGPU& _prog, std::string _nomPos, std::string _nomCoul, std::string _nomNorm, std::string _nomText)
{
    if(_nomPos!="") m_attribPosition = _prog.avoirAttributeLocation(_nomPos);
    if(_nomCoul!="") m_attribCouleur = _prog.avoirAttributeLocation(_nomCoul);
    if(_nomNorm!="") m_attribNormal = _prog.avoirAttributeLocation(_nomNorm);
    if(_nomText!="") m_attribTextureCoord = _prog.avoirAttributeLocation(_nomText);
    //std::cout << "Attribut Mesh" << std::endl;
    //std::cout << m_attribPosition << " " << m_attribCouleur << " " << m_attribNormal << " " << m_attribTextureCoord << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nomMatriceMonde, std::string _nomMatriceNormal)
{
    m_uniformMatrice = _prog.avoirUniformLocation(_nomMatriceMonde);
    m_uniformNormal = _prog.avoirUniformLocation(_nomMatriceNormal);

    //std::cout << "Uniforme Mesh" << std::endl;
    //std::cout << m_uniformMatrice << " " << m_uniformNormal << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::envoyerUniformVersGPU()
{
    glUniformMatrix4fv(m_uniformMatrice,1,GL_FALSE,glm::value_ptr(m_matriceMonde));
    glUniformMatrix4fv(m_uniformNormal,1,GL_FALSE,glm::value_ptr(m_matriceNormal));
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::creerMesh(GLuint _nbVertice, GLuint _nbElement, glm::vec3* _position, glm::vec3* _couleur, glm::vec3* _normal, glm::vec2* _textureCoord, GLuint* _indices)
{
    m_nbVertice = _nbVertice;
    m_nbElement = _nbElement;

    initializeOpenGLFunctions();

    if(_position == NULL) m_positionPresent = false;
    if(_couleur == NULL) m_couleurPresent = false;
    if(_normal == NULL) m_normalPresent = false;
    if(_textureCoord == NULL) m_textureCoordPresent = false;
    if(_indices == NULL) m_eboPresent = false;

    //VBO
    m_VBOPosition = creerBuffer(GL_ARRAY_BUFFER,m_nbVertice*sizeof(glm::vec3),_position);
    m_VBOCouleur = creerBuffer(GL_ARRAY_BUFFER,m_nbVertice*sizeof(glm::vec3),_couleur);
    m_VBONormal = creerBuffer(GL_ARRAY_BUFFER,m_nbVertice*sizeof(glm::vec3),_normal);
    m_VBOTextureCoord = creerBuffer(GL_ARRAY_BUFFER,m_nbVertice*sizeof(glm::vec2),_textureCoord);
    m_EBO = creerBuffer(GL_ELEMENT_ARRAY_BUFFER,m_nbElement*sizeof(GLuint),_indices);

    //std::cout << m_VBOPosition << " " << m_VBOCouleur << " " << m_VBONormal << " " << m_VBOTextureCoord << std::endl;

    //VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    {
        if(m_positionPresent) creerVAODepuisBuffer(m_VBOPosition,3,m_attribPosition);
        if(m_couleurPresent) creerVAODepuisBuffer(m_VBOCouleur,3,m_attribCouleur);
        if(m_normalPresent) creerVAODepuisBuffer(m_VBONormal,3,m_attribNormal);
        if(m_textureCoordPresent) creerVAODepuisBuffer(m_VBOTextureCoord,2,m_attribTextureCoord);
    }
    glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::dessiner()
{
    glBindVertexArray(m_VAO);
    {
        if(m_EBO==0)
        {
            glDrawArrays(m_mode,0,m_nbVertice);
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_EBO);
            {
                glDrawElements(m_mode,m_nbElement,GL_UNSIGNED_INT,0);
            }
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        }
    }
    glBindVertexArray(0);
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::multiplierMatriceMonde(glm::mat4 _matrice)
{
    m_matriceMonde = m_matriceMonde * _matrice;
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::modifierCentre(glm::vec3 _centre)
{
    m_matriceMonde[3].x += _centre.x;
    m_matriceMonde[3].y += _centre.y;
    m_matriceMonde[3].z += _centre.z;
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::translation(glm::vec3 _nouvellePosition)
{
    m_matriceMonde[3].x = _nouvellePosition.x;
    m_matriceMonde[3].y = _nouvellePosition.y;
    m_matriceMonde[3].z = _nouvellePosition.z;

    m_matriceNormal = glm::inverseTranspose(m_matriceMonde);
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::rotation(float _angle,glm::vec3 _axe)
{
    m_matriceMonde = glm::rotate(m_matriceMonde,glm::radians(_angle),_axe);

    m_matriceNormal = glm::inverseTranspose(m_matriceMonde);
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::modifMode(GLenum _mode)
{
    m_mode = _mode;
}

//----------------------------------------------------------------------------------------------------------------------------
glm::mat4 Mesh::avoirMatriceMonde() const
{
    return m_matriceMonde;
}

//----------------------------------------------------------------------------------------------------------------------------
glm::vec3 Mesh::avoirPosition() const
{
    glm::vec3 vec;

    vec.x = m_matriceMonde[3].x;
    vec.y = m_matriceMonde[3].y;
    vec.z = m_matriceMonde[3].z;

    return vec;
}

//----------------------------------------------------------------------------------------------------------------------------
GLuint Mesh::creerBuffer(GLenum _type, GLuint _taille, GLvoid* _donnees)
{
    GLuint vbo = 0;

    if(_donnees != NULL)
    {
        glGenBuffers(1,&vbo);
        glBindBuffer(_type,vbo);
        {
            glBufferData(_type,_taille,_donnees,GL_STATIC_DRAW);
        }
        glBindBuffer(_type,0);
    }

    return vbo;
}

//----------------------------------------------------------------------------------------------------------------------------
void Mesh::creerVAODepuisBuffer(GLuint _buffer, GLuint _taille, GLuint _attribut)
{
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glEnableVertexAttribArray(_attribut);
    glVertexAttribPointer(_attribut,_taille, GL_FLOAT, GL_FALSE, 0, 0);
}
