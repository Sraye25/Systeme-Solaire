#include "fenetre.h"

Fenetre::Fenetre() :
    m_programmePlanete(),
    m_programmeSoleil(),
    m_programmeCercle(),
    m_programmeBillboard(),
    m_mesh(),
    m_camera(),
    m_soleil(0.f,0.f,0.f,4.5*RAYON),
    m_texSoleil(),
    m_lune(2*VITESSE_REVO,2.0f,0.001*VITESSE_ROTA,0.1*RAYON),
    m_texLune(),
    m_billboardSoleil(),
    m_billboardLune(),
    m_lumiere(),
    m_scenegraph(&m_soleil),
    m_positionCamera(glm::vec3(0.f,0.f,-20.f)),
    m_positionAngle(glm::vec3(0.f,0.f,0.f))
{
    //Planetes
    m_planete[0].modifierParametre(VITESSE_REVO,8.0*DISTANCE_SOL,0.0002*VITESSE_ROTA,0.17*RAYON);
    m_planete[1].modifierParametre(0.42*VITESSE_REVO,14*DISTANCE_SOL,-0.0001*VITESSE_ROTA,0.42*RAYON);
    m_planete[2].modifierParametre(0.26*VITESSE_REVO,20*DISTANCE_SOL,0.037*VITESSE_ROTA,0.44*RAYON);
    m_planete[3].modifierParametre(0.14*VITESSE_REVO,30*DISTANCE_SOL,0.02*VITESSE_ROTA,0.24*RAYON);
    m_planete[4].modifierParametre(0.02*VITESSE_REVO,45*DISTANCE_SOL,0.5*VITESSE_ROTA,2*RAYON);
    m_planete[5].modifierParametre(0.008*VITESSE_REVO,60*DISTANCE_SOL,0.16*VITESSE_ROTA,1.6*RAYON);
    m_planete[6].modifierParametre(0.002*VITESSE_REVO,75*DISTANCE_SOL,-0.22*VITESSE_ROTA,0.7*RAYON);
    m_planete[7].modifierParametre(0.001*VITESSE_REVO,95*DISTANCE_SOL,0.20*VITESSE_ROTA,0.7*RAYON);

    //Cercle
    m_cerclePlanete[0].modifRayon(8.0*DISTANCE_SOL);
    m_cerclePlanete[1].modifRayon(14*DISTANCE_SOL);
    m_cerclePlanete[2].modifRayon(20*DISTANCE_SOL);
    m_cerclePlanete[3].modifRayon(30*DISTANCE_SOL);
    m_cerclePlanete[4].modifRayon(45*DISTANCE_SOL);
    m_cerclePlanete[5].modifRayon(60*DISTANCE_SOL);
    m_cerclePlanete[6].modifRayon(75*DISTANCE_SOL);
    m_cerclePlanete[7].modifRayon(95*DISTANCE_SOL);

    //Ajouter au scene graphe
    SceneNoeud* racine = m_scenegraph.avoirRacine();
    for(int i=0;i<8;i++) racine->ajouterEnfant(&m_planete[i]);
    racine->avoirEnfant(2)->ajouterEnfant(&m_lune);

    //Camera
    m_camera.associer(&m_lune);

    m_timer.start();
    setAnimating(true);
}

