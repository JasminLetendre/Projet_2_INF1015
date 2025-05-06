#ifndef DEPLACEMENTTEMPORAIRE_H
#define DEPLACEMENTTEMPORAIRE_H
#pragma once
#include "Echiquier.h"
#include <memory>

namespace Modele {

class DeplacementTemporaire {
public:
    DeplacementTemporaire(Echiquier& echiquier, int x1, int y1, int x2, int y2);
    ~DeplacementTemporaire();

private:
    Echiquier& echiquier;
    int x1, y1, x2, y2;
    std::shared_ptr<Piece> pieceSource;
    std::shared_ptr<Piece> pieceDestination;
};

}
#endif // DEPLACEMENTTEMPORAIRE_H
