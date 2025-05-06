/**
* Implémentation des méthodes de deplacementtemporaire.h
* \file   deplacementtemporaire.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "deplacementtemporaire.h"

namespace Logique {

DeplacementTemporaire::DeplacementTemporaire(Echiquier& ech, int srcX, int srcY, int destX, int destY)
    : echiquier(ech), x1(srcX), y1(srcY), x2(destX), y2(destY) {
    pieceSource = echiquier.getPiece(x1, y1);
    pieceDestination = echiquier.getPiece(x2, y2);
    echiquier.placerPiece(x2, y2, pieceSource);
    echiquier.placerPiece(x1, y1, nullptr);
}

DeplacementTemporaire::~DeplacementTemporaire() {
    echiquier.placerPiece(x1, y1, pieceSource);
    echiquier.placerPiece(x2, y2, pieceDestination);
}

}
