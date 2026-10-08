#include <stdio.h>
#include <stdlib.h>

typedef struct Popis
{
    char ime[50];
    char prezime[50];
    int bodovi;
} _popis ; //_popis je ime strutkure(naziv tipa podataka), to je ka int, float itd


int main(){

    _popis studenti; //ovdi deklariran varijablu, npr studenti.ime ce se updejtat svaki novi red, a studentipokazivac[i].ime ima rezervirano misto za svaki

    FILE *fp = fopen("popis.txt", "r");

    if (fp == NULL)
    {
       printf("Greska");
       return -1;
    }
    else{
        printf("File je uspjesno otvoren");
    }
    
    int brojstudenata = 0;
    int i;
    
    //moran koristit while jel za for unaprid moran znat koliko ce bit redaka

    while (fscanf(fp, "%s %s %d", studenti.ime, studenti.prezime, &studenti.bodovi) == 3)
    {
        brojstudenata++;
        // ovdi procita jel ima 3 elementra u retku, (==3), ako ima znat ce da je red popunjen s podacima o studentu i povecaja broj
    }
    printf("\nBroj studenata je: %d", brojstudenata);
    
    rewind(fp);
    //vracan se na pocetak datoteke

    _popis *studentipokazivac;
    studentipokazivac = (_popis*)malloc(brojstudenata*sizeof(_popis));

    
    float relativan_broj_bodova = 0;
    int maxbrojbodova = 30;
    



    printf("\nIme, prezime, bodovi studenta i relativni bodovi studenta su: ");
    for (i = 0; i < brojstudenata; i++)
    {
        fscanf(fp,"%s %s %d", studentipokazivac[i].ime, studentipokazivac[i].prezime, &studentipokazivac[i].bodovi); //tocno pristupa odredenom redu
        relativan_broj_bodova = (float)studentipokazivac[i].bodovi / maxbrojbodova * 100;

        printf("\n%s %s %d %.2f", studentipokazivac[i].ime, studentipokazivac[i].prezime, studentipokazivac[i].bodovi, relativan_broj_bodova);
    }
    

free(studentipokazivac);
fclose(fp);
 
    return 0;
}