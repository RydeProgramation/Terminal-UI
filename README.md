# 🧱 Terminal-UI — Projet C++ de Rendu et Interface Terminal

> **Auteur :** MOHAMED  
> **Langage :** C++17+ / C++20  
> **Version :** 0.4.1 (Prototype avancé)  
> **Statut :** En développement 🚧  
> **Objectif :** Créer un moteur modulaire pour interfaces terminal, avec rendu, widgets et langage de définition `.widg`.

---

## 🧭 Présentation du projet

Le projet **Terminal-UI** est une bibliothèque C++ visant à fournir une **infrastructure complète de rendu et d’interaction dans le terminal**.  
Il permet de créer des **widgets textuels dynamiques** (boutons, fenêtres, barres de progression, etc.) avec un langage XML propriétaire, sans dépendances graphiques externes.

Objectifs principaux :
1. Fournir une base solide pour le **rendu en mode texte**.  
2. Permettre aux développeurs de **concevoir leurs propres composants visuels**, à la manière d’un moteur d’interface moderne, mais dans le terminal.

> 🎯 *“Tu rêves de pouvoir faire des widgets à ta sauce ? Ce projet te donne les outils pour les créer.”*

---

## ⚙️ Architecture modulaire

Le projet est découpé en modules indépendants, chacun responsable d’une partie spécifique du moteur :

| Module | Rôle principal | Statut |
|--------|----------------|--------|
| **AudioModule** | Gestion des sons et notifications audio | 🟡 À Dévlopper |
| **Components** | Composants de base des widgets (boutons, textes, conteneurs) | 🟢 Fonctionnel |
| **Core** | Structures internes, types fondamentaux (trPair, trMulti, etc.) | 🟢 Stable |
| **Engine** | Cœur du moteur, logique principale et communication inter-modules | 🟢 Stable |
| **InputModule** | Gestion des entrées clavier et souris | 🟢 Stable |
| **LoadModule** | Chargement et parsing des fichiers `.widg` (XML propriétaire) | 🟡 En développemen |
| **PrintModule** | Impression texte et gestion couleurs ANSI | 🟡 Instable |
| **Render** | Pipeline de rendu, positionnement | 🟢 Fonctionnel |
| **Tool** | Boîte à outils mathématique, alogorithmique... | 🟡 En développement |
| **UI** | Système hiérarchique des widgets, focus, masquage | 🟢 Fonctionnel |
| **World** | Contexte global, gestion de scène et logique environnementale | 🟢 Fonctionnel |

---

## 🧩 Langage `.widg` — XML propriétaire

Chaque widget peut être décrit via un fichier `.widg`, utilisant un XML personnalisé avec des balises avancées.  
Ces balises permettent de définir **les propriétés, la position, le contenu et les couleurs...** d’un widget.

### 📋 Liste des balises et leur rôle (INCOMPLET)

| Balise | Description |
|--------|-------------|
| `<trObject>` | Conteneur principal d’un objet dans la scène. Peut contenir des widgets, actors ou pawns. |
| `<Properties>` | Définition des propriétés de l’objet (booléens, entiers, chaînes). |
| `<Property>` | Une propriété spécifique d’un objet. Attributs : `name` (nom), `type` (type de donnée). |
| `<trActor>` | Section pour définir le comportement d’un acteur dans le widget. |
| `<APPLY_Implementation>` | Code spécifique à exécuter pour cet acteur. (Optionnel, à supprimer si vide.) |
| `<trPawn>` | Définition de la position et du type de placement du widget dans le terminal. |
| `<Position>` | Coordonnées du widget : `x` et `y`. |
| `<RelativePositionType>` | Type de position relative : ex. `MiddleCenter`, `TopLeft`. |
| `<trWidget>` | Section représentant le widget réel à afficher, avec taille et contenu. |
| `<Size>` | Définition de la taille du widget : `width` et `height`. |
| `<Content>` | Contenu textuel du widget, structuré en lignes. |
| `<Line>` | Ligne de texte à afficher dans le widget. Attribut : `Content`. |
| `<Color>` | Couleurs du widget : `foreground` et `background` (format HEX RGBA). |

Le tableau n'est pas complet, me contacter pour d'autre informations !

## 🧩 Fonctionnalités actuelles

