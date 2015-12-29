#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions_3_3_Core>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "astre.h"

enum Mode_Vue
{
    SPHERIQUE,
    LUNE,
    SOLEIL
};

class Camera : protected QOpenGLFunctions_3_3_Core
{
    public:
        Camera(Astre* _lune = NULL);

        //Creer la camera
        void creer(float largEcran=4, float hautEcran=3);

        //Translation
        //void translation(glm::vec3 _nouvellePosition);

        //Redimensionnement de la fenetre
        void redimensionnementFenetre(float largEcran, float hautEcran);

        //Avoir uniforme
        void avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nomMatriceVue, std::string _nomMatriceProj, std::string _nomPos);

        //Envoyer uniformes
        void envoyerUniformVersGPU();

        //Avoir Matrice Vue
        glm::mat4 avoirMatriceVue() const;

        //Avoir Matrice Projection
        glm::mat4 avoirMatriceProjection() const;

        //Bouger la camera avec la souris
        void evenementSouris(QMouseEvent *ev);

        //Bouger la camera avec le clavier
        void evenementClavier(QKeyEvent *ev);

        //Mise à jour de la camera
        void miseAJour(float _temps);

        //Associer camera à astre
        void associer(Astre* _astre);

    private:

        //Mise a jour des coord en mode Spherique
        void majCoordonneeSpherique();

        //Mise à jour des coord en mode de vue depuis la lune
        void majCoordonneeLune(float _temps);

        //Mise à jour des coord en mode de vue depuis le soleil
        void majCoordonneeSoleil();

        glm::mat4 m_matriceVue;
        glm::mat4 m_matriceProjection;
        glm::vec3 m_position;

        float m_rayon;
        float m_anglePhi;
        float m_angleTheta;

        GLuint m_uniformeMatriceVue;
        GLuint m_uniformeMatriceProjection;
        GLuint m_uniformePosition;

        Astre* m_astre;

        Mode_Vue m_mode;
};

#endif // CAMERA_H
