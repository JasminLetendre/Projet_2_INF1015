#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <array>
#include <memory>
#include "Echiquier.h"
#include <QLabel>
#include "ClickableLabel.h"


namespace affichage {
class ProjetJeuxEchecs : public QMainWindow
{
    Q_OBJECT
public:
    ProjetJeuxEchecs(QWidget* parent = nullptr);
    ~ProjetJeuxEchecs();
    void placerImagePiece(int i, int j, const QString& nomFichier);
    void selectionnerOuAfficherMessageSiVide(int ligne, int colonne);
    void tenterDeplacerPieceVers(int ligne, int colonne);
    bool cibleEstAlliee(int ligne, int colonne) const;
    void deselectionnerCase();
    void montrerMouvementsPossibles(int ligne, int colonne);
    void reinitialiserSurbrillance();
    QString notationEchecs(int ligne, int colonne);
    QVector<QPair<int, int>> casesSurbrillantes; // moves poossibles
    void reinitialiserEchiquier();
public slots:
    void caseCliquee(int ligne, int colonne);

private:
    QGridLayout* grilleEchiquier = nullptr;
    std::array<std::array<ClickableLabel*, 8>, 8> cases{}; // qlabel utilisee dans ClickableLabel au lieux de qpushbuttons
    std::unique_ptr<Logique::Echiquier> echiquier;

    int caseXSelectionnee = -1;
    int caseYSelectionnee = -1;

    bool pieceSelectionnee = false;
    int ligneSelection = -1;
    int colonneSelection = -1;

    QLabel* infoLabel = nullptr;
    QLabel* statusLabel = nullptr;
};
}

