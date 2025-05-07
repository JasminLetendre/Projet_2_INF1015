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
#include <QPixmap>
#include "deplacementtemporaire.h"
#include <QStatusBar>

using namespace Logique;

namespace affichage {
    ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
        : QMainWindow(parent), echiquier(std::make_unique<Echiquier>())
    {

        grilleEchiquier = new QGridLayout;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                ClickableLabel* caseLabel = new ClickableLabel;
                caseLabel->setCoordonnees(i, j);
                connect(caseLabel, &ClickableLabel::clic, this, &ProjetJeuxEchecs::caseCliquee);
                caseLabel->setFixedSize(60, 60);
                caseLabel->setStyleSheet((i + j) % 2 == 0
                                             ? "background-color: #A9DFBF;"
                                             : "background-color: #196F3D;");
                caseLabel->setAlignment(Qt::AlignCenter);
                grilleEchiquier->addWidget(caseLabel, i, j);
                cases[i][j] = caseLabel; // g changer les qpushbuttons par dees caselabels
            }
        }



        // affichage des msg avec  statusBar
        infoLabel = new QLabel("Bienvenue dans le jeu d'échecs !");
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->setStyleSheet("padding: 6px; font-weight: bold;");
        infoLabel->setFixedHeight(30);

        statusLabel = new QLabel("Bienvenue dans le jeu d'échecs !");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setStyleSheet("padding: 6px; font-weight: bold; color: white; background-color: red;");

        QPushButton* boutonNouvellePartie = new QPushButton("Nouvelle partie");
        connect(boutonNouvellePartie, &QPushButton::clicked, this, &ProjetJeuxEchecs::reinitialiserEchiquier);

        QVBoxLayout* layoutPrincipal = new QVBoxLayout;
        layoutPrincipal->addLayout(grilleEchiquier);
        layoutPrincipal->addWidget(boutonNouvellePartie);
        layoutPrincipal->addWidget(infoLabel);
        layoutPrincipal->addWidget(statusLabel);

        QWidget* central = new QWidget(this);
        central->setLayout(layoutPrincipal);
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

    void ProjetJeuxEchecs::caseCliquee(int ligne, int colonne) {
        if (!pieceSelectionnee) {
            selectionnerOuAfficherMessageSiVide(ligne, colonne);
        } else {
            tenterDeplacerPieceVers(ligne, colonne);
            deselectionnerCase();
        }
    }

    void ProjetJeuxEchecs::selectionnerOuAfficherMessageSiVide(int ligne, int colonne) {
        auto piece = echiquier->getPiece(ligne, colonne);
        infoLabel->clear();
        statusLabel->clear();
        if (piece) {
            if (piece->getCouleur() != echiquier->getJoueurActuel()) {
                infoLabel->setText("Erreur: Ce n'est pas à ton tour !");
                return;
            }

            pieceSelectionnee = true;
            ligneSelection = ligne;
            colonneSelection = colonne;
            cases[ligne][colonne]->setStyleSheet("background-color: yellow;");
            infoLabel->setText(QString("La piece %1 sélectionné.").arg(piece->getNom()));
            montrerMouvementsPossibles(ligne, colonne);
        }  else {
            infoLabel->setText(QString("La case %1 est vide.").arg(notationEchecs(ligne, colonne)));
        }

    }

    void ProjetJeuxEchecs::tenterDeplacerPieceVers(int ligne, int colonne) {
        auto piece = echiquier->getPiece(ligneSelection, colonneSelection);
        infoLabel->clear();
        statusLabel->clear();
        if (ligneSelection < 0 || ligneSelection >= 8 || colonneSelection < 0 || colonneSelection >= 8)
            return;
        if (!piece) return;

        if (piece->getCouleur() != echiquier->getJoueurActuel()) {
            infoLabel->setText("Erreur: Ce n'est pas à ton tour !");
            return;
        }

        if (cibleEstAlliee(ligne, colonne)) {
            infoLabel->setText( "Erreur: Tu ne peux pas capturer une piece allie !");
            return;
        }


        if (!piece->estMouvementValide(ligneSelection, colonneSelection, ligne, colonne)) {
            infoLabel->setText(QString("La pièce %1 ne peut pas aller en %2.")
                            .arg(piece->getNom(), notationEchecs(ligne, colonne)));
            return;
        }

        auto pieceCapturee = echiquier->getPiece(ligne, colonne);

        if (!echiquier->deplacerPiece(ligneSelection, colonneSelection, ligne, colonne)) {
            statusLabel->setText( "Erreur: Tu es en échec, tu ne peux pas faire ce déplacement.");
            //deselectionnerCase();
            return;
        }


        QPixmap piecePixmap = cases[ligneSelection][colonneSelection]->pixmap();
        if (!piecePixmap.isNull()) {
            cases[ligne][colonne]->setPixmap(piecePixmap.scaled(50, 50, Qt::KeepAspectRatio));
            cases[ligneSelection][colonneSelection]->clear();
            if (pieceCapturee) {
                infoLabel->setText(
                    QString("La pièce %1 a capturé une pièce en %2.")
                        .arg(piece->getNom(), notationEchecs(ligne, colonne))
                    );
            } else {
                infoLabel->setText(
                    QString("La pièce %1 s'est déplacée en %2.")
                        .arg(piece->getNom(), notationEchecs(ligne, colonne))
                    );
            }
        }
    }

    bool ProjetJeuxEchecs::cibleEstAlliee(int ligne, int colonne) const {
        auto pieceSource = echiquier->getPiece(ligneSelection, colonneSelection);
        auto pieceCible = echiquier->getPiece(ligne, colonne);
        return pieceCible && pieceSource && pieceCible->getCouleur() == pieceSource->getCouleur();
    }

    void ProjetJeuxEchecs::deselectionnerCase() {
        bool clair = (ligneSelection + colonneSelection) % 2 == 0;
        //->clear();
        //statusLabel->clear();
        cases[ligneSelection][colonneSelection]->setStyleSheet(
            clair ? "background-color: #A9DFBF;" : "background-color: #196F3D;");
        pieceSelectionnee = false;
        ligneSelection = -1;
        colonneSelection = -1;
        reinitialiserSurbrillance();
    }

    void ProjetJeuxEchecs::montrerMouvementsPossibles(int ligne, int colonne) {
        auto piece = echiquier->getPiece(ligne, colonne);
        if (!piece) return;

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (!piece->estMouvementValide(ligne, colonne, i, j))
                    continue;

                auto cible = echiquier->getPiece(i, j);
                if (cible && cible->getCouleur() == piece->getCouleur())
                    continue;

                // Sécurité : simulation du déplacement, protégée par try/catch
                try {
                    DeplacementTemporaire tentative(*echiquier, ligne, colonne, i, j);
                    if (echiquier->estEnEchec(piece->getCouleur()))
                        continue;
                } catch (...) {
                    continue; // ignore tout plantage lors du test de simulation
                }

                // Illuminer les cases valides
                cases[i][j]->setStyleSheet("background-color: orange;");
                casesSurbrillantes.append({i, j});
            }
        }
    }


    void ProjetJeuxEchecs::reinitialiserSurbrillance() {
        for (const auto& [i, j] : casesSurbrillantes) {
            bool clair = (i + j) % 2 == 0;
            cases[i][j]->setStyleSheet(clair ? "background-color: #A9DFBF;" : "background-color: #196F3D;");
        }
        casesSurbrillantes.clear();
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
                QPixmap pixmap(chemin);
                cases[i][j]->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio));
                cases[i][j]->setAlignment(Qt::AlignCenter);
                ;
                //cases[i][j]->setIconSize(QSize(50, 50)); plus de pushbutton
            }
        }
        catch (const Logique::TropDeRoisException& e) {
            QMessageBox::critical(this, "Erreur", e.what());
            //cases[i][j]->setIcon(QIcon());
        }
    }

    void ProjetJeuxEchecs::reinitialiserEchiquier() {
        // Vider toutes les cases
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cases[i][j]->clear();
                bool clair = (i + j) % 2 == 0;
                cases[i][j]->setStyleSheet(clair ? "background-color: #A9DFBF;" : "background-color: #196F3D;");
            }
        }

        // Vider l'échiquier logique
        echiquier = std::make_unique<Echiquier>();

        // Réinitialiser les états
        pieceSelectionnee = false;
        ligneSelection = colonneSelection = -1;
        reinitialiserSurbrillance();

        // Réafficher les pièces initiales
        placerImagePiece(0, 3, "roi_blanc.png");
        placerImagePiece(3, 3, "roi_noir.png");
        placerImagePiece(1, 6, "reine_blanc.png");
        placerImagePiece(2, 1, "tour_noir.png");

        infoLabel->setText("Nouvelle partie commencée !");
        statusLabel->clear();
    }


    ProjetJeuxEchecs::~ProjetJeuxEchecs() {
    }
}
