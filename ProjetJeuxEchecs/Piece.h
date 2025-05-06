#ifndef PIECE_H
#define PIECE_H

#pragma once
#include "Couleur.h"

namespace Modele {

class Piece
{
public:

    Piece(Couleur couleur) : couleur_(couleur) {}
    virtual ~Piece() = default;

    virtual bool estMouvementValide(int x1, int y1, int x2, int y2) const = 0;
    virtual const char* getNom() const = 0;

    Couleur getCouleur() const {return couleur_; }
private:
    Couleur couleur_;
};
}



#endif // PIECE_H
