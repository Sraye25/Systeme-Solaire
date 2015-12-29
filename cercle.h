#ifndef CERCLE_H
#define CERCLE_H

#include "mesh.h"

#define NB_SEGM 90

class Cercle : public Mesh
{
    public:
        //Constructeur
        Cercle(float _rayon = 0.0);

        //Changer m_rayon
        void modifRayon(float _rayon);

        //Creer
        void creer();

    private:
        float m_rayon;
};

#endif // CERCLE_H
