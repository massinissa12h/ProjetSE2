# projet - Reponses au questions.
## Les participans de projet:
```
ce projet est réalisé grâce aux efforts de Messaoudi Massinissa du groupe 2 et Kherfi Lyes du groupe 1.
```
## Q1 : Structures de Données
```
Matrices B, C, et A : Utilisez des tableaux bidimensionnels pour représenter les matrices et stockées les données dans B et C et en sauvegarde le resultat dans le tableau A.
Tampon T : Utilisez un tableau (T) pour stocker les résultats intermédiaires.
```
## Q2 : Protection de l'Accès aux Données
```
Mutex pour le Tampon T : Implémentez un mutex (pthread_mutex_t) pour protéger l'accès concurrentiel au tampon T.
Mutex pour la Matrice A : Si nécessaire, utilisez un autre mutex pour protéger l'accès à la matrice résultante A.
```
## Q3 :  Risques
```
Problèmes de Concurrence : Risque d'accès simultané aux données partagées par plusieurs threads.(tampons et matrices dans ce cas)
Problèmes de Performance : Une gestion inadéquate des threads peut entraîner des performances dégradées, ce qui entraîne un blocage mutuel des threads.
```
