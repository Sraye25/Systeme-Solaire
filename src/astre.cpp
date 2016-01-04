#include "astre.h"

Astre::Astre() :
    Mesh(),
    m_rayonDeplacement(0.f),
    m_vitesseDeplacement(0.f),
    m_vitesseRotation(0.f),
    m_rayon(0.f)
{

}

//----------------------------------------------------------------------------------------------------------------------------
Astre::Astre(float _vitesseDeplacement, float _rayonDeplacement, float _vitesseRotation, float _rayon) :
    Mesh(),
    m_rayonDeplacement(_rayonDeplacement),
    m_vitesseDeplacement(_vitesseDeplacement),
    m_vitesseRotation(_vitesseRotation),
    m_rayon(_rayon)
{
}

//----------------------------------------------------------------------------------------------------------------------------
void Astre::modifierParametre(float _vitesseDeplacement, float _rayonDeplacement, float _vitesseRotation, float _rayon)
{
    m_rayonDeplacement = _rayonDeplacement;
    m_vitesseDeplacement = _vitesseDeplacement;
    m_vitesseRotation = _vitesseRotation;
    m_rayon = _rayon;
}

//----------------------------------------------------------------------------------------------------------------------------
void Astre::creer()
{
    GLuint nbVertices = 0;
    GLuint nbElements = 0;

    nbVertices = NB_MERIDIEN * NB_PARALLELE;
    nbElements = (NB_MERIDIEN-1)*(NB_PARALLELE-1)*2*3;

    glm::vec3* position = new glm::vec3[nbVertices];
    glm::vec3* normal = new glm::vec3[nbVertices];
    glm::vec2* coordTex = new glm::vec2[nbVertices];
    GLuint* indices = new GLuint[nbElements];

    //On génere la sphere et on crée le mesh
    initSphere(m_rayon,nbVertices,position,normal,coordTex,indices);
    creerMesh(nbVertices,nbElements,position,NULL,normal,coordTex,indices);

    delete[] position;
    delete[] normal;
    delete[] coordTex;
    delete[] indices;
}

//----------------------------------------------------------------------------------------------------------------------------
void Astre::deplacer(float _temps)
{
    //On tourne l'affichage de la planete
    m_matriceMonde = glm::mat4(1.0f);
    m_matriceMonde = glm::rotate(m_matriceMonde,glm::radians(-90.0f),glm::vec3(1.0f,0.0f,0.0f));

    //Calcul des nouvelle coordonée
    m_matriceMonde[3].x = m_rayonDeplacement*cos(m_vitesseDeplacement*_temps);
    m_matriceMonde[3].y = 0.f;
    m_matriceMonde[3].z = m_rayonDeplacement*sin(m_vitesseDeplacement*_temps);

    //Rotation sur lui-même
    m_matriceMonde = glm::rotate(m_matriceMonde,glm::radians(m_vitesseRotation*_temps),glm::vec3(0.f,0.f,1.f));
}

//----------------------------------------------------------------------------------------------------------------------------
void Astre::modifierCentre(glm::vec3 _centre)
{
    //On modifie le centre de l'astre
    m_matriceMonde[3].x += _centre.x;
    m_matriceMonde[3].y += _centre.y;
    m_matriceMonde[3].z += _centre.z;
}

//----------------------------------------------------------------------------------------------------------------------------
void Astre::multiplierMatriceMonde(glm::mat4 _matrice)
{
    //On enleve l'inclinaison
    _matrice = glm::rotate(_matrice,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));

    m_matriceMonde = m_matriceMonde * _matrice;
}

//----------------------------------------------------------------------------------------------------------------------------
float Astre::avoirRayon() const
{
    return m_rayon;
}

//----------------------------------------------------------------------------------------------------------------------------
float Astre::avoirVitesseRotation() const
{
    return m_vitesseRotation;
}

//----------------------------------------------------------------------------------------------------------------------------
void initSphere(float rayon, GLuint nbVertices, glm::vec3* position, glm::vec3* normal, glm::vec2* coordTex, GLuint* auiIndices)
{
    //Generation d'une sphère
    float a1 = (180.0/(NB_PARALLELE + 1))*M_PI/180.0;
    float a2 = (360.0/(NB_MERIDIEN - 1))*M_PI/180.0;

    uint k = 0;
    for(uint i=0;i<NB_PARALLELE;i++)
    {
        float fAngle    = - M_PI / 2.0 + a1 * ( i + 1 );
        float z         = rayon * sin( fAngle );
        float fRadius   = rayon * cos( fAngle );
        for(uint j=0;j<NB_MERIDIEN;j++)
        {
            position[k] = glm::vec3(fRadius*cos(a2*j),fRadius*sin(a2*j),z);
            coordTex[k] = glm::vec2(float(j)/NB_MERIDIEN,float(NB_PARALLELE-i)/NB_PARALLELE);
            k++;
        }
    }

    for(uint i=0;i<nbVertices;i++) normal[i] = glm::normalize(position[i]);

    k=0;
    for(uint i=0;i<(NB_PARALLELE - 1);i++)
    {
        for(uint j=0;j<(NB_MERIDIEN - 1);j++)
        {
            auiIndices[ k++ ] = NB_MERIDIEN * i + j;
            auiIndices[ k++ ] = NB_MERIDIEN * i + ( j + 1 );
            auiIndices[ k++ ] = NB_MERIDIEN * ( i + 1 ) + ( j + 1 );
            auiIndices[ k++ ] = NB_MERIDIEN * ( i + 1 ) + ( j + 1 );
            auiIndices[ k++ ] = NB_MERIDIEN * ( i + 1 ) + j;
            auiIndices[ k++ ] = NB_MERIDIEN * i + j;
        }
    }
}
