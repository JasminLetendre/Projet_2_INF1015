/**
* Implémentation des méthodes de deplacementtemporaire.h
* \file   deplacementtemporaire.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "deplacementtemporaire.h"

namespace Logique {

DeplacementTemporaire::DeplacementTemporaire(Echiquier& ech, int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres)
    : echiquier(ech), x1(ColonneAvant), y1(RangeeAvant), x2(ColonneApres), y2(RangeeApres) {
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
