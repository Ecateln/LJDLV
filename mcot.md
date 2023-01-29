# Le Jeu de la Ville: Étude de modèles de villes générées via un automate cellulaire

## Présentation rapide

L'optimisation des structures urbaines et de leur organisation est un enjeu primordial au bien être des citoyens.
C'est pourquoi la génération d'une ville respectant certains critères donnés, à l'aide d'un outil informatique, peut s'avérer des plus utiles dans le contexte sociétal actuel.

L'utilisation d'un automate cellulaire permet, avec une grande flexibilité, de construire un modèle de ville ainsi que de représenter et d'étudier son évolution afin d'adapter les résultats obtenus pour proposer de nouvelles règles et mieux répondre aux besoins des futurs habitants.

## Positionnement thématique

INFORMATIQUE (Informatique pratique)  
INFORMATIQUE (Informatique théorique)  
MATHÉMATIQUES (Autres domaines: Automates Cellulaires)  

## Mots-clés

### Français
Automate cellulaire  
Modélisation  
Évolution Probabiliste  
Représentation Graphique  
Optimisation  

### Anglais

Cellular Automaton  
Modeling  
Probabilistic Evolution  
Graphical Interface  
Optimization  

## Bibliographie commentée

John von Neumann, un mathématicien et physicien américo-hongrois (1903-1957), qui travaillait dans les années 1940 sur les systèmes auto-réplicatifs, ne parvennait pas à trouver de modèle satisfaisant afin de démontrer son idée de robot capable de construire une copie de lui-même à partir de pièces détachées. Il s'inspira alors du travail d'un de ses collègues chercheur en cristallographie pour créer le premier automate cellulaire. Cette première version est représentée par une grille en deux dimensions dont chaque case peut prendre l'un des 29 états disponibles. [1]  
C'est en 1970, alors que d'autres étudiaient le comportement de ce nouveau concept, que John Conway publia son "Jeu de la Vie", un automate cellulaire dont il avait méticuleusement choisi les règles, ne comportant cette fois-ci que deux états possibles : "vivant" ou "mort". Cette publication entraîna une longue succession d'études de la part de communautés de mathématiciens, d’informaticiens et de certains physiciens, qui commençaient à comprendre les applications infinies du modèle proposé par Neumann. [2] [3] [5]  

Je me suis alors demandé s'il était possible de me servir de l'invention de Neumann pour proposer à mon tour un ensemble de règles qui, cette fois-ci, permettraient de représenter l'évolution d'une ville en fonction de ses besoins, de ses capacités de développement et/ou d'autres facteurs. Je souhaitais en plus de cela trouver une façon simple pour moi de représenter ce futur algorithme complexe tout en optimisant autant que possible le calcul de chaque état via des techniques telle que la mémoïsation. [2]  
Commença alors la phase d'élaboration des règles, que je cherchais à rendre aussi fidèles que possible au comportement "réel" d'une ville, le but principal étant ici de produire une ville qui serait considérée comme viable et agréable pour sa population. Je me renseignai donc sur les critères les plus importants aux yeux des habitants d'une ville. [4]  
Certains paramètres ne pourront malheureusement pas être pris en compte pour ce projet, principalement par manque de temps concernant la mise en oeuvre de ceux-ci dans mon programme, mais il serait fort intéressant de voir un outil prenant en compte des critères de génération tels que la météo ou bien la création de réseaux routiers. Je me concentrerai donc sur des règles prenant en compte les composants les plus importants au sein d'une ville, tels que les habitations, les commerces, et des lieux de travail, ainsi que des loisirs. L'utilisation de règles probabilistes pour la modélisation sera d'autant plus intéressante, car l'interprétation des résultats n'en sera que plus significative en cas de convergence vers un même état final pour un état initial ou règles différents.  

## Problématique retenue

Peut-on espérer pouvoir un jour compter sur des algorithmes tels que des automates cellulaires afin de générer des organisations de villes entières ?

## Objectifs du TIPE

1. Appliquer le principe d'automate cellulaire à une modélisation de zone urbaine
2. Étudier les différents besoins d'une ville et de ses habitants
3. Définir des règles de génération à partir de l'étude précédente et étudier les comportements de celles-ci

## Abstract

(résumé de la bio en anglais)

## Références bibliographiques (phase 2)

John Von Neumann: [Theory of self-reproducing automata](https://archive.org/details/theoryofselfrepr00vonn_0/page/n13/mode/2up)

Ralph William Gosper: [Exploiting regularities in large cellular spaces](https://doi.org/10.1016/0167-2789(84)90251-3)

Martin Gardner: [The fantastic combinations of John Conway's new solitaire game « life »](https://web.stanford.edu/class/sts145/Library/life.pdf)

Huw Oliver: [The 53 best cities in the world in 2022](https://www.timeout.com/things-to-do/best-cities-in-the-world)

Numberphile: [Inventing Game of Life](https://www.youtube.com/watch?v=R9Plq-D1gEk)

## DOT

~~TODO: Rencontrer Conway ?~~
* j'ai codé un truc à un moment, faudrait ptet le dire
* La conférence avec le matheux qui avait des fonds d'écran rigolos
(- pourquoi pas passer 5h en OCaml pour faire un quadrillage avec des pixels qui bougent ?)
