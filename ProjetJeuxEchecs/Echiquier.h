#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#pragma once
#include <memory>
#include <array>
#include "Piece.h"

namespace Logique {

class Echiquier {
public:
    Echiquier();

    bool deplacerPiece(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres);
    std::shared_ptr<Piece> getPiece(int colonne, int rangee) const;
    void placerPiece(int colonne, int rangee, std::shared_ptr<Piece> piece);

private:
    std::array<std::array<std::shared_ptr<Piece>, 8>, 8> grille;
};

}

#endif
