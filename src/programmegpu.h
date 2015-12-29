#ifndef PROGRAMMEGPU_H
#define PROGRAMMEGPU_H

#include <string>
#include <iostream>
#include <fstream>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <QOpenGLFunctions_3_3_Core>
#define SHADER_DIR "shader/"

class ProgrammeGPU : protected QOpenGLFunctions_3_3_Core
{
    public:
        //Constructeur
        ProgrammeGPU();

        //Détruire
        void detruire();

        //Créer un programme GPU depuis des fichiers
        void creerDepuisFichier(const std::string& _VSchemin, const std::string& _FSchemin, const std::string &_GSchemin = "");

        //Binder le programme
        void bind();

        //Debinder le programme
        void unbind();

        //Avoir la localisation d'un uniforme
        GLuint avoirUniformLocation(const std::string& _nom);

        //Avoir la localisation d'un attribute
        GLuint avoirAttributeLocation(const std::string& _nom);

    private:
        //Afficher les erreurs de compil des shaders
        bool afficherShaderCompileInfo( GLuint shaderID, const std::string& message);

        GLuint m_idProgramme;
        GLuint m_idFS;
        GLuint m_idVS;
        GLuint m_idGS;

        bool m_utiliser_gs;
};

//Lire un ficher et le renvoyer en string
std::string lireFichierSource(const std::string& _chemin);

void afficherMatrice44(glm::mat4 matrice);

#endif // PROGRAMMEGPU_H
