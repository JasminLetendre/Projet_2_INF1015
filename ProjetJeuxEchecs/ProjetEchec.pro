QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Cavalier.cpp \
    Dame.cpp \
    Echiquier.cpp \
    Piece.cpp \
    ProjetJeuxEchecs.cpp \
    Roi.cpp \
    TestJeuxEchecs.cpp \
    Tour.cpp \
    deplacementtemporaire.cpp \
    main.cpp

HEADERS += \
    Cavalier.h \
    Couleur.h \
    Dame.h \
    Echiquier.h \
    Piece.h \
    ProjetJeuxEchecs.h \
    Roi.h \
    Tour.h \
    deplacementtemporaire.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/chevalier_blanc.png \
    images/chevalier_noir.png \
    images/reine_blanc.png \
    images/reine_noir.png \
    images/roi_blanc.png \
    images/roi_noir.png \
    images/tour_blanc.png \
    images/tour_noir.png

QMAKE_POST_LINK += xcopy /E /Y /I images $$OUT_PWD\\images
