
# ✅ Répartition des tâches — Projet Jeux d'Échecs

Cette liste est basée sur les fichiers fournis et les exigences de la remise. Elle inclut d'abord les tâches globales **à faire immédiatement**, puis la répartition entre Dév A (logique/modèle) et Dév B (interface/vue Qt).

---

## 🚨 À faire immédiatement avant de séparer

- [x] Supprimer toute logique de `QMessageBox` du modèle (`Echiquier`, `Roi`, etc.)
- [x] Supprimer toute manipulation graphique (`setIcon`, `QPushButton`, `QPixmap`) dans le modèle
- [x] Corriger tous les chemins d'accès aux images Qt (ex. via `QDir::currentPath()` ou copie automatique en `.pro`)
- [ ] Passer de `QPushButton` à `QLabel` + `QPixmap` pour dessiner l'échiquier
- [ ] Renommer le namespace `Modele` → `Chess` (ou `Logique`, `Engine`, etc.)
- [x] Utiliser des noms explicites pour les coordonnées (`ligneDepart`, `colonneArrivee`, etc.)
- [x] Créer un `struct Position { int ligne, colonne; };` (facultatif mais recommandé)

---

## 👤 Dev A– Logique / Modèle (`Chess`)

### 🔧 Refactor et responsabilité du modèle
- [ ] Supprimer `changerJoueur()` de `Echiquier`, le faire dans le contrôleur
- [ ] Revoir la responsabilité d’`Echiquier` : ne plus peindre l’interface
- [x] Implémenter la **capture de pièces**
- [ ] Ajouter une méthode dans chaque pièce : `std::vector<Position> mouvementsPossibles(Position pos, const Echiquier&)`
- [ ] Déplacer la logique de mise en échec **dans les classes des pièces**
- [ ] Intégrer la vérification de mise en échec dans les méthodes de déplacement
- [ ] Ajouter support d’une **position initiale chargée dynamiquement** (menu ou fichier)
- [ ] Couvrir **100% du code du modèle avec tests unitaires** (`TestJeuxEchecs.cpp`)

---

## 👤 Dev B – Interface / Vue (`ProjetJeuxEchecs`)

### 🎨 Qt & Interaction
- [ ] Remplacer tous les `QPushButton` par des `QLabel` pour les cases
- [ ] Utiliser `QPixmap` pour afficher les pièces sur l’échiquier
- [ ] Mettre en surbrillance les mouvements valides d’une pièce sélectionnée
- [ ] Gérer la sélection/déplacement de pièce via clic sur cases
- [ ] Afficher les messages de retour (`mise en échec`, `capture`, etc.) via `statusBar()` ou `QLabel` sous l’échiquier
- [ ] Ajouter un bouton/menu `Nouvelle partie` (réinitialiser échiquier)
- [ ] Intégrer une `ComboBox` ou équivalent pour choisir une position initiale
- [x] Supprimer toute dépendance aux `.ui` si non utilisé

---

## 📦 À valider ensemble avant la remise

- [ ] Compilation croisée avec `qmake` et pas `cmake`
- [ ] Exécutable fonctionne sans fichiers manquants (`images/`, etc.)
- [ ] Fichier `.pro` minimal et à jour
- [ ] Tous les tests unitaires passent (utilisation de `gtest`)
- [ ] Interface claire, sans widgets inutilisés ou morts
