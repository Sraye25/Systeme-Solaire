#include "cercle.h"

Cercle::Cercle(float _rayon) : Mesh(), m_rayon(_rayon)
{
    //Cercle = suie de segment qui boucle
    modifMode(GL_LINE_LOOP);
}

//----------------------------------------------------------------------------------------------------------------------------
void Cercle::modifRayon(float _rayon)
{
    m_rayon = _rayon;
}

//----------------------------------------------------------------------------------------------------------------------------
void Cercle::creer()
{
    //Generation du cercle
    GLuint nbVertices = NB_SEGM;

    glm::vec3* position = new glm::vec3[nbVertices];

    double ecart = 360/NB_SEGM;

    for(unsigned int i=0;i<nbVertices;i++)
    {
        position[i].x = m_rayon * cos(glm::radians(ecart*i));
        position[i].y = 0.0;
        position[i].z = m_rayon * sin(glm::radians(ecart*i));
    }

    creerMesh(nbVertices,0,position,NULL,NULL,NULL,NULL);

    delete[] position;
}
