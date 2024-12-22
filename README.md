# Terminal-UI
Tu rêve de pouvoir faire des widget a ta sauce ?

# BUG-PROBLEM
- Il faut gérer les caractère UTF-8.
- Réorganiser l'orde des fonciton de le fichier trWidget.cpp
- Il faut gérer les différentes couleurs.
- ~~Il faut mieux gérer les problèmes de clean d'un widget.~~
- Il faut gérer le fait de pouvoir "hide" un widget.
- Il faut recrée le system de keyboardmanagment et crée un système pour la souris.
- FAIRE une meilleur documentation des fonction
- Il faut gérer tout les code/séquence :

| Séquence/Caractère | Description ou Problème potentiel                             |
|--------------------|--------------------------------------------------------------|
| \n                 | Saut de ligne. Peut perturber la mise en forme en ajoutant des sauts. |
| \f                 | Saut de page.                                                | fait
| \v                 | Tabulation verticale.                                        | fait
| \r                 | Retour chariot. Peut causer des comportements différents selon l'OS. | fait
| \t                 | Tabulation horizontale. Les tabulations peuvent varier selon l'éditeur. | fait
| \b                 | Retour arrière (backspace). Difficulté visuelle, car invisible. | fait
| \\\                 | Barre oblique inversée (\\). Doit être échappée pour éviter des erreurs. | PAS fait


# Pour le futur
## Plus tard
- améliorer ce read.me avec des images
## ajout
- Pourvoir créer/utiliser des ficher par exemple .widget pour avoir des widgets
