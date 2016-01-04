#include "sourcelumiere.h"

SourceLumiere::SourceLumiere() :
     m_position(glm::vec3(0,0,0))
    ,m_uniformPosition(0)
    ,m_lumiereProp()
    ,m_materialProp()
{
    m_uniformLumiereProp[0] = 0;
    m_uniformLumiereProp[1] = 0;
    m_uniformLumiereProp[2] = 0;

    m_uniformMaterialProp[0] = 0;
    m_uniformMaterialProp[1] = 0;
    m_uniformMaterialProp[2] = 0;
    m_uniformMaterialProp[3] = 0;
}

//----------------------------------------------------------------------------------------------------------------------------
void SourceLumiere::creer(glm::vec3 _position)
{
    initializeOpenGLFunctions();
    translation(_position);
}

//----------------------------------------------------------------------------------------------------------------------------
void SourceLumiere::avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nomLumiereProp[3], std::string _nomMaterialProp[4], std::string _nomPos)
{
    m_uniformLumiereProp[0] = _prog.avoirUniformLocation(_nomLumiereProp[0]);
    m_uniformLumiereProp[1] = _prog.avoirUniformLocation(_nomLumiereProp[1]);
    m_uniformLumiereProp[2] = _prog.avoirUniformLocation(_nomLumiereProp[2]);

    m_uniformMaterialProp[0] = _prog.avoirUniformLocation(_nomMaterialProp[0]);
    m_uniformMaterialProp[1] = _prog.avoirUniformLocation(_nomMaterialProp[1]);
    m_uniformMaterialProp[2] = _prog.avoirUniformLocation(_nomMaterialProp[2]);
    m_uniformMaterialProp[3] = _prog.avoirUniformLocation(_nomMaterialProp[3]);

    m_uniformPosition = _prog.avoirUniformLocation(_nomPos);
}

//----------------------------------------------------------------------------------------------------------------------------
void SourceLumiere::envoyerUniformVersGPU()
{
    glUniform3fv(m_uniformLumiereProp[0], 1, glm::value_ptr(m_lumiereProp.m_vAmbiant) );
    glUniform3fv(m_uniformLumiereProp[1], 1, glm::value_ptr(m_lumiereProp.m_vDiffuse) );
    glUniform3fv(m_uniformLumiereProp[2], 1, glm::value_ptr(m_lumiereProp.m_vSpecular) );

    glUniform3fv(m_uniformMaterialProp[0], 1, glm::value_ptr(m_materialProp.m_vAmbiant) );
    glUniform3fv(m_uniformMaterialProp[1], 1, glm::value_ptr(m_materialProp.m_vDiffuse) );
    glUniform3fv(m_uniformMaterialProp[2], 1, glm::value_ptr(m_materialProp.m_vSpecular) );
    glUniform1f(m_uniformMaterialProp[3], m_materialProp.m_fSpecularPower );

    glUniform3fv(m_uniformPosition, 1, glm::value_ptr( m_position ) );
}

//----------------------------------------------------------------------------------------------------------------------------
void SourceLumiere::translation(glm::vec3 _nouvelle_coord)
{
    m_position = _nouvelle_coord;
}

//----------------------------------------------------------------------------------------------------------------------------
void SourceLumiere::changerProprietesLumiere(glm::vec3 _ambiant, glm::vec3 _diffuse, glm::vec3 _specular)
{
    m_lumiereProp.m_vAmbiant = _ambiant;
    m_lumiereProp.m_vDiffuse = _diffuse;
    m_lumiereProp.m_vSpecular = _specular;
}

//----------------------------------------------------------------------------------------------------------------------------
void SourceLumiere::changerProprietesMateriaux(glm::vec3 _ambiant, glm::vec3 _diffuse, glm::vec3 _specular, float _puissance_specular)
{
    m_materialProp.m_vAmbiant = _ambiant;
    m_materialProp.m_vDiffuse = _diffuse;
    m_materialProp.m_vSpecular = _specular;
    m_materialProp.m_fSpecularPower = _puissance_specular;
}
