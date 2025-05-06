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
using namespace Logique;

namespace affichage {
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

    QString ProjetJeuxEchecs::notationEchecs(int ligne, int colonne) {
        QChar colonneLettre = QChar('A' + colonne);
        int ligneEchiquier = 8 - ligne;
        return QString("%1%2").arg(colonneLettre).arg(ligneEchiquier);
    }

    void ProjetJeuxEchecs::caseCliquee()
    {
        QObject* boutonClique = sender();

        for (int ligne = 0; ligne < 8; ++ligne) {
            for (int colonne = 0; colonne < 8; ++colonne) {
                if (boutonClique == boutons[ligne][colonne]) {
                    QString notation = notationEchecs(ligne, colonne);
                    if (!pieceSelectionnee) {
                        auto piece = echiquier->getPiece(ligne, colonne);
                        if (piece) {
                            pieceSelectionnee = true;
                            ligneSelection = ligne;
                            colonneSelection = colonne;
                            boutons[ligne][colonne]->setStyleSheet("background-color: yellow;");
                        } else {
                            QMessageBox::information(this, "Info", QString("La case %1 est vide.").arg(notation));
                        }
                    } else {
                        auto piece = echiquier->getPiece(ligneSelection, colonneSelection);

                        QString depart = notationEchecs(ligneSelection, colonneSelection);
                        QString arrivee = notation;

                        if (piece) {
                            if (piece->getCouleur() != echiquier->getJoueurActuel()) {
                                QMessageBox::warning(this, "Erreur", "Ce n'est pas à ton tour !");
                            } else if (!piece->estMouvementValide(ligneSelection, colonneSelection, ligne, colonne)) {
                                QMessageBox::warning(this, "Mouvement interdit",
                                                     QString("La pièce '%1' ne peut pas se déplacer de %2 à %3.")
                                                         .arg(piece->getNom()).arg(depart, arrivee));
                            } else if (!echiquier->deplacerPiece(ligneSelection, colonneSelection, ligne, colonne)) {
                                QMessageBox::warning(this, "Erreur", "Tu es en échec, tu ne peux pas faire ce déplacement.");
                            } else {
                                QIcon icone = boutons[ligneSelection][colonneSelection]->icon();
                                boutons[ligne][colonne]->setIcon(icone);
                                boutons[ligne][colonne]->setIconSize(QSize(50, 50));
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
        std::shared_ptr<Logique::Piece> piece = nullptr;
        try {
            Logique::Couleur couleur = nomFichier.contains("blanc", Qt::CaseInsensitive)
                ? Logique::Couleur::Blanc
                : Logique::Couleur::Noir;

            if (nomFichier.contains("roi", Qt::CaseInsensitive)) {
                piece = std::make_shared<Logique::Roi>(couleur);
            }
            else if (nomFichier.contains("reine", Qt::CaseInsensitive)) {
                piece = std::make_shared<Logique::Dame>(couleur);
            }
            else if (nomFichier.contains("tour", Qt::CaseInsensitive)) {
                piece = std::make_shared<Logique::Tour>(couleur);
            }
            else if (nomFichier.contains("chevalier", Qt::CaseInsensitive)) {
                piece = std::make_shared<Logique::Cavalier>(couleur);
            }

            if (piece) {
                echiquier->placerPiece(i, j, piece);
                QString chemin = QDir::currentPath() + "/images/" + nomFichier;
                if (!QFile::exists(chemin)) {
                    QMessageBox::warning(this, "Image introuvable", "Fichier non trouvé: " + chemin);
                }
                QIcon icone(chemin);
                boutons[i][j]->setIcon(icone);
                boutons[i][j]->setIconSize(QSize(50, 50));
            }
        }
        catch (const Logique::TropDeRoisException& e) {
            QMessageBox::critical(this, "Erreur", e.what());
            boutons[i][j]->setIcon(QIcon());
        }
    }

    /*void ProjetJeuxEchecs::placerRoi(int i, int j, const QString& nomFichier)
    {
        try {
            placerImagePiece(i, j, nomFichier);
            echiquier->placerPiece(i, j, std::make_shared<Logique::Roi>());
        }
        catch (const Logique::TropDeRoisException& e) {
            QMessageBox::critical(this, "Erreur - Trop de rois", e.what());
            boutons[i][j]->setIcon(QIcon());
        }
    }*/


    ProjetJeuxEchecs::~ProjetJeuxEchecs() {
    }
}


