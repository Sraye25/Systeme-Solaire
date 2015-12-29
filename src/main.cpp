#include "fenetre.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;

    #ifndef _WIN32
        format.setMajorVersion(3);
        format.setMinorVersion(3);
        format.setProfile(QSurfaceFormat::CoreProfile);
    #endif
    format.setSamples(16);
    format.setDepthBufferSize(24);

    Fenetre fenetre;
    fenetre.setFormat(format);
    fenetre.resize(800, 600);
    fenetre.show();

    return app.exec();
}
