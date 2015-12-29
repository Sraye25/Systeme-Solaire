#ifndef Billboard_H
#define Billboard_H

#include <QOpenGLFunctions_3_3_Core>
#include "texture.h"
#include "astre.h"

class Billboard : protected Texture
{
    public:
        //Constructeur
        Billboard();

        //Creer
        void creer(std::string _nomFichier, Astre* _astre, glm::vec3 _position);

        //Detruire
        void detruire();

        //Associer à un astre
        void associer(Astre* _astre);

        //Dessiner
        void dessiner();

        //Avoir uniforme
        void avoirUniformLocalisation(ProgrammeGPU& _prog, std::string _nom, std::string _nomMatriceMonde);

        //Avoir attribut
        void avoirAttributLocalisation(ProgrammeGPU& _prog, std::string _position);

        //Mettre le texture unit
        void mettreTextureUnit(int _idTextureUnit);

        //Envoyer au gpu la texture
        void envoyerUniformVersGPU();

    private:

        Astre* m_astre;
        glm::vec3 m_position;

        glm::mat4 m_matriceMonde;
        GLuint m_uniformMatriceMonde;

        GLuint m_attributPosition;
        GLuint m_VBOPosition;
        GLuint m_VAO;
};

#endif // Billboard_H
