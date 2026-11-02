#include <stdio.h>
#include <stdlib.h>
#define M 100

typedef struct Polinom
{
    int koeficijent;
    int potencija;
    struct Polinom *sljedeci;
    

} polinom;

polinom *SortiranaLista(polinom* head, int koeficijent, int potencija){

    polinom* lista;
    lista = (polinom*)malloc(sizeof(polinom));
    
    lista->koeficijent = koeficijent;
    lista->potencija = potencija;

    polinom* temp = head;

    if (temp == NULL)
    {
       lista->sljedeci = temp;
       return lista;
    }

    if (lista->potencija > temp->potencija)
    {
        lista->sljedeci = temp;
        return lista;
    }
   
    while (temp->sljedeci != NULL && temp->sljedeci->potencija > lista->potencija) {
        temp = temp->sljedeci; 
    }

    
    lista->sljedeci = temp->sljedeci;
    temp->sljedeci = lista;

    return head;
}

void IspisPolinoma(polinom *head) {

    polinom *temp = head;
    while (temp != NULL) {
        
        printf("%d %d ", temp->koeficijent, temp->potencija);

        temp = temp->sljedeci;
    }
   
}


polinom *ZbrojPolinoma(polinom *head1, polinom *head2) {

    polinom *rezultat = NULL;
    polinom *temp1 = head1;
    polinom *temp2 = head2;

    while (temp1 != NULL || temp2 != NULL) {
        int koef = 0, pot = 0;

        if (temp1 != NULL && (temp2 == NULL || temp1->potencija > temp2->potencija)) {
            koef = temp1->koeficijent;
            pot = temp1->potencija;
            temp1 = temp1->sljedeci;
        } 
        else if (temp2 != NULL && (temp1 == NULL || temp2->potencija > temp1->potencija)) {
            koef = temp2->koeficijent;
            pot = temp2->potencija;
            temp2 = temp2->sljedeci;
        } 
        else {
            koef = temp1->koeficijent + temp2->koeficijent;
            pot = temp1->potencija;
            temp1 = temp1->sljedeci;
            temp2 = temp2->sljedeci;
        }

        if (koef != 0) {
            rezultat = SortiranaLista(rezultat, koef, pot);
        }
    }

    return rezultat;
}

polinom *UmnozakPolinoma(polinom *head1, polinom *head2) {
    polinom *rezultat = NULL;
    polinom *temp1 = head1;

    while (temp1 != NULL) {
        polinom *temp2 = head2;
        while (temp2 != NULL) {
            int novi_koef = temp1->koeficijent * temp2->koeficijent;
            int nova_pot = temp1->potencija + temp2->potencija;

            polinom *temp = rezultat;
            int pronadjeno = 0;
            while (temp != NULL) {
                if (temp->potencija == nova_pot) {
                    temp->koeficijent += novi_koef;
                    pronadjeno = 1;
                    break;
                }
                temp = temp->sljedeci;
            }

            if (!pronadjeno && novi_koef != 0) {
                rezultat = SortiranaLista(rezultat, novi_koef, nova_pot);
            }

            temp2 = temp2->sljedeci;
        }
        temp1 = temp1->sljedeci;
    }

    return rezultat;
}


int main(){
    
    
    polinom *polinom1 = NULL;
    polinom *polinom2 = NULL;

    FILE *fp = fopen("polinomi.txt", "r");

    if (fp == NULL)
    {
        printf("greska");
        return -1;
    }
    else{
        printf("uspjeno otvoreno\n");
    }


    char buffer[M];
    int koeficijent;
    int potencija;
    int pomak;
    int redak = 0;

    while (fgets(buffer,M,fp) != NULL)
    {
       redak++;
       char *prolaz = buffer;

       while(sscanf(prolaz, "%d %d %n", &koeficijent, &potencija, &pomak) == 2)   //procita prvi par iz buffera, sto je prvi red trenuto i to je 2 i 3 i spremi
       {
         prolaz = prolaz + pomak;    //%n sluzi za citanje znakova, procita prvi par i razmak, znaci 3 , ond kad se opet izvrti preskoci prvi par

           if (redak == 1)
           {
                polinom1 = SortiranaLista(polinom1, koeficijent,potencija);
           }
           else if (redak == 2)
           {
                polinom2 = SortiranaLista(polinom2, koeficijent,potencija);
           }
       }
    }


    printf("Prvi polinom: ");
    IspisPolinoma(polinom1);

    printf("\nDrugi polinom: ");
    IspisPolinoma(polinom2);

    polinom *zbroj = ZbrojPolinoma(polinom1, polinom2);
    printf("\nZbroj polinoma: ");
    IspisPolinoma(zbroj);

    polinom *umnozak = UmnozakPolinoma(polinom1, polinom2);
    printf("\nUmnozak polinoma: ");
    IspisPolinoma(umnozak);
 
fclose(fp);
    

    


    return 0;
}