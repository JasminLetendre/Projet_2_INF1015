/**
* Gère les différentes règles et fonctionnements du jeux en général
* \file   Echiquier.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "Echiquier.h"
#include "deplacementtemporaire.h"




namespace Logique {

	Echiquier::Echiquier() {
		for (auto& ligne : grille)
			ligne.fill(nullptr);
	}

    void Echiquier::placerPiece(int colonne, int rangee, std::shared_ptr<Piece> piece) {
        grille[colonne][rangee] = piece;
	}

    std::shared_ptr<Piece> Echiquier::getPiece(int colonne, int rangee) const {
        return grille[colonne][rangee];
	}

    /**
    bool Echiquier::deplacerPiece(int colonneAvantDeplacement, int rangeeAvantDeplacement, int colonneApresDeplacement, int rangeeApresDeplacement) {
        auto piece = grille[colonneAvantDeplacement][rangeeAvantDeplacement];
        if (!piece || piece->couleur_ != getJoueurActuel() || !piece->estMouvementValide(colonneAvantDeplacement, rangeeAvantDeplacement, colonneApresDeplacement, rangeeApresDeplacement))
			return false;

        {
            DeplacementTemporaire tentative(*this, colonneAvantDeplacement, rangeeAvantDeplacement, colonneApresDeplacement, rangeeApresDeplacement);
            if (estEnEchec(getJoueurActuel())) {
                return false; // mssg tu est en echec tu ne peux pas faire ce deplacement
            }
        }


        grille[colonneApresDeplacement][rangeeApresDeplacement] = piece;
        grille[colonneAvantDeplacement][rangeeAvantDeplacement] = nullptr;



		return true;
	}
    */
}


