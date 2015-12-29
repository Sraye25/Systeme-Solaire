#ifndef SOURCELUMIERE_H
#define SOURCELUMIERE_H

#include <QOpenGLFunctions_3_3_Core>
#include "programmegpu.h"

struct LightProperties
{
    glm::vec3   m_vAmbiant;
    glm::vec3   m_vDiffuse;
    glm::vec3   m_vSpecular;

    LightProperties()
    :   m_vAmbiant  ( 0.15f )
    ,   m_vDiffuse  ( 1.f, 1.f, 1.f )
    ,   m_vSpecular (1.0f, 1.0f, 1.0f)
    {}
};

struct MaterialProperties
{
    glm::vec3   m_vAmbiant;
    glm::vec3   m_vDiffuse;
    glm::vec3   m_vSpecular;
    float       m_fSpecularPower;

    MaterialProperties()
    :   m_vAmbiant      ( 0.1f, 0.4f, 0.4f )
    ,   m_vDiffuse      ( 0.3f, 0.4f, 1.0f )
    ,   m_vSpecular     ( 0.1f, 0.1f, 0.1f )
    ,   m_fSpecularPower( 1.f )
    {}
};

class SourceLumiere : protected QOpenGLFunctions_3_3_Core
{
    public:
        //Constructeur
        SourceLumiere();

        //Creer
        void creer(glm::vec3 _position = glm::vec3(0,0,0));

        //Avoir uniforme
        void avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nomLumiereProp[3], std::string _nomMaterialProp[4], std::string _nomPos);

        //Envoyer au GPU
        void envoyerUniformVersGPU();

        //Deplacer lumieres
        void translation(glm::vec3 _nouvelle_coord);

        //Changer Propriete Lumiere
        void changerProprietesLumiere(glm::vec3 _ambiant, glm::vec3 _diffuse, glm::vec3 _specular);

        //Changer Propriete Materiaux
        void changerProprietesMateriaux(glm::vec3 _ambiant, glm::vec3 _diffuse, glm::vec3 _specular, float _puissance_specular);


    private:

        glm::vec3 m_position;
        GLuint m_uniformPosition;

        LightProperties m_lumiereProp;
        GLuint m_uniformLumiereProp[3];

        MaterialProperties m_materialProp;
        GLuint m_uniformMaterialProp[4];
};

#endif // SOURCELUMIERE_H
