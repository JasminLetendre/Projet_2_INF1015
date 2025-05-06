#ifndef ROI_H
#define ROI_H
#pragma once
#include "PIECE.H"
#include <stdexcept>

namespace Logique {


class Roi: public Piece

{
public:
    Roi(Couleur couleur);
    ~Roi();
    bool estMouvementValide(int x1, int y1, int x2, int y2) const override;

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