//----------------------------------------------------------------------------------------------------------------------------
Fenetre::~Fenetre()
{
    m_programmePlanete.detruire();
    m_programmeSoleil.detruire();
    m_programmeCercle.detruire();
    m_programmeBillboard.detruire();

    m_soleil.detruire();
    m_texSoleil.detruire();
    m_billboardSoleil.detruire();

    m_lune.detruire();
    m_texLune.detruire();
    m_billboardLune.detruire();

    for(int i=0; i<8; i++)
    {
        m_planete[i].detruire();
        m_texPlanete[i].detruire();
        m_cerclePlanete[i].detruire();
        m_billboard[i].detruire();
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void Fenetre::initialize()
{
    std::string extension;

    #ifdef NOM_RUSSE
        extension = "r.png";
    #else
        extension = ".png";
    #endif

    std::string lumiere[3], material[4];
    std::cout << "GL Version : " << (char*)glGetString(GL_VERSION) << std::endl;

    lumiere[0] = "u_light.vAmbiant";
    lumiere[1] = "u_light.vDiffuse";
    lumiere[2] = "u_light.vSpecular";

    material[0] = "u_material.vAmbiant";
    material[1] = "u_material.vDiffuse";
    material[2] = "u_material.vSpecular";
    material[3] = "u_material.fSpecPower";

    m_programmePlanete.creerDepuisFichier("VS_planete.glsl","FS_planete.glsl");
    m_programmeSoleil.creerDepuisFichier("VS_soleil.glsl","FS_soleil.glsl");
    m_programmeCercle.creerDepuisFichier("VS_cercle.glsl","FS_cercle.glsl");
    m_programmeBillboard.creerDepuisFichier("VS_billboard.glsl","FS_billboard.glsl","GS_billboard.glsl");

    m_camera.avoirUniformLocalisation(m_programmeCercle,"matrice_vue","matrice_projection","");
    m_camera.avoirUniformLocalisation(m_programmeSoleil,"matrice_vue","matrice_projection","");
    m_camera.avoirUniformLocalisation(m_programmeBillboard,"matrice_vue","matrice_projection","position_camera");
    m_camera.avoirUniformLocalisation(m_programmePlanete,"matrice_vue","matrice_projection","position_camera");

    m_lumiere.avoirUniformLocalisation(m_programmePlanete,lumiere,material,"position_lumiere");

    m_soleil.avoirAttributLocalisation(m_programmeSoleil,"vextexPosition","","vertexNormal","vextexTexcoor");
    m_soleil.avoirUniformLocalisation(m_programmeSoleil,"matrice_monde","matrice_normal");
    m_texSoleil.avoirUniformLocalisation(m_programmeSoleil,"texture");
    m_billboardSoleil.avoirAttributLocalisation(m_programmeBillboard,"position");
    m_billboardSoleil.avoirUniformLocalisation(m_programmeBillboard,"texture","matrice_monde");

    m_lune.avoirAttributLocalisation(m_programmePlanete,"vextexPosition","","vertexNormal","vextexTexcoor");
    m_lune.avoirUniformLocalisation(m_programmePlanete,"matrice_monde","matrice_normal");
    m_texLune.avoirUniformLocalisation(m_programmePlanete,"texture");
    m_billboardLune.avoirAttributLocalisation(m_programmeBillboard,"position");
    m_billboardLune.avoirUniformLocalisation(m_programmeBillboard,"texture","matrice_monde");

    for(int i=0;i<8;i++)
    {
        m_planete[i].avoirAttributLocalisation(m_programmePlanete,"vextexPosition","","vertexNormal","vextexTexcoor");
        m_planete[i

                ].avoirUniformLocalisation(m_programmePlanete,"matrice_monde","matrice_normal");
        m_texPlanete[i].avoirUniformLocalisation(m_programmePlanete,"texture");

        m_cerclePlanete[i].avoirAttributLocalisation(m_programmeCercle,"vextexPosition","","","");
        m_cerclePlanete[i].avoirUniformLocalisation(m_programmeCercle,"matrice_monde","");

        m_billboard[i].avoirAttributLocalisation(m_programmeBillboard,"position");
        m_billboard[i].avoirUniformLocalisation(m_programmeBillboard,"texture","matrice_monde");
    }

    m_camera.creer(width(),height());
    m_lumiere.creer(glm::vec3(0.f,0.f,0.f));

    m_soleil.creer();
    m_texSoleil.creer("soleil.png",QImage::Format_RGB888);
    m_billboardSoleil.creer("billboard_soleil"+extension,&m_soleil,glm::vec3(0.f,0.f,7.f));

    m_lune.creer();
    m_texLune.creer("lune.png",QImage::Format_RGB888);
    m_billboardLune.creer("billboard_lune"+extension,&m_lune,glm::vec3(0.f,0.f,3.5f));

    for(int i=0;i<8;i++)
    {
        std::stringstream ss; ss << i;
        std::string str; ss>>str;

        m_planete[i].creer();
        m_texPlanete[i].creer(str+".png",QImage::Format_RGB888);
        m_cerclePlanete[i].creer();

        m_billboard[i].creer("billboard_"+str+extension,&m_planete[i],glm::vec3(0.f,0.f,3.5f));
    }

    update();
}

//----------------------------------------------------------------------------------------------------------------------------
void Fenetre::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glPointSize(80.0f);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glCullFace(GL_BACK);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_programmePlanete.bind();
    {
        m_camera.envoyerUniformVersGPU();
        m_lumiere.envoyerUniformVersGPU();

        m_lune.envoyerUniformVersGPU();
        m_texLune.mettreTextureUnit(0);
        m_texLune.envoyerUniformVersGPU();
        m_lune.dessiner();

        for(int i=0;i<8;i++)
        {
            m_planete[i].envoyerUniformVersGPU();
            m_texPlanete[i].mettreTextureUnit(0);
            m_texPlanete[i].envoyerUniformVersGPU();
            m_planete[i].dessiner();
        }

    }
    m_programmePlanete.unbind();
    m_programmeSoleil.bind();
    {
        m_camera.envoyerUniformVersGPU();

        m_soleil.envoyerUniformVersGPU();
        m_texSoleil.mettreTextureUnit(0);
        m_texSoleil.envoyerUniformVersGPU();
        m_soleil.dessiner();
    }
    m_programmeSoleil.unbind();
    m_programmeCercle.bind();
    {
        m_camera.envoyerUniformVersGPU();

        for(int i=0;i<8;i++)
        {
            m_cerclePlanete[i].envoyerUniformVersGPU();
            m_cerclePlanete[i].dessiner();
        }
    }
    m_programmeCercle.unbind();
    m_programmeBillboard.bind();
    {
        m_camera.envoyerUniformVersGPU();

        m_billboardSoleil.mettreTextureUnit(0);
        m_billboardSoleil.envoyerUniformVersGPU();
        m_billboardSoleil.dessiner();

        m_billboardLune.mettreTextureUnit(0);
        m_billboardLune.envoyerUniformVersGPU();
        m_billboardLune.dessiner();

        for(int i=0;i<8;i++)
        {
            m_billboard[i].mettreTextureUnit(0);
            m_billboard[i].envoyerUniformVersGPU();
            m_billboard[i].dessiner();
        }
    }
    m_programmeBillboard.unbind();
}

//----------------------------------------------------------------------------------------------------------------------------
void Fenetre::update()
{
    float fTimeElapsed = (float) m_timer.elapsed();

    m_soleil.deplacer(fTimeElapsed);
    m_lune.deplacer(fTimeElapsed);
    for(int i=0;i<8;i++)
    {
        m_planete[i].deplacer(fTimeElapsed);
    }

    m_scenegraph.miseAJour();
    m_camera.miseAJour(fTimeElapsed);
}

//----------------------------------------------------------------------------------------------------------------------------
void Fenetre::resizeEvent(QResizeEvent * event)
{
    m_camera.redimensionnementFenetre(width(),height());
}

//----------------------------------------------------------------------------------------------------------------------------
void Fenetre::keyPressEvent(QKeyEvent* event)
{
    m_camera.evenementClavier(event);
}

//----------------------------------------------------------------------------------------------------------------------------
void Fenetre::mousePressEvent(QMouseEvent* event)
{
    //m_camera.evenementSouris(event);
}


