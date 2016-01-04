#include "scenegraph.h"

SceneNoeud::SceneNoeud(Mesh* _mesh):
    m_mesh(_mesh)
   ,m_enfants()
{
}

//----------------------------------------------------------------------------------------------------------------------------
SceneNoeud::~SceneNoeud()
{
    for(unsigned i=0;i<m_enfants.size();i++)
    {
        delete m_enfants[i];
        m_enfants[i] = NULL;
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void SceneNoeud::ajouterEnfant(Mesh* _mesh)
{
    SceneNoeud* noeud = new SceneNoeud(_mesh);
    m_enfants.push_back(noeud);
}

//----------------------------------------------------------------------------------------------------------------------------
SceneNoeud* SceneNoeud::avoirEnfant(unsigned int i) const
{
    SceneNoeud* res = NULL;
    if(i < m_enfants.size()) res = m_enfants[i];
    return res;
}

//----------------------------------------------------------------------------------------------------------------------------
void SceneNoeud::miseAJour(glm::vec3 _positionCentre)
{
    m_mesh->modifierCentre(_positionCentre);
    glm::vec3 vec = m_mesh->avoirPosition();

    //Mise à jour de la matrice referentielle des enfants
    for(unsigned int i=0;i<m_enfants.size();i++)
    {
        //std::cout << m_enfants.size() << std::endl;
        m_enfants[i]->miseAJour(vec);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------

SceneGraph::SceneGraph(Mesh* _meshPrincipal)
{
    m_racine = new SceneNoeud(_meshPrincipal);
}

//----------------------------------------------------------------------------------------------------------------------------
SceneGraph::~SceneGraph()
{
    delete m_racine;
    m_racine = NULL;
}

//----------------------------------------------------------------------------------------------------------------------------
SceneNoeud* SceneGraph::avoirRacine() const
{
    return m_racine;
}

//----------------------------------------------------------------------------------------------------------------------------
void SceneGraph::miseAJour()
{
    m_racine->miseAJour(glm::vec3(0.0f,0.0f,0.0f));
}
