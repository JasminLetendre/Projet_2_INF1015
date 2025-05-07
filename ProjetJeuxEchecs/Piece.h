#ifndef PIECE_H
#define PIECE_H


#pragma once
#include "Couleur.h"
#include <utility>

namespace Jeu {
class ProjetJeuxEchecs;
}

namespace Logique {


class Piece
{
public:

    friend class Jeu::ProjetJeuxEchecs;
    friend class Echiquier;
    Piece(Couleur couleur, int colonne, int rangee) : couleur_(couleur), colonne_(colonne), rangee_(rangee) {}
    virtual ~Piece() = default;
    void deplacer(int nouvelleX, int nouvelleY);

    virtual bool estMouvementValide(int colonneAvant, int RangeeAvant, int colonneApres, int RangeeApres) const = 0;
    virtual const char* getNom() const = 0;

    virtual bool peutSeDeplacer(Echiquier& echiquier, int colonneAvant, int RangeeAvant, int colonneApres, int RangeeApres) const;
    std::pair<int, int> getPosition() const {
        return {colonne_, rangee_};
    }
    //Couleur getCouleur() const {return couleur_; }
private:
    Couleur couleur_;
    int colonne_;
    int rangee_;
};
}



#endif // PIECE_H
