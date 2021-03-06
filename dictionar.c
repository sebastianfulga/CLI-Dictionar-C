#include "interfata.h"

struct word
{
    char *cuvant;
    char *parte_de_vorbire;
    char *descriere;
    char *provenienta;
    char *sursa;
    int numar_cuvant;
    char *traducere_engleza;
};

struct dictionar
{
    int nmax;
    int liber;
    int inc;
    Word w;
};

typedef struct dictionar Dictionar;

DEX newd()
{
    DEX d = malloc(NMAX * sizeof(Dictionar));
    if (d == NULL)
        return NULL;
    d->nmax = NMAX;
    d->inc = INCREMENT;
    d->liber = 0;
    return d;
}

void destroyd(DEX d)
{
    int i;
    if (d != NULL)
    {
        for (i=0; i<d->liber; i++)
        {
            free(d[i].w.cuvant);
            free(d[i].w.parte_de_vorbire);
            free(d[i].w.descriere);
            free(d[i].w.provenienta);
            free(d[i].w.sursa);
            free(d[i].w.numar_cuvant);
            free(d[i].w.traducere_engleza);
        }
        free(d);
    }
}

DEX adaugare(DEX d, Word w2)
{
    int i;
    if (isFull(d))
    {
        if((d=realloc(d, (d->nmax)*sizeof(Dictionar))) == NULL)
            return d;
        d->nmax += d->inc;
    }
    i = d->liber++;
    setCuvant(d, w2.cuvant, i);
    setParteDeVorbire(d, w2.parte_de_vorbire, i);
    setDescriere(d, w2.descriere, i);
    setProvenienta(d, w2.provenienta, i);
    setSursa(d, w2.sursa, i);
    setAparitiiCuvant(d, i);
    setTraducere(d, i);
    return d;
}

void setCuvant(DEX d, char* var1, int i)
{
    assert(d != NULL);
    d[i].w.cuvant = malloc(strlen(var1)+1);
    strcpy(d[i].w.cuvant, var1);
}

void setParteDeVorbire(DEX d, char* var2, int i)
{
    assert(d != NULL);
    d[i].w.parte_de_vorbire = malloc(strlen(var2)+1);
    strcpy(d[i].w.parte_de_vorbire, var2);
}

void setDescriere(DEX d, char* var3, int i)
{
    assert(d != NULL);
    d[i].w.descriere = malloc(strlen(var3)+1);
    strcpy(d[i].w.descriere, var3);
}

void setProvenienta(DEX d, char* var4, int i)
{
    assert(d != NULL);
    d[i].w.provenienta = malloc(strlen(var4)+1);
    strcpy(d[i].w.provenienta, var4);
}

void setSursa(DEX d, char* var5, int i)
{
    assert(d != NULL);
    d[i].w.sursa = malloc(strlen(var5)+1);
    strcpy(d[i].w.sursa, var5);
}

void setAparitiiCuvant(DEX d, int i)
{
    assert(d != NULL);
    d[i].w.numar_cuvant = 0;
}

void setTraducere(DEX d, int i)
{
    assert(d != NULL);
    d[i].w.traducere_engleza = NULL;
}

void toString(DEX d)
{
    int i;
    if (isEmptyd(d))
    {
        printf("Dictionarul este gol");
    }
    else
        for (i=0; i<d->liber; i++)
            printf("%s | %s | %s | %s | %s\n", d[i].w.cuvant, d[i].w.parte_de_vorbire, d[i].w.descriere, d[i].w.provenienta, d[i].w.sursa);
}

bool isEmptyd(DEX d)
{
    return d==NULL || d->liber==0;
}

bool isFull(DEX d)
{
    return d!=NULL && d->liber==d->nmax;
}

int cautare_cuvant(DEX d, char *numeCuvant)
{
    int i;
    for (i=0; i<d->liber; i++)
    {
        if (strcmp(d[i].w.cuvant, numeCuvant) == 0)
        {
            d[i].w.numar_cuvant++;
            return i;
        }
    }
    return -1;
}

char* getCuvant(DEX d, int i)
{
    assert(d != NULL);
    return d[i].w.cuvant;
}

char* getParteDeVorbire(DEX d, int i)
{
    assert(d != NULL);
    return d[i].w.parte_de_vorbire;
}

char* getDescriere(DEX d, int i)
{
    assert(d != NULL);
    return d[i].w.descriere;
}

char* getProvenienta(DEX d, int i)
{
    assert(d != NULL);
    return d[i].w.provenienta;
}

