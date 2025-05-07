#ifndef CAVALIER_H
#define CAVALIER_H
#pragma once
#include "PIECE.H"


namespace Logique {



class Cavalier: public Piece

{
public:
    Cavalier(Couleur couleur, int colonne, int rangee);
    ~Cavalier();

    bool estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const override;

    const char* getNom() const override { return "Cavalier"; }

};
}
#endif // CAVALIER_H
