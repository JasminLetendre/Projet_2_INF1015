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

	void Echiquier::placerPiece(int x, int y, std::shared_ptr<Piece> piece) {
		grille[x][y] = piece;
	}

	std::shared_ptr<Piece> Echiquier::getPiece(int x, int y) const {
		return grille[x][y];
	}

	bool Echiquier::deplacerPiece(int x1, int y1, int x2, int y2) {
		auto piece = grille[x1][y1];
        if (!piece || piece->getCouleur() != joueurActuel || !piece->estMouvementValide(x1, y1, x2, y2))
			return false;

        {
            DeplacementTemporaire tentative(*this, x1, y1, x2, y2);
            if (estEnEchec(joueurActuel)) {
                return false; // mssg tu est en echec tu ne peux pas faire ce deplacement
            }
        }


		grille[x2][y2] = piece;
		grille[x1][y1] = nullptr;
        changerJoueur();


		return true;
	}

    Couleur Echiquier::getJoueurActuel() const {
        return joueurActuel;
    }

    void Echiquier::changerJoueur() {
        joueurActuel = (joueurActuel == Couleur::Blanc) ? Couleur::Noir : Couleur::Blanc;
    }

    bool Echiquier::estEnEchec(Couleur couleur) const {
        int roiX = -1, roiY = -1;

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                auto p = grille[i][j];
                if (p && p->getNom()[0] == 'R' && p->getCouleur() == couleur) {
                    roiX = i;
                    roiY = j;
                }
            }
        }
        if (roiX == -1) return false;

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                auto p = grille[i][j];
                if (p && p->getCouleur() != couleur && p->estMouvementValide(i, j, roiX, roiY)) {
                    return true;
                }
            }
        }
        return false;
    }

}


