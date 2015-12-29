#ifndef MESH_H
#define MESH_H

#include <QOpenGLFunctions_3_3_Core>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <string>

#include "programmegpu.h"

class Mesh : protected QOpenGLFunctions_3_3_Core
{
    public:
        //Constructeur
        Mesh();

        //detruire un mesh
        void detruire();

        //Activer Attribut
        void activerAttribut(bool position, bool couleur, bool normal, bool coordTex, bool ebo);

        //Avoir attribut
        void avoirAttributLocalisation(ProgrammeGPU& _prog, std::string _nomPos, std::string _nomCoul, std::string _nomNorm, std::string _nomText);

        //Avoir uniforme
        void avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nomMatriceMonde, std::string _nomMatriceNormal);

        //Envoyer uniforme
        void envoyerUniformVersGPU();

        //Creer un mesh
        void creerMesh(GLuint _nbVertice, GLuint _nbElement, glm::vec3* _position, glm::vec3* _couleur, glm::vec3* _normal, glm::vec2* _textureCoord, GLuint* _indices);

        //Dessiner
        void dessiner();

        //Multiplier la matrice monde par une autre matrice
        virtual void multiplierMatriceMonde(glm::mat4 _matrice);

        //Modifier centre autour duquel la planéte tourne
        virtual void modifierCentre(glm::vec3 _centre);

        //Translation
        virtual void translation(glm::vec3 _nouvellePosition);

        //Rotation
        virtual void rotation(float _angle,glm::vec3 _axe);

        //Modifier le mode de dessin
        void modifMode(GLenum _mode);

        //Avoir matrice monde
        glm::mat4 avoirMatriceMonde() const;

        //Avoir position
        glm::vec3 avoirPosition() const;

    protected:

        //Creer un VBO
        GLuint creerBuffer(GLenum _type, GLuint _taille, GLvoid* _donnees);

        //Creer Attribute VAO depuis VBO
        void creerVAODepuisBuffer(GLuint _buffer, GLuint _taille, GLuint _attribut);

        GLuint m_nbVertice;
        GLuint m_nbElement;

        GLuint m_VAO;

        GLuint m_VBOPosition;
        GLuint m_VBOCouleur;
        GLuint m_VBONormal;
        GLuint m_VBOTextureCoord;

        GLuint m_EBO;

        GLuint m_attribPosition;
        GLuint m_attribCouleur;
        GLuint m_attribNormal;
        GLuint m_attribTextureCoord;

        bool m_positionPresent;
        bool m_couleurPresent;
        bool m_normalPresent;
        bool m_textureCoordPresent;
        bool m_eboPresent;

        glm::mat4 m_matriceMonde;
        glm::mat4 m_matriceNormal;

        GLuint m_uniformMatrice;
        GLuint m_uniformNormal;

        GLenum m_mode;
};

#endif // MESH_H
