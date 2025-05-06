#ifndef CAVALIER_H
#define CAVALIER_H
#pragma once
#include "PIECE.H"


namespace Modele {



class Cavalier: public Piece

{
public:
    Cavalier(Couleur couleur);
    ~Cavalier();

    bool estMouvementValide(int x1, int y1, int x2, int y2) const override;

    const char* getNom() const override { return "Cavalier"; }

};
}
#endif // CAVALIER_H
