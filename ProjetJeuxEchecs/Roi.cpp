/**
* Implémentation des méthodes de Roi.h
* \file   Roi.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "Roi.h"
#include <cmath>

namespace Logique {


int Roi::compteurRois = 0;

Roi::Roi(Couleur couleur, int colonne, int rangee) : Piece (couleur, colonne, rangee) {
    if (++compteurRois > 2) {
        --compteurRois;
        throw TropDeRoisException();
    }

}

Roi::~Roi() {
    --compteurRois;
}

bool Roi::estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const {
    int distanceColonne = std::abs(ColonneApres - ColonneAvant);
    int distanceRangee = std::abs(RangeeApres - RangeeAvant);
    return distanceColonne <= 1 && distanceRangee <= 1 && (distanceColonne + distanceRangee != 0);
}
}
