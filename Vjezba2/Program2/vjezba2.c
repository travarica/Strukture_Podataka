#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
    char ime[50];
    char prezime[50];
    int godina;
    Position next;
} Person;

Position stvoriOsobu(char* ime, char* prezime, int godina) {
    Position newP = (Position)malloc(sizeof(Person));
    if (!newP) {
        return NULL;
    }

    strcpy(newP->ime, ime);
    strcpy(newP->prezime, prezime);
    newP->godina = godina;
    newP->next = NULL;
    return newP;
}

int ubaciIza(Position p, Position q) {
    q->next = p->next;
    p->next = q;
    return 0;
}

int unosNaPocetak(Position head, char* ime, char* prezime, int godina) {
    Position newP = stvoriOsobu(ime, prezime, godina);
    if (!newP) {
        return -1;
    }
    return ubaciIza(head, newP);
}

int unosNaKraj(Position head, const char* ime, const char* prezime, int godina) {
   
    Position p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    Position newP = stvoriOsobu(ime, prezime, godina);
    
    return ubaciIza(p, newP);
}

void ispisiListu(Position head) {
    Position q = head->next;
    while (q) {
        printf("Ime prezime i godina : %s %s %d\n", q->ime, q->prezime, q->godina);
        q = q->next;
    }
}

Position pronadjiPoPrezimenu(Position head, char* prezime) {
    Position q = head->next;
    while (q) {
        if (strcmp(q->prezime, prezime) == 0) return q;
        q = q->next;
    }
    return NULL;
}

int obrisiElement(Position p, char* prezime) {
    Position prev = p;
    Position curr = p->next;
    while (curr && strcmp(curr->prezime, prezime) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        return 0; 
    }
    prev->next = curr->next;
    free(curr);
    return 1; 
}

int dodajOsobu(Position head) {
    char ime[50], prezime[50];
    int god;
    char odabir;

    printf("\nUpisi ime prezime i godine: ");
    if (scanf("%s %s %d", ime, prezime, &god) != 3) {
        return -1;
    }

    printf("Di zelis spremit ove podatke? (p - pocetak , k - kraj): ");
    scanf(" %c", &odabir);

    if (odabir == 'p' || odabir == 'P')
        return unosNaPocetak(head, ime, prezime, god);
    else
        return unosNaKraj(head, ime, prezime, god);
}

int main(void) {
    Person prazni = { .ime = { 0 }, .prezime = { 0 }, .godina = 0, .next = NULL };
    Position head = &prazni;

    int n = 0;
    printf("Koliko unosa zelis: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Neispravan unos broja\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        if (dodajOsobu(head) != 0) {
            printf("Greska prilikom dodavanja\n");
        }
    }

    ispisiListu(head);

    char pronalazak[99];
    printf("\nUpisi prezime za nac: ");
    scanf("%s", pronalazak);
    
    Position pronadjena = pronadjiPoPrezimenu(head, pronalazak);
    if (pronadjena) 
        printf("Pronadena osoba: %s %s %d\n", pronadjena->ime, pronadjena->prezime, pronadjena->godina);
    else 
        printf("Nema te osobe\n");

    
    while (1) {
        printf("\nUpisi prezime osobe koju zelis izbrisati (ili 'e' za izlaz iz brisanja): ");
        scanf("%s", pronalazak);
        
        if (strcmp(pronalazak, "e") == 0 || strcmp(pronalazak, "E") == 0) {
            printf("Prekid\n");
            break;
        }

        int obrisano = obrisiElement(head, pronalazak);
        if (obrisano == 1) {
            printf("Obrisano\n");
            break; 
        } else {
            printf("Nema to prezime\n");
        }
    }

    printf("\nFinalna lista:\n");
    ispisiListu(head);

    Position curr = head->next;
    while (curr) {
        Position temp = curr;
        curr = curr->next;
        free(temp);
    }
    head->next = NULL;

    return 0;
}