- Rendu de texte et de widgets dans le terminal avec rafraîchissement partiel et multi-couches.  
- Gestion des événements clavier en continu (mode non-bloquant).  
- Système de couleurs interne compatible ANSI avec support du masquage et superposition des widgets.  
- Support complet des séquences spéciales (`\n`, `\r`, `\t`, `\b`, etc.) et gestion des caractères invisibles.  
- Gestion mémoire avancée : allocation/désallocation automatique, suivi des fuites potentielles.  
- Système de **delta time** pour synchroniser animations, déplacements et transitions des widgets indépendamment du taux de rafraîchissement.  
- **Animations et transitions** : déplacement fluide des widgets, apparitions/disparitions progressives, effets de surbrillance et changement de couleurs dynamique.  
- Optimisation du rendu : rafraîchissement partiel des zones modifiées, évitant le redessin complet du terminal.  
- Gestion hiérarchique des widgets : focus, masquage (`hide/show`) et organisation interne.  
- Support de fichiers `.widg` pour charger dynamiquement des widgets depuis XML.  
- Structures internes puissantes : `trPair`, `trMulti`, `trMap` personnalisée pour améliorer la performance par rapport à `std::vector`.  
- Base prête pour intégrer des modules supplémentaires : audio, interactions souris, scènes complexes, etc.  

> 💡 *Ces fonctionnalités montrent que Terminal-UI est un système **modulaire, performant et capable de gérer des animations complexes** directement dans le terminal.* 

---

## 🧪 Étapes de développement

### 1️⃣ — Première itération : Base du moteur
- Mise en place du moteur de rendu en texte pur.  
- Création de la première classe `trPair` (élément de base pour gérer coordonnées et styles).  
- Définition d’une map interne (`trMap`) pour stocker les entités affichables.  
- Tests initiaux sur la coloration, l’alignement et la performance du rafraîchissement.  
- Premiers essais d’affichage multi-lignes et multi-éléments dans le terminal.  

### 2️⃣ — Seconde itération : Gestion des entrées
- Ajout d’un système de détection des touches, en mode **non-bloquant**.  
- Implémentation d’un **tampon multithread** pour ne rater aucune touche même lors de rendus complexes.  
- Découverte et correction d’un bug critique : *les touches restaient actives en permanence* (effet “Cheval de Troie”).  
- Optimisation des boucles d’événements pour réduire la latence entre saisie et réaction.  

### 3️⃣ — Troisième itération : Organisation des contenus
- Développement de `ContentReorganisation()` pour optimiser le rafraîchissement et éviter le redessin complet inutile.  
- Gestion de **fuites mémoire potentielles** à la création massive de widgets.

**Ancien rendu :**

