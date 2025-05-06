/**
* Gère l'interface du jeu
* \file   ProjetJeuxEchecs.cpp
* \author Jasmin et Yahia
* \date   17 avril 2025
* Créé le 17 avril 2025
*/

#include "ProjetJeuxEchecs.h"
#include <QMessageBox>
#include <QFile>
#include <Qdir>
#include "Roi.h"
#include "Dame.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Echiquier.h"
#include "Couleur.h"
using namespace Modele;

namespace interface {
    ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
        : QMainWindow(parent), echiquier(std::make_unique<Echiquier>())
    {

        grilleEchiquier = new QGridLayout;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                QPushButton* bouton = new QPushButton;
                bouton->setFixedSize(60, 60);
                bouton->setStyleSheet((i + j) % 2 == 0
                    ? "background-color: #A9DFBF;"
                    : "background-color: #196F3D;");
                grilleEchiquier->addWidget(bouton, i, j);
                boutons[i][j] = bouton;
                connect(bouton, &QPushButton::clicked, this, &ProjetJeuxEchecs::caseCliquee);
            }
        }
        QWidget* central = new QWidget(this);
        central->setLayout(grilleEchiquier);
        setCentralWidget(central);


        placerImagePiece(0, 3, "roi_blanc.png");

        placerImagePiece(3, 3, "roi_noir.png");
        //placerImagePiece(7, 7, "roi_noir.png"); // la case 7 7 doit etre vide

        placerImagePiece(1, 6, "reine_blanc.png");


        placerImagePiece(2, 1, "tour_noir.png");


    }

    void ProjetJeuxEchecs::caseCliquee()
    {
        QObject* boutonClique = sender();

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (boutonClique == boutons[i][j]) {
                    if (!pieceSelectionnee) {
                        auto piece = echiquier->getPiece(i, j);
                        if (piece) {
                            pieceSelectionnee = true;
                            ligneSelection = i;
                            colonneSelection = j;
                            boutons[i][j]->setStyleSheet("background-color: yellow;");
                        }
                        else {
                            QMessageBox::information(this, "Info",
                                QString("La case (%1, %2) est vide.").arg(i).arg(j));
                        }
                    }
                    else {
                        auto piece = echiquier->getPiece(ligneSelection, colonneSelection);

                        if (piece) {
                            // check les tours
                            if (piece->getCouleur() != echiquier->getJoueurActuel()) {
                                QMessageBox::warning(this, "Erreur", "Ce n'est pas à ton tour !");
                            }
                            else if (!piece->estMouvementValide(ligneSelection, colonneSelection, i, j)) {
                                QMessageBox::warning(this, "Mouvement interdit",
                                    QString("La pièce '%1' ne peut pas se déplacer de (%2, %3) à (%4, %5).")
                                    .arg(piece->getNom()).arg(ligneSelection).arg(colonneSelection).arg(i).arg(j));
                            }// ne pas deplacer limage avant d'avoir check si il n'y ai pas d'echec 
                            else if (!echiquier->deplacerPiece(ligneSelection, colonneSelection, i, j)) {
                                // il ya echec donc pas de deplacement
                                QMessageBox::warning(this, "Erreur", "Tu es en échec, tu ne peux pas faire ce déplacement.");
                            }
                            else {// si pas d'echec et mouvement valide ... deplacer piece et image
                                QIcon icone = boutons[ligneSelection][colonneSelection]->icon();
                                boutons[i][j]->setIcon(icone);
                                boutons[i][j]->setIconSize(QSize(50, 50));
                                boutons[ligneSelection][colonneSelection]->setIcon(QIcon());
                            }
                        }

                        bool clair = (ligneSelection + colonneSelection) % 2 == 0;
                        boutons[ligneSelection][colonneSelection]->setStyleSheet(
                            clair ? "background-color: #A9DFBF;" : "background-color: #196F3D;");

                        pieceSelectionnee = false;
                        ligneSelection = -1;
                        colonneSelection = -1;
                    }
                    return;
                }
            }
        }
    }

    void ProjetJeuxEchecs::placerImagePiece(int i, int j, const QString& nomFichier)
    {
        std::shared_ptr<Modele::Piece> piece = nullptr;
        try {
            Modele::Couleur couleur = nomFichier.contains("blanc", Qt::CaseInsensitive)
                ? Modele::Couleur::Blanc
                : Modele::Couleur::Noir;

            if (nomFichier.contains("roi", Qt::CaseInsensitive)) {
                piece = std::make_shared<Modele::Roi>(couleur);
            }
            else if (nomFichier.contains("reine", Qt::CaseInsensitive)) {
                piece = std::make_shared<Modele::Dame>(couleur);
            }
            else if (nomFichier.contains("tour", Qt::CaseInsensitive)) {
                piece = std::make_shared<Modele::Tour>(couleur);
            }
            else if (nomFichier.contains("chevalier", Qt::CaseInsensitive)) {
                piece = std::make_shared<Modele::Cavalier>(couleur);
            }

            if (piece) {
                echiquier->placerPiece(i, j, piece);
                QIcon icone(QString("images/") + nomFichier);
                boutons[i][j]->setIcon(icone);
                boutons[i][j]->setIconSize(QSize(50, 50));
            }
        }
        catch (const Modele::TropDeRoisException& e) {
            QMessageBox::critical(this, "Erreur", e.what());
            boutons[i][j]->setIcon(QIcon());
        }
    }

    /*void ProjetJeuxEchecs::placerRoi(int i, int j, const QString& nomFichier)
    {
        try {
            placerImagePiece(i, j, nomFichier);
            echiquier->placerPiece(i, j, std::make_shared<Modele::Roi>());
        }
        catch (const Modele::TropDeRoisException& e) {
            QMessageBox::critical(this, "Erreur - Trop de rois", e.what());
            boutons[i][j]->setIcon(QIcon());
        }
    }*/


    ProjetJeuxEchecs::~ProjetJeuxEchecs() {
    }
}


