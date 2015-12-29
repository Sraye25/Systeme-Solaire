#ifndef ASTRE_H
#define ASTRE_H

#include "mesh.h"

#define NB_PARALLELE 40
#define NB_MERIDIEN 60

class Astre : public Mesh
{
    public:
        //Constructeur
        Astre();
        Astre(float _vitesseDeplacement, float _rayonDeplacement, float _vitesseRotation, float _rayon);

        //Modifier parametre astre
        void modifierParametre(float _vitesseDeplacement, float _rayonDeplacement, float _vitesseRotation, float _rayon);

        //Deplacer
        void deplacer(float _temps);

        //Deplacer centre de rotation l'astre
        void modifierCentre(glm::vec3 _centre);

        //Multiplier matrice monde
        void multiplierMatriceMonde(glm::mat4 _matrice);

        //Creer un astre
        void creer();

        //Avoir rayon
        float avoirRayon() const;

        //Avoir vitesse de rotation
        float avoirVitesseRotation() const;

    private:

        float m_rayonDeplacement;
        float m_vitesseDeplacement;
        float m_vitesseRotation;
        float m_rayon;
};

//Initialiser une sphere
void initSphere(float rayon, GLuint nbVertices, glm::vec3* position, glm::vec3* normal, glm::vec2* coordTex, GLuint* auiIndices);

#endif // ASTRE_H
