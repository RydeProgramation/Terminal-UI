# Terminal-UI
Tu rêve de pouvoir faire des widget a ta sauce ?

# BUG-PROBLEM
- Il faut gérer les caractère UTF-8.
- Réorganiser l'orde des fonciton de le fichier trWidget.cpp
- Il faut gérer les différentes couelurs.
- Il faut mieux gérer les problèmes de clean d'un widget.
- Il faut gérer le fait de pouvoir "hide" un widget.
- Il faut recrée le system de keyboardmanagment et crée un système pour la souris.
- FAIRE une meilleur documentation des focntion
- Il faut gérer tout les code/séquence :

| Séquence/Caractère | Description ou Problème potentiel                             |
|--------------------|--------------------------------------------------------------|
| \n                 | Saut de ligne. Peut perturber la mise en forme en ajoutant des sauts. |
| \r                 | Retour chariot. Peut causer des comportements différents selon l'OS. |
| \t                 | Tabulation horizontale. Les tabulations peuvent varier selon l'éditeur. |
| \v                 | Tabulation verticale.                                        |
| \b                 | Retour arrière (backspace). Difficulté visuelle, car invisible. |
| \f                 | Saut de page.                                                |
| \\\                 | Barre oblique inversée (\\). Doit être échappée pour éviter des erreurs. |


# Pour le futur
## Plus tard
- améliorer ce read.me avec des images
## ajout
- Pourvoir créer/utiliser des ficher par exemple .widget pour avoir des widgets
