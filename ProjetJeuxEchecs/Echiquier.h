#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#pragma once
#include <memory>
#include <array>
#include "Piece.h"

namespace Modele {

class Echiquier {
public:
    Echiquier();

    bool deplacerPiece(int x1, int y1, int x2, int y2);
    std::shared_ptr<Piece> getPiece(int x, int y) const;
    void placerPiece(int x, int y, std::shared_ptr<Piece> piece);

    Couleur getJoueurActuel() const;
    void changerJoueur();
    bool estEnEchec(Couleur couleur) const;

private:
    std::array<std::array<std::shared_ptr<Piece>, 8>, 8> grille;
    Couleur joueurActuel = Couleur::Blanc;
};

}

#endif
