#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <array>
#include <memory>
#include "Echiquier.h"
#include "Couleur.h"

namespace Jeu {
class ProjetJeuxEchecs : public QMainWindow
{
    Q_OBJECT
public:
    ProjetJeuxEchecs(QWidget* parent = nullptr);
    ~ProjetJeuxEchecs();
    void placerImagePiece(int i, int j, const QString& nomFichier);
    QString notationEchecs(int ligne, int colonne);
    Logique::Couleur getJoueurActuel() const;
    void changerJoueur();
    bool estEnEchec(Logique::Couleur couleur) const;
    std::shared_ptr<Logique::Piece> getPieceSurCase(int col, int row) const;

private:
    QGridLayout* grilleEchiquier = nullptr;
    std::array<std::array<QPushButton*, 8>, 8> boutons{};
    std::unique_ptr<Logique::Echiquier> echiquier;
    Logique::Couleur joueurActuel_ = Logique::Couleur::Blanc;

    std::vector<std::shared_ptr<Logique::Piece>> pieces_;
    void caseCliquee();
    int caseXSelectionnee = -1;
    int caseYSelectionnee = -1;

    bool pieceSelectionnee = false;
    int ligneSelection = -1;
    int colonneSelection = -1;
};
}

