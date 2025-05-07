#pragma once

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr);
    void setCoordonnees(int ligne, int colonne);

signals:
    void clic(int ligne, int colonne);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    int ligne_, colonne_;
};
