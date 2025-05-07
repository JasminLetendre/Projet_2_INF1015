#include "Piece.h"
#include "Echiquier.h"

namespace Logique {

bool Piece::peutSeDeplacer(Echiquier& echiquier, int colonneAvantDeplacement, int rangeeAvantDeplacement, int colonneApresDeplacement, int rangeeApresDeplacement) const {
    if (!estMouvementValide(colonneAvantDeplacement, rangeeAvantDeplacement, colonneApresDeplacement, rangeeApresDeplacement)) return false;
    auto destination = echiquier.getPiece(colonneApresDeplacement, rangeeApresDeplacement);
    return !destination || destination->couleur_ != couleur_;
}

void Piece::deplacer(int nouvelleColonne, int nouvelleRangee) {
    colonne_ = nouvelleColonne;
    rangee_ = nouvelleRangee;
}

}
