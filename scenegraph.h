#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <vector>

#include "mesh.h"
#include "programmegpu.h"

class SceneNoeud
{
    public:
        //Constructeur
        SceneNoeud(Mesh* _mesh);

        //Destructeur
        ~SceneNoeud();

        //Ajouter un enfant
        void ajouterEnfant(Mesh* _mesh);

        //Avoir enfant
        SceneNoeud* avoirEnfant(unsigned int i) const;

        //Mise à jour
        void miseAJour(glm::vec3 _positionCentre);

    private:

        Mesh* m_mesh;
        std::vector<SceneNoeud*> m_enfants;

};

class SceneGraph
{
    public:
        //Constructeur
        SceneGraph(Mesh* _meshPrincipal);

        //Destructeur
        ~SceneGraph();

        //Avoir noeud racine
        SceneNoeud* avoirRacine() const;

        //Mise à jour
        void miseAJour();

    private:

        SceneNoeud* m_racine;
};

#endif // SCENEGRAPH_H
