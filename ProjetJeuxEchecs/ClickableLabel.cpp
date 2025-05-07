#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent), ligne_(0), colonne_(0) {}

void ClickableLabel::setCoordonnees(int ligne, int colonne) {
    ligne_ = ligne;
    colonne_ = colonne;
}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        emit clic(ligne_, colonne_);
}