char* getSursa(DEX d, int i)
{
    assert(d != NULL);
    return d[i].w.sursa;
}


DEX actualizare(DEX d, char* _descriere, char* _sursa, int i)
{
    setDescriere(d, _descriere, i);
    setSursa(d, _sursa, i);
    return d;
}

void cuvantulLunii(DEX d)
{
    int i, max, poz = 0;
    max = d[0].w.numar_cuvant;
    for (i=1; i<d->liber; i++)
    {
        if (d[i].w.numar_cuvant > max)
        {
            max = d[i].w.numar_cuvant;
            poz = i;
        }
    }
    afisareComplet(d, poz);
}

int getRandom(DEX d)
{
    int i;
    assert(d != NULL);
    if (!isEmptyd(d))
    {
        srand(time(NULL));
        i = rand()%(d->liber);
        return i;
    }
    else
        return -1;
}

void afisareComplet(DEX d, int i)
{
    printf("%s = %s %s %s %s", getCuvant(d, i), getParteDeVorbire(d, i), getDescriere(d, i), getProvenienta(d, i), getSursa(d, i));
}

DEX adaugareTraducere(DEX d, char* _traducere_engleza, int i)
{
    assert(d != NULL);
    d[i].w.traducere_engleza = malloc(strlen(_traducere_engleza)+1);
    strcpy(d[i].w.traducere_engleza, _traducere_engleza);
    return d;
}

char* getTraducere(DEX d, int i)
{
    assert(d != NULL);
    return d[i].w.traducere_engleza;
}

DEX stergereCuvant(DEX d, char* _cuvant, int i)
{
    int j, k = 0;
    DEX r;
    r = malloc((d->liber-1) * sizeof(Dictionar));
    r->nmax = d->nmax ;
    r->inc = d->inc ;
    r->liber = d->liber-1;
    if (d->liber == 1)
        return NULL;
    assert (r != NULL);
    for (j=0; j<d->liber; j++)
    {
        if (strcmp(d[j].w.cuvant, _cuvant) == 0)
            continue;
        setCuvant(r, d[j].w.cuvant, k);
        setParteDeVorbire(r, d[j].w.parte_de_vorbire, k);
        setDescriere(r, d[j].w.descriere, k);
        setProvenienta(r, d[j].w.provenienta, k);
        setSursa(r, d[j].w.sursa, k);
        r[k].w.numar_cuvant = d[j].w.numar_cuvant;
        if (d[j].w.traducere_engleza != NULL)
            r = adaugareTraducere(r, d[j].w.traducere_engleza, k);
        else
            r[k].w.traducere_engleza = NULL;
        k++;
    }
    return r;
}

/** =============================G E N E R A R E----F I S I E R----H T M L============================================ **/
void generare_fisier(DEX d)
{
    int i;
    char buff[100];
    FILE *g;
    g = fopen("backup.html", "w");
    if (g == NULL)
    {
        printf("Eroare generare fisier !");
        return ;
    }
    fprintf(g, "<!DOCTYPE html> \n\
                <html lang=""en-US""> \n\
                <meta charset=""utf-8""> \n\
                <meta name=""viewport"" content=""width=device-width, initial-scale=1""> \n\
                <style> \n\
                div p, h1 { \n\
                    margin: 0; \n\
                    color: #566b78; \n\
                    text-decoration: none; \n\
                    text-transform: uppercase; \n\
                    margin: 3rem 10rem; \n\
                    padding: 0; justify-content: center; transition: all 800ms; \n\
                } \
                div p:hover { background: crimson; color: #fff; padding: 1em 2em; } \n\
                body { \n\
                    background-color: #dddddd; \n\
                    color: #566b78; \n\
                    font-family: ""Inconsolata"", monospace; \n\
                    font-size: 18px; \n\
                    line-height: 1.5; margin 0; padding 0; \n\
                } </style> \n\
                <body> \n\
                <main> \n\
                    <h1>APLICATIE DEX FISIER BACK UP HTML</br>%s</h1> \n\
                    <div>", data_curenta(buff));
        if (isEmptyd(d))
            fprintf(g, "<p>Dictionarul este gol</p>");
        for (i=0; i<d->liber; i++)
            fprintf(g, "<p>%s | %s | %s | %s | %s\n</p>", d[i].w.cuvant, d[i].w.parte_de_vorbire, d[i].w.descriere,
                    d[i].w.provenienta, d[i].w.sursa);
        fprintf(g, "</div></main></body></html>");
    printf("Fisier generat cu succes la %s", data_curenta(buff));
    fclose(g);
}
