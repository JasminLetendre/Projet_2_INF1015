/**
* Implémentation des méthodes de Dame.h
* \file   Dame.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/
#include "Dame.h"
#include <cmath>

namespace Modele {

Dame::Dame(Couleur couleur) : Piece (couleur) {}

Dame::~Dame() {}


bool Dame::estMouvementValide(int x1, int y1, int x2, int y2) const {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    return (x1 == x2 || y1 == y2 || dx == dy) && !(x1 == x2 && y1 == y2);
}

}

