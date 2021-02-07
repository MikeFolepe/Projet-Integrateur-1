Projet d'INF1900 / Version 1.0 / Date : 2020-12-08
_______________________________________________________________________________________________________________
Étapes à suivre pour la création du fichier ".HEX", afin d'exécuter la simulation du projet final

1- Compilation de la librairie :
Dans un premier temps, il vous faudra compiler les fichiers sources de la librairie contenant 
l'ensemble des fichiers utiles à la création de l'exécutable du code du projet. Pour ce faire, 
il vous suffit d'entrer dans le dossier "lib_dir". Par la suite, ouvrez un invité de commande 
et entrez dans le terminal la commande "make";

Chemin pour l'accès aux fichiers sources de la librairie : /inf1900-0712/lib_dir


2- Création du fichier .HEX (firmware) pour le microcontrôleur :
Lorsque l'étape précédente est effectuée, il suffit de générer le fichier .HEX qui vous per-
mettra de mettre en marche notre projet. Pour ce faire, il suffit de retourner dans le 
dossier "Projet", puis d'entrer dans le dossier intitulé "main". Lorsqu'effectué, exécutez
la commande "make";

Chemin pour l'accès au répertoire : /inf1900-0712/Projet/main


3-Chargement du circuit dans simulIDE (fichier .simu) :
Exécutez l'application "simulIDE". Sélectionnez l'option "ouvrir circuit" (open circuit en anglais) 
(la deuxième à partir de l'extrême gauche), entrez dans le dossier "inf1900-0712", ensuite dans le 
dossier "Projet", puis dans le dossier main. Cliquez sur le fichier intitulé "montage.simu";

Chemin pour l'accès au fichier ".simu" : /inf1900-0712/Projet/main


4- Simulation du projet final :
Après avoir effectué les étapes précédentes, vous êtes en mesure de pouvoir exécuter le fichier
".HEX" du projet final sur le microcontrôleur. Pour ce faire, faites un clique-droit sur la puce 
(microcontrôleur), cliquez sur "charger le firmware" (load firmware en anglais). 
Entrez ensuite dans le même dossier où vous avez généré le fichier ".HEX" à l'étape 2, et 
sélectionnez le fichier du nom "main.HEX".

Avant de lancer la simulation SimulIDE, il faut activer le voltage fixe relié au relais (reset de l'horloge).

Chemin pour l'accès au répertoire : /inf1900-0712/Projet

---------------------------------------------------------------------------------------------------------------
****L'implémentation des fonctions permettant de contrôler les périphériques suivant
se trouvent dans la librairie**** : Clavier, Portes (barres de DEL), Servomoteurs, Horloge, Sonar, écran LCD;

Pour y accéder, il suffit de se rendre dans le dossier "inf1900-0712". Cliquez ensuite sur le 
dossier "lib_dir". 

Chemin pour l'accès aux fichiers : /inf1900-0712/lib_dir

Voici les fichiers sources et les périphériques les correspondant :

Clavier --> clavier_lib.h, clavier_lib.cpp;
Barres de DEL (portes) --> barresDEL.h, barresDEL.cpp;
Horloge --> Horloge.h, Horloge.cpp;
Servomoteurs --> ServoMoteur.h, ServoMoteur.cpp
Sonar --> Sonar.h, Sonar.cpp;
écran LCD --> lcm_so1602dtr_m.h, lcm_so1602dtr_m.cpp, lcm_so1602dtr_m_fw.h, lcm_so1602dtr_m_fw.cpp;
---------------------------------------------------------------------------------------------------------------
Le fichier "main.cpp" contenant le programme s'exécutant sur le microcontrôleur comporte une inclusion du 
fichier "Projet.h" qui permet de règler ce dernier (le microcontrôleur) dépendamment de s'il est mode 
"simulation" ou "configuration". 


Chemin pour l'accès aux fichiers "Projet.h" et "Projet.cpp" : /inf1900-0712/lib_dir

---------------------------------------------------------------------------------------------------------------
Le fichier "Projet.h" contient une inclusion du fichier "Option2.h" qui comprend la signature de fonctions 
implémentées pour les actions de l'option 2 du mode "Configuration". Les fichiers "Option2.h" et "Option2.cpp" 
sont dans le dossier de la librairie --> Chemin pour l'accès aux fichiers "Option2.h" et "Option2.cpp" :  
/inf1900-0712/lib_dir

Le fichier "Projet.h" contient aussi une inclusion du fichier "action_lib.h" qui comprend la signature de 
fonctions implémentées permettant à l'utilisateur certains comportements sur une action , i.e. supprimer une 
action, ajouter une action, etc.

Chemin pour l'accès aux fichiers "action_lib.h" et "action_lib.cpp" : /inf1900-0712/lib_dir
---------------------------------------------------------------------------------------------------------------
Le fichier clavier_lib.h contient une inclusion du fichier "Tableaux.h", fichier comprenant la signature de 
fonctions pour la manipulation de tableaux (uint8_t[], char[], etc).

Chemin pour l'accès aux fichiers "Tableaux.h" et "Tableaux.cpp".
_______________________________________________________________________________________________________________











