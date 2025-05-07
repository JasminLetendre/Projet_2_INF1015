/**
* Implémentation des méthodes de Dame.h
* \file   Dame.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/
#include "Dame.h"
#include <cmath>

namespace Logique {

Dame::Dame(Couleur couleur, int colonne, int rangee) : Piece (couleur, colonne, rangee) {}

Dame::~Dame() {}


bool Dame::estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const {
    int distanceColonne = std::abs(ColonneApres - ColonneAvant);
    int distanceRangee = std::abs(RangeeApres - RangeeAvant);
    return (ColonneAvant == ColonneApres || RangeeAvant == RangeeApres || distanceColonne == distanceRangee) && !(ColonneAvant == ColonneApres && RangeeAvant == RangeeApres);
}

}

