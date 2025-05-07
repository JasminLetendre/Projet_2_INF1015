#ifndef DAME_H
#define DAME_H
#pragma once
#include "PIECE.H"


namespace Logique {

class Dame: public Piece

{
public:
    Dame(Couleur couleur, int colonne, int rangee);
    ~Dame();

    bool estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const override;

    const char* getNom() const override { return "Dame"; }

};

}
#endif // DAME_H
