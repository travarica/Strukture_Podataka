#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Osoba {

    char ime[99]; //99
    char prezime[99];   //99
    int godina;   //4
    struct Osoba *sljedeci;   //sljedeci ce pokazivat na sljedeci element u listi, ako je prvi element a drugi b on pokazuje na b tako da ako je sljedeci NULL zna da je kraj liste


} lista;


int UnosNaPocetak(lista *head){

};


int main(){

lista *head = NULL; //predstavlja prvo mjesto u strukturi lista, na pocetku null jer nema elemenata

    
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