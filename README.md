# PRO B-13 : ÉVOLUTION D’AUTOMATES POUR LE TRAITEMENT DE SÉQUENCES GÉNOMIQUES

Outil pour traiter les informations génomiques de différents organismes, issues de bases de données publiques. L’outil sera basée, d’un côté, sur l’analyse des séquences par des automates (machines à états) et, d’un autre, sur l’utilisation d’un algorithme évolutionniste (une technique d'apprentissage automatique) pour la construction automatique desdits automates.

Une bonne partie du comportement des êtres vivantes est définie par son génome (ADN) et par les protéines qui en découlent. L’analyse des informations contenues dans le génome d’un organisme facilite la compréhension de nombreux phénomènes. Ces informations génomiques sont représentées en forme de (longues) séquences de caractères. Que ce soit de l’ADN, dont les séquences sont composées par un alphabet de 4 lettres (A,C,G,T), ou des protéines représentées par un alphabet de 20 lettres.

Une forme de parcourir et traiter de telles séquences (par exemple pour y trouver des sous-séquences particulières) est d’utiliser des automates finis. Néanmoins, la conception des automates adéquats pour une analyse particulier étant très complexe, on propose d’utiliser une technique d’apprentissage automatique à ce fin: un algorithme évolutionniste simple.

L’outil développé devra permettre à un utilisateur d’appliquer la méthode décrite ci-dessus à une collection de séquences fournie.

Development team:

| Name                                 | Email                        | Github            |
|--------------------------------------|------------------------------|-------------------|
| Bonjour Mickael                      | mickael.bonjour@heig-vd.ch   | mbonjour          |
| Mettler Samuel                       | samuel.mettler@heig-vd.ch    | SamuelMettler     |
| Pantic Nemanja                       | nemanja.pantic@heig-vd.ch    | panticne          |
| Seville Nathan                       | nathan.seville@heig-vd.ch    | nathanseville     |
| Simeonovic David                     | david.simeonovic@heig-vd.ch  | IxSysTech         |

## Dependencies

Ce logiciel est compatible sur un environnement Linux et Mac OS. Notre application peut se connecter en SSH à un serveur afin de récupérer des données contenant des séquences ACGT. Il est également possible de fournir un fichier.

## Build and install

Vous trouverez dans les différents dossiers des exécutables qui correspondent aux OS cités précédemment.

## Run

Notre interface se présente sous cette forme :

<--Insérer image-->

Dans un premier temps l'application a besoin de récupérer des séquences, vous avez le choix entre deux onglets, un pour se connecter en SSH sur un serveur et un autre pour upload un fichier.

Une fois cette étape franchie vous arriverez sur cette deuxième fenêtre

<--Insérer image-->

Elle vous permet de sélectionner vos méthodes d'évolution,de croisement, etc. Vous pouvez également décider d'enregistrer dans un fichier de log tous les résultats générés par l'application. Lancez les simulations en appuyant sur "Run simulation" <expliquer où sera stocké le résultat de la machine finale>

## Documentation

Vous trouverez dans /documentations nos différents documents concernant les outils utilisés dans notre projet ainsi que notamment un manuel d'utilisateur

