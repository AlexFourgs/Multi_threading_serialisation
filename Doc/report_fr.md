# Sérialisations de threads en C
*par Alexandre FOURGS*

## Threads sérialisés "en dur"

### Présentation de la solution

La solution utilisée dans le premier cas, est d'utiliser une variable globale.
Tout d'abord, on réalise deux fonctions de threads distincts :
* Les threads concurrents (qui sont des threads normaux)
* Les threads sérialisés

La seule différence entre ces deux types de fonction est que les threads sérialisés ont une condition. En effet, un thread sérialisé ne prend le dessus que si la variable globale est égale à la donnée en entrée du thread, une fois le travail effectué le thread incrémente la variable globale sauf si c'est le dernier thread de la ligne, dans ce cas il remet la variable globale à sa valeur de base pour que le premier thread de la ligne reprenne la main.

**Code :** https://github.com/AlexFourgs/Multi_threading_serialisation/blob/master/Codes/serialisation_global_variable.c


### Avantages

Cette solution est simple et rapide à mettre en place, elle peut être très utile dans le cas d'un système qui restera toujours le même.

### Inconvénients

Comme nous l'avons souligné dans les avantages, cette solution est efficace pour un petit système qui n'évolue pas, en revanche si l'on doit ajouter un thread sur une des lignes, on devra soit recréer une autre variable globale et une autre fonction de thread sérialisé, soit adapter la fonction du thread sérialisé.
De plus cette solution peut vite devenir lourde et longue à mettre en place si on a énormément de thread.


## Création des threads en fonction d'un model. (solution non réalisé car bug)

### Présentation de la solution

Dans un premier temps ont parse le modèle afin d'en recueillir les informations.

La solution utilisée ici est les listes chaînées. Pour chaque ligne du modèle on créer une liste chaînée, et chaque listes chaînées des threads sont elles-même mise dans une autre liste chaînée des lignes.
Pour le modèle suivant :

NB_LINES = 3
LINE 1 : T1 -> End
LINE 2 : T2 -> T3 -> T4 -> End
LINE 3 : T5 -> End

On obtient donc 4 listes chaînées entre elles de cette manière :

![schema_listes](https://github.com/AlexFourgs/Multi_threading_serialisation/raw/master/Doc/schema_list.png)

### Avantages

L'avantage de cette solution est qu'on peut mettre autant de threads que l'on veut sur chaque ligne, le programme s'adaptera.

### Inconvénients

On ne peut pas ajouter de threads à chaud.
