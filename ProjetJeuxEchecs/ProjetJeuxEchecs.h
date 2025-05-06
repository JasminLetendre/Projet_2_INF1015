#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <array>
#include <memory>
#include "Echiquier.h"

namespace affichage {
class ProjetJeuxEchecs : public QMainWindow
{
    Q_OBJECT
public:
    ProjetJeuxEchecs(QWidget* parent = nullptr);
    ~ProjetJeuxEchecs();
    void placerImagePiece(int i, int j, const QString& nomFichier);
    QString notationEchecs(int ligne, int colonne);

private:
    QGridLayout* grilleEchiquier = nullptr;
    std::array<std::array<QPushButton*, 8>, 8> boutons{};
    std::unique_ptr<Logique::Echiquier> echiquier;

    void caseCliquee();
    int caseXSelectionnee = -1;
    int caseYSelectionnee = -1;

    bool pieceSelectionnee = false;
    int ligneSelection = -1;
    int colonneSelection = -1;
};
}

