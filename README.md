# Terminal-UI
Tu rêve de pouvoir faire des widget a ta sauce ?

# BUG-PROBLEM
- Il faut gérer les caractère UTF-8.
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
| \\                 | Barre oblique inversée (\\). Doit être échappée pour éviter des erreurs. |
| \'                 | Apostrophe (dans les littéraux de caractère).                |
| \"                 | Guillemet (dans les chaînes). Peut perturber si mal échappé. |
| \?                 | Point d'interrogation pour éviter ?? (trigraphes).           |
| Caractères invisibles | Espaces insécables (\u00A0), etc., difficiles à repérer visuellement. |


| Code     | Description                      |
|----------|----------------------------------|
| \0       | Caractère nul (fin de chaîne C) |
| \xNN     | Caractère hexadécimal (e.g., \x41 pour A) |
| \NNN     | Caractère octal (e.g., \101 pour A)        |

| Séquence    | Description                                |
|-------------|--------------------------------------------|
| \uXXXX      | Code point Unicode sur 16 bits (UTF-16)   |
| \UXXXXXXXX  | Code point Unicode sur 32 bits (UTF-32)   |




# Plus tard
- améliorer ce read.me avec des images
