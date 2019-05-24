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
<ul>
    <li>LibSSH</li>   
    <li>QT 5</li>
</ul>

## Build and install
Pour que l'application puisse compiler, vous devez d'abord installer le paquet suivant :
<ul>
    <li>libssh-devel</li>   
</ul>

Voir sur [libssh](https://www.libssh.org) pour l'installation.
On sait que sur linux mint :

> sudo apt install libssh-dev

Pour mac :

> brew install libssh

Configuration QT Creator (à installer au préalable) :

Une fois cela fait, il vous faut ouvrir le projet avec QT. Il faut faire un clic droit sur le projet > Add Library > External Library > 
Platform : La plateforme correspondante
Library file : Le fichier de l'installation faite à l'étape précédente (p.ex. /usr/lib/x86_64-linux-gnu/libssh.so -> ${whereis libssh}) 
Include : à partir de notre projet -> GUI/libssh/include > Next > Finish.

Une fois cela fait, l'application est prête à compiler.

## Run

Il y dossier release qui contient les différents exécutables selon les OS :
<ul>
    <li>Linux : *.appimage</li>   
    <li>Mac OS : *.dmg</li>
</ul>
Linux : Avant de pouvoir l'exécuter on devra faire :

> sudo chmod u+x MegaMachineEvolution-x86_64.AppImage

> ./MegaMachineEvolution-x86_64.AppImage

## Documentation
La documentation est inclue à la racine, sous forme d'un fichier PDF regroupant 3 fichiers : Rapport de projet, Manuel Utilisateur et Documentation Développeur. 
