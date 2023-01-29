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
John von Neumann, un mathématicien et physicien américo-hongrois (1903-1957), qui travaillait dans les années 1940 sur les systèmes auto-réplicatifs ne parvennait pas à trouver de modèle satisfaisant afin de démontrer son idée de robot capable de construire un copie de lui même à partir de pièces détachées. Il s'inspira alors du travail d'un de ses collègues chercheur en crystallographie pour créer le premier automate cellulaire. Cette première version représentée par une grille en deux dimensions dont les cases peuvent prendre 29 états différents entraîna une longue succession d'études de la part de communautés de mathématiciens et de certains physiciens. [1] [6]

- organisation de villes very important -> prendre en compte bcp de facteurs (faire liste), trop de situations dans lesquels bcp inconvénients, alors on va coder un truc qui évite tout ça
- importance du choix des règles (Conway il a mis 1an et demi (trouver vidéo (veritassium ?)))
- expliquer que ici juste ébauche et non travail complet -> bcp plus de temps requis afin de faire un truc qui tient la route -> exemples de fonctionalités supplémentaires (grille infinie, optimisations avec mémoization des patterns...)

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

Tim Tyler: [Cellular Automata FAQ](http://cafaq.com/)

Huw Oliver: [The 53 best cities in the world in 2022](https://www.timeout.com/things-to-do/best-cities-in-the-world)

Numberphile: [Inventing Game of Life](https://www.youtube.com/watch?v=R9Plq-D1gEk)

Martin Gardner: [The fantastic combinations of John Conway's new solitaire game « life »](https://web.stanford.edu/class/sts145/Library/life.pdf)

## DOT
~~TODO: Rencontrer Conway ?~~
- j'ai codé un truc à un moment, faudrait ptet le dire
- La conférence avec le matheux qui avait des fonds d'écran rigolos
(- pourquoi pas passer 5h en OCaml pour faire un quadrillage avec des pixels qui bougent ?)