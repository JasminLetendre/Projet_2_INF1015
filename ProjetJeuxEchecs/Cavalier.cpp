/**
* Implémentation des méthodes de Cavalier.h
* \file   Cavalier.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "Cavalier.h"
#include <cmath>
namespace Logique {



Cavalier::Cavalier(Couleur couleur, int colonne, int rangee) : Piece (couleur, colonne, rangee) {}

Cavalier::~Cavalier() {}


bool Cavalier::estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const {
    int distanceColonne = std::abs(ColonneApres - ColonneAvant);
    int distanceRangee = std::abs(RangeeApres - RangeeAvant);
    return (distanceColonne == 2 && distanceRangee == 1) || (distanceColonne == 1 && distanceRangee == 2);
}
}
