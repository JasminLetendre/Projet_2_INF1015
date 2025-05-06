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



Cavalier::Cavalier(Couleur couleur) : Piece (couleur) {}

Cavalier::~Cavalier() {}


bool Cavalier::estMouvementValide(int x1, int y1, int x2, int y2) const {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
}