![image](https://github.com/user-attachments/assets/13648a60-4fb6-4188-bc11-3bef1952be6e)

**Nouveau rendu :**

![image](https://github.com/user-attachments/assets/3da9de98-7350-4619-a5cb-2649bafdf5c2)
  
- Mise en place de tests internes pour valider le comportement des widgets dans des conditions extrêmes.  
- Ajout du **système de détection de collisions** entre widgets : l’utilisateur peut récupérer les collisions et définir les réactions souhaitées.  

### 4️⃣ — Quatrième itération : Expérimentation graphique et systèmes de rendu
- Création de **trois systèmes de rendu** distincts :  

  | Système | Description | Avantages / Inconvénients |
  |---------|------------|---------------------------|
  | **DIRECT_SYSTEM** | Chaque caractère est écrit directement sur le terminal | Très simple, mais **très lent**, provoque lag et bugs visuels |
  | **BUFFER_SYSTEM** | Tout est écrit dans un `ostringstream` tampon avant affichage | Fluide pour peu d’actions, mais **instable** avec de nombreux changements simultanés |
  | **RENDER_SYSTEM** | Buffer complet pour tous les éléments, sans toucher directement au terminal | **Le plus performant et fluide**, gestion complète des positions et superpositions, modifications possibles **avant affichage** |

- Passage progressif à une architecture **multi-couches** pour le rendu.  
- Gestion de la **superposition contrôlée des widgets** et des zones d’affichage partiel.  
- Optimisation globale avec **delta time**, permettant des animations et transitions fluides indépendamment du framerate.  
- Déplacement dynamique des widgets, changements de contenu et effets de transition appliqués directement via le buffer.  
- **Gestion complète des couleurs** : couleurs de premier plan, arrière-plan, surbrillance, et transitions dynamiques sur tous les widgets.  

### 5️⃣ — Cinquième itération : Optimisation et robustesse
- Optimisation **partout** : rafraîchissement partiel, calcul delta time, buffers internes.  
- Système de **détection de collisions** entièrement intégré pour gérer interactions entre widgets.  
- Gestion hiérarchique des widgets : focus, masquage (`hide/show`) et organisation interne.  
- **Chargement et aperçu dynamique d’un fichier `.widg`** :  
  - Ouvrir un widget depuis l’application pour le visualiser **seul** avec toutes ses animations et couleurs.  
  - **Modification en direct du fichier XML** : les changements apparaissent immédiatement dans l’aperçu du widget.  
  - Permet de tester et déboguer des widgets sans recompiler l’application.  
- Base solide pour intégrer des fonctionnalités supplémentaires : sons, souris, multi-couches complexes.  

> 💡 *À ce stade, Terminal-UI est un moteur **extrêmement flexible et interactif**, capable de gérer des interfaces complexes, animations, collisions, couleurs et interactions dans un environnement purement console, tout en permettant l’édition et la prévisualisation en temps réel.*

---

## 🧰 Liste des bugs et problèmes connus

- [ ] Gestion du masquage (`hide`) des widgets.  
- [ ] Système de souris à implémenter (détection, clic, hover).   
- [ ] Les touches fonctionnent en continu — effet cheval de Troie.  
- [ ] Optimiser `ContentReorganisation()`.  
- [ ] Améliorer `trMap` → remplacer le `std::vector` par une structure interne personnalisée.  
- [ ] Surveillance mémoire : vérifier les potentielles fuites lors de la création de multiples widgets.  

---

## 🔤 Gestion des séquences et caractères spéciaux

| Séquence/Caractère | Description / Effet potentiel |
|--------------------|------------------------------|
| `\n` | Saut de ligne — peut casser la mise en forme. |
| `\f` | Saut de page — rarement utilisé. |
| `\v` | Tabulation verticale — peut désaligner le rendu. |
| `\r` | Retour chariot — peut écraser une ligne existante selon l’OS. |
| `\t` | Tabulation horizontale — espacement variable selon le terminal. |
| `\b` | Retour arrière — effet visuel imprévisible. |
| `\0x` | Caractère vide — à surveiller. |
| `\\` | Barre oblique inversée — doit être échappée correctement. |

---

## 🧠 Difficultés rencontrées

- Gestion asynchrone des entrées clavier sans bloquer le rendu.  
- Synchronisation entre rafraîchissement visuel et logique des widgets.  
- Manipulation directe des codes ANSI pour les couleurs et positions.  
- Compatibilité entre environnements Windows / Linux.  
- Suivi mémoire précis sans dépendance externe.

---

## 🚀 Prochaines étapes

### 🔹 Améliorations prévues
- Implémenter le **système de souris** (détection des positions, clics, événements).  
- Créer un **fichier de définition de widget** (`.widget`) pour sauvegarder la configuration d’un composant.  
- Ajouter une **API de son** simple pour des effets audio dans le terminal.  
- Améliorer la **documentation interne** (Doxygen ou Markdown détaillé).  
- Créer un **exemple complet** (mini UI avec plusieurs widgets interactifs).  
- Intégrer un **système de profilage mémoire et CPU** pour l’optimisation.  

### 🔹 Vision long terme
> Transformer Terminal-UI en un **moteur complet de rendu console** open-source, modulable et extensible, inspiré des architectures d’Unreal Engine et d’autres frameworks C++ modernes, mais conçu pour un environnement texte.

---

## 📈 Conclusion

Le projet **Terminal-UI** représente une tentative ambitieuse de **repenser l’interface utilisateur dans le terminal**, avec une approche orientée performance, modularité et plaisir de développement.  
Le travail futur consistera à consolider les fondations techniques et à étendre les capacités d’interaction, tout en maintenant une **philosophie minimaliste et purement C++**.

> 🧠 *“Quand le terminal devient ton canvas, chaque caractère compte.”*  

---
