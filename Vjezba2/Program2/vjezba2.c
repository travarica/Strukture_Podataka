#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {

    char ime[99]; //99
    char prezime[99];   //99
    int godina;   //4

} lista;


int main(){

    
lista *_lista;
_lista = (lista*)malloc(sizeof(lista));


if (_lista == NULL)
    {
        printf("Greska");
        return -1;
    }
else{
    printf("Velicina rezervirana je : %d ", sizeof(lista));
}








    return 0;
}