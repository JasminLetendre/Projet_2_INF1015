#ifndef TOUR_H
#define TOUR_H
#include "PIECE.H"

#pragma once
namespace Logique {


class Tour: public Piece

{
public:
    Tour(Couleur couleur, int colonne, int rangee);
    ~Tour();

    bool estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const override;

    const char* getNom() const override { return "Tour"; }

};

}

#endif // TOUR_H
