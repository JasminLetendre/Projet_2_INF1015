#include "ProjetJeuxEchecs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    interface::ProjetJeuxEchecs w;
    w.show();
    return app.exec();
}
