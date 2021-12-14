# Colons_Game
![image description](./data/logo.png)


## Description


## requirement 

- C++ 11 
- une distribution d'un Systeme Linux est préferé (Ubuntu , Debian ) .

## Compiler et lancer le jeu 
le fichier makefile contient tous les instructions essentiels pour compiler et lancer le jeu . 

    make clean ; make ; ./out ;

Vous pouvez egalemet lancer directement 

    ./out


## Organisation du projet 

<code>board_data_structures</code> ce dossier contient les classes utilisées dans le backend et qui stockent les données du tableaux de board comme les positions des tuiles , noeuds et routes ainsi que les contraintes du regles de jeu .

<code>game</code> ce dossier comporte tous les classes qui controle la parti graphique du programme ainsi que d'autre classes intermedieres entre le back-end et le front-end comme board.cpp 

    ├── board_data_structures  
    │   ├── data_structures.cpp         
    │   ├── data_structures.h            
    │   └── workspace.code-workspace
    |
    ├── data
    ├── game
    │   ├── board.cpp
    │   ├── dessin.cpp
    │   ├── Dice.cpp
    │   ├── my_window.cpp
    │   ├── player.cpp
    │   ├── rules_win.cpp
    │   ├── thief_win.cpp
    │   ├── welcome_window.cpp
    │   └── workspace.code-workspace
    ├── header.h
    ├── Icon.png
    ├── LICENSE
    ├── main.cpp
    ├── makefile
    ├── README.md
    ├── style.css




## Run app  

make clean ;make; ./out;


## Diagram de class 

Ce diagramme UMl donne une idée  sur l'architecture generale du projet . des informations plus en detail sur les methodes et les attributs sont disponible dans les fichier <code> header.h</code> et <code> data_structure.h</code> . 


![image description](Catanes_UML.png)



## Jeu

Le score finale pour gangner a ete fixer à 5 (au lieu de 10 ) .  

### Régles du jeu

puisque ce jeu ne permet pas de faire les echanges entre joueur et banque  si le jouer ne place pas correctement ces colonie lors de la phase d'initiation ça peut arriver qu'il puisse pas avoir une ressource particluiere et donc ce jouer=uer reste bloqué 
Donc essayer de bien placer vos colonie pour tester le jeux SVP. 

### Comment jouer  