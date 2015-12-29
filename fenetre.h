#ifndef FENETRE_H
#define FENETRE_H

#include <QKeyEvent>
#include <QTime>
#include <QWidget>
#include <sstream>
#include <QResizeEvent>

#include "openglwindow.h"
#include "astre.h"
#include "camera.h"
#include "programmegpu.h"
#include "sourcelumiere.h"
#include "scenegraph.h"
#include "cercle.h"
#include "billboard.h"

#define VITESSE_REVO 0.001
#define VITESSE_ROTA 0.6
#define DISTANCE_SOL 1
#define RAYON 1.3

#define NOM_RUSSE

class Fenetre : public OpenGLWindow
{
    Q_OBJECT
    public:
        Fenetre();
        virtual ~Fenetre();
        void initialize();
        void render();
        void update();
        void resizeEvent(QResizeEvent * event);
        void keyPressEvent(QKeyEvent* event);
        void mousePressEvent(QMouseEvent* event);

    private:

        void majCameraObjet();

        ProgrammeGPU m_programmePlanete;
        ProgrammeGPU m_programmeSoleil;
        ProgrammeGPU m_programmeCercle;
        ProgrammeGPU m_programmeBillboard;

        Mesh m_mesh;
        Camera m_camera;

        Astre m_soleil;
        Texture m_texSoleil;
        Astre m_planete[8];
        Texture m_texPlanete[8];
        Astre m_lune;
        Texture m_texLune;

        Cercle m_cerclePlanete[8];

        Billboard m_billboard[8];
        Billboard m_billboardSoleil;
        Billboard m_billboardLune;

        SourceLumiere m_lumiere;

        SceneGraph m_scenegraph;

        glm::vec3 m_positionCamera;
        glm::vec3 m_positionAngle;

        QTime m_timer;
};

#endif // FENETRE_H
