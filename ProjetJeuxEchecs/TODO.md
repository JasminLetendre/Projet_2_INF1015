- Je ne suis pas capable de voir les images dans mon dossier /images
- QLabel et QPixmap pour les images

- Ne pas utiliser des Push buttons pour les cases. Utilisez des labels ou des images

- Afficher les mouvements légaux d'une pièce en illuminant les cases où la pièce peut se déplacer
- Donner un nom plus descriptif pour votre namespace model, du genre logique, engine, chess, etc
- Évitez les getters, utilisez des fonctions amies
- Donner des noms plus descriptifs pour vos variables et paramètres plutôt que x1, y1, dx, etc et commentez vos fonctions qui performent des tâches complexes comme le déplacement de pièces, la mise en échec, la vérification des mouvements valides
- La mise en échec devrait être vérifiée lors du mouvement de la pièce, et donc être intégrale aux méthodes de déplacement, et non une méthode de votre classe échiquier.
- Le rôle de votre classe échiquier n'est pas très clair. Peindre l'interface relève de votre vue, soit votre classe ProjetJeuEchecs, et le mouvement des pièces est implémenter par les pièces elles-mêmes, la détection d'évènements comme une pièces cliquée relève de votre contrôleur, soit votre classe ProjetJeuEchecs. Le changement de joueur est implémenté dans votre logique une fois qu'un mouvement est fait.
- Faire la capture de pièces fonctionnels
- Avoir une manière pour dire qu’on veut démarrer une nouvelle partie et choisir d’une liste une position de départ
- Les tests avec aucune ligne non couverte pour la partie modèle du jeu. Vous n’avez pas à automatiser les tests de l’interface graphique (pas matière à ce cours).