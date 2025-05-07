#include "ProjetJeuxEchecs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Jeu::ProjetJeuxEchecs w;
    w.show();
    return app.exec();
}
