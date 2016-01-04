#include "programmegpu.h"

ProgrammeGPU::ProgrammeGPU()
{
    m_idProgramme = 0;
    m_idFS = 0;
    m_idVS = 0;
    m_idGS = 0;
    m_utiliser_gs = true;
}

//----------------------------------------------------------------------------------------------------------------------------
void ProgrammeGPU::detruire()
{
    glDeleteProgram(m_idProgramme);
    glDeleteShader(m_idFS);
    if(m_utiliser_gs) glDeleteShader(m_idGS);
    glDeleteShader(m_idVS);

    m_idProgramme = 0;
    m_idFS = 0;
    m_idVS = 0;
    m_idGS = 0;
}

//----------------------------------------------------------------------------------------------------------------------------
void ProgrammeGPU::creerDepuisFichier( const std::string& _VSchemin, const std::string& _FSchemin, const std::string& _GSchemin)
{
    initializeOpenGLFunctions();

    //VS
    std::string strvs = lireFichierSource(SHADER_DIR+_VSchemin);
    const char* strVS = strvs.c_str();
    m_idVS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_idVS,1,&strVS,0);
    glCompileShader(m_idVS);
    afficherShaderCompileInfo(m_idVS,_VSchemin.c_str());

    //FS
    std::string strfs = lireFichierSource(SHADER_DIR+_FSchemin);
    const char* strFS = strfs.c_str();
    m_idFS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_idFS,1,&strFS,0);
    glCompileShader(m_idFS);
    afficherShaderCompileInfo(m_idFS,_FSchemin.c_str());

    if(_GSchemin != "") //GS
    {
        std::string strgs = lireFichierSource(SHADER_DIR+_GSchemin);
        const char* strGS = strgs.c_str();
        m_idGS = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(m_idGS,1,&strGS,0);
        glCompileShader(m_idGS);
        afficherShaderCompileInfo(m_idGS,_GSchemin.c_str());
    }
    else m_utiliser_gs = false;

    m_idProgramme = glCreateProgram();

    glAttachShader(m_idProgramme, m_idVS);
    if(m_utiliser_gs) glAttachShader(m_idProgramme, m_idGS);
    glAttachShader(m_idProgramme, m_idFS);

    glLinkProgram(m_idProgramme);

    glDetachShader(m_idProgramme, m_idVS);
    if(m_utiliser_gs) glDetachShader(m_idProgramme, m_idGS);
    glDetachShader(m_idProgramme, m_idFS);
}

//----------------------------------------------------------------------------------------------------------------------------
void ProgrammeGPU::bind()
{
    glUseProgram(m_idProgramme);
}

//----------------------------------------------------------------------------------------------------------------------------
void ProgrammeGPU::unbind()
{
    glUseProgram(0);
}

//----------------------------------------------------------------------------------------------------------------------------
GLuint ProgrammeGPU::avoirUniformLocation(const std::string& _nom)
{
    return glGetUniformLocation(m_idProgramme,_nom.c_str());
}

//----------------------------------------------------------------------------------------------------------------------------
GLuint ProgrammeGPU::avoirAttributeLocation(const std::string& _nom)
{
    return glGetAttribLocation(m_idProgramme,_nom.c_str());
}

//----------------------------------------------------------------------------------------------------------------------------
bool ProgrammeGPU::afficherShaderCompileInfo( GLuint shaderID, const std::string& message)
{
    int iInfologLength = 0;
    int iCharsWritten  = 0;
    char* strInfoLog;

    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, & iInfologLength );

    if( iInfologLength > 1 )
    {
        strInfoLog = new char[ iInfologLength + 1 ];
        glGetShaderInfoLog(shaderID, iInfologLength, & iCharsWritten, strInfoLog );
        //Afficher erreur de compilation du shader
        std::cerr << "--------------"<< std::endl << "compilation de " << message <<  " : "<<std::endl << strInfoLog <<std::endl<< "--------------"<< std::endl;
        delete [] strInfoLog;
    }

    return ( 1 == iInfologLength );
}

//----------------------------------------------------------------------------------------------------------------------------
std::string lireFichierSource(const std::string& _chemin)
{
    std::cout << "Ouverture du shader " << _chemin << std::endl;

    std::string strContent;
    std::ifstream fichier(_chemin.c_str());

    if(!fichier)
    {
        std::cerr << "Impossible d'ouvrir le fichier : " << _chemin << std::endl;
        exit(EXIT_FAILURE);
    }

    fichier.seekg(0, std::ios::end);
    strContent.reserve(fichier.tellg());
    fichier.seekg(0, std::ios::beg);
    strContent.assign((std::istreambuf_iterator<char>(fichier)),std::istreambuf_iterator<char>());

    return strContent;
}

//----------------------------------------------------------------------------------------------------------------------------
void afficherMatrice44(glm::mat4 matrice)
{
    //Fonction de debug
    std::cout << matrice[0].x << " " << matrice[1].x << " " << matrice[2].x << " " << matrice[3].x << std::endl;
    std::cout << matrice[0].y << " " << matrice[1].y << " " << matrice[2].y << " " << matrice[3].y << std::endl;
    std::cout << matrice[0].z << " " << matrice[1].z << " " << matrice[2].z << " " << matrice[3].z << std::endl;
    std::cout << matrice[0].t << " " << matrice[1].t << " " << matrice[2].t << " " << matrice[3].t << std::endl;
}
