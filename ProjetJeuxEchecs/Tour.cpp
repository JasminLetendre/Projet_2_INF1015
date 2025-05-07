/**
* Implémentation des méthodes de Tour.h
* \file   Tour.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "Tour.h"
namespace Logique {
Tour::Tour(Couleur couleur, int colonne, int rangee) : Piece (couleur, colonne, rangee) {}


Tour::~Tour() {}


bool Tour::estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const {
    return (ColonneAvant == ColonneApres || RangeeAvant == RangeeApres) && !(ColonneAvant == ColonneApres && RangeeAvant == RangeeApres);
}
}
