#ifndef DAME_H
#define DAME_H
#pragma once
#include "PIECE.H"


namespace Modele {

class Dame: public Piece

{
public:
    Dame(Couleur couleur);
    ~Dame();

    bool estMouvementValide(int x1, int y1, int x2, int y2) const override;

    const char* getNom() const override { return "Dame"; }

};

}
#endif // DAME_H
