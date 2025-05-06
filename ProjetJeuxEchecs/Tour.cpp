/**
* Implémentation des méthodes de Tour.h
* \file   Tour.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "Tour.h"
namespace Modele {
Tour::Tour(Couleur couleur) : Piece (couleur) {}


Tour::~Tour() {}


bool Tour::estMouvementValide(int x1, int y1, int x2, int y2) const {
    return (x1 == x2 || y1 == y2) && !(x1 == x2 && y1 == y2);
}
}
