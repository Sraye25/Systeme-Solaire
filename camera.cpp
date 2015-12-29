#include "camera.h"

Camera::Camera(Astre* _lune) :
    m_matriceVue(glm::mat4(1.0f)),
    m_matriceProjection(glm::mat4(1.0f)),
    m_position(glm::vec3(0.f,0.f,0.f)),
    m_rayon(150.0f),
    m_anglePhi(250),
    m_angleTheta(10),
    m_uniformeMatriceVue(0),
    m_uniformeMatriceProjection(0),
    m_uniformePosition(0),
    m_astre(_lune),
    m_mode(SPHERIQUE)
{
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::creer(float largEcran, float hautEcran)
{
    const glm::vec3 vEye(0.f,0.f,5.f);
    const glm::vec3 vUp(0.f,1.f,0.f);
    //const glm::vec3 vFront(0.f,0.f,-1.f);

    initializeOpenGLFunctions();

    majCoordonneeSpherique();
    redimensionnementFenetre(largEcran,hautEcran);
}

//----------------------------------------------------------------------------------------------------------------------------
/*void Camera::translation(glm::vec3 _nouvellePosition)
{
    m_matriceVue[3].x = _nouvellePosition.x;
    m_matriceVue[3].y = _nouvellePosition.y;
    m_matriceVue[3].z = _nouvellePosition.z;

    m_position = _nouvellePosition;
}*/

//----------------------------------------------------------------------------------------------------------------------------
void Camera::redimensionnementFenetre(float largEcran, float hautEcran)
{
    m_matriceProjection = glm::perspective(glm::radians(45.f),largEcran/hautEcran,0.1f,250.f);
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nomMatriceVue, std::string _nomMatriceProj, std::string _nomPos)
{
    m_uniformeMatriceVue = _prog.avoirUniformLocation(_nomMatriceVue);
    m_uniformeMatriceProjection = _prog.avoirUniformLocation(_nomMatriceProj);

    m_uniformePosition = _prog.avoirUniformLocation(_nomPos);
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::envoyerUniformVersGPU()
{
    glUniformMatrix4fv(m_uniformeMatriceProjection,1,GL_FALSE,glm::value_ptr(m_matriceProjection));
    glUniformMatrix4fv(m_uniformeMatriceVue,1,GL_FALSE,glm::value_ptr(m_matriceVue));
    glUniform3fv(m_uniformePosition,1,glm::value_ptr(m_position));
}

//----------------------------------------------------------------------------------------------------------------------------
glm::mat4 Camera::avoirMatriceVue() const
{
    return m_matriceVue;
}

//----------------------------------------------------------------------------------------------------------------------------
glm::mat4 Camera::avoirMatriceProjection() const
{
    return m_matriceProjection;
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::evenementSouris(QMouseEvent *ev)
{

}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::evenementClavier(QKeyEvent *ev)
{
    if(QEvent::KeyPress == ev->type())
    {
        float vitesse  = 1.f;
        switch(ev->key())
        {
            case Qt::Key_L:
                switch (m_mode)
                {
                    case SPHERIQUE:
                        m_mode = LUNE;
                    break;
                    case LUNE:
                        m_mode = SOLEIL;
                    break;
                    case SOLEIL:
                        m_mode = SPHERIQUE;
                    break;
                }
            break;

            case Qt::Key_Minus:
                m_rayon -= vitesse;
            break;
            case Qt::Key_Plus:
                m_rayon += vitesse;
            break;

            case Qt::Key_Left:
                m_anglePhi -= vitesse;
            break;
            case Qt::Key_Right:
                m_anglePhi += vitesse;
            break;
            case Qt::Key_Up:
                m_angleTheta += vitesse;
            break;
            case Qt::Key_Down:
                m_angleTheta -= vitesse;
            break;
        }

        if(m_mode == SPHERIQUE) majCoordonneeSpherique();
        if(m_mode == SOLEIL) majCoordonneeSoleil();
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::miseAJour(float _temps)
{
    if(m_mode == LUNE)
    {
        majCoordonneeLune(_temps);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::associer(Astre* _astre)
{
    m_astre = _astre;
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::majCoordonneeSpherique()
{
    if(m_angleTheta <= -90) m_angleTheta = -89;
    if(m_angleTheta >= 90) m_angleTheta = 89;
    if(m_anglePhi < 0) m_anglePhi = 360;
    if(m_anglePhi > 360) m_anglePhi = 0;

    m_position.x = m_rayon * cos(glm::radians(m_angleTheta)) * sin(glm::radians(m_anglePhi));
    m_position.y = m_rayon * sin(glm::radians(m_angleTheta));
    m_position.z = m_rayon * cos(glm::radians(m_angleTheta)) * cos(glm::radians(m_anglePhi));

    m_matriceVue = glm::lookAtRH(m_position,glm::vec3(0.f,0.f,0.f),glm::vec3(0.f,1.f,0.f));
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::majCoordonneeLune(float _temps)
{
    if(m_astre == NULL)
    {
        m_mode = SPHERIQUE;
    }
    else
    {
        glm::vec3 vecteur;
        glm::vec3 posLune = m_astre->avoirPosition();
        float vitLune = m_astre->avoirVitesseRotation();
        float rayonLune = m_astre->avoirRayon();

        //Calcul d'un position
        m_position.x = posLune.x;
        m_position.y = 0.0;
        m_position.z = posLune.z;

        //Calcul du vecteur
        vecteur.x = posLune.x + rayonLune*cos(vitLune*_temps);
        vecteur.y = 0.0;
        vecteur.z = posLune.z + rayonLune*sin(vitLune*_temps);

        m_matriceVue = glm::lookAtRH(m_position,vecteur,glm::vec3(0.f,1.f,0.f));
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void Camera::majCoordonneeSoleil()
{
    glm::vec3 vecteur;

    //Calcul d'un position
    m_position.x = 0.0;
    m_position.y = 0.0;
    m_position.z = 0.0;

    //Calcul du vecteur
    vecteur.x = cos(glm::radians(m_anglePhi));
    vecteur.y = 0.0;
    vecteur.z = sin(glm::radians(m_anglePhi));

    m_matriceVue = glm::lookAtRH(m_position,vecteur,glm::vec3(0.f,1.f,0.f));
}
