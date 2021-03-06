#include "interfata.h"

#define antet1 \
    FILE *f = fopen("header.in", "r"); \
    char sir[900]; \
    int count_file = 0; \
    while (!feof(f)) \
    { \
        sir[count_file] = fgetc(f); \
        count_file++; \
    } \
    fclose(f);

#define antet_2 \
    int q; \
    for (q = 0; q<strlen(sir)-2; q++) \
        printf("%c", sir[q]); \
    puts(" "); \
    puts(" "); \
    puts("###########################################"); \
    puts("### initializare meniu\n");

char* data_curenta(char *s)
{
    char zona[100];
    s[0] ='\0';
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(zona, "Data curenta: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    strcat(s, zona);
    return s;
}

struct word
{
    char *_cuvant;
    char *_parte_de_vorbire;
    char *_descriere;
    char *_provenienta;
    char *_sursa;
};

typedef struct _dictionar
{
    struct word w1;
} DICTIONAR;

DICTIONAR* citire_din_fisier(char *numeFisier, int *n)
{
    int i = 0;
    char linie[1000], var1[20], var2[20], var3[200], var4[20], var5[20];
    DICTIONAR *v = NULL;
    FILE *fp = fopen(numeFisier, "r");
    assert(fp != NULL);
    fscanf(fp, "%d", n);
    v = malloc(*n*sizeof(DICTIONAR));
    assert(v != NULL);
    fgets(linie, sizeof(linie), fp);
    for (i=0; i<*n; i++)
    {
        if (fgets(linie, sizeof(linie), fp) == NULL)
            break;
        strcpy(var1, strtok(linie, ";"));
        v[i].w1._cuvant = malloc(strlen(var1)+1);
        strcpy(v[i].w1._cuvant, var1);

        strcpy(var2, strtok(NULL, ";"));
        v[i].w1._parte_de_vorbire = malloc(strlen(var2)+1);
        strcpy(v[i].w1._parte_de_vorbire, var2);

        strcpy(var3, strtok(NULL, ";"));
        v[i].w1._descriere = malloc(strlen(var3)+1);
        strcpy(v[i].w1._descriere, var3);

        strcpy(var4, strtok(NULL, ";"));
        v[i].w1._provenienta = malloc(strlen(var4)+1);
        strcpy(v[i].w1._provenienta, var4);

        strcpy(var5, strtok(NULL, ";"));
        v[i].w1._sursa = malloc(strlen(var5)+1);
        strcpy(v[i].w1._sursa, var5);
    }
    fclose(fp);
    return v;
}

DICTIONAR* citire_tastatura()
{
    char var1[20], var2[20], var3[200], var4[20], var5[20];
    DICTIONAR *v2 = NULL;
    v2 = malloc(sizeof(DICTIONAR));
    assert(v2 != NULL);

    printf("Cuvant: ");
    scanf("%s", var1);
    v2->w1._cuvant = malloc(strlen(var1)+1);
    strcpy(v2->w1._cuvant, var1);
    fflush(stdin);

    printf("Parte de vorbire: ");
    scanf("%s", var2);
    v2->w1._parte_de_vorbire = malloc(strlen(var2)+1);
    strcpy(v2->w1._parte_de_vorbire, var2);
    fflush(stdin);

    printf("Descriere cuvant: ");
    gets(var3);
    v2->w1._descriere = malloc(strlen(var3)+1);
    strcpy(v2->w1._descriere, var3);
    fflush(stdin);

    printf("Provenienta geografica cuvant: ");
    gets(var4);
    v2->w1._provenienta = malloc(strlen(var4)+1);
    strcpy(v2->w1._provenienta, var4);
    fflush(stdin);

    printf("Sursa cuvant: ");
    gets(var5);
    v2->w1._sursa = malloc(strlen(var5)+1);
    strcpy(v2->w1._sursa, var5);
    fflush(stdin);
    return v2;
}

int main(void)
{
    DEX d1;
    d1 = newd();
    DICTIONAR *tab, *tab2;
    int n, i, k;
    char buf[900];
    char var1[20], var3[200], var5[20];
    antet1
    do
    {
        system("cls");
        antet_2
        puts("1. Initializare dictionar [ din fisier extern ]");
        puts("2. Adaugare cuvant manual");
        puts("3. Actualizare cuvant");
        puts("4. Cautare cuvant");
        puts("5. Cuvant random");
        puts("6. Cuvantul lunii");
        puts("7. Adaugare traducere cuvant");
        puts("8. Traducere engleza");
        puts("9. Stergere cuvant");
        puts("S. Afisare dictionar");
        puts("A. Informatii dezvoltator");
        puts("G. Generarare fisier back up html");
        puts("O. Data si ora");
        puts("X. Terminare program");
        switch(toupper(getch()))
        {
            case '1': printf("Initializare dex");
                      puts(" ");
                      tab = citire_din_fisier("date.in", &n);
                      for (i=0; i<n; i++)
                          d1 = adaugare(d1, tab[i].w1);
                      getch(); break;
            case '2': tab2 = citire_tastatura();
                      if ((d1 = adaugare(d1, tab2->w1)) != NULL)
                          printf("Cuvantul a fost adaugat cu succes !");
                      else
                          printf("Eroare adaugare cuvant !");
                      getch();
                      break;
            case '3': printf("Ce cuvant doriti sa actualizati ? ");
                      scanf("%s", var1);
                      k = cautare_cuvant(d1, var1);
                      if (k >= 0)
                      {
                          printf("Noua descriere: ");
                          fflush(stdin);
                          gets(var3);
                          fflush(stdin);
                          printf("Noua sursa: ");
                          gets(var5);
                          if ((d1 = actualizare(d1, var3, var5, k)) != NULL)
                              printf("Cuvantul a fost actualizat cu succes !");
                      }
                      else
                          printf("Cuvantul nu a putut fi actualizat, deoarece nu exista in baza de date a aplicatiei");
                      getch();
                      break;
            case '4': printf("Ce cuvant doriti sa cautati ? ");
                      scanf("%s", var1);
                      k = cautare_cuvant(d1, var1);
                      if (k >= 0)
                          printf("%s = %s %s\nProvenienta: %s Sursa: %s", getCuvant(d1, k), getParteDeVorbire(d1, k), getDescriere(d1, k),
                               getProvenienta(d1, k), getSursa(d1, k));
                      else
                          printf("404 cuvant negasit : (");
                      getch();
                      break;
            case '5': k = getRandom(d1);
                      if (k >= 0)
                      {
                          printf("Generare cuvant aleatoriu = ");
                          afisareComplet(d1, k);
                      }
                      else
                          printf("Dictionarul este gol !");
                      getch();
                      break;
            case '6': printf("Cuvantul lunii este: "); cuvantulLunii(d1); getch(); break;
            case '7': printf("Adaugati cuvantul pe care doriti sa il traduceti: ");
                      scanf("%s", var1);
                      k = cautare_cuvant(d1, var1);
                      if (k >= 0)
                      {
                          printf("Adaugati traducerea: ");
                          fflush(stdin);
                          gets(var3);
                          if ((d1 = adaugareTraducere(d1, var3, k)) != NULL)
                              printf("Traducerea a fost adaugata cu succes !");
                      }
                      else
                          printf("Cuvantul nu a fost gasit in baza de date a aplicatiei");
                      getch();
                      break;
            case '8': printf("Ce cuvant doriti sa traduceti ? ");
                      scanf("%s", var1);
                      if ((k = cautare_cuvant(d1, var1)) >= 0)
                          printf("%s = %s", getTraducere(d1, k), var1);
                      else
                          printf("404 traducerea nu a fost gasita ! : (");
                      getch();
                      break;
            case '9': printf("Introduceti cuvantul pe care doriti sa il stergeti: ");
                      scanf("%s", var1);
                      if ((k = cautare_cuvant(d1, var1)) >= 0)
                      {
                          if ((d1 = stergereCuvant(d1, var1, k)) != NULL)
                              printf("Stergerea a reusit cu succes !");
                      }
                      else
                          printf("Nu s-a putut sterge cuvantul, deoarece nu a putut fi gasit");
                      getch();
                      break;
            case 'S': //buf[0] = '\0';
                      //printf("Afisare: %s", toStringd(d1, buf));
                      toString(d1);
                      getch(); break;
            case 'A': printf("Autor proiect:\tFulga Sergiu-Sebastian");
                      printf("\nFacultate\tFIESC - Calculatoare");
                      printf("\nGitHub\t\thttps://github.com/sebastianfulga");
                      printf("\n\nVizitati-ne pe\thttps://blog.dexonline.ro\n\t\thttps://www.facebook.com/groups/comunitatea.dexonline/\n");
                      printf("\t\thttps://twitter.com/DexOnlineRo");
                      getch();
                      break;
            case 'O': printf("%s", data_curenta(buf)); getch(); break;
            case 'G': generare_fisier(d1); getch(); break;
            case 'X': printf("< terminare app >"); destroyd(d1); exit(0);
            default: printf("S-a introdus o valoarea gresita din meniu : ("); getch();
        }
    }
    while (ADEVARAT);
    return 0;
}
