#ifndef ROI_H
#define ROI_H
#pragma once
#include "PIECE.H"
#include <stdexcept>

namespace Logique {


class Roi: public Piece

{
public:
    Roi(Couleur couleur, int colonne, int rangee);
    ~Roi();
    bool estMouvementValide(int ColonneAvant, int RangeeAvant, int ColonneApres, int RangeeApres) const override;

    const char* getNom() const override { return "Roi"; }


private:
    static int compteurRois;
};

class TropDeRoisException : public std::runtime_error {
public:
    TropDeRoisException() : std::runtime_error("Trop de rois, seul les 2 premiers rois sont pris en consideration") {}
};

}

#endif // ROI_H
