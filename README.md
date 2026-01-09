# BABA IS YOU - Implémentation C++

Ce projet est une implémentation en C++ du jeu **BABA IS YOU**, réalisée par Badr Motaim et NANMEDIGOU yendoumban.

Le jeu repose sur un système de règles dynamiques où les propriétés des objets peuvent changer en fonction des mots présents dans le niveau. Le joueur doit exploiter ces règles pour résoudre les énigmes et atteindre la condition de victoire.

## Modes de jeu

* **Mode Normal** : Le joueur parcourt les niveaux dans un ordre prédéfini. Il doit terminer un niveau pour débloquer et accéder au suivant.
* **Mode Explorer** : Le joueur peut choisir librement n’importe quel niveau disponible, sans contrainte de progression.

## Prérequis

* Un compilateur C++ compatible (g++ recommandé)
* **make**
* Un environnement Linux ou WSL (testé sous WSL)

## Compilation et exécution

La compilation et l’exécution du jeu se font automatiquement via le Makefile.

1.  **Se placer à la racine du projet (otosan) :**
    ```bash
    cd otosan
    ```

2.  **Nettoyer les fichiers de compilation :**
    ```bash
    make clean
    ```

3.  **Compiler et lancer le jeu :**
    ```bash
    make
    ```
    Le `make` compile le projet et lance directement le jeu.

## Exemple de commandes dans le terminal

```bash
/mnt/c/Users/DELL/OneDrive/Desktop/Cours Master/C++/otosan$ make clean
/mnt/c/Users/DELL/OneDrive/Desktop/Cours Master/C++/otosan$ make