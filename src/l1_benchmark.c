#include <stdio.h>
#include <sys/time.h>

#define MAX_TAILLE_DATA_KO 4096
#define CACHE_LINE_SIZE 64

int tab[(MAX_TAILLE_DATA_KO * 1024) / sizeof(int)];

int main(void)
{
    int i;
    int taille_data;
    int nbdonnee;
    int pas = CACHE_LINE_SIZE / sizeof(int);

    // À compléter

    return 0;
}