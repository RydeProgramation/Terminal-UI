# Terminal-UI
Tu rêve de pouvoir faire des widget a ta sauce ?

# BUG-PROBLEM
- Il faut gérer le fait de pouvoir "hide" un widget.
- Il faut gérer quand on reste cliquait sur une touche. Comme sur un jeu quand on veut avancer.
- Il faut recrée le system de keyboardmanagment et crée un système pour la souris.
- FAIRE une meilleur documentation des fonction
- J'ai un trPair, il faut implémenter un trMulti
- Améliorer trMap, éviter d'utiliser un vector est crée un truc moi-même
- La mémoire ne fait qu'augmenter ? Normalement régler
- ![image](https://github.com/user-attachments/assets/13648a60-4fb6-4188-bc11-3bef1952be6e)
- passé a 
- ![image](https://github.com/user-attachments/assets/3da9de98-7350-4619-a5cb-2649bafdf5c2)

- Il faut gérer tout les code/séquence :

| Séquence/Caractère | Description ou Problème potentiel                             |
|--------------------|--------------------------------------------------------------|
| \n fait                | Saut de ligne. Peut perturber la mise en forme en ajoutant des sauts. |
| \f fait               | Saut de page.                                                |
| \v fait                | Tabulation verticale.                                        | 
| \r fait                | Retour chariot. Peut causer des comportements différents selon l'OS. | 
| \t fait                | Tabulation horizontale. Les tabulations peuvent varier selon l'éditeur. |
| \b fait                | Retour arrière (backspace). Difficulté visuelle, car invisible. | 
| \0x                 | Vide |
| \\\                 | Barre oblique inversée (\\). Doit être échappée pour éviter des erreurs. |


# Pour le futur
## Plus tard
- améliorer ce read.me avec des images
## ajout
- Pourvoir créer/utiliser des ficher par exemple .widget pour avoir des widgets
- Pouvoir gérer le son !
