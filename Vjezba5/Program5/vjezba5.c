#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 50

typedef struct stog {

    int broj;
    struct stog *sljedeci;

} _stog;

int push(int broj, _stog *head) {

    _stog *novi = (_stog *)malloc(sizeof(_stog));

    if (novi == NULL) {
        return -1;
    }

    novi->broj = broj;
    novi->sljedeci = head->sljedeci;
    head->sljedeci = novi;

    return 0;
}

int pop(_stog *head) {

    if (head->sljedeci == NULL) {
        printf("prazan stog\n");
        return 0;
    }

    _stog *temp = head->sljedeci;

    int izbrisani_broj = temp->broj;
    head->sljedeci = temp->sljedeci;

    free(temp);

    return izbrisani_broj;
}

int main() {
    
    _stog head;
    head.sljedeci = NULL;

    FILE *fp = fopen("postfiks.txt", "r");
    if (fp == NULL) {
        printf("\ngreska u povezivanju");
        return -1;
    }

    char buffer[M];
    int pomak;
    int broj;
    char znak;
    int a, b, rez;

    while (fgets(buffer, M, fp) != NULL) {
        char *prolaz = buffer;
        while (*prolaz != '\0') {
            if (sscanf(prolaz, "%d %n", &broj, &pomak) == 1) {
                push(broj, &head);
                prolaz = prolaz + pomak;
            }
            else if (sscanf(prolaz, " %c %n", &znak, &pomak) == 1) {
                b = pop(&head);
                a = pop(&head);

                switch (znak) {
                    case '+': rez = a + b; break;
                    case '-': rez = a - b; break;
                    case '*': rez = a * b; break;
                    case '/':
                        if (b == 0) {
                            printf("\ndijeljenje s nulon");
                            fclose(fp);
                            return -1;
                        }
                        rez = a / b;
                        break;
                    default:
                        printf("\nnepoznat operator: %c", znak);
                        fclose(fp);
                        return -1;
                }

                push(rez, &head);
                prolaz = prolaz + pomak;
            }
            else {
                break;
            }
        }
    }

    printf("\nrezultat: %d\n", pop(&head));

    fclose(fp);
    return 0;
}