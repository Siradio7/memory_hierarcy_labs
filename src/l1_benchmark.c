#include <stdio.h>
#include <time.h>

#define MAX_TAILLE_DATA_KO 4096
#define CACHE_LINE_SIZE 64

int tab[(MAX_TAILLE_DATA_KO * 1024) / sizeof(int)];

int main(void)
{
    int i;
    int taille_data;
    int nbdonnee;
    int pas = CACHE_LINE_SIZE / sizeof(int);

    volatile long long x = 0;
    struct timespec t1, t2;

    for (taille_data = CACHE_LINE_SIZE; taille_data <= MAX_TAILLE_DATA_KO * 1024; taille_data += CACHE_LINE_SIZE) {
        nbdonnee = taille_data / sizeof(int);

        /* Préchargement des données dans le cache */
        for (i = 0; i < nbdonnee; i += pas) {
            x += tab[i];
        }

        /* Début de la mesure */
        clock_gettime(CLOCK_MONOTONIC, &t1);

        for (i = 0; i < nbdonnee; i += pas) {
            x += tab[i];
        }

        /* Fin de la mesure */
        clock_gettime(CLOCK_MONOTONIC, &t2);

        /* Temps moyen d'un accès en microsecondes */
        double temps_total = (double)(t2.tv_sec - t1.tv_sec) * 1000000.0 + (double)(t2.tv_nsec - t1.tv_nsec);
        double temps_acces_moyen = temps_total / (nbdonnee / pas);

        printf("%d : %.6f\n", taille_data, temps_acces_moyen);
    }

    /* Empêche le compilateur de considérer x comme inutile */
    if (x == -1) {
        printf("x = %lld\n", x);
    }

    return 0;
}