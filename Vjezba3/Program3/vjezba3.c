#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {

char ime[99]; //99
char prezime[99]; //99
int godina; //4
struct Osoba *sljedeci; //sljedeci ce pokazivat na sljedeci element u listi, ako je prvi element a drugi b on pokazuje na b tako da ako je sljedeci NULL zna da je kraj liste

} lista;




lista* UnosNaPocetak(lista *head){

lista *pocetak;
pocetak = (lista*)malloc(sizeof(lista));

printf("Unesi ime,prezime i godinu: ");
scanf("%s %s %d", pocetak->ime, pocetak->prezime, &pocetak->godina);

pocetak->sljedeci = head;
/*prvi unos head pokazuje na cvor a, a njegov sljedeci je poakziva na null, ond unesemo cvor b i ond head pokazuje na b ,
sljedeci na a i a pokazuje na NULL, svaki novi cvor ima svoj sljedeci
*/
return pocetak;

};




lista* UnosNaKraj(lista *head) {

lista *kraj;
kraj = (lista*)malloc(sizeof(lista));

printf("Unesi ime, prezime i godinu: ");
scanf("%s %s %d", kraj->ime, kraj->prezime, &kraj->godina);
kraj->sljedeci = NULL;
//onaj cvor koji ce bit zadnji moramo stavit da gleda na NULL jer definira kraj

if (head == NULL) {
    return kraj;
}

lista *temp = head;
while (temp->sljedeci != NULL) {
    temp = temp->sljedeci;
}
/*pomocni pokazivac koji ne mijenja glavni head, nego sluzi da vrati kroz sve cvorove dok ne dode do onog koji gleda na NULL
da smo pomicali head izgubili bi pocetak liste
*/

temp->sljedeci = kraj;
//ovo znaci da taj temp koji je bia zadnji koji je gleda na null stavljamo vise ne gleda na null nego na element koji smo mi dodali, a on automatski gleda na null radi ovog kraj->sljedeci = NULL;

return head;
}






lista* PronadiPrezime(lista *head, char pretrazi[99]){

lista *temp = head;

while (temp != NULL && strcmp(pretrazi, temp->prezime) != 0)
{
    temp = temp->sljedeci;
}
//vrtit ce se dok privremen pokazivac koji gleda na head nije prazan i dok se pronade to prezime, trenutno usporeduje sto smo upisali sa svakin cvorom dok ne nade

return temp;
}






lista* BrisanjeElementa(lista *head, char obrisi[99]){

if (strcmp(head->prezime, obrisi) == 0) {
//ako je element koji zelimo izbrisat na prvom mistu
    lista *brisat = head;
    head = head->sljedeci;
    free(brisat);
    return head;
}

lista *temp = head;
while (temp->sljedeci != NULL && strcmp(temp->sljedeci->prezime, obrisi) != 0) {
    temp = temp->sljedeci;
//temp zavrsava na onom prije nego onaj koi brisemo
}
//ova radnja ce se izvrsavat sve dok nije Null i dok ne nade prezime koje zelimo izbrisat

if (temp->sljedeci != NULL)
{
    lista *brisat = temp->sljedeci;
    temp->sljedeci = temp->sljedeci->sljedeci;
    free(brisat);
//znaci taj element koji brisemo ce bit zamijenjen s elementom iza njega, tako da ce ostat veza
}
    return head;
}


lista* DodajIzaOdredenog(lista *head, char pretrazi[99]){

lista *pronadeni = PronadiPrezime(head, pretrazi); //pronadeni sadrzi podatke cvora s prezimenom koje zelim
lista *privremen;

if (pronadeni == NULL)
{
    printf("Prezime nije pronadeno");
    return head;
}


lista *novi = (lista*)malloc(sizeof(lista));
printf("Unesi ime, prezime i godinu za novi element: ");
scanf("%s %s %d", novi->ime, novi->prezime, &novi->godina);

privremen = pronadeni->sljedeci;
pronadeni->sljedeci = novi;
novi->sljedeci = privremen;


return head;

}



int main(){

lista *head = NULL;



int n = 0;
printf("Unesi kolicinu osoba: ");
scanf("%d", &n);



for (int i = 0; i < n; i++){
char izbor;

printf("Zelite li osobu[%d] dodat na pocetak ili kraj (p - pocetak, k - kraj): ", i+1);
scanf(" %c", &izbor);

{
if (izbor == 'p' || izbor == 'P')
{
head = UnosNaPocetak(head);
}
else if(izbor == 'k' || izbor == 'K'){
head = UnosNaKraj(head);
}
else{
printf("Krivi unos\n");
}

}
}



char pretrazi[99];
printf("Upisi prezime koje zelis nac: ");
scanf("%s", pretrazi);

lista *rezultat = PronadiPrezime(head, pretrazi);



char obrisi[99];
printf("Upisi prezime koje zelis obrisat: ");
scanf("%s", obrisi);

lista *temp = head;



/* ne triba mi
while (temp != NULL)
{
printf("\nIme prezime i godina: %s %s %d", temp->ime, temp->prezime, temp->godina);
temp = temp->sljedeci;

}
*/



if (rezultat != NULL) {
printf("\nIme, prezime i godina pronadene osobe: %s %s %d", rezultat->ime, rezultat->prezime, rezultat->godina);
} else {
printf("\nNema te osobe");
}




head = BrisanjeElementa(head,obrisi);


char IzaOvogPrezimena[99];
printf("\nOdaberi iza kojeg elementa zelis da se dodaju novi podaci: ");
scanf("%s", IzaOvogPrezimena);

head = DodajIzaOdredenog(head, IzaOvogPrezimena);



temp = head; // vraca temp na pocetak da prolista kroz sve cvorove
while (temp != NULL)
{
printf("\nIme prezime i godina finalne liste: %s %s %d", temp->ime, temp->prezime, temp->godina);
temp = temp->sljedeci;

}

//oslobadanje memorije
temp = head;
lista *privremeno;
while (temp != NULL)
{
  privremeno = temp;
  temp = temp->sljedeci;
  free(privremeno);
}
head = NULL;
//moram posebno i head jer kroz while petlju san ja izrbisa sve liste, al u headu su ostali podaci prve liste

//provjera jesu li liste ociscene
if (head == NULL)
{
    printf("\nocisceno");
}
else{
    printf("\nnije ocisceno");
}









return 0;
}