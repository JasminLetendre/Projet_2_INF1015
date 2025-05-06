#ifndef TOUR_H
#define TOUR_H
#include "PIECE.H"

#pragma once
namespace Logique {


class Tour: public Piece

{
public:
    Tour(Couleur couleur);
    ~Tour();

    bool estMouvementValide(int x1, int y1, int x2, int y2) const override;

    const char* getNom() const override { return "Tour"; }

};

}

#endif // TOUR_H
