/**
* Implémentation des méthodes de Roi.h
* \file   Roi.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "Roi.h"
#include <cmath>

namespace Modele {


int Roi::compteurRois = 0;

Roi::Roi(Couleur couleur) : Piece (couleur) {
    if (++compteurRois > 2) {
        --compteurRois;
        throw TropDeRoisException();
    }

}

Roi::~Roi() {
    --compteurRois;
}

bool Roi::estMouvementValide(int x1, int y1, int x2, int y2) const {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    return dx <= 1 && dy <= 1 && (dx + dy != 0);
}
}
