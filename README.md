# PRESENT24

"Le chiffrement par bloc que vous devez implanter est une version réduite du chiffrement PRESENT.
PRESENT est un chiffrement à bas coût, conçu en 2007 par Bogdanov et al et standardisé ensuite par
l’ISO. La version de PRESENT que vous allez implanter, et qu’on appellera désormais PRESENT24 prendra
en entrée un message clair de 24 bits ainsi qu’une clé maître de 24 bits et produira en sortie un bloc chiffré
de 24 bits également. [...]. PRESENT appartient à la famille des
chiffrements dits SPN (Substitution-Permutation Network). Cette construction est la deuxième famille
largement utilisée pour concevoir un chiffrement par bloc, l’autre étant les réseaux de Feistel. Le principe
d’un chiffrement SPN est simple : chaque tour du chiffrement est constitué de trois couches :
* Une addition (XOR) de la sous-clé du tour à l’état.
* une couche de substitution pour assurer la confusion.
* une couche linéaire pour assurer la diffusion.
Le nombre de tours de PRESENT24 est fixé à 10."

# Table des matières

- [Hiérarchie des dossiers](#Hiérarchie-des-dossiers)
- [Lancement](#Lancement)
- [Details](#Details)
- [Information execution](#Information execution)
 
# Hiérarchie des dossiers

```bash
.
├── bin
│   └── crypto
├── build.sh
├── Makefile
├── README.md
├── src
│   ├── lib
│   │   ├── Attaque2Present24.c
│   │   ├── Attaque2Present24.h
│   │   ├── brouillon.c
│   │   ├── Cadencement.c
│   │   ├── Cadencement.h
│   │   ├── Chiffrement.c
│   │   ├── Chiffrement.h
│   │   ├── Dechiffrement.c
│   │   ├── Dechiffrement.h
│   │   ├── MyInclude.c
│   │   ├── MyInclude.h
│   │   ├── Test.c
│   │   ├── Test.h
│   │   ├── Trier.c
│   │   └── Trier.h
│   └── main
│       └── Main.c
└── target
    ├── Attaque2Present24.o
    ├── Cadencement.o
    ├── Chiffrement.o
    ├── Dechiffrement.o
    ├── Main.o
    ├── MyInclude.o
    ├── Test.o
    └── Trier.o

5 directories, 28 files
```

Les dossiers sont organisés de la sorte :
* Le dossier `bin` contient le binaire du programme.
* Le dossier `src` contient les programmes sources avec :
  * `lib` pour les fichiers de programmation, les `.c` et `.h`.
  * `main` pour le fichier principal.
  * `target` pour les objets, les `.o`.

Le fichier `build.sh` créer le dossier `bin` et le dossier `target`.

# Lancement

Pour lancer le projet vous devez commencer par faire `make` à la source du projet.

Ensuite vous avez plusieurs options décrites ci-dessous : 
```bash
./bin/crypto -c message cleMaitre # Pour chiffre;
./bin/crypto -d message cleMaitre # Pour dechiffer
./bin/crypto -a m1 c1 m2 c2 # Pour attaquer
```

# Details

Voici une liste détaillant le contenu des fichiers :
* Le fichier `MyInclude` contient les fonctions, les structures et les variables globales.
* Les fichiers `Chiffrement.c` et `Dechiffrement.c` contienent les méthodes qui appliquent la substitution, la permutation et chiffre/ dechiffre le message.
* Les deux précédents fichiers utilisent le fichier `Cadencement.c` qui s'occupe de la cle maitre.
* Le fichier `Attaque2Present24.c` contient les fonctions pour appliquer l'attaque par le milieu.
* Le fichier `Trier.c` est utilisé par le précedent fichier pour avoir les algorithmes de `quick sort` et `rechercheDichotomique`.
* Enfin le fichier `Test.c` est un fichier contenant des fonctions de tests.

# Information execution

L'execution de ce programme est faite sur une machine virtuel Linux Mint tournant sur un ordinateur portable sous Window 10 64bits avec un processeur Intel i7-8750H 2.20GHz et 16Go de RAM, dont 8 pour la machine virtuel.
Sans autre application tournant en parallèle ce code s'execute en environ 35 secondes. La mémoire utilisée par le programme est inconnue